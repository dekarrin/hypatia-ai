/*******************************************************************************
 * This is the header file for the combiner module of the Hypatia AI system,
 * which includes the different types of combiners of neuron inputs.
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

#ifndef HYPATIA_COMBINER_H
#define HYPATIA_COMBINER_H

/**
 * This module contains all different types of combiners, which convert many
 * inputs into a single signal to be used with a neuron's activation function.
 *
 * All combiner functions accept two parameters. The first is a pointer to a
 * vector of input values, and the second is a pointer to vector of weight
 * values. The features of each vector are then combined such that the function
 * produces a single output value, which is returned as a double.
 */

#include "vector.h"

// pointer to a combiner function.
typedef double (*hyp_comb_ptr)(vector_t const *inputs, vector_t const *weights);

/**
 * Takes the dot product of the two inputs. This is the same as adding up the
 * inputs after the weights have been applied.
 */
double hyp_comb_linear(vector_t const *inputs, vector_t const *weights);

#endif
