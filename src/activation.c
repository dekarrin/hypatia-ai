/*******************************************************************************
 * This file contains implementations of the activation functions for Hypatia AI
 * neurons.
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

/**
 * All functions are of prototype double func(double, void *). First param is
 * output from neuron input cominator, already adjusted for bias. Functions must
 * assume that bias is already applied. Second param is additional parameters
 * for the shape of the function. Return value is the output of the activation
 * function, and thus the output of the neuron. See activation.h for a more
 * verbose introduction.
 */

#include "activation.h"

#include <math.h>

double hyp_act_threshold(double input, void const *const *params)
{
	double out = 0;
	if (input >= 0)
	{
		out = 1;
	}
	return out;
}

double hyp_act_signum(double input, void const *const *params)
{
	double out = 0;
	if (input > 0)
	{
		out = 1;
	}
	else if (input < 0)
	{
		out = -1;
	}
	return out;
}

double hyp_act_logistic(double input, void const *const *params)
{
	double steepness = 1;
	if (params != NULL)
	{
		double const *ptr1 = (double const *)params[0];
		if (ptr1 != NULL)
		{
			steepness = *ptr1;
		}
	}
	double out = 1.0 / (1.0 + exp(-input * steepness));
	return out;
}

double hyp_act_tanh(double input, void const *const *params)
{
	double steepness = 1;
	if (params != NULL)
	{
		double const *ptr1 = (double const *)params[0];
		if (ptr1 != NULL)
		{
			steepness = *ptr1;
		}
	}
	double out = tanh(input * steepness);
	return out;
}

