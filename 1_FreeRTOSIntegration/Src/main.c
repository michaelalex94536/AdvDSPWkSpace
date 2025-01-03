/*
 *
 * 		"FreeRTOSIntegration.c"
 *
	 *  Added files for FreeRTOS, make two task and count how
	 *  much time is spent in each task.
	 *
	 *  Use "Live Expressions" window to compare.
	 *
	 *  Change each task priority and FreeRTOSConfig.h settings to
	 *  see how these change things.
 */

#include "stm32f4xx.h"
#include <stdio.h>
#include "signals.h"
#include "uart.h"
#include "FreeRTOS.h"
#include "task.h"

extern float _5hz_signal[HZ_5_SIG_LEN];
extern float32_t input_signal_f32_1kHz_15kHz[KHZ1_15_SIG_LEN] ;
float g_in_sig_sample;

// static void swv_plot_signal(void);
// static void serial_plot_signal(void);
// static void pseudo_dly(int dly);
static void fpu_enable(void);

// Here are the variables to add to Live Expressions.  These are just counters.
uint32_t Task1_profiler, Task2_profiler;

// Here is where we can change task priorities
// The higher the number, the higher the task priority.
int Task1_priority = 2;
int Task2_priority = 2;

// Here are the task names
void Task1(void *pvParameters);
void Task2(void *pvParameters);

int main(void)
{
	// Enable FPU
	fpu_enable();

	// Initialize the UART
	uart2_tx_init();

	// Create the two tasks
	xTaskCreate(Task1, "Task1", 100, NULL, Task1_priority, NULL);
	xTaskCreate(Task2, "Task2", 100, NULL, Task2_priority, NULL);

	// Must start the scheduler or nothing happens!
	vTaskStartScheduler();

	while(1)
	{
			// swv_plot_signal();
			// serial_plot_signal();
	}


} // End of main

// Definition of the first task
void Task1(void *pvParameters)
{
	while(1)
	{
		Task1_profiler++;

		taskYIELD();
	}

}

// Definition of the second task
void Task2(void *pvParameters)
{
	while(1)
	{
		Task2_profiler++;

		taskYIELD();
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









