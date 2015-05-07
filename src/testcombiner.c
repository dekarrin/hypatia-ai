/*******************************************************************************
 * This is a test of the combiner module of the Hypatia AI system.
 * Copyright (C) 2015  Rebecca Nelson
 *
 * To contact by email, send to username dekarrin on the domain outlook.com.
 * To contact by mail, send to:
 * Rebecca Nelson
 * 1001 18th St N. Apt #8
 * In the city of Fargo, in the state of North Dakota, with area code 58102
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have recieved a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "combiner.h"

#include <stdio.h>

int main(int argc, char const **argv)
{
	vector_t *inputs = hyp_math_create_vector(3);
	inputs->values[0] = 12;
	inputs->values[1] = 2.42;
	inputs->values[2] = -3.92;

	vector_t *weights = hyp_math_create_vector(3);
	weights->values[0] = 0.3;
	weights->values[1] = 0.3452;
	weights->values[2] = 0.5;

	double lin_out = hyp_comb_linear(inputs, weights);

	printf("%.5f\n", lin_out);

	hyp_math_free_vector(inputs);
	hyp_math_free_vector(weights);

	return 0;
}
