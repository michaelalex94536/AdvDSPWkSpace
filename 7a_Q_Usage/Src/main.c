/*
	 *  Q data type usage
	 *
	 *  1) Get some integer data values from the sensor/ADC, for example
	 *
	 *  2) Convert the integers to floats, and scale data to be between -1 and +1
	 *
	 *  3) Convert the data to desired Q data type and do your DSP stuff with it
	 *
	 *	4) Convert the post-processed Q data back to floating point
	 *
	 *	5) Convert the floating point data back to integers
	 *
	 *	6) Compare the original data from Step 1) with the data in Step 5)
	 *
	 *
	 *	Try using q31, q15, and q7 data types - Only q7 showed some loss of precision in conversion
	 *	Of course, here we didn't do any DSP operations...
	 *
	 *
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


static void fpu_enable(void);

#define BLOCK_SIZE		7


//  Here is some initial, fictitious sensor/ADC data: 12-bit integers
uint32_t src_sensor_data[BLOCK_SIZE] = {0, 2043, 1023, 990, 67, 3013, 4095};

//  Here is the scaled sensor/ADC data in floating point
float32_t f32_sensor_data[BLOCK_SIZE];

//  Here is the initial sensor/ADC data in Q format
q31_t q31_sensor_data[BLOCK_SIZE];

//  Here is the final sensor/ADC data converted back to floating point
float32_t f32_final_sensor_data[BLOCK_SIZE];

//  Here is the final sensor/ADC data converted back to integers
uint32_t u32_final_sensor_data[BLOCK_SIZE];

int main(void)
{
	// Enable FPU
	fpu_enable();

	// Initialize the UART
	uart2_tx_init();

	/*    Scale ADC values from -1 to +1   */
	for(int i = 0; i< BLOCK_SIZE; i++)
	{
		// Scaling data: divide by 4095/2 and subtract 1.0
		f32_sensor_data[i] = ((float32_t)(src_sensor_data[i] & 0xFFF)/(0xFFF >> 1)) - 1.0;
	}

	/*    Convert float 32 data type to q data type            */
	arm_float_to_q31(f32_sensor_data, q31_sensor_data, BLOCK_SIZE);

	/*    Do some DSP in fixed point       */

	/*    Convert q data back to floating point         */
	arm_q31_to_float(q31_sensor_data, f32_final_sensor_data, BLOCK_SIZE);

	/*    Convert float to uint32_t  - and don't forget to rescale!      */
	float32_t temp_data;

	for(int i = 0; i< BLOCK_SIZE; i++)
	{
		// Rescale the float32_t data - remember it comes in normalized, so we have to
		// add 1.0 and multiply by 4095/2
		temp_data = (f32_final_sensor_data[i] + 1)*(0xFFF >> 1);

		//  Round to the nearest integer
		u32_final_sensor_data[i] = (uint32_t)(temp_data + 0.50);
	}



	while(1)
	{
			// swv_plot_signal();
			// serial_plot_signal();
	}


} // End of main


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









