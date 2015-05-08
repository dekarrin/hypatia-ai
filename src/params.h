/*******************************************************************************
 * This is the header file for the params module of Hypatia AI. It contains
 * functionality for passing generic parameters to functions.
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

#ifndef HYPATIA_PARAMS_H
#define HYPATIA_PARAMS_H

/**
 * This module contains functions for working with a final 'additional params'
 * argument to a function. The primary method for this is the params_t struct,
 * which contains an array of pointers as well as the size of the array. A
 * pointer to params_t can then be specified as the final argument of a
 * function, which allows the programmer to specify that optional arguments to
 * the function must be placed in the params struct. If no optional arguments
 * are required, the user of the function may pass NULL instead of a pointer to
 * params_t.
 *
 * In order to conveniently extract data from the params_t struct, several 'get'
 * functions are defined, such as hyp_params_iget for integers and
 * hyp_params_dget for doubles. Each of these functions returns the specified
 * parameter casted to a particular type. These functions accept the index of
 * the parameter to retrieve (inside of the params_t struct) as well as a
 * default value. If the parameter at the given index is not available, the
 * default value is returned instead.
 *
 * A parameter at an index not being available is defined as the following
 * conditions:
 *
 * - params points to NULL
 * OR
 * - params is a valid pointer AND
 * - The given index is outside the range of the array in params
 * OR
 * - params is a valid pointer AND
 * - params contains the given index AND
 * - the given index points to NULL
 */

#include <stddef.h>
#include <stdbool.h>

/**
 * Holds optional arguments to be passed to a function by a final 'additional
 * params' argument.
 */
typedef struct params
{
	size_t size;
	void **values;
} params_t;

/**
 * Allocates a new params_t. All pointers in the values array are set to NULL.
 * If pointers in the values array are made to point to heap memory, it is the
 * responsibilty of the user of this function to ensure that heap allocations
 * are freed before passing the params_t to hyp_params_free().
 */
params_t *hyp_params_create(size_t size);

/**
 * Frees a params_t. Any pointers in the values array are not freed; if they
 * are made to point to heap memory, it is the user's responsibility to ensure
 * that this memory is not leaked.
 *
 * If the params_t pointer is NULL, no action is taken.
 */
void hyp_params_free(params_t *p);

/**
 * Gets the specified index casted as a bool.
 */
bool hyp_params_bget(params_t const *params, size_t index, bool def);

/**
 * Gets the specified index casted as an int.
 */
int hyp_params_iget(params_t const *params, size_t index, int def);

/**
 * Gets the specified index casted as a double.
 */
double hyp_params_dget(params_t const *params, size_t index, double def);

#endif

