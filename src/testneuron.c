/*******************************************************************************
 * This is a test of the neuron module of the Hypatia AI system.
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

#include "testneuron.h"
#include "vector.h"
#include "params.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const **argv)
{
	srand(256);
	neuron_t *pcpt = hyp_testneuron_make_neuron();
	hyp_testneuron_trn_nand(pcpt, "NAND");
	hyp_testneuron_print_params(pcpt);
	hyp_testneuron_test_nand(pcpt);
	hyp_neuron_free(pcpt);
	return 0;
}

static neuron_t *hyp_testneuron_make_neuron()
{
	params_t *params = hyp_params_create(2);
	bool thresh_up = false;
	double thresh = 0.5;
	params->values[0] = &thresh_up;
	params->values[1] = &thresh;
	neuron_t *pcpt = hyp_neuron_create_perceptron(2, 0.1, params);
	return pcpt;
}

static void hyp_testneuron_print_params(neuron_t const *n, char const *type)
{
	printf("%s Perceptron\n", type);
	printf("===========================\n");
	printf("\n");
	printf("Parameters\n");
	printf("---------------------------\n");
	printf("Inputs: %d\n", n->input_count);
	printf("Alpha (Learning Rate): %.2f\n", n->learn_rate);
	printf("---------------------------\n");
	printf("\n");
}

static void hyp_testneuron_trn_nand(neuron_t *pcpt)
{
	vector_t **in = NULL;
	double *out = NULL;
	hyp_neuron_init(pcpt);
	hyp_testneuron_make_nand_trn_set(&in, &out);
	hyp_neuron_train_conv(pcpt, in, out, NAND_TRAINING_SIZE, 0, MAX_ITERS);
	hyp_testneuron_free_nand_trn_set(in, out);
}

static void hyp_testneuron_free_nand_trn_set(vector_t **inputs, double *outputs)
{
	for (size_t i = 0; i < NAND_TRAINING_SIZE; i++)
	{
		hyp_vec_free(inputs[i]);
	}
	free(inputs);
	free(outputs);
}

static void hyp_testneuron_test_nand(neuron_t *n)
{
	vector_t **inputs = malloc(sizeof(vector_t *) * NAND_TRAINING_SIZE);
	for (size_t i = 0; i < NAND_TRAINING_SIZE; i++)
	{
		inputs[i] = hyp_vec_create(2);	
	}
	inputs[0]->values[0] = 0;
	inputs[0]->values[1] = 0;
	inputs[1]->values[0] = 0;
	inputs[1]->values[1] = 1;
	inputs[2]->values[0] = 1;
	inputs[2]->values[1] = 0;
	inputs[3]->values[0] = 1;
	inputs[3]->values[1] = 1;
	double nand0_0 = hyp_neuron_fire(n, inputs[0]);
	double nand1_0 = hyp_neuron_fire(n, inputs[1]);
	double nand0_1 = hyp_neuron_fire(n, inputs[2]);
	double nand1_1 = hyp_neuron_fire(n, inputs[3]);
	for (size_t i = 0; i < NAND_TRAINING_SIZE; i++)
	{
		hyp_vec_free(inputs[i]);
	}
	free(inputs);
	hyp_testneuron_print_nand(nand0_0, nand1_0, nand0_1, nand1_1);
}

static void hyp_testneuron_print_nand(double n0_0, double n1_0, double n0_1,
  double n1_1)
{
	printf("Results\n");
	printf("---------------------------\n");
	printf("(0, 0) => %.2f\n", n0_0);
	printf("(1, 0) => %.2f\n", n1_0);
	printf("(0, 1) => %.2f\n", n0_1);
	printf("(1, 1) => %.2f\n", n1_1);
	printf("---------------------------\n");
}

static void hyp_testneuron_make_nand_trn_set(vector_t ***inputs_ptr,
  double **outputs_ptr)
{
	*inputs_ptr = malloc(sizeof(vector_t *) * NAND_TRAINING_SIZE);
	for (size_t i = 0; i < NAND_TRAINING_SIZE; i++)
	{
		(*inputs_ptr)[i] = hyp_vec_create(2);
	}
	*outputs_ptr = malloc(sizeof(double) * NAND_TRAINING_SIZE);
	(*inputs_ptr)[0]->values[0] = 0;
	(*inputs_ptr)[0]->values[1] = 0;
	(*outputs_ptr)[0] = 1;
	(*inputs_ptr)[1]->values[0] = 0;
	(*inputs_ptr)[1]->values[1] = 1;
	(*outputs_ptr)[1] = 1;
	(*inputs_ptr)[2]->values[0] = 1;
	(*inputs_ptr)[2]->values[1] = 0;
	(*outputs_ptr)[2] = 1;
	(*inputs_ptr)[3]->values[0] = 1;
	(*inputs_ptr)[3]->values[1] = 1;
	(*outputs_ptr)[3] = 0;
}

