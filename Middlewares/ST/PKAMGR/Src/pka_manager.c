/**
******************************************************************************
* @file    pka_manager.c
* @author  AMS - RF Application Team
* @brief   This file provides weak functions for PKA Manager.
*
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "pka_manager.h"
#include "rng_manager.h"
#include "rf_driver_ll_bus.h"


/** @defgroup PKA_Manager  PKA Manager
* @{
*/



/** @defgroup PKA_Manager_BlueNRG_LP_Private_Variables Private Variables
* @{
*/

/**
* @}
*/

/** @defgroup PKA_Manager_TypesDefinitions Private Type Definitions
* @{
*/

/* Internal state of the PKA */
typedef enum
{
  PKAMGR_STATE_READY     =  0,
  PKAMGR_STATE_IDLE,
  PKAMGR_STATE_RESET,
  PKAMGR_STATE_BUSY
} PKAMGR_State;

/**
* @}
*/

/** @defgroup PKA_Manager_Private_Defines Private Defines
* @{
*/
#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
__disable_irq(); \
  /* Must be called in the same or in a lower scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)
/**
* @}
*/


/** @defgroup PKA_Manager_Private_Variables Private Variables
* @{
*/
static volatile uint32_t internalState = PKAMGR_STATE_RESET;
/**
* @}
*/


/** @defgroup PKA_Manager_Private_FunctionPrototypes Private Function Prototypes
* @{
*/
PKAMGR_ResultStatus PKAMGR_PrivateInit(void);

PKAMGR_ResultStatus PKAMGR_PrivateDeinit(void);

PKAMGR_ResultStatus PKAMGR_Status(void);
/**
* @}
*/

/** @defgroup PKA_Manager_Public_Functions Public Functions
* @{
*/
PKAMGR_ResultStatus PKAMGR_Init(void)
{
  PKAMGR_ResultStatus return_value = PKAMGR_ERROR;

  if(PKAMGR_PrivateInit() == PKAMGR_SUCCESS)
  {
    ATOMIC_SECTION_BEGIN();
    internalState = PKAMGR_STATE_IDLE;
    ATOMIC_SECTION_END();
    return_value = PKAMGR_SUCCESS;
  }
  return return_value;
}

PKAMGR_ResultStatus PKAMGR_Deinit(void)
{
  PKAMGR_ResultStatus return_value = PKAMGR_ERROR;

  if( PKAMGR_PrivateDeinit() == PKAMGR_SUCCESS)
  {
    ATOMIC_SECTION_BEGIN();
    internalState = PKAMGR_STATE_RESET;
    ATOMIC_SECTION_END();
    return_value = PKAMGR_SUCCESS;
  }

  return return_value;
}

PKAMGR_ResultStatus PKAMGR_SleepCheck(void)
{
  PKAMGR_ResultStatus return_value = PKAMGR_ERR_BUSY;

  if(internalState == PKAMGR_STATE_IDLE)
    return_value = PKAMGR_SUCCESS;

  return return_value;
}

PKAMGR_ResultStatus PKAMGR_Lock()
{
  PKAMGR_ResultStatus return_value = PKAMGR_SUCCESS;

  /* Only one consumer (Application layer or Stack) can use the PKA at the time */
  ATOMIC_SECTION_BEGIN();
  if(internalState != PKAMGR_STATE_IDLE)
  {
    return_value = PKAMGR_ERR_BUSY;
  }
  else
  {
    /* Lock mechanism to access concurrently at the PKA resource */
    internalState = PKAMGR_STATE_BUSY;
  }
  ATOMIC_SECTION_END();

  return return_value;
}

PKAMGR_ResultStatus PKAMGR_Unlock()
{
  PKAMGR_ResultStatus return_value = PKAMGR_SUCCESS;

  /* Only one consumer (Application layer or Stack) can use the PKA at the time */
  ATOMIC_SECTION_BEGIN();
  if(internalState != PKAMGR_STATE_BUSY)
  {
    return_value = PKAMGR_ERR_BUSY;
  }
  else
  {
    /* Unlock mechanism to access concurrently at the PKA resource */
    internalState = PKAMGR_STATE_IDLE;
  }
  ATOMIC_SECTION_END();
  
  return return_value;
}


PKAMGR_ResultStatus PKAMGR_StartP256PublicKeyGeneration(PKAMGR_funcCB funcCB)
{
  uint32_t secretKey[8] = {0};
  uint8_t i;
  
  for (i=0; i<8; i++)
    RNGMGR_GetRandom32(&secretKey[i]);
  
  return PKAMGR_StartP256DHkeyGeneration(secretKey, (uint32_t *)&PKAStartPoint[0], funcCB);
}  


WEAK_FUNCTION(PKAMGR_ResultStatus PKAMGR_StartP256DHkeyGeneration(uint32_t *secretKey, uint32_t *publicKey, PKAMGR_funcCB funcCB))
{
  (void) secretKey;                                 /* To avoid gcc/g++ warnings */
  (void) publicKey;                                 /* To avoid gcc/g++ warnings */
  (void) funcCB;                                    /* To avoid gcc/g++ warnings */
  return PKAMGR_SUCCESS;

  /* NOTE : This function should not be modified, the callback is implemented
  in the dedicated board file */
}

WEAK_FUNCTION(PKAMGR_ResultStatus PKAMGR_PrivateInit(void))
{
  return PKAMGR_SUCCESS;
}

WEAK_FUNCTION(PKAMGR_ResultStatus PKAMGR_PrivateDeinit(void))
{
  return PKAMGR_SUCCESS;
}

WEAK_FUNCTION(PKAMGR_ResultStatus PKAMGR_Status(void))
{
  return PKAMGR_SUCCESS;
}


/**
* @}
*/

/**
* @}
*/
