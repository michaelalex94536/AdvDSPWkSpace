/*
 * fir_filter.h
 *
 *  Created on: Dec 30, 2024
 *      Author: michaelalex
 */

#ifndef FIR_FILTER_H_
#define FIR_FILTER_H_

#include <stdint.h>
#include "arm_math.h"

typedef struct
{
	float32_t* buffer;
	uint32_t buff_idx;
	float32_t* kernel;
	uint32_t kernel_len;
	float32_t output;

}fir_filter_type;

void fir_filter_init(fir_filter_type * fir, float32_t * fltr_kernel, uint32_t fltr_kernel_len);
float32_t fir_filter_exec(fir_filter_type * fir, float32_t curr_sample);

#endif /* FIR_FILTER_H_ */
