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



#include <stdlib.h>
#include <stdio.h>

#include <blasfeo_target.h>
#include <blasfeo_common.h>
#include <blasfeo_d_aux.h>
#include <blasfeo_d_blas.h>

#include <hpipm_d_sim_rk.h>
#include <hpipm_d_sim_erk.h>
#include <hpipm_aux_mem.h>



#define BLASFEO_AXPY blasfeo_daxpy
#define BLASFEO_VEC blasfeo_dvec
#define REAL double
#define SIM_ERK_ARG d_sim_erk_arg
#define SIM_RK_DATA d_sim_rk_data
#define SIM_ERK_WS d_sim_erk_ws



#define SIM_ERK_ARG_MEMSIZE d_sim_erk_arg_memsize
#define SIM_ERK_ARG_CREATE d_sim_erk_arg_create
#define SIM_ERK_ARG_SET_ALL d_sim_erk_arg_set_all

#define SIM_ERK_WS_MEMSIZE d_sim_erk_ws_memsize
#define SIM_ERK_WS_CREATE d_sim_erk_ws_create
#define SIM_ERK_WS_SET_ALL d_sim_erk_ws_set_all
#define SIM_ERK_WS_SET_NF d_sim_erk_ws_set_nf
#define SIM_ERK_WS_SET_X d_sim_erk_ws_set_x
#define SIM_ERK_WS_SET_FS d_sim_erk_ws_set_fs
#define SIM_ERK_WS_GET_X d_sim_erk_ws_get_x
#define SIM_ERK_WS_SET_P d_sim_erk_ws_set_p
#define SIM_ERK_WS_SET_ODE d_sim_erk_ws_set_ode
#define SIM_ERK_WS_SET_VDE_FOR d_sim_erk_ws_set_vde_for
#define SIM_ERK_WS_SET_ODE_ARGS d_sim_erk_ws_set_ode_args
#define SIM_ERK_WS_GET_FS d_sim_erk_ws_get_fs
#define SIM_ERK_SOLVE d_sim_erk_solve



#include "x_sim_erk.c"
