#ifndef SINE_GENERATOR_H_
#define SINE_GENERATOR_H_

#include "arm_math.h"

typedef struct
{
	// Biquad cascade IIR from ARM
	arm_biquad_casd_df1_inst_q15 iir_sine_generator_instance;
	q15_t coeff[6];
	q15_t state[4];
}sine_generator_q15_t;

void sine_gen_init_q15(sine_generator_q15_t *sine_desc,  q15_t sine_freq, q15_t sample_freq);
q15_t sine_calc_sample_q15(sine_generator_q15_t *sine_desc);



#endif /* SINE_GENERATOR_H_ */
