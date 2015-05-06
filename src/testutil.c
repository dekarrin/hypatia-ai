/*******************************************************************************
 * This is a test of the util module of the Hypatia AI system.
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

#include "util.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const **argv)
{
	srand(4);
	double a1 = rand_range(-1, 1);
	double a2 = rand_range(0, 1);
	double a3 = rand_range(-3, -5);
	double a4 = rand_range(31, 35);

	printf("%.3f\n", a1);
	printf("%.3f\n", a2);
	printf("%.3f\n", a3);
	printf("%.3f\n", a4);
}
