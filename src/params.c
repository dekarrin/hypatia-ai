/*******************************************************************************
 * This is the implementation of the params module of Hypatia AI. It contains
 * functionality for passing generic parameters to functions.
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

#include "params.h"

#include <stdlib.h>

static bool hyp_params_available(params_t const *p, size_t index);

params_t *hyp_params_create(size_t size)
{
	params_t *p = malloc(sizeof(params_t));
	p->size = size;
	p->values = malloc(sizeof(void *) * size);
	return p;
}

void hyp_params_free(params_t *p)
{
	if (p != NULL)
	{
		free(p->values);
	}
	free(p);
}

bool hyp_params_bget(params_t const *params, size_t index, bool def)
{
	if (hyp_params_available(params, index))
	{
		return *((bool *)(params->values[index]));
	}
	else
	{
		return def;
	}
}

int hyp_params_iget(params_t const *params, size_t index, int def)
{
	if (hyp_params_available(params, index))
	{
		return *((int *)(params->values[index]));
	}
	else
	{
		return def;
	}
}

double hyp_params_dget(params_t const *params, size_t index, double def)
{
	if (hyp_params_available(params, index))
	{
		return *((double *)(params->values[index]));
	}
	else
	{
		return def;
	}
}

static bool hyp_params_available(params_t const *params, size_t index)
{
	bool avail = false;
	if (params != NULL)
	{
		if (index < params->size)
		{
			if ((params->values[index]) != NULL)
			{
				avail = true;
			}
		}
	}
	return avail;
}

