/*
 * lowpassfilter.h
 *
 *  Created on: Dec 25, 2024
 *      Author: michael
 */

#ifndef LOWPASSFILTER_H_
#define LOWPASSFILTER_H_

#include "arm_math.h"

void lowpass_filter_init(void);
q15_t lowpass_filter_exec(q15_t * input);


#endif /* LOWPASSFILTER_H_ */
