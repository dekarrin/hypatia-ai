/*******************************************************************************
 * This is the implementation of the test executable for the vector module of
 * the Hypatia AI system.
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

#include "vector.h"
#include <stdio.h>

int main(int argc, char const **argv)
{
	vector_t *v1, *v2, *v3, *v4;
	v1 = hyp_math_create_vector(3);
	v2 = hyp_math_create_vector(2);
	v3 = hyp_math_create_vector(2);
	v4 = hyp_math_create_vector(0);

	v1->values[0] = 1;
	v1->values[1] = 1;
	v1->values[2] = 1;

	v2->values[0] = 3;
	v2->values[1] = -2;

	v3->values[0] = -5;
	v3->values[1] = -4;

	double d1_2 = hyp_math_dot(v1, v2);
	double d1_1 = hyp_math_dot(v1, v1);
	double d2_3 = hyp_math_dot(v2, v3);
	double d1_4 = hyp_math_dot(v1, v4);
	double d4_4 = hyp_math_dot(v4, v4);

	hyp_math_free_vector(v1);
	hyp_math_free_vector(v2);
	hyp_math_free_vector(v3);
	hyp_math_free_vector(v4);

	printf("[1, 1, 1] * [3, -2] =    %.1f\n", d1_2);
	printf("[1, 1, 1] * [1, 1, 1] =  %.1f\n", d1_1);
	printf("[3, -2] * [-5, -4] =     %.1f\n", d2_3);
	printf("[1, 1, 1] * [] =         %.1f\n", d1_4);
	printf("[] * [] =                %.1f\n", d4_4);
}
