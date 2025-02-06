/*
 *
 * 		"6a_FreeRTOSIntegration.c" (Used to be 1_FreeRTOSIntegration.c)
 *
	 *  Added files for FreeRTOS, make two tasks and count how
	 *  much time is spent in each task.
	 *
	 *  Use "Live Expressions" window to compare.
	 *
	 *  Change each task priority and FreeRTOSConfig.h settings to
	 *  see how these change things.
 */

#include "stm32f4xx.h"
#include <stdio.h>
#include "uart.h"
#include "FreeRTOS.h"
#include "task.h"




static void fpu_enable(void);

// Here are the variables to add to Live Expressions.  These are just counters.
uint32_t Task1_profiler, Task2_profiler;

// Here is where we can change task priorities.
// The higher the number, the higher the task priority.
int Task1_priority = 1;
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

	}

} // End of main

// Definition of the first task
void Task1(void *pvParameters)
{
	while(1)
	{
		Task1_profiler++;

	}

}

// Definition of the second task
void Task2(void *pvParameters)
{
	while(1)
	{
		Task2_profiler++;

	}

}


static void fpu_enable(void)
{
	// Enable FPU - Set bits 20, 21, 22, 23 to "1" - See page 264 of Cortex-M4 Devices Users Guide
	SCB->CPACR |= ((3UL << 20) | (3UL << 22));
}









