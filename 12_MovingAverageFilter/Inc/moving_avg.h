/*
 * moving_avg.h
 *
 *  Created on: Dec 31, 2024
 *      Author: michaelalex
 */

#ifndef MOVING_AVG_H_
#define MOVING_AVG_H_

#include "arm_math.h"

void moving_average(float32_t *sig_src_arr, float32_t *sig_out_arr, uint32_t signal_len, uint32_t filter_len);



#endif /* MOVING_AVG_H_ */
