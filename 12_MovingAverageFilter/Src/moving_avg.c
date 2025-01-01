/*
 * moving_avg.c
 *
 *  Created on: Dec 31, 2024
 *      Author: michaelalex
 */

#include "moving_avg.h"

// Function to compute the moving average
// Inputs: 1) Input signal to be filtered, 2) output filtered signal, 3)input/output signal length, 4) filter length in samples
void moving_average(float32_t *sig_src_arr, float32_t *sig_out_arr, uint32_t signal_len, uint32_t filter_len)
{
	uint32_t i, j;
	for(i = floor(filter_len/2); i < ((signal_len - (filter_len/2)) - 1); i++)
	{
		sig_out_arr[i] = 0;

		for(j = -floor(filter_len/2); j < floor(filter_len/2); j++)
		{
			sig_out_arr[i] = sig_out_arr[i] + sig_src_arr[i + j];
		}

		sig_out_arr[i] = sig_out_arr[i]/filter_len;
	}
}
