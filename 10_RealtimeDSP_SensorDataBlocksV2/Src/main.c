/*
 *
 * 				10_RealtimeDSP_SensorDataBlocksV2
 *
 *
* 				Instead of using ARM convolution function to convolve the signal and the filter kernel,
 * 				here we will use the ARM FIR filter function.
 *
 * 				Sample ADC and put data into a FIFO/buffer whenever the timer generates an interrupt.
 *
 * 				Data is not acquired in an RTOS thread here.  Instead, data is captured in the background
 * 				based on timer interrupts, which then tells the RTOS thread there is now data to be processed.
 *
 * 				Files "adc.c" and "adc.h" simply added to this project.
 *
 * 				We also add tim.c and fifo.c files from basic DSP course, project 28_SamplingInBackgroundThrd project
 *
 * 				The FIFO size has 300 elements.
 *
 *
 */

#include "stm32f4xx.h"
#include <stdio.h>
#include "signals.h"
#include "uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sine_generator.h"
#include "lowpassfilter.h"
#include "semphr.h"
#include "adc.h"
#include "tim.h"
#include "fifo.h"

#define SIGNAL_FREQ					10
#define NOISE_FREQ						50
#define SAMPLING_FREQ 				1000
#define INPUT_SIG_LENGTH			RXFIFOSIZE

extern float _5hz_signal[HZ_5_SIG_LEN];
extern float32_t input_signal_f32_1kHz_15kHz[KHZ1_15_SIG_LEN] ;
extern  float LP_1HZ_2HZ_IMPULSE_RESPONSE[IMP_RSP_LENGTH];

extern void tim2_1khz_interrupt_init(void);
void TIM2_IRQHandler(void);

float g_in_sig_sample;
float32_t f32_output_signal_buffer[IMP_RSP_LENGTH + INPUT_SIG_LENGTH - 1];

// static void swv_plot_signal(void);
// static void serial_plot_signal(void);
static void pseudo_dly(int dly);
static void fpu_enable(void);

static uint8_t read_fifo(rx_dataType *data_buff);
static void clear_data_buffer(void);

// Here are the variables to add to Live Expressions.  These are just counters.
uint32_t TaskAcq_profiler, TaskProc_profiler, TaskDisp_profiler, TIM2Profiler;

// Name a semaphore
SemaphoreHandle_t xBinarySemaphore;

// Here is where we can change task priorities
// The higher the number, the higher the task priority.
int Task1_priority = 1;
int Task2_priority = 1;
int Task3_priority = 1;

// Here are the task names
void data_disp_task(void *pvParameters);
void data_proc_task(void *pvParameters);

void acquisition_func(void);



// For the FIR
arm_fir_instance_f32 fir_desc;

// Data buffers for input and output signals
float32_t *f32_input_pt, *f32_output_pt;



// Create a delay of 10 msec in clock ticks
const TickType_t millisec_to_ticks = pdMS_TO_TICKS(10);

uint32_t g_adc_value;  		// Measured, raw ADC value - an unsigned integer
float32_t f32_adc_value;		// ADC value converted to normalized float: range is -1.0 to 1.0
q15_t q15_adc_value;			// ADC value as Q type

// Flag to denote data is ready to be processed and when FIFO is full.
uint8_t g_process_flag;
uint8_t g_fifo_full_flag;   //Means FIFO can accept data - it is NOT full.

rx_dataType sensor_data_buffer[RXFIFOSIZE];
float32_t f32_sensor_data_buffer[RXFIFOSIZE];

// Stuff added so that we can use the ARM FIR filter
#define BLOCK_SIZE			32
#define NUM_TAPS				IMP_RSP_LENGTH

static float32_t f32_fir_state[BLOCK_SIZE + NUM_TAPS - 1];

uint32_t num_of_blocks = INPUT_SIG_LENGTH/BLOCK_SIZE;


int main(void)
{
	// Initialize input and output pointers
	f32_input_pt = &f32_sensor_data_buffer[0];
	f32_output_pt = &f32_output_signal_buffer[0];

	// Initialize FIR filter
	arm_fir_init_f32(&fir_desc,
			NUM_TAPS,
			(float32_t *) LP_1HZ_2HZ_IMPULSE_RESPONSE,
			(float32_t*) f32_fir_state,
			BLOCK_SIZE);


	// Enable FPU
	fpu_enable();

	// Initialize the UART
	uart2_tx_init();

	// Initialize the ADC
	pa1_adc_init();

	// Start ADC conversion
	// This command must be executed BEFORE the TIMER 2 interrupt is initialized!
	start_conversion();

	// Initialize the FIFO
	rx_fifo_init();

	//Timer 2 interrupt init
	tim2_1khz_interrupt_init();

	g_fifo_full_flag =  1;


	//Create the semaphore (Must be done before the task creation and scheduler starts!)
	xBinarySemaphore = xSemaphoreCreateBinary();

	// Create several tasks
	xTaskCreate(data_disp_task, "Display signals", 256, NULL, Task2_priority, NULL);
	xTaskCreate(data_proc_task, "Process signals", 256, NULL, Task3_priority, NULL);

	// Must start the scheduler or nothing happens!
	vTaskStartScheduler();
} // End of main


// This function samples the ADC on PA1, and puts the data in the FIFO if the FIFO is not full yet
// The logic here - the flag names - is confusing and should be reversed...
void acquisition_func(void)
{
	if(g_fifo_full_flag == 1)		// FIFO is not full (!)[Data was put into FIFO successfully, so it can't be full yet.]
	{
		g_fifo_full_flag = rx_fifo_put(adc_read());
	}
	else					// FIFO is full, since if flag is 0 data was not put into FIFO successfully
	{
		// If FIFO is full, time to start data processing
		g_process_flag = 1;
	}
		TaskAcq_profiler++;
}


// This task scales the ADC data and filters it with the FIR
// Task is only executed if "g_process_flag" == 1
void data_proc_task(void *pvParameters)
{

	while(1)
	{
		if(g_process_flag)
		{
			// 1)  Clear buffer
			clear_data_buffer();

			// 2)  Read FIFO contents into data buffer
			for(int i = 0; i < RXFIFOSIZE; i ++)
			{
				// Wait until an entire batch is collected
				while(g_fifo_full_flag == 1){ }

				g_fifo_full_flag = read_fifo(sensor_data_buffer + i);
			}

			// 3) Scale ADC values to +/- 1
			for(int i = 0; i < RXFIFOSIZE; i ++)
			{
				f32_sensor_data_buffer[i] = ((float32_t)(sensor_data_buffer[i] & 0xFFF)/(0xFFF/2)) - 1;
			}

			// 4) Perform DSP - execute FIR function for every block
			for(int i = 0; i < num_of_blocks; i++)
			{
				arm_fir_f32(&fir_desc,
									f32_input_pt + (i * BLOCK_SIZE),
									f32_output_pt + (i * BLOCK_SIZE),
									BLOCK_SIZE);
			}

			TaskProc_profiler++;

			g_process_flag = 0;

			xSemaphoreGive(xBinarySemaphore);
		}
	}
}

// This task displays the various signals
void data_disp_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		for(int i = 0; i < (IMP_RSP_LENGTH + INPUT_SIG_LENGTH - 1); i++)
		{
			if(i < INPUT_SIG_LENGTH)
			{
				printf("%f\t, ", f32_sensor_data_buffer[i]);			// This is the shorter signal vector - the ADC data
			}
			printf("%f\n\r ", f32_output_signal_buffer[i]);			// Here is filtered data
		}

		TaskDisp_profiler++;

//		vTaskDelay(millisec_to_ticks);
	}
}


void TIM2_IRQHandler(void)
{
	acquisition_func();

	TIM2Profiler++;

	// Clear the update interrupt flag
	TIM2->SR &= ~SR_UIF;
}

static uint8_t read_fifo(rx_dataType *data_buff)
{
	__IO uint8_t rd_flag;

	// Place FIFO data into data buffer, check the FIFO full flag
	rd_flag = rx_fifo_get(data_buff);

	// If FIFO is empty, reset global FIFO full flag, else leave it set to full
	if(rd_flag == 0)
	{
		g_fifo_full_flag = 1;
	}
	else
	{
		g_fifo_full_flag = 0;
	}
	return g_fifo_full_flag;
}

static void clear_data_buffer(void)		// Do this a more efficient way
{
//	for(int i = 0; i < RXFIFOSIZE; i++)
//	{
//		sensor_data_buffer[i] = 0;
//		f32_sensor_data_buffer[i] = 0.0;
//	}

    // Using memset()
	memset(sensor_data_buffer, 0, sizeof(sensor_data_buffer));
	memset(f32_sensor_data_buffer, 0, sizeof(sensor_data_buffer));
}


/*

// Function to plot using the SWV
static void swv_plot_signal(void)
{
	for(int i = 0; i < KHZ1_15_SIG_LEN; i++)
	{
		g_in_sig_sample = input_signal_f32_1kHz_15kHz[i];
		pseudo_dly(9000);
	}
}

// Function to plot using the serial port
static void serial_plot_signal(void)
{
	for(int i = 0; i < KHZ1_15_SIG_LEN; i++)
	{
		printf("%f\r\n", input_signal_f32_1kHz_15kHz[i]);
		pseudo_dly(9000);
	}
}

*/

static void pseudo_dly(int dly)
{
	for(int i = 0; i < dly; i++){}
}



static void fpu_enable(void)
{
	// Enable FPU - Set bits 20, 21, 22, 23 to "1" - See page 264 of Cortex-M4 Devices Users Guide
	SCB->CPACR |= ((3UL << 20) | (3UL << 22));
}









