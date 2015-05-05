/*******************************************************************************
 * This is the implementation for the neuron module of the Hypatia AI system,
 * which includes different types of neurons.
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

#include "neuron.h"
#include "util.h"

#include <stdlib.h>

#define INITIAL_WEIGHT_RANGE 1.0

neuron_t *hyp_neuron_create(size_t inputs, double learning_rate)
{
	neuron_t *nrn = malloc(sizeof(neuron_t));
	nrn->input_count = inputs;
	nrn->weights = hyp_math_create_vector(inputs);
	nrn->bias = 0.0;
	nrn->combiner = NULL;
	nrn->activation = NULL;
	nrn->learn_rate = learning_rate;
	return nrn;
}

neuron_t *hyp_neuron_create_perceptron(size_t inputs, double learning_rate)
{
	neuron_t *pcpt = hyp_neuron_create(inputs, learning_rate);
	pcpt->combiner = &hyp_comb_linear;
	pcpt->activation = malloc(sizeof(hyp_act_t));
	pcpt->activation->func = &hyp_act_threshold;
	pcpt->activation->params = NULL;
	return pcpt;
}

void hyp_neuron_free(neuron_t *n)
{
	if (n->activation != NULL)
	{
		if (n->activation->params != NULL)
		{
			for (size_t i = 0; i < n->activation->params_count; i++)
			{
				void *ptr = n->activation->params[i];
				free(ptr);
			}
			free(n->activation->params);
		}
		free(n->activation);
	}
	if (n->weights != NULL)
	{
		hyp_math_free_vector(n->weights);
	}
	free(n);
}

void hyp_neuron_init(neuron_t *n)
{
	for (size_t i = 0; i < n->input_count; i++)
	{
		n->weights->values[i] =
		  rand_range(-INITIAL_WEIGHT_RANGE, INITIAL_WEIGHT_RANGE);
	}
	n->bias = rand_range(-INITIAL_WEIGHT_RANGE, INITIAL_WEIGHT_RANGE);
}

double hyp_neuron_fire(neuron_t const *n, vector_t const *inputs)
{
	double comb = n->combiner(inputs, n->weights);
	void **params = n->activation->params;
	double result = n->activation->func(comb + n->bias, params);
	return result;
}

void hyp_neuron_train(neuron_t *n, vector_t const *const *inputs,
  double const *expected, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		vector_t const *in = inputs[i];
		double ex = expected[i];
		double actual = hyp_neuron_fire(n, in);
		double *weight_vals = n->weights->values;
		double err = ex - actual;
		for (size_t j = 0; j < n->weights->dim; j++)
		{
			weight_vals[j] += n->learn_rate * err * in->values[j];
		}
	}
}

