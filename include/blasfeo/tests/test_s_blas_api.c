/**************************************************************************************************
*                                                                                                 *
* This file is part of BLASFEO.                                                                   *
*                                                                                                 *
* BLASFEO -- BLAS For Embedded Optimization.                                                      *
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

#include <stdlib.h>
#include <stdio.h>

#include "../include/blasfeo_target.h"
#include "../include/blasfeo_common.h"
#include "../include/blasfeo_timing.h"
#include "../include/blasfeo_s_aux.h"
#include "../include/blasfeo_s_aux_ext_dep.h"
#include "../include/blasfeo_s_kernel.h"
#include "../include/blasfeo_s_blas.h"

#include "../include/s_blas.h"



//float cblas_sdot(int, float*, int, float*, int);



int main()
	{

#if !defined(BLAS_API)
	printf("\nRecompile with BLAS_API=1 to run this test!\n\n");
	exit(1);
#endif

	int n = 16;

	int ii;

	float *A = malloc(n*n*sizeof(float));
	for(ii=0; ii<n*n; ii++)
		A[ii] = ii+1;
	int lda = n;
//	s_print_mat(n, n, A, n);

	float *B = malloc(n*n*sizeof(float));
	for(ii=0; ii<n*n; ii++)
		B[ii] = -0.0;
	for(ii=0; ii<n; ii++)
		B[ii*(n+1)] = 1.0;
	int ldb = n;
//	s_print_mat(n, n, B, ldb);

	float *C = malloc(n*n*sizeof(float));
	for(ii=0; ii<n*n; ii++)
		C[ii] = -1;
	int ldc = n;
//	s_print_mat(n, n, C, ldc);

	float *C2 = malloc(n*n*sizeof(float));
	for(ii=0; ii<n*n; ii++)
		C2[ii] = -1;
//	int ldc = n;
//	s_print_mat(n, n, C, ldc);

	float *D = malloc(n*n*sizeof(float));
	for(ii=0; ii<n*n; ii++)
		D[ii] = -1;
	int ldd = n;
//	s_print_mat(n, n, C, ldc);

	int *ipiv = malloc(n*sizeof(int));


	int bs = 4;

	float d_0 = 0.0;
	float d_1 = 1.0;

	int i_1 = 1;

	char c_l = 'l';
	char c_n = 'n';
	char c_r = 'r';
	char c_t = 't';
	char c_u = 'u';

	float alpha = 2.0;
	float beta = 1.0;

	char ta = 'n';
	char tb = 'n';
	char uplo = 'u';
	int info = 0;

	int m0 = n;
	int n0 = n;
	int k0 = n;



//	for(ii=0; ii<n*n; ii++) D[ii] = B[ii];
//	blasfeo_dsyrk(&c_l, &c_n, &n, &n, &d_1, A, &n, &d_1, D, &n);
//	blasfeo_dpotrf(&c_l, &n, D, &n, &info);
//	dsyrk_(&c_u, &c_n, &n, &n, &d_1, A, &n, &d_1, D, &n);
//	dpotrf_(&c_u, &n, D, &n, &info);
//	s_print_mat(n, n, D, n);
//	return 0;
	s_print_mat(n, n, A, n);


	// blas

	printf("\nBLAS\n");

	for(ii=0; ii<n*n; ii++) C[ii] = -1;

#if 0
//	dgemm_(&ta, &tb, &m0, &n0, &k0, &alpha, A, &n, B, &n, &beta, C, &n);
	for(ii=0; ii<n*n; ii++) C[ii] = B[ii];
	for(ii=0; ii<n*n; ii++) D[ii] = B[ii];
	dgemm_(&ta, &tb, &n, &n, &n, &alpha, A, &n, A, &n, &beta, C, &n);
//	dpotrf_(&c_l, &m0, C, &n, &info);
	dposv_(&c_u, &m0, &n0, C, &n, D, &n, &info);
	s_print_mat(n, n, C, ldc);
	s_print_mat(n, n, D, ldd);
#endif

#if 1
	sgemm_(&c_t, &c_t, &m0, &n0, &k0, &alpha, B, &n, A, &n, &beta, C, &n);
#endif

#if 0
	dsyrk_(&c_u, &c_t, &m0, &k0, &alpha, A, &n, &beta, C, &n);
#endif

#if 0
	for(ii=0; ii<n*n;  ii++) C[ii] = B[ii];
//	strsm_(&c_l, &c_l, &c_n, &c_n, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_l, &c_l, &c_n, &c_u, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_l, &c_l, &c_t, &c_n, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_l, &c_l, &c_t, &c_u, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_l, &c_u, &c_n, &c_n, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_l, &c_u, &c_n, &c_u, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_l, &c_u, &c_t, &c_n, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_l, &c_u, &c_t, &c_u, &m0, &n0, &alpha, D, &n, C, &n);
	strsm_(&c_r, &c_l, &c_n, &c_n, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_r, &c_l, &c_n, &c_u, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_r, &c_l, &c_t, &c_n, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_r, &c_l, &c_t, &c_u, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_r, &c_u, &c_n, &c_n, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_r, &c_u, &c_n, &c_u, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_r, &c_u, &c_t, &c_n, &m0, &n0, &alpha, D, &n, C, &n);
//	strsm_(&c_r, &c_u, &c_t, &c_u, &m0, &n0, &alpha, D, &n, C, &n);
#endif

#if 0
	for(ii=0; ii<n*n;  ii++) C[ii] = A[ii];
	dtrmm_(&c_l, &c_l, &c_n, &c_n, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_l, &c_l, &c_n, &c_u, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_l, &c_l, &c_t, &c_n, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_l, &c_l, &c_t, &c_u, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_l, &c_u, &c_n, &c_n, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_l, &c_u, &c_n, &c_u, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_l, &c_u, &c_t, &c_n, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_l, &c_u, &c_t, &c_u, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_r, &c_l, &c_n, &c_n, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_r, &c_l, &c_n, &c_u, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_r, &c_l, &c_t, &c_n, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_r, &c_l, &c_t, &c_u, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_r, &c_u, &c_n, &c_n, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_r, &c_u, &c_n, &c_u, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_r, &c_u, &c_t, &c_n, &m0, &n0, &alpha, A, &n, C, &n);
//	dtrmm_(&c_r, &c_u, &c_t, &c_u, &m0, &n0, &alpha, A, &n, C, &n);
#endif

#if 0
	for(ii=0; ii<n*n; ii++) C[ii] = B[ii];
	for(ii=0; ii<n*n; ii++) D[ii] = B[ii];
	dgemm_(&c_n, &c_t, &n, &n, &n, &d_1, A, &n, A, &n, &d_1, C, &n);
	dgetrf_(&m0, &n0, C, &n, ipiv, &info);
//	dgetrs_(&c_t, &m0, &n0, C, &n, ipiv, D, &n, &info);
//	dgesv_(&m0, &n0, C, &n, ipiv, D, &n, &info);
	int_print_mat(1, n, ipiv, 1);
	s_print_mat(n, n, C, ldc);
//	s_print_mat(n, n, D, ldd);
#endif

//	int n1 = n-1;
#if 0
	C[0] = sdot_(&n, A, &i_1, A, &i_1);
//	C[0] = sdot_(&n, A, &n, A, &n);
//	C[0] = cblas_sdot(n, A, i_1, A, i_1);
#endif

#if 0
	for(ii=0; ii<n; ii++) C[ii] = A[ii];
	saxpy_(&n, &d_1, A, &i_1, C, &i_1);
#endif

//	printf("\ninfo %d\n", info);
//	s_print_mat(n, n, A, lda);
//	s_print_mat(n, n, B, ldb);
	s_print_mat(n, n, C, ldc);
//	s_print_mat(n, n, D, ldd);

#if 0
	for(ii=0; ii<globm*globn; ii++)
		C[ii] = globA[ii];
	s_print_mat(globm, globn, C, globm);
	dgetrf_(&globm, &globn, C, &globm, ipiv, &info);
	s_print_mat(globm, globn, C, globm);
	int_print_mat(1, n, ipiv, 1);
#endif


	// blasfeo blas

	printf("\nBLASFEO BLAS API\n");

	for(ii=0; ii<n*n; ii++) C2[ii] = -1;

#if 0
//	blasfeo_dgemm(&ta, &tb, &m0, &n0, &k0, &alpha, A, &n, B, &n, &beta, C, &n);
	for(ii=0; ii<n*n; ii++) C[ii] = B[ii];
	for(ii=0; ii<n*n; ii++) D[ii] = B[ii];
	blasfeo_dgemm(&ta, &tb, &n, &n, &n, &alpha, A, &n, A, &n, &beta, C, &n);
//	blasfeo_dpotrf(&c_l, &m0, C, &n, &info);
	blasfeo_dposv(&c_u, &m0, &n0, C, &n, D, &n, &info);
	s_print_mat(n, n, C, ldc);
	s_print_mat(n, n, D, ldd);
#endif

#if 1
//	blas_sgemm(&c_t, &c_t, &m0, &n0, &k0, &alpha, B, &n, A, &n, &beta, C2, &n);
	blasfeo_sgemm(c_t, c_t, m0, n0, k0, alpha, B, n, A, n, beta, C2, n, C2, n);
#endif

#if 0
	blasfeo_dsyrk(&c_u, &c_t, &m0, &k0, &alpha, A, &n, &beta, C, &n);
#endif

#if 0
	for(ii=0; ii<n*n;  ii++) C2[ii] = B[ii];
//	blasfeo_strsm(&c_l, &c_l, &c_n, &c_n, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_l, &c_l, &c_n, &c_u, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_l, &c_l, &c_t, &c_n, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_l, &c_l, &c_t, &c_u, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_l, &c_u, &c_n, &c_n, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_l, &c_u, &c_n, &c_u, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_l, &c_u, &c_t, &c_n, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_l, &c_u, &c_t, &c_u, &m0, &n0, &alpha, D, &n, C2, &n);
	blasfeo_strsm(&c_r, &c_l, &c_n, &c_n, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_r, &c_l, &c_n, &c_u, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_r, &c_l, &c_t, &c_n, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_r, &c_l, &c_t, &c_u, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_r, &c_u, &c_n, &c_n, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_r, &c_u, &c_n, &c_u, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_r, &c_u, &c_t, &c_n, &m0, &n0, &alpha, D, &n, C2, &n);
//	blasfeo_strsm(&c_r, &c_u, &c_t, &c_u, &m0, &n0, &alpha, D, &n, C2, &n);
#endif

#if 0
	for(ii=0; ii<n*n;  ii++) C2[ii] = A[ii];
	blasfeo_dtrmm(&c_l, &c_l, &c_n, &c_n, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_l, &c_l, &c_n, &c_u, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_l, &c_l, &c_t, &c_n, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_l, &c_l, &c_t, &c_u, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_l, &c_u, &c_n, &c_n, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_l, &c_u, &c_n, &c_u, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_l, &c_u, &c_t, &c_n, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_l, &c_u, &c_t, &c_u, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_r, &c_l, &c_n, &c_n, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_r, &c_l, &c_n, &c_u, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_r, &c_l, &c_t, &c_n, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_r, &c_l, &c_t, &c_u, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_r, &c_u, &c_n, &c_n, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_r, &c_u, &c_n, &c_u, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_r, &c_u, &c_t, &c_n, &m0, &n0, &alpha, A, &n, C2, &n);
//	blasfeo_dtrmm(&c_r, &c_u, &c_t, &c_u, &m0, &n0, &alpha, A, &n, C2, &n);
#endif

#if 0
	for(ii=0; ii<n*n; ii++) C[ii] = B[ii];
	for(ii=0; ii<n*n; ii++) D[ii] = B[ii];
	blasfeo_dgemm(&c_n, &c_t, &n, &n, &n, &d_1, A, &n, A, &n, &d_1, C, &n);
	blasfeo_dgetrf(&m0, &n0, C, &n, ipiv, &info);
//	blasfeo_dgetrs(&c_t, &m0, &n0, C, &n, ipiv, D, &n, &info);
//	blasfeo_dgesv(&m0, &n0, C, &n, ipiv, D, &n, &info);
	int_print_mat(1, n, ipiv, 1);
	s_print_mat(n, n, C, ldc);
//	s_print_mat(n, n, D, ldd);
#endif

#if 0
	C2[0] = blasfeo_sdot_blas(&n, A, &i_1, A, &i_1);
//	C2[0] = blasfeo_sdot_blas(&n, A, &n, A, &n);
#endif

#if 0
	for(ii=0; ii<n; ii++) C2[ii] = A[ii];
	blasfeo_saxpy_blas(&n, &d_1, A, &i_1, C2, &i_1);
#endif

//	printf("\ninfo %d\n", info);
//	s_print_mat(n, n, A, lda);
//	s_print_mat(n, n, B, ldb);
	s_print_mat(n, n, C2, ldc);
//	s_print_mat(n, n, D, ldd);

#if 0
	for(ii=0; ii<globm*globn; ii++)
		C[ii] = globA[ii];
	s_print_mat(globm, globn, C, globm);
	blasfeo_dgetrf(&globm, &globn, C, &globm, ipiv, &info);
	s_print_mat(globm, globn, C, globm);
	int_print_mat(1, n, ipiv, 1);
#endif

	// compute and print difference
	printf("\nerror\n");
	for(ii=0; ii<n*n; ii++)
		C2[ii] -= C[ii];

	s_print_mat(n, n, C2, ldc);

	// free memory

	free(A);
	free(B);
	free(C);
	free(C2);
	free(D);
	free(ipiv);


	// return

	return 0;

	}

