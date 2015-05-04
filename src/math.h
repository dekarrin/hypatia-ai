/*******************************************************************************
 * This is the header file for the math module of the Hypatia AI system.
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

#ifndef __HYPATIA_MATH_H
#define __HYPATIA_MATH_H

#include <stddef.h>

typedef struct vector {
	size_t dim;
	double *values;
} vector_t;

vector_t *hyp_math_create_vector(size_t dim);
void hyp_math_free_vector(vector_t *vec);

/*
 * If vectors difer in length, the shorter is converted to the length of the
 * larger one by using zeros for the missing values. For example, if vec1 is
 * [0, 1], and vec2 is [0, 1, 2], this function will return the dot product
 * between [0, 1, 0] and [0, 1, 2].
 */
double hyp_math_dot(vector_t const *vec1, vector_t const *vec2);

#endif
