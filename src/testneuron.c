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
#include <string.h>

#define NAND_TRAINING_SIZE 4
#define ITERATIONS 8

int main(int argc, char const **argv)
{
	// ensure weight initialization is always the same
	srand(256);

	params_t *params = hyp_params_create(2);
	bool thresh_up = false;
	double thresh = 0.5;
	params->values[0] = &thresh_up;
	params->values[1] = &thresh;
	neuron_t *pcpt = hyp_neuron_create_perceptron(2, 0.1, params);

	printf("Perceptron\n");
	printf("===========================\n");
	printf("\n");
	printf("Parameters\n");
	printf("---------------------------\n");
	printf("Inputs: %d\n", pcpt->input_count);
	printf("Alpha (Learning Rate): %.2f\n", pcpt->learn_rate);
	printf("---------------------------\n");
	printf("\n");	
	printf("NAND Training\n");
	printf("---------------------------\n");

	
	// create NAND training set
	vector_t **inputs = malloc(sizeof(vector_t *) * NAND_TRAINING_SIZE);
	inputs[0] = hyp_vec_create(2);
	inputs[1] = hyp_vec_create(2);
	inputs[2] = hyp_vec_create(2);
	inputs[3] = hyp_vec_create(2);

	double *outputs = malloc(sizeof(double) * NAND_TRAINING_SIZE);

	inputs[0]->values[0] = 0;
	inputs[0]->values[1] = 0;
	outputs[0] = 1;

	inputs[1]->values[0] = 0;
	inputs[1]->values[1] = 1;
	outputs[1] = 1;

	inputs[2]->values[0] = 1;
	inputs[2]->values[1] = 0;
	outputs[2] = 1;

	inputs[3]->values[0] = 1;
	inputs[3]->values[1] = 1;
	outputs[3] = 0;

	hyp_neuron_init(pcpt);
	pcpt->weights->values[0] = 0.1;
	pcpt->weights->values[1] = 0.1;
	pcpt->bias = 0.3;

	iter_record_t **rs =
	  hyp_testneuron_create_records(NAND_TRAINING_SIZE * ITERATIONS, 2);
	// now train the neuron
	int rep = 0;
	do
	{
		for (size_t i = 0; i < NAND_TRAINING_SIZE; i++)
		{
			iter_record_t *rec = rs[rep + i];
			vector_t const *input = inputs[i];
			double expected = outputs[i];
			rec->inputs->values[0] = input->values[0];
			rec->inputs->values[1] = input->values[1];
			rec->bias = pcpt->bias;
			rec->expected = expected;
			rec->initial_weights->values[0] =
			  pcpt->weights->values[0];
			rec->initial_weights->values[1] =
			  pcpt->weights->values[1];

			hyp_neuron_train(pcpt, input, expected);

			rec->final_bias = pcpt->bias;
			rec->final_weights->values[0] =
			  pcpt->weights->values[0];
			rec->final_weights->values[1] =
			  pcpt->weights->values[1];
		}
		rep++;
	}
	while(rep < ITERATIONS);

	hyp_testneuron_print_records(rs, NAND_TRAINING_SIZE * ITERATIONS);

	printf("\n");

	// now test it with real data
	double nand0_0 = hyp_neuron_fire(pcpt, inputs[0]);
	double nand1_0 = hyp_neuron_fire(pcpt, inputs[1]);
	double nand0_1 = hyp_neuron_fire(pcpt, inputs[2]);
	double nand1_1 = hyp_neuron_fire(pcpt, inputs[3]);

	// free memory
	for (size_t i = 0; i < NAND_TRAINING_SIZE; i++)
	{
		hyp_vec_free(inputs[i]);
	}
	free(inputs);
	free(outputs);
	hyp_neuron_free(pcpt);
	hyp_testneuron_free_records(rs, NAND_TRAINING_SIZE * ITERATIONS);

	// output results
	printf("NAND Results\n");
	printf("---------------------------\n");
	printf("(0, 0) => %.2f\n", nand0_0);
	printf("(1, 0) => %.2f\n", nand1_0);
	printf("(0, 1) => %.2f\n", nand0_1);
	printf("(1, 1) => %.2f\n", nand1_1);
	printf("---------------------------\n");

	return 0;
}

iter_record_t *hyp_testneuron_create_record(size_t inputs)
{
	iter_record_t *r = malloc(sizeof(iter_record_t));
	r->inputs = hyp_vec_create(inputs);
	r->initial_weights = hyp_vec_create(inputs);
	r->final_weights = hyp_vec_create(inputs);
	return r;
}

void hyp_testneuron_free_record(iter_record_t *r)
{
	hyp_vec_free(r->final_weights);
	hyp_vec_free(r->initial_weights);
	hyp_vec_free(r->inputs);
	free(r);
}

iter_record_t **hyp_testneuron_create_records(size_t size, size_t inputs)
{
	iter_record_t **rs = malloc(sizeof(iter_record_t *) * size);
	for (size_t i = 0; i < size; i++)
	{
		rs[i] = hyp_testneuron_create_record(inputs);	
	}
	return rs;
}

void hyp_testneuron_free_records(iter_record_t **rs, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		hyp_testneuron_free_record(rs[i]);
	}
	free(rs);
}

void hyp_testneuron_print_sep(size_t inputs)
{
	for (size_t i = 0; i < inputs * 3 + 4; i++)
	{
		printf(SEP_FMT);
	}
	printf(SEP_EDGE "\n");
}

void hyp_testneuron_print_title(size_t inputs)
{
	for (size_t i = 0; i < inputs + 1; i++)
	{
		printf(OUTPUT_EDGE " x%-6d ", i);
	}
	printf(OUTPUT_EDGE " z       ");
	for (size_t i = 0; i < inputs + 1; i++)
	{
		printf(OUTPUT_EDGE " w%-6d ", i);
	}
	for (size_t i = 0; i < inputs + 1; i++)
	{
		printf(OUTPUT_EDGE " wf%-5d ", i);
	}
	printf(OUTPUT_EDGE "\n");
}

void hyp_testneuron_print_records(iter_record_t **rs, size_t size)
{
	size_t inputs = rs[0]->inputs->dim;
	hyp_testneuron_print_sep(inputs);
	hyp_testneuron_print_title(inputs);
	for (size_t i = 0; i < size; i++)
	{
		if (i % NAND_TRAINING_SIZE == 0)
		{
			hyp_testneuron_print_sep(inputs);
		}
		hyp_testneuron_print_record(rs[i]);
	}
	hyp_testneuron_print_sep(inputs);
}

void hyp_testneuron_print_record(iter_record_t *r)
{
	printf(DATA_FMT, 1.0);
	for (size_t i = 0; i < r->inputs->dim; i++)
	{
		printf(DATA_FMT, r->inputs->values[i]);
	}
	printf(DATA_FMT DATA_FMT, r->expected, r->bias);
	for (size_t i = 0; i < r->initial_weights->dim; i++)
	{
		printf(DATA_FMT, r->initial_weights->values[i]);
	}
	printf(DATA_FMT, r->final_bias);
	for (size_t i = 0; i < r->final_weights->dim; i++)
	{
		printf(DATA_FMT, r->final_weights->values[i]);
	}
	printf(OUTPUT_EDGE "\n");
}

