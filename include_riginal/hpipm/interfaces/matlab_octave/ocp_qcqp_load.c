/**************************************************************************************************
*                                                                                                 *
* This file is part of HPIPM.                                                                     *
*                                                                                                 *
* HPIPM -- High-Performance Interior Point Method.                                                *
* Copyright (C) 2019 by Gianluca Frison.                                                          *
* Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              *
* All rights reserved.                                                                            *
*                                                                                                 *
* The 2-Clause BSD License                                                                        *
*                                                                                                 *
* Redistribution and use in source and binary forms, with or without                              *
* modification, are permitted provided that the following conditions are met:                     *
*                                                                                                 *
* 1. Redistributions of source code must retain the above copyright notice, this                  *
*    list of conditions and the following disclaimer.                                             *
* 2. Redistributions in binary form must reproduce the above copyright notice,                    *
*    this list of conditions and the following disclaimer in the documentation                    *
*    and/or other materials provided with the distribution.                                       *
*                                                                                                 *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND                 *
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED                   *
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                          *
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR                 *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES                  *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;                    *
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND                     *
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                      *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                   *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                    *
*                                                                                                 *
* Author: Gianluca Frison, gianluca.frison (at) imtek.uni-freiburg.de                             *
*                                                                                                 *
**************************************************************************************************/

// macro to string
#define STR(x) STR_AGAIN(x)
#define STR_AGAIN(x) #x

// system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// hpipm
#include "hpipm_d_ocp_qcqp_dim.h"
#include "hpipm_d_ocp_qcqp.h"
// mex
#include "mex.h"

// data
#include STR(QP_DATA_H)



void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
	{

//	printf("\nin ocp_qcqp_dim_load\n");

	mxArray *tmp_mat;
	long long *l_ptr;
	char *c_ptr;

	/* RHS */

	// dim
	l_ptr = mxGetData( prhs[0] );
	struct d_ocp_qcqp_dim *dim = (struct d_ocp_qcqp_dim *) *l_ptr;

	/* qp */

	hpipm_size_t qp_size = sizeof(struct d_ocp_qcqp) + d_ocp_qcqp_memsize(dim);
	void *qp_mem = malloc(qp_size);

	c_ptr = qp_mem;

	struct d_ocp_qcqp *qp = (struct d_ocp_qcqp *) c_ptr;
	c_ptr += sizeof(struct d_ocp_qcqp);

	d_ocp_qcqp_create(dim, qp, c_ptr);
	c_ptr += d_ocp_qcqp_memsize(dim);

//	d_ocp_qcqp_set_all(hA, hB, hb, hQ, hS, hR, hq, hr, hidxbx, hlbx, hubx, hidxbu, hlbu, hubu, hC, hD, hlg, hug, hZl, hZu, hzl, hzu, hidxs, hlls, hlus, qp);

	int ii;

	// dynamics
	for(ii=0; ii<N; ii++)
		{
		d_ocp_qcqp_set_A(ii, hA[ii], qp);
		d_ocp_qcqp_set_B(ii, hB[ii], qp);
		d_ocp_qcqp_set_b(ii, hb[ii], qp);
		}
	
	// cost
	for(ii=0; ii<=N; ii++)
		{
		d_ocp_qcqp_set_Q(ii, hQ[ii], qp);
		d_ocp_qcqp_set_S(ii, hS[ii], qp);
		d_ocp_qcqp_set_R(ii, hR[ii], qp);
		d_ocp_qcqp_set_q(ii, hq[ii], qp);
		d_ocp_qcqp_set_r(ii, hr[ii], qp);
		}
	
	// constraints
	for(ii=0; ii<=N; ii++)
		{
		d_ocp_qcqp_set_idxbx(ii, hidxbx, qp);
		d_ocp_qcqp_set_lbx(ii, hlbx, qp);
		d_ocp_qcqp_set_ubx(ii, hubx, qp);
		d_ocp_qcqp_set_idxbu(ii, hidxbu, qp);
		d_ocp_qcqp_set_lbu(ii, hlbu, qp);
		d_ocp_qcqp_set_ubu(ii, hubu, qp);
		d_ocp_qcqp_set_C(ii, hC, qp);
		d_ocp_qcqp_set_D(ii, hD, qp);
		d_ocp_qcqp_set_lg(ii, hlg, qp);
		d_ocp_qcqp_set_ug(ii, hug, qp);
		d_ocp_qcqp_set_Qq(ii, hQq, qp);
		d_ocp_qcqp_set_Sq(ii, hSq, qp);
		d_ocp_qcqp_set_Rq(ii, hRq, qp);
		d_ocp_qcqp_set_qq(ii, hqq, qp);
		d_ocp_qcqp_set_rq(ii, hrq, qp);
		d_ocp_qcqp_set_uq(ii, huq, qp);
		d_ocp_qcqp_set_uq_mask(ii, huq_mask, qp);
		}
	
	// TODO soft constr

	/* LHS */

	tmp_mat = mxCreateNumericMatrix(1, 1, mxINT64_CLASS, mxREAL);
	l_ptr = mxGetData(tmp_mat);
	l_ptr[0] = (long long) qp_mem;
	plhs[0] = tmp_mat;

	return;

	}
