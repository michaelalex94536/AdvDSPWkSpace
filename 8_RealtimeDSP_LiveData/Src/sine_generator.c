

#include "sine_generator.h"


void sine_gen_init_q15(sine_generator_q15_t *sine_desc,  q15_t sine_freq, q15_t sample_freq)
{
	//  Variables to hold intermediate sine values and coefficients
	float32_t y[4];
	float32_t coeff4;
	float32_t coeff5;

	y[0] = 0.0;

	// Calculate sine values normalized by sampling frequency for first three harmonics
	y[1] = arm_sin_f32(2.0 * PI * sine_freq/sample_freq);
	y[2] = arm_sin_f32(4.0 * PI * sine_freq/sample_freq);
	y[3] = arm_sin_f32(6.0 * PI * sine_freq/sample_freq);

	// Calculate coefficients for sine wave generator
	coeff4 = (y[2]/y[1])/2.0;
	coeff5 = ((y[1] * y[3] - y[2] * y[2])/(y[1] * y[1]))/2.0;

	// Convert floats to q data type
	arm_float_to_q15(&coeff4, &(sine_desc->coeff[4]), 1);
	arm_float_to_q15(&coeff5, &(sine_desc->coeff[5]), 1);

	// Initialize biquad filter for sine wave generator
	arm_biquad_cascade_df1_init_q15(&(sine_desc->iir_sine_generator_instance), 1, sine_desc->coeff, sine_desc->state, 1);

	// Initialize state variables
	arm_float_to_q15(&y[1], &(sine_desc->state[3]), 1);

}


q15_t sine_calc_sample_q15(sine_generator_q15_t *sine_desc)
{
	q15_t input, output;

	input = 0;

	// Generate one sample of the sine wave using biquad filter
	arm_biquad_cascade_df1_q15(&(sine_desc->iir_sine_generator_instance), &input, &output, 1);

	return (output);

}






