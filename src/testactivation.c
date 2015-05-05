/*******************************************************************************
 * This file contain a test of the activation module of the Hypatia AI system.
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

#include "activation.h"

#include <stdio.h>

int main(int argc, char const **argv)
{
	// should be 1
	double thresh_0 = hyp_act_threshold(0, NULL);
	// should be 1
	double thresh_1 = hyp_act_threshold(1, NULL);
	// should be 0
	double thresh_n1 = hyp_act_threshold(-1, NULL);
	
	// should be 0
	double signum_0 = hyp_act_signum(0, NULL);
	// should be 1
	double signum_1 = hyp_act_signum(1, NULL);
	// should be -1
	double signum_n1 = hyp_act_signum(-1, NULL);


	double slope = 1.5;
	double slopeptr
	// should be 
	double log_0 = hyp_act_log(0, NULL);

	double log_7 = hyp_act_log(7, &&slo

	return 0;
}
