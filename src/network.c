/*******************************************************************************
 * This is the implentation of the artificial neural network  module of the
 * Hypatia AI system, which groups neurons together into networks.
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

#include "network.h"

#include <stdlib.h>

typedef struct hyp_net_node_vec
{
	size_t size;
	size_t capacity;
	hyp_net_node_t **nodes;
} hyp_net_node_vec_t;

typedef struct hyp_net_node
{
	hyp_net_node_vec_t *inputs;
	hyp_net_node_vec_t *outputs;
	// if neuron is NULL, a node will simply pass its first input directly
	// to its output.
	neuron_t *neuron;
} hyp_net_node_t;

static hyp_net_node_vec_t *hyp_net_create_node_vec(size_t capacity)
{
	hyp_net_node_vec_t *vec = malloc(sizeof(hyp_net_node_vec_t));
	vec->nodes = malloc(sizeof(hyp_net_node_t *) * capacity);
	for (size_t i = 0; i < capacity; i++)
	{
		vec->nodes[i] = NULL;
	}
	vec->size = 0;
	vec->capacity = capacity;
	return vec;
}

static void hyp_net_free_node_vec(hyp_net_node_vec_t *vec)
{
	if (vec != NULL)
	{
		free(vec->nodes);
	}
	free(vec);
}

static void hyp_net_node_vec_insert(hyp_net_node_vec_t *vec, size_t pos,
  hyp_net_node_t *node)
{
	hyp_net_node_vec_chkcap(vec, pos + 1);
	vec->nodes[pos] = node;
	if (size <= pos)
	{
		size = pos + 1;
	}
}

static void hyp_net_node_vec_chkcap(hyp_net_node_vec_t vec, size_t cap)
{
	if (vec->capacity < cap)
	{
		vec->nodes = realloc(sizeof(hyp_net_node_t *) * cap)
		for (size_t i = vec->capacity; i < cap; i++)
		{
			vec->nodes[i] = NULL;
		}
		vec->capacity = cap;
	}
}

static void hyp_net_node_vec_append(hyp_net_node_vec_t *vec,
  hyp_net_node_t *node)
{
	hyp_net_node_vec_insert(vec, vec->size + 1, node);
}

hyp_network_t *hyp_net_create(size_t inputs, size_t neurons, size_t outputs)
{
	hyp_network_t *net = malloc(sizeof(hyp_network_t));
	net->inputs = malloc(sizeof(hyp_net_node_t *) * inputs);
	net->outputs = malloc(sizeof(hyp_net_node_t *) * outputs);
	net->neurons = malloc(sizeof(hyp_net_node_t *) * neurons);
	net->inputs_size = inputs;
	net->outputs_size = outputs;
	net->neurons_size = neurons;
	net->neurons_count = 0;
	for (size_t i = 0; i < inputs; i++)
	{
		net->inputs[i] = malloc(sizeof(hyp_net_node_t));
		net->inputs[i]->inputs = NULL;
		net->inputs[i]->outputs = hyp_net_node_vec_create(3);
		net->inputs[i]->neuron = NULL;
	}
	for (size_t i = 0; i < outputs; i++)
	{
		net->outputs[i] = malloc(sizeof(hyp_net_node_t));
		net->outputs[i]->inputs = hyp_net_node_vec_create(3);
		net->outputs[i]->outputs = NULL;
		net->outputs[i]->neuron = NULL;
	}
}

void hyp_net_free(hyp_network_t *net)
{
	for (size_t i = 0; i < net->outputs_size; i++)
	{
		hyp_net_node_vec_free(net->outputs[i]->inputs);
		free(net->outputs[i]);
	}
	free(net->outputs);
	for (size_t i = 0; i < net->inputs_size; i++)
	{
		hyp_net_node_vec_free(net->inputs[i]->outputs);
		free(net->inputs[i]);
	}
	free(net->inputs);
	for (size_t i = 0; i < net->neurons_count; i++)
	{
		hyp_net_node_vec_free(net->neurons[i]->inputs);
		hyp_net_node_vec_free(net->neurons[i]->outputs);
		hyp_neuron_free(net->neurons[i]->neuron);
		free(net->neurons[i]);
	}
	free(net->neurons);
	free(net);
}

size_t hyp_net_attach_neuron(hyp_network_t *net, neuron_t *n)
{
	hyp_net_node_t *node = malloc(sizeof(hyp_net_node_t));
	node->inputs = hyp_net_node_vec_create(n->input_count);
	node->outputs = hyp_net_node_vec_create(3);
	node->neuron = n;
	size_t id = net->neuron_count;
	net->neurons[id] = node;
	net->neuron_count++;
	return id;
}
