###################################################################################################
#                                                                                                 #
# This file is part of HPIPM.                                                                     #
#                                                                                                 #
# HPIPM -- High-Performance Interior Point Method.                                                #
# Copyright (C) 2019 by Gianluca Frison.                                                          #
# Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              #
# All rights reserved.                                                                            #
#                                                                                                 #
# The 2-Clause BSD License                                                                        #
#                                                                                                 #
# Redistribution and use in source and binary forms, with or without                              #
# modification, are permitted provided that the following conditions are met:                     #
#                                                                                                 #
# 1. Redistributions of source code must retain the above copyright notice, this                  #
#    list of conditions and the following disclaimer.                                             #
# 2. Redistributions in binary form must reproduce the above copyright notice,                    #
#    this list of conditions and the following disclaimer in the documentation                    #
#    and/or other materials provided with the distribution.                                       #
#                                                                                                 #
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND                 #
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED                   #
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                          #
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR                 #
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES                  #
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;                    #
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND                     #
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                      #
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                   #
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                    #
#                                                                                                 #
# Author: Gianluca Frison, gianluca.frison (at) imtek.uni-freiburg.de                             #
#                                                                                                 #
###################################################################################################


include ../Makefile.rule

OBJS =

ifeq ($(TARGET), GENERIC)
OBJS +=
endif

# double
OBJS += d_cond_aux.o
OBJS += d_cond.o
OBJS += d_part_cond.o
OBJS += d_cond_qcqp.o
OBJS += d_cast_qcqp.o
OBJS += d_part_cond_qcqp.o
# single
OBJS += s_cond_aux.o
OBJS += s_cond.o
OBJS += s_part_cond.o
OBJS += s_cond_qcqp.o
OBJS += s_cast_qcqp.o
OBJS += s_part_cond_qcqp.o

obj: $(OBJS)

clean:
	rm -f *.o
	rm -f *.s

d_cond_aux.o: d_cond_aux.c x_cond_aux.c
s_cond_aux.o: s_cond_aux.c x_cond_aux.c
d_cond.o: d_cond.c x_cond.c
s_cond.o: s_cond.c x_cond.c
d_part_cond.o: d_part_cond.c x_part_cond.c
s_part_cond.o: s_part_cond.c x_part_cond.c
d_cond_qcqp.o: d_cond_qcqp.c x_cond_qcqp.c
s_cond_qcqp.o: s_cond_qcqp.c x_cond_qcqp.c
d_cast_qcqp.o: d_cast_qcqp.c x_cast_qcqp.c
s_cast_qcqp.o: s_cast_qcqp.c x_cast_qcqp.c
d_part_cond_qcqp.o: d_part_cond_qcqp.c x_part_cond_qcqp.c
s_part_cond_qcqp.o: s_part_cond_qcqp.c x_part_cond_qcqp.c
