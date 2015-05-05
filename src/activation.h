/*******************************************************************************
 * This is the header file for the activation function module of the Hypatia AI
 * system.
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

#ifndef HYPATIA_ACTIVATION_H
#define HYPATIA_AVTIVATION_H

/**
 * This file contains declarations for neuron activation functions. All
 * activation functions follow the prototype of double func(double, void *).
 *
 * The first parameter is the input to the function, which will be the
 * value of the input combiner of the neuron. Because of the way that the bias
 * is calculated in Hypatia neurons, this will be equivalent to the induced
 * local field, and thus additional bias is not introduced by the activation
 * function.
 *
 * The second parameter is an array of pointers containing any number of
 * additional parameters that are used for modifying the function itself.
 * Typically, these are some kind of transformation(s) to the function. For
 * functions that accept parameters, NULL may be passed to indicate that all
 * parameters should be set to their default values, otherwise any pointer in
 * the array that is set to NULL will indicate that the parameter associated
 * with that position is to revert to its default value. If NULL is not passed
 * in as this array, then the array must be a size that is at least equal to the
 * number of additional parameters. The parameters that are accepted vary; see
 * each function for more information on what it accepts.
 *
 * Each function uses a special notation to denote the possible output values,
 * known as the range. If the range interval is continuous, open-closed notation
 * will be used, for example (x, y] indicates that the possible range for output
 * is x < output <= y. If the range interval is discrete, than all possible
 * values will be listed by using list notation, for example [x..y] indicates
 * that output is any integer such that x <= output <= y.
 *
 * All functions return the output of the activation function. This value is
 * then directly passed to the output of the neuron.
 */

// A pointer to a raw activation function; that is, one without associated
// parameters.
typedef void (*hyp_act_raw_ptr)(double input, void const *const *params);

// A composite struct that contains both an activation function pointer and its
// additional parameters.
typedef struct hyp_act
{
	hyp_act_raw_ptr func;
	void **params;
	size_t params_count;
} hyp_act_t;

/**
 * Standard threshold function. If input is less than 0, outputs 0. If input is
 * greater than or equal to 0, outputs 1.
 *
 * Output range: [0..1]
 *
 * This function does not accept additional parameters.
 */
double hyp_act_threshold(double input, void const *const *params);

/**
 * Returns the sign of the input. If input is less than 0, outputs -1. If input
 * is 0, outputs 0. If input is greater than 0, outputs 1.
 *
 * Output range: [-1..1]
 *
 * This function does not accept additional parameters.
 */
double hyp_act_signum(double input, void const *const *params);

/**
 * A sigmoid function that follows the logistic curve.
 *
 * Output range: (0, 1)
 *
 * This function accepts the following additional parameters:
 * [0] - k, the steepness of the curve (1 by default)
 */
double hyp_act_logistic(double input, void const *const *params);

/**
 * A sigmoid function similar to the logistic curve but extended such that
 * negative values are permitted.
 *
 * Output range: (-1, 1)
 *
 * This function accepts the following additional parameters:
 * [0] k, the steepness of the curve (1 by default)
 */
double hyp_act_tanh(double input, void const *const *params);

#endif
