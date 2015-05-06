/*******************************************************************************
 * This is implementation of the math module of the Hypatia AI system.
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

#include "math.h"

#include <stdlib.h>
#include <math.h>

static double max(double x1, double x2)
{
	return (x1 > x2 ? x1 : x2);
}

vector_t *hyp_math_create_vector(size_t dim)
{
	vector_t *vec = malloc(sizeof(vector_t));
	vec->dim = dim;
	vec->values = malloc(sizeof(double) * dim);
	return vec;
}

void hyp_math_free_vector(vector_t *vec)
{
	free(vec->values);
	free(vec);
}

double hyp_math_dot(vector_t const *vec1, vector_t const *vec2)
{
	size_t dim = max(vec1->dim, vec2->dim);
	double sum = 0;
	for (size_t i = 0; i < dim; i++)
	{
		double v1, v2;
		v1 = (vec1->dim > i ? vec1->values[i] : 0);
		v2 = (vec2->dim > i ? vec2->values[i] : 0);
		sum += v1 * v2;
	}
	return sum;
}

