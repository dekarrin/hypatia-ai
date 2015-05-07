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

#include "neuron.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>

#define NAND_TRAINING_SIZE 4

int main(int argc, char const **argv)
{
	// ensure weight initialization is always the same
	srand(256);

	neuron_t *pcpt = hyp_neuron_create_perceptron(2, 0.2);

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

	printf("Initialization:\n");
	for (size_t i = 0; i < pcpt->input_count; i++)
	{
		printf("w%02d: %.4f\n", pcpt->weights->values[i]);
	}
	printf("bias: %.4f\n", pcpt->bias);
	printf("---------------------------\n");
	// now train the neuron
	int iter = 0;
	do
	{
		hyp_neuron_train(n, inputs, outputs, NAND_TRAINING_SIZE);
		printf("Iteration #%d:\n", iter + 1);
		for (size_t i = 0; i < pcpt->input_count; i++)
		{
			printf("w%02d: %.4f\n", pcpt->weights->values[i]);
		}
		printf("b: %.4f\n", pcpt->bias);
		printf("---------------------------\n");
	}
	while(rep < 2);

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
	hyp_neuron_free_perceptron(pcpt);

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
