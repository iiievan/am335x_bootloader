/**
 *  \file   cp15.h
 *
 *  \brief  CP15 related function prototypes
 *
 *  This file contains the API prototypes for configuring CP15
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef __CP15_H
#define __CP15_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*
** Macros which can be passed to cp15_control_feature_disable/enable APIs
** as 'features'. Any, or an OR combination of the below macros can be
** passed to disable/enable the corresponding feature.
*/
#define CP15_CONTROL_TEXREMAP                  (0x10000000)
#define CP15_CONTROL_ACCESSFLAG                (0x20000000)
#define CP15_CONTROL_ALIGN_CHCK                (0x00000002)
#define CP15_CONTROL_MMU                       (0x00000001)
#define AM335X_VECTOR_BASE                     (0x4030FC00)

/*****************************************************************************/
/*
** API prototypes
*/
extern void cp15_aux_control_feature_enable(unsigned int enFlag);
extern void cp15_aux_control_feature_disable(unsigned int disFlag);
extern void cp15_D_cache_clean_buff(unsigned int bufPtr, unsigned int size);
extern void cp15_D_cache_clean_flush_buff(unsigned int bufPtr, unsigned int size);
extern void cp15_D_cache_flush_buff(unsigned int bufPtr, unsigned int size);
extern void cp15_I_cache_flush_buff(unsigned int bufPtr, unsigned int size);
extern void cp15_I_cache_disable(void);
extern void cp15_D_cache_disable(void);
extern void cp15_I_cache_enable(void);
extern void cp15_D_cache_enable(void);
extern void cp15_D_cache_clean_flush(void);
extern void cp15_D_cache_clean(void);
extern void cp15_D_cache_flush(void);
extern void cp15_I_cache_flush(void);
extern void cp15_TTB0_set(unsigned int ttb);
extern void cp15_TLB_invalidate(void);
extern void cp15_MMU_disable(void);
extern void cp15_MMU_enable(void);
extern void cp15_vector_base_addr_set(unsigned int addr);
extern void cp15_branch_predictor_invalidate(void);
extern void cp15_branch_prediction_enable(void);
extern void cp15_branch_prediction_disable(void);
extern void cp15_domain_access_client_set(void);
extern void cp15_control_feature_disable(unsigned int features);
extern void cp15_control_feature_enable(unsigned int features);
extern void cp15_TTB_ctl_TTB0_config(void);
extern unsigned int cp15_main_id_prim_part_num_get(void);

/*
** Memory Barrier API prototypes
*/
extern void cp15_ISB_barrier(void);              /* Instruction Synchronization Barrier */
extern void cp15_DMB_barrier(void);              /* Data Memory Barrier */
extern void cp15_DSB_barrier(void);              /* Data Synchronization Barrier */
extern void cp15_DSB_ISB_sync_barrier(void);     /* DSB + ISB combined */

#ifdef __cplusplus
}
#endif
#endif /* __CP15_H__ */