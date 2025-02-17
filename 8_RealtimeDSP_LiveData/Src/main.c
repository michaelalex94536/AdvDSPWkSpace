/*
 *
 * 				RealtimeDSP_LiveData
 *
 * 				Sample ADC and filter blocks of data this time
 *
 * 				Files "adc.c" and "adc.h" simply added to this project.
 *
 * 				The low pass filter taps (impulse response) are in the file "signals.c"
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

#define SIGNAL_FREQ		10
#define NOISE_FREQ		50
#define SAMPLING_FREQ 	1000

extern float _5hz_signal[HZ_5_SIG_LEN];
extern float32_t input_signal_f32_1kHz_15kHz[KHZ1_15_SIG_LEN] ;
float g_in_sig_sample;

// static void swv_plot_signal(void);
// static void serial_plot_signal(void);
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


// Here are the names of the signals (and noise) we wish to generate
sine_generator_q15_t signal_desc, noise_desc;

// Signal, noise and sum samples in Q15 format
q15_t sine_sig_sample, noise_sig_sample;

// Signal plus noise
q15_t corrupt_sig_sample;

// Post-filtered corrupt signal
q15_t fltr_sig_sample;

// Create a delay of 10 msec in clock ticks
const TickType_t millisec_to_ticks = pdMS_TO_TICKS(10);


uint32_t g_adc_value;  			// Measured, raw ADC value - an unsigned integer
float32_t f32_adc_value;		// ADC value converted to normalized float: range is -1.0 to 1.0
q15_t q15_adc_value;			// ADC value as Q type


int main(void)
{
	// Enable FPU
	fpu_enable();

	// Initialize the UART
	uart2_tx_init();

	// Initialize the ADC
	pa1_adc_init();

	// Start ADC conversion
	start_conversion();

	// Create several tasks
	xTaskCreate(data_acq_task, "Create signals", 100, NULL, Task1_priority, NULL);
	xTaskCreate(data_disp_task, "Display signals", 100, NULL, Task2_priority, NULL);
	xTaskCreate(data_proc_task, "Process signals", 100, NULL, Task3_priority, NULL);


	// Initialize the low pass filter here
	lowpass_filter_init();

	// Initialize the signal (and noise) generators here
	sine_gen_init_q15(&signal_desc, SIGNAL_FREQ, SAMPLING_FREQ);
	sine_gen_init_q15(&noise_desc, NOISE_FREQ, SAMPLING_FREQ);


	//Create the semaphore (Must be done before the task scheduler starts!)
	xBinarySemaphore = xSemaphoreCreateBinary();

	// Must start the scheduler or nothing happens!
	vTaskStartScheduler();


	while(1)
	{

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

		g_adc_value = adc_read();

		Task1_profiler++;

		xSemaphoreGive(xBinarySemaphore);
		vTaskDelay(millisec_to_ticks);
	}
}


// Definition of the second task
// Scale ADC data, convert to q type, filter
void data_proc_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		// Scale ADC values to +/- 1
		f32_adc_value = ((float32_t)(g_adc_value & 0xFFF)/(0xFFF/2)) - 1;

		// Convert float to q
		arm_float_to_q15(&f32_adc_value, &q15_adc_value, 1);

		// Perform DSP
		fltr_sig_sample = lowpass_filter_exec(&q15_adc_value);

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

		printf("%d\t", (int)q15_adc_value);			// Raw data sample
		printf("%d\n\r", (int)fltr_sig_sample); 	// Post-filtered signal

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









