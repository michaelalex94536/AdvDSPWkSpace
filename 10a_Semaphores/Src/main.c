/*
 *
 * 				10a_Semaphores.c
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

#define SIGNAL_FREQ		10
#define NOISE_FREQ			50
#define SAMPLING_FREQ 	1000

extern float _5hz_signal[HZ_5_SIG_LEN];
extern float32_t input_signal_f32_1kHz_15kHz[KHZ1_15_SIG_LEN] ;
float g_in_sig_sample;

// static void swv_plot_signal(void);
// static void serial_plot_signal(void);
//static void pseudo_dly(int dly);
static void fpu_enable(void);

// Here are the variables to add to Live Expressions.  These are just counters.
uint32_t Task1_profiler, Task2_profiler, Task3_profiler, Task4_profiler;

// Name a semaphore
SemaphoreHandle_t xBinarySemaphore;

// Here is where we can change task priorities
// The higher the number, the higher the task priority.
int Task1_priority = 1;
int Task2_priority = 1;
int Task3_priority = 1;
int Task4_priority = 1;

// Here are the task names
void data_acq_task(void *pvParameters);
void data_proc_task(void *pvParameters);
void data_disp_task(void *pvParameters);
void data_filt_task(void *pvParameters);

// Here are the names of the signals (and noise) we wish to generate
sine_generator_q15_t signal_desc, noise_desc;

// Signal, noise and sum samples in Q15 format
q15_t sine_sig_sample, noise_sig_sample;

// Signal plus noise
q15_t corrupt_sig_sample;

// Post-filtered corrupt signal
q15_t filtered_sig_sample;

int main(void)
{
	// Enable FPU
	fpu_enable();

	// Initialize the UART
	uart2_tx_init();

	// Create several tasks
	xTaskCreate(data_acq_task, "Get signals", 100, NULL, Task1_priority, NULL);
	xTaskCreate(data_proc_task, "Noise and signal", 100, NULL, Task2_priority, NULL);
	xTaskCreate(data_disp_task, "Combine signals", 100, NULL, Task3_priority, NULL);
	xTaskCreate(data_filt_task, "Filter signals", 100, NULL, Task4_priority, NULL);

	//Create the semaphore
	xBinarySemaphore = xSemaphoreCreateBinary();

	// Must start the scheduler or nothing happens!
	vTaskStartScheduler();



/*  This code never runs when we use RTOS
	// Initialize the low pass filter here
	lowpass_filter_init();

	// Initialize the signal (noise) generators here
	sine_gen_init_q15(&signal_desc, SIGNAL_FREQ, SAMPLING_FREQ);
	sine_gen_init_q15(&noise_desc, NOISE_FREQ, SAMPLING_FREQ);
*/


	while(1)
	{
/*			This code never runs when we use RTOS
 *
 * 			// swv_plot_signal();
			// serial_plot_signal();

		sine_sig_sample = sine_calc_sample_q15(&signal_desc)/2;
		noise_sig_sample = sine_calc_sample_q15(&noise_desc)/2;
		corrupt_sig_sample = sine_sig_sample + noise_sig_sample;

		// Filter the corrupt signal here to get the filtered signal
		filtered_sig_sample = lowpass_filter_exec(&corrupt_sig_sample);


//  Use tabs between data for Tauno plotter to work
		printf("%d\t ", (int)sine_sig_sample);
		printf("%d\t", (int)noise_sig_sample);
		printf("%d\t", (int)corrupt_sig_sample);
		printf("%d\n\r", (int)filtered_sig_sample);

		pseudo_dly(9000);*/
	}


} // End of main

// Definition of the first task - it gives the semaphore initially
void data_acq_task(void *pvParameters)
{
	xSemaphoreGive(xBinarySemaphore);

	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		Task1_profiler++;

		xSemaphoreGive(xBinarySemaphore);
	}
}

// Definition of the second task
void data_proc_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		Task2_profiler++;

		xSemaphoreGive(xBinarySemaphore);
	}
}

// Definition of the third task
void data_disp_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		Task3_profiler++;

		xSemaphoreGive(xBinarySemaphore);
	}
}

// Definition of the fourth task
void data_filt_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		Task4_profiler++;

		xSemaphoreGive(xBinarySemaphore);
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



static void pseudo_dly(int dly)
{
	for(int i = 0; i < dly; i++){}
}

*/

static void fpu_enable(void)
{
	// Enable FPU - Set bits 20, 21, 22, 23 to "1" - See page 264 of Cortex-M4 Devices Users Guide
	SCB->CPACR |= ((3UL << 20) | (3UL << 22));
}









