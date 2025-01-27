/*
 *
 * 				RealtimeDSP.c
 *
 * 	Here, tasks give and take semaphores.
 *
 *
 * 	Three tasks emulate a typical RTOS DSP scenario. An ARM low pass filter is
 * 	used (defined in "lowpassfilter.c") to remove high frequency noise from a
 * 	noise-corrupted signal.
 *
 * 	Signals and noise are synthetic here.
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
q15_t filtered_sig_sample;

// Convert time in millisec to clock ticks
// Each task needs a delay to work correctly. 1 msec is way too short; 10 msec is fine.
const TickType_t _ms_ticks = pdMS_TO_TICKS(5);


int main(void)
{
	// Enable FPU
	fpu_enable();

	// Initialize the UART
	uart2_tx_init();

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
// This task generates the sine wave signal as well as the noise
void data_acq_task(void *pvParameters)
{
	xSemaphoreGive(xBinarySemaphore);

	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		sine_sig_sample = sine_calc_sample_q15(&signal_desc)/2;
		noise_sig_sample = sine_calc_sample_q15(&noise_desc)/8;

		Task1_profiler++;

		xSemaphoreGive(xBinarySemaphore);
		vTaskDelay(_ms_ticks);
	}
}


// Definition of the second task
// Add the sine wave and noise signals to create the corrupt signal, then low pass filter it
void data_proc_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		corrupt_sig_sample = sine_sig_sample + noise_sig_sample;

		filtered_sig_sample = lowpass_filter_exec(&corrupt_sig_sample);

		Task2_profiler++;

		xSemaphoreGive(xBinarySemaphore);
		vTaskDelay(_ms_ticks);
	}
}

// Definition of the third task
// This task displays the various signals
void data_disp_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		printf("%d\t ", (int)sine_sig_sample);      // Original uncorrupted signal
		// printf("%d\t", (int)noise_sig_sample);		// Noise signal
		printf("%d\t", (int)corrupt_sig_sample);	// Noise-corrupted signal (Signal plus noise)
		printf("%d\n\r", (int)filtered_sig_sample); // Post-filtered signal

		Task3_profiler++;

		xSemaphoreGive(xBinarySemaphore);
		vTaskDelay(_ms_ticks);
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









