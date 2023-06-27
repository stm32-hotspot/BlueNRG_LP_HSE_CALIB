/**
******************************************************************************
* @file    aes_manager.c
* @author  AMS - RF Application Team
* @brief   This file provides weak functions for BlueNRG-LP AES manager
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
#include "aes_manager.h"
#include "rf_driver_ll_bus.h"


/** @defgroup AES_Manager  AES MANAGER
* @{
*/

/** @defgroup AESMGR_TypesDefinitions Private Type Definitions
* @{
*/
/**
* @}
*/

/** @defgroup AESMGR_Private_Defines Private Defines
* @{
*/
/**
* @}
*/

/** @defgroup AESMGR_Private_Macros Private Macros
* @{
*/
/**
* @}
*/

/** @defgroup AESMGR_Private_Variables Private Variables
* @{
*/  
/**
* @}
*/

/** @defgroup AESMGR_External_Variables External Variables
* @{
*/
/**
* @}
*/

/** @defgroup AESMGR_Private_FunctionPrototypes Private Function Prototypes
* @{
*/
/**
* @}
*/

/** @defgroup AESMGR_Public_Functions Public Functions
* @{
*/
WEAK_FUNCTION(AESMGR_ResultStatus AESMGR_Init(void))
{
  return AESMGR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

WEAK_FUNCTION(AESMGR_ResultStatus AESMGR_Deinit(void))
{
  return AESMGR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

/**
 * @brief Perform AES128 encryption on plainTextData using the given key
 * @param  plainTextData: pointer to the data to be encrypted (128 bits)
 * @param  key: encryption key (128 bits)
 * @param  isr:
 *                  1 = The function is being called from  the radio isr context
 *                  0 = The function is being called from the user context
 *
 * @retval encryptedData: pointer to the encrypted data returned     
 */
WEAK_FUNCTION(AESMGR_ResultStatus AESMGR_Encrypt(const uint32_t *plainTextData, const uint32_t *key, uint32_t *encryptedData, uint8_t isr))
{
  return AESMGR_SUCCESS;
  
  /* NOTE : This function should not be modified, the callback is implemented 
  in the dedicated board file */
}

/**
* @}
*/

  
