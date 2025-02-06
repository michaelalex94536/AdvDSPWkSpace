/*
 * 		"4a_CMSIS _DSP_BASE"
 *		Added CMSIS DSP support files and library
 */

#include "stm32f4xx.h"
#include <stdio.h>
#include "signals.h"
#include "uart.h"

extern float _5hz_signal[HZ_5_SIG_LEN];
float g_in_sig_sample;

static void plot_input_signal(void);
static void pseudo_dly(int dly);
static void fpu_enable(void);

int main(void)
{
	// Enable FPU
	fpu_enable();

	// Initialize the UART
	uart2_tx_init();

	while(1)
	{
			//plot_input_signal();								//For sending data to SWV
		for(int i = 0; i < HZ_5_SIG_LEN; i++)
		{
			printf("%f\r\n", _5hz_signal[i]);
			pseudo_dly(9000);
		}
	}


} // End of main

static void plot_input_signal(void)
{
	for(int i = 0; i < HZ_5_SIG_LEN; i++)
	{
		g_in_sig_sample = _5hz_signal[i];
		pseudo_dly(9000);
	}
}

static void pseudo_dly(int dly)
{
	for(int i = 0; i < dly; i++){}
}

static void fpu_enable(void)
{
	// Enable FPU - Set bits 20, 21, 22, 23 to "1" - See page 264 of Cortex-M4 Devices Users Guide
	SCB->CPACR |= ((3UL << 20) | (3UL << 22));
}









