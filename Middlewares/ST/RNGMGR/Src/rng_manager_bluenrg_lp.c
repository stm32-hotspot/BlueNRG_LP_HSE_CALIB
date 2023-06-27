/**
******************************************************************************
* @file    rng_manager_bluenrg_lp.c
* @author  AMS - RF Application Team
* @brief   This file provides functions implementation for BlueNRG-LP RNG Manager.
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
#include "rng_manager.h"
#include "rf_driver_ll_rng.h"
#include "rf_driver_ll_bus.h"
#include "bluenrg_lpx.h"

/** @defgroup RNG_Manager_BlueNRG_LP  RNG Manager
* @{
*/

/** @defgroup RNG_Manager_BlueNRG_LP_TypesDefinitions Private Type Definitions
* @{
*/
/**
* @}
*/

/** @defgroup RNG_Manager_BlueNRG_LP_Private_Defines Private Defines
* @{
*/
/**
* @}
*/

/** @defgroup RNG_Manager_BlueNRG_LP_Private_Variables Private Variables
* @{
*/
/**
* @}
*/

/** @defgroup RNG_Manager_BlueNRG_LP_External_Variables External Variables
* @{
*/
/**
* @}
*/

/** @defgroup RNG_Manager_BlueNRG_LP_Public_Functions Public Functions
* @{
*/

RNGMGR_ResultStatus RNGMGR_Init(void)
{
  /* Peripheral clock enable */
  LL_AHB_EnableClock(LL_AHB_PERIPH_RNG);
  
  /* Initialize random numbers generation */
  LL_RNG_Enable(RNG);
    
  /* Wait for DRDY flag to be raised */
  while (!LL_RNG_IsActiveFlag_RNGRDY(RNG));
  
  /* Check if error occurs */
  if (  LL_RNG_IsActiveFlag_FAULT(RNG)  )
  {
    /* Clock or Seed Error detected. Set LED to blinking mode (Error type)*/
    return RNGMGR_ERROR;
  }
  
  /* Values of Generated Random numbers are now available in buffer array. */
  return RNGMGR_SUCCESS;
}


RNGMGR_ResultStatus RNGMGR_Deinit(void)
{
  /* Stop random numbers generation */
  LL_RNG_Disable(RNG);
  return RNGMGR_SUCCESS;
}


/**
 * @brief Provide a 16-bit true random number 
 * @param buffer: pointer to the random value returned
 * @param isr: 1 = The function is being called from  the radio isr context
 *             0 = The function is being called from the user context
 * @return error status: 0 = No error
 */
RNGMGR_ResultStatus RNGMGR_GetRandom16(uint32_t* buffer, uint8_t isr)
{
  /* Wait for RNGRDY signal */
  while (!LL_RNG_IsActiveFlag_RNGRDY(RNG));
  
  buffer[0] = (uint32_t)LL_RNG_ReadRandData16(RNG);
  
  return RNGMGR_SUCCESS;
}

/**
 * @brief Provide a 32-bit true random number
 * @param buffer: pointer to the random value returned
 *
 * @return error status: 0 = No error
 */
RNGMGR_ResultStatus RNGMGR_GetRandom32(uint32_t* buffer)
{
  uint16_t *buffer_16 = (uint16_t *) buffer;

  /* Wait for RNGRDY signal */
  while (!LL_RNG_IsActiveFlag_RNGRDY(RNG));

  buffer_16[0] = (uint16_t)LL_RNG_ReadRandData16(RNG);

/* Wait for RNGRDY signal */
  while (!LL_RNG_IsActiveFlag_RNGRDY(RNG));

  buffer_16[1] = (uint16_t)LL_RNG_ReadRandData16(RNG);

  return RNGMGR_SUCCESS;
}

/**
* @}
*/

/**
* @}
*/
