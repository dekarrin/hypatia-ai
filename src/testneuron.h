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

#define OUTPUT_EDGE "|"
#define OUTPUT_MIDDLE " % 7.3f "
#define SEP_EDGE "+"
#define SEP_MIDDLE "---------"
#define SEP_FMT SEP_EDGE SEP_MIDDLE
#define DATA_FMT OUTPUT_EDGE OUTPUT_MIDDLE

#include "neuron.h"

#include <stddef.h>

typedef struct iter_record
{
	vector_t *inputs;
	double bias;
	double expected;
	vector_t *initial_weights;
	double final_bias;
	vector_t *final_weights;
} iter_record_t;

iter_record_t *hyp_testneuron_create_record(size_t inputs);
void hyp_testneuron_free_record(iter_record_t *r);
iter_record_t **hyp_testneuron_create_records(size_t size, size_t inputs);
void hyp_testneuron_free_records(iter_record_t **rs, size_t size);
void hyp_testneuron_print_record(iter_record_t *r);
void hyp_testneuron_print_title(size_t inputs);
void hyp_testneuron_print_sep(size_t inputs);
void hyp_testneuron_print_records(iter_record_t **rs, size_t size);
char *hyp_testneuron_output_fmt(const char *middle, const char *edge,
  size_t inputs, char *buf);

#endif

