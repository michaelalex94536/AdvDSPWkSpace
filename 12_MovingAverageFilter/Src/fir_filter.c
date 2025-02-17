/*
 * fir_filter.c
 *
 *  Created on: Dec 30, 2024
 *      Author: michaelalex
 */

#include "fir_filter.h"
#include <stdlib.h>

void fir_filter_init(fir_filter_type * fir, float32_t * fltr_kernel, uint32_t fltr_kernel_len)
{
	// Reset the buffer
	fir->buff_idx = 0;

	// Clear filter output
	fir->output = 0.0f;

	// Set filter kernel
	fir->kernel = fltr_kernel;

	// Set kernel length
	fir->kernel_len = fltr_kernel_len;

	// Dynamically allocate buffer and initialize to zero
	fir->buffer = (float32_t *)calloc(fir->kernel_len, sizeof(float32_t));
}

float32_t fir_filter_exec(fir_filter_type * fir, float32_t curr_sample)
{
	uint32_t sum_idx;

	// Store latest sample in buffer
	fir->buffer[fir->buff_idx] = curr_sample;

	// Increment buffer index and wrap around if at the end
	fir->buff_idx++;

	if(fir->buff_idx == (fir->kernel_len))
	{
		fir->buff_idx = 0;
	}

	/*  Perform convolution */
	fir->output = 0.0f;

	for(int i = 0; i < fir->kernel_len; i ++)
	{
		if(sum_idx > 0)
		{
			sum_idx--;
		}
		else
		{
			sum_idx = (fir->kernel_len) - 1;
		}

		fir->output += fir->kernel[i] * fir->buffer[sum_idx];
	}

	return fir->output;
}






