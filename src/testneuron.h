/*******************************************************************************
 * This is the header file for the test of the neuron module of the Hypatia AI
 * system.
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

#ifndef HYPATIA_TESTNEURON_H
#define HYPATIA_TESTNEURON_H

#include "neuron.h"
#include "vector.h"

#define NAND_TRAINING_SIZE 4
#define MAX_ITERS 10

static neuron_t *hyp_testneuron_make_neuron();
static void hyp_testneuron_print_params(neuron_t const *, char const *);
static void hyp_testneuron_make_nand_trn_set(vector_t ***, double **);
static void hyp_testneuron_trn_nand(neuron_t *);
static void hyp_testneuron_free_nand_trn_set(vector_t **, double *);
static void hyp_testneuron_test_nand(neuron_t *);
static void hyp_testneuron_print_nand(double, double, double, double);

#endif

