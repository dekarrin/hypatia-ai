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
#include "params.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

hyp_act_t *hyp_act_create(size_t param_count)
{
	hyp_act_t *comp = malloc(sizeof(hyp_act_t));
	comp->params = NULL;
	if (param_count > 0)
	{
		comp->params = hyp_params_create(param_count);
	}
	return comp;
}

void hyp_act_free(hyp_act_t *comp)
{
	if (comp != NULL)
	{
		hyp_params_free(comp->params);
	}
	free(comp);
}

double hyp_act_threshold(double input, params_t *params)
{
	bool thresh_up = hyp_params_bget(params, 0, true);
	double thresh = hyp_params_dget(params, 1, 0.0);
	double out = 0;
	if (input > thresh || (input == thresh && thresh_up))
	{
		out = 1;
	}
	return out;
}

double hyp_act_signum(double input, params_t *params)
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

double hyp_act_logistic(double input, params_t *params)
{
	double steepness = hyp_params_dget(params, 0, 1.0);
	return 1.0 / (1.0 + exp(-input * steepness));
}

double hyp_act_tanh(double input, params_t *params)
{
	double steepness = hyp_params_dget(params, 0, 1.0);
	return tanh(input * steepness);
}

