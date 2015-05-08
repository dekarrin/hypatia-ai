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
	bool up = false;
	double thresh = 0.5;
	params_t *th_params = hyp_params_create(2);
	th_params->values[0] = &up;
	th_params->values[1] = &thresh;

	// should be 1
	double thresh_0 = hyp_act_threshold(0, NULL);
	// should be 1
	double thresh_1 = hyp_act_threshold(1, NULL);
	// should be 0
	double thresh_n1 = hyp_act_threshold(-1, NULL);
	// should be 0
	double thresh_n0_5 = hyp_act_threshold(0.5, th_params);
	th_params->values[0] = NULL;
	// should be 1
	double thresh_n0_5_u = hyp_act_threshold(0.5, th_params);
	
	// should be 0
	double signum_0 = hyp_act_signum(0, NULL);
	// should be 1
	double signum_1 = hyp_act_signum(1, NULL);
	// should be -1
	double signum_n1 = hyp_act_signum(-1, NULL);

	double slope = 1.5;
	params_t *params = hyp_params_create(1);
	params->values[0] = &slope;

	// should be 0.5
	double log_0 = hyp_act_logistic(0.0, NULL);
	// should be ~0.999972
	double log_7 = hyp_act_logistic(7.0, params);
	// should be ~0.0758581
	double log_n2_5 = hyp_act_logistic(-2.5, NULL);

	// should be 0
	double tanh_0 = hyp_act_tanh(0.0, NULL);
	// should be ~0.9999999999
	double tanh_7 = hyp_act_tanh(7.0, params);
	// should be ~-0.986614
	double tanh_n2_5 = hyp_act_tanh(-2.5, NULL);

	hyp_params_free(params);
	hyp_params_free(th_params);

	printf("Input : Output\n");
	printf("\n");
	printf("Threshold Function:\n");
	printf("  0, t = 1.0, >= :  %.6f\n", thresh_0);
	printf("  1, t = 1.0, >= :  %.6f\n", thresh_1);
	printf(" -1, t = 1.0, >= :  %.6f\n", thresh_n1);
	printf("0.5, t = 0.5, >  :  %.6f\n", thresh_n0_5);
	printf("0.5, t = 0.5, >= :  %.6f\n", thresh_n0_5_u);
	printf("\n");
	printf("Signum Function:\n");
	printf(" 0 :  %.6f\n", signum_0);
	printf(" 1 :  %.6f\n", signum_1);
	printf("-1 :  %.6f\n", signum_n1);
	printf("\n");
	printf("Logistic Function:\n");
	printf(" 0.0, v = 1.0 :  %.6f\n", log_0);
	printf(" 7.0, v = 1.5 :  %.6f\n", log_7);
	printf("-2.5, v = 1.0 :  %.6f\n", log_n2_5);
	printf("\n");
	printf("Tanh Function:\n");
	printf(" 0.0, v = 1.0 :  %.6f\n", tanh_0);
	printf(" 7.0, v = 1.5 :  %.6f\n", tanh_7);
	printf("-2.5, v = 1.0 :  %.6f\n", tanh_n2_5);

	return 0;
}
