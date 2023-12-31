/**************************************************************************************************
*                                                                                                 *
* This file is part of BLASFEO.                                                                   *
*                                                                                                 *
* BLASFEO -- BLAS for embedded optimization.                                                      *
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

#include <blasfeo_common.h>
#include <blasfeo_d_blasfeo_api.h>



#define DOUBLE_PRECISION



#if ( defined(BLAS_API) & defined(MF_PANELMAJ) )
#define SYRK_LN blasfeo_cm_dsyrk_ln
#define SYRK_LT blasfeo_cm_dsyrk_lt
#define SYRK_UN blasfeo_cm_dsyrk_un
#define SYRK_UT blasfeo_cm_dsyrk_ut
#define SYRK3_LN blasfeo_cm_dsyrk3_ln
#define SYRK3_LT blasfeo_cm_dsyrk3_lt
#define SYRK3_UN blasfeo_cm_dsyrk3_un
#define SYRK3_UT blasfeo_cm_dsyrk3_ut
#define MAT blasfeo_cm_dmat
#else
#define SYRK_LN blasfeo_dsyrk_ln
#define SYRK_LT blasfeo_dsyrk_lt
#define SYRK_UN blasfeo_dsyrk_un
#define SYRK_UT blasfeo_dsyrk_ut
#define SYRK3_LN blasfeo_dsyrk3_ln
#define SYRK3_LT blasfeo_dsyrk3_lt
#define SYRK3_UN blasfeo_dsyrk3_un
#define SYRK3_UT blasfeo_dsyrk3_ut
#define MAT blasfeo_dmat
#endif
#define REAL double



#if defined(FORTRAN_BLAS_API)
#define SYRK dsyrk_
#else
#define SYRK blasfeo_blas_dsyrk
#endif




#include "xsyrk_ref.c"

