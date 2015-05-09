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
	nrn->weights = hyp_vec_create(inputs);
	nrn->bias = 0.0;
	nrn->combiner = NULL;
	nrn->activation = NULL;
	nrn->learn_rate = learning_rate;
	return nrn;
}

neuron_t *hyp_neuron_create_perceptron(size_t inputs, double learning_rate,
  params_t *params)
{
	neuron_t *pcpt = hyp_neuron_create(inputs, learning_rate);
	pcpt->combiner = &hyp_comb_linear;
	pcpt->activation = hyp_act_create(0);
	pcpt->activation->func = &hyp_act_threshold;
	pcpt->activation->params = params;
	return pcpt;
}

void hyp_neuron_free(neuron_t *n)
{
	hyp_act_free(n->activation);
	if (n->weights != NULL)
	{
		hyp_vec_free(n->weights);
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
	params_t *params = n->activation->params;
	return n->activation->func(comb + n->bias, params);
}

void hyp_neuron_train(neuron_t *n, vector_t const *input, double expected)
{
	double actual = hyp_neuron_fire(n, input);
	double err = expected - actual;
	double *w = n->weights->values;
	double *x = input->values;
	for (size_t i = 0; i < n->weights->dim; i++)
	{
		w[i] += n->learn_rate * err * x[i];
	}
	n->bias += n->learn_rate * err;
}

void hyp_neuron_train_multi(neuron_t *n, vector_t **inputs,
  double const *expected, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		vector_t const *in = inputs[i];
		double ex = expected[i];
		hyp_neuron_train(n, in, ex);
	}
}

void hyp_neuron_train_conv(neuron_t *n, vector_t **inputs,
  double const *expected, size_t size, double err_thresh, size_t max_iters)
{
	size_t iters = 0;
	double err = 0.0;
	do
	{
		hyp_neuron_train_multi(n, inputs, expected, size);
		err = hyp_neuron_iter_error(n, inputs, expected, size);
		iters++;
	} while (err >= err_thresh && iters < max_iters);
}

double hyp_neuron_iter_error(neuron_t *n, vector_t **inputs,
  double const *expected, size_t size)
{
	double sum = 0;
	for (size_t i = 0; i < size; i ++)
	{
		double actual = hyp_neuron_fire(n, inputs[i]);
		double err = expected[i] - actual;
		err *= (err < 0 ? -1 : 1);
		sum += err;
	}
	return sum / size;
}

