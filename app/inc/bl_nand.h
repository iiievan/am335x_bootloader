/**
 * \file  bl_nand.h
 *
 * \brief NAND functions used inside the bootloader
 *
 * This file contains functions for NAND Initialization
 */

/*
* Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
*
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
*/

#ifndef __BL_NAND_H__
#define __BL_NAND_H__

#include "nandlib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _nandbootheader_
{
    unsigned int magicNum;    
    unsigned int entryPoint;  
    unsigned int numPage;
    unsigned int block;
    unsigned int page; 
    unsigned int ldAddress;
}
BL_NAND_Header;

/******************************************************************************
**                    Internal Macro Definitions
*******************************************************************************/


/******************************************************************************
**                    External Function Declarations 
*******************************************************************************/
extern NandInfo_t *BL_NAND_Configure(void);
extern void BlNANDReadFlash( NandInfo_t *nandInfo,
                             unsigned int flashAddr,
                             unsigned int size,
                             unsigned char *destAddr);

#ifdef __cplusplus
}
#endif
#endif    // __BL_NAND_H__

