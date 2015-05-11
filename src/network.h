/*******************************************************************************
 * This is the header file for the artificial neural network module of the
 * Hypatia AI system.
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

#ifndef HYPATIA_NETWORK_H
#define HYPATIA_NETWORK_H

#include "neuron.h"

struct hyp_net_node;

typedef struct hyp_network
{
	size_t inputs_size;
	size_t outputs_size;
	hyp_net_node **inputs;
	hyp_net_node **hidden;
	hyp_net_node **outputs;
} hyp_network_t;

/**
 * Allocates a new artificial neural network. The network will have the
 * specified number of output and input nodes, and will have space for the given
 * number of neurons in the hidden layer.
 */
hyp_network_t *hyp_net_create(size_t inputs, size_t hidden, size_t outputs);

/**
 * Free memory in an artificial neural network. All neurons contained in the
 * network are also freed, though see the docs on hyp_neuron_free for
 * information regarding memory used in a neuron's activation function
 * compostion.
 */
void hyp_net_free(hyp_network_t *net);

/**
 * Adds a neuron to a neural network. This only adds it to the list of neurons
 * in the neural network; it does not link the neuron's input/output with any
 * other neurons.
 *
 * The ID of the neuron inside of the network is returned.
 */
size_t hyp_net_attach_neuron(hyp_network_t *net, neuron_t *n);

/**
 * Removes the neuron with the given neuron ID from a neural network. The neuron
 * is not freed. Any neurons that remain in the network with a higher neuron ID
 * than the one that was removed will have their ID decreased by one. Any links
 * to the neuron that was removed are reset.
 */
void hyp_net_remove_neuron(hyp_network_t *net, size_t id);

/**
 * Links the output of the neuron with ID n1 to an input of the neuron with ID
 * n2. The input that the first neuron is linked to is the first input that is
 * not already linked to a neuron.
 */
void hyp_net_link_neurons(hyp_network_t *net, size_t n1, size_t n2);

/**
 * Links an input node with ID in_id to the input of the neuron with ID n2. The
 * input that the input node is linked to is the first input that is not already
 * linked to a neuron.
 *
 * The ID of the input node is simply a zero-indexed incremental value; i.e. the
 * first input has ID 0, the second has ID 1, etc.
 */
void hyp_net_link_input(hyp_network_t *net, size_t in_id, size_t n2);

/**
 * Links the output of the neuron with ID n1 to the output node with ID out_id.
 *
 * The ID of the output node is simply a zero-indexed incremental value; i.e.
 * the first output has ID 0, the second has ID 1, etc.
 */
void hyp_net_link_output(hyp_network_t *net, size_t n1, size_t out_id);

/**
 * 
 */

#endif

