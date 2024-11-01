/**************************************************************************
*  Copyright (c) 2013-2015 by Michael Fischer (www.emb4fun.de).
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*  
*  1. Redistributions of source code must retain the above copyright 
*     notice, this list of conditions and the following disclaimer.
*  2. Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the 
*     documentation and/or other materials provided with the distribution.
*  3. Neither the name of the author nor the names of its contributors may 
*     be used to endorse or promote products derived from this software 
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
*  THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
*  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
*  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
*  SUCH DAMAGE.
*
***************************************************************************
*  History:
*
*  03.10.2013  mifi  First Version, based on StarterWare v2.0.1.1
**************************************************************************/

/*=======================================================================*/
/*  Includes                                                             */
/*=======================================================================*/
#include <stdint.h>
#include "uartStdio.h"
#include "bl_copy.h"
#include "bl_platform.h"
#include "bl.h"

/******************************************************************************
**                    External Variable Declararions
*******************************************************************************/

extern char *deviceType;


/******************************************************************************
**                     Local Function Declararion
*******************************************************************************/

static void (*appEntry)();


/******************************************************************************
**                     Global Variable Definitions
*******************************************************************************/

unsigned int entryPoint = 0;
unsigned int DspEntryPoint = 0;

/*=======================================================================*/
/*  All code exported                                                    */
/*=======================================================================*/

/*************************************************************************/
/*  main                                                                 */
/*************************************************************************/
int main (void)
{
    // Configures PLL and DDR controller
    BlPlatformConfig();
  
    UARTPuts("StarterWare ", -1);
    UARTPuts(deviceType, -1);
    UARTPuts(" Boot Loader\n\r", -1);

    // Copies application from non-volatile flash memory to RAM
    ImageCopy();

    UARTPuts("Jumping to StarterWare Application...\r\n\n", -1);

    // Do any post-copy config before leaving bootloader
    BlPlatformConfigPostBoot();

    /* Giving control to the application */
    appEntry = (void (*)(void)) entryPoint;

    (*appEntry)( );

    return(0);
}

/*** EOF ***/