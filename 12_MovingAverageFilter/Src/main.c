/*
 *
 * 				12_MovingAverageFilter
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
#include "fir_filter.h"
#include "moving_avg.h"

// Signals defined in "signals.c"
extern float32_t input_signal_f32_1kHz_15kHz[KHZ1_15_SIG_LEN];
extern float _5hz_signal[HZ_5_SIG_LEN];
float32_t output_signal_array[KHZ1_15_SIG_LEN];

#define MA_FLTR_PTS		51

static void pseudo_dly(int dly);
static void fpu_enable(void);

// Here are the variables to add to Live Expressions.  These are just counters.
uint32_t Task1_profiler, Task2_profiler, Task3_profiler;

// Name a semaphore
SemaphoreHandle_t xBinarySemaphore;

// Here is where we can change task priorities
// The higher the number, the higher the task priority.
int Task1_priority = 1;
int Task2_priority = 1;
int Task3_priority = 1;

// Here are the task names
void data_acq_task(void *pvParameters);
void data_disp_task(void *pvParameters);
void data_proc_task(void *pvParameters);


// FIR filter stuff here
fir_filter_type lpf_fir;
float32_t fltr_sensor_value;
uint16_t g_sensor_value;
float32_t f32_sensor_value;

extern float LP_1HZ_2HZ_IMPULSE_RESPONSE[IMP_RSP_LENGTH];


// Create a delay of 10 msec in clock ticks
const TickType_t millisec_to_ticks = pdMS_TO_TICKS(10);

uint32_t g_adc_value;  			// Measured, raw ADC value - an unsigned integer
float32_t f32_adc_value;		// ADC value converted to normalized float: range is -1.0 to 1.0

float32_t in_signal, out_signal;

int main(void)
{
	// Enable FPU
	fpu_enable();

	// Initialize the UART
	uart2_tx_init();


		moving_average((float32_t *) input_signal_f32_1kHz_15kHz,
									(float32_t *) output_signal_array,
									(uint32_t) KHZ1_15_SIG_LEN,
									(uint32_t) MA_FLTR_PTS);

		while(1)
		{
			for(int i = 0; i <KHZ1_15_SIG_LEN; i++)
			{
				in_signal = input_signal_f32_1kHz_15kHz[i];
				out_signal = output_signal_array[i];

				printf("%f, ", input_signal_f32_1kHz_15kHz[i]);
				printf("%f\r\n ", output_signal_array[i]);
				pseudo_dly(30000);
			}
		}

} // End of main

// Definition of the first task - it gives the semaphore initially
// This task samples the ADC on PA1
void data_acq_task(void *pvParameters)
{
	xSemaphoreGive(xBinarySemaphore);

	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		g_sensor_value = adc_read();

		Task1_profiler++;

		xSemaphoreGive(xBinarySemaphore);
		vTaskDelay(millisec_to_ticks);
	}
}


// Definition of the second task
// Scale ADC data, convert to q type, filter
void data_proc_task(void *pvParameters)
{
	fir_filter_init(&lpf_fir, LP_1HZ_2HZ_IMPULSE_RESPONSE, IMP_RSP_LENGTH);

	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		// Scale ADC values to +/- 1
		//f32_adc_value = ((float32_t)(g_adc_value & 0xFFF)/(0xFFF/2)) - 1;

		// Perform DSP
		fltr_sensor_value = fir_filter_exec(&lpf_fir, g_sensor_value);

		Task2_profiler++;

		xSemaphoreGive(xBinarySemaphore);
		vTaskDelay(millisec_to_ticks);
	}
}

// Definition of the third task
// This task displays the various signals
void data_disp_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		printf("%d\t", g_sensor_value);				// Raw data sample
		printf("%f\n\r", fltr_sensor_value);			// Filtered data sample

		Task3_profiler++;

		xSemaphoreGive(xBinarySemaphore);
		vTaskDelay(millisec_to_ticks);
	}
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









