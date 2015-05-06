/*******************************************************************************
 * This is the header file for the neuron module of the Hypatia AI system, which
 * includes the different types of neurons.
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

#ifndef HYPATIA_NEURON_H
#define HYPATIA_NEURON_H

#include "activation.h"
#include "combiner.h"
#include "vector.h"

#include <stddef.h>

/**
 * The base structure of a neuron.
 */
typedef struct neuron
{
	// number of inputs to neuron:
	size_t input_count;
	// weights in the neuron:
	vector_t *weights;
	// bias of the actiavation function:
	double bias;
	// input combiner function:
	hyp_comb_ptr combiner;
	// activation function:
	hyp_act_t *activation;
	// rate of learning. 0 > a >= 1.
	double learn_rate;
} neuron_t;

/**
 * Allocates a neuron that accepts the given number of inputs. The approriate
 * values are assigned: weights is allocated with a size equal to the number of
 * inputs, bias is set to 0, combiner is set to NULL, and activation is set to
 * NULL.
 *
 * learning_rate is how fast weight training compensates for error, and should
 * be greater than 0 and less than or equal to 1.
 *
 * Note that changing the input_count after creation will not cause reallocation
 * of the weights vector. If the weights vector's size is to be modified, it
 * should be allocated / deallocated using the appropriate functions in the
 * Hypatia math module (hyp_math_create_vector / hyp_math_free_vector).
 *
 * If the weights vector pointer is deallocated before the neuron_t pointer is
 * passed to hyp_neuron_free, the weights pointer must be set to NULL or be
 * reallocated before passing the neuron_t pointer to hyp_neuron_free.
 */
neuron_t *hyp_neuron_create(size_t inputs, double learning_rate);

/**
 * Creates a perceptron neuron ready for use with the given number of inputs.
 * The notes on weight vector pointer memory meanagement in hyp_neuron_create
 * also apply to the neuron returned from this function.
 *
 * learning_rate is how fast weight training compensates for error, and should
 * be greater than 0 and less than or equal to 1.
 */
neuron_t *hyp_neuron_create_perceptron(size_t inputs, double learning_rate);

/**
 * Deallocates a neuron_t pointer, recursively freeing any memory used by
 * pointers inside of it.
 *
 * Any pointer inside of the neuron_t struct that does not point to NULL is
 * recursively freed.
 *
 * Before the neuron_t pointer is passed in, all pointers inside of the neuron_t
 * struct must either point to valid memory or else point to NULL. If any
 * pointer directly or indirectly contained in the struct points to invalid
 * memory, the behavior of this function is undefined.
 */
void hyp_neuron_free(neuron_t *n);

/**
 * Randomizes the weights and biases of a neuron.
 */
void hyp_neuron_init(neuron_t *n);

/**
 * Trains a neuron using the given training data. Training data consists of an
 * array of pointers to vectors of inputs as well as an array containing the
 * same number of expected output values. Each set of training data is applied
 * one time to the neuron, and weight training is applied for every set.
 *
 * TODO: This only works for perceptrons. Training algorithms should be
 * generalized.
 */
void hyp_neuron_train(neuron_t *n, vector_t const *const *inputs,
  double const *expected, size_t size);

/**
 * Executes an input on a neuron and returns the result.
 *
 * TODO: This can easily be generated to full neural networks. This function
 * should be generalized to them.
 */
double hyp_neuron_fire(neuron_t const *n, vector_t const *inputs);

#endif
