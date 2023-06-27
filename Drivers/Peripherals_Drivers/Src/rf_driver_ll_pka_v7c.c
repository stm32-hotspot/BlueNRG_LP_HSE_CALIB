/**
  ******************************************************************************
  * @file    rf_driver_ll_pka_v7c.c
  * @author  RF Application Team
  * @brief   PKA LL module driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "rf_driver_ll_pka_v7c.h"
#include "rf_driver_ll_bus.h"

#ifdef  USE_FULL_ASSERT
#include "rf_driver_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif

/** @addtogroup RF_DRIVER_LL_Driver
  * @{
  */

#if defined(PKA)

/** @addtogroup PKA_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup PKA_LL_Private_Macros PKA Private Constants
  * @{
  */
#define IS_LL_PKA_MODE(__VALUE__)     (((__VALUE__) == LL_PKA_MODE_MONTGOMERY_PARAM_MOD_EXP) ||\
                                      ((__VALUE__) == LL_PKA_MODE_MONTGOMERY_PARAM)          ||\
                                      ((__VALUE__) == LL_PKA_MODE_MODULAR_EXP)               ||\
                                      ((__VALUE__) == LL_PKA_MODE_MONTGOMERY_PARAM_ECC)      ||\
                                      ((__VALUE__) == LL_PKA_MODE_ECC_KP_PRIMITIVE)          ||\
                                      ((__VALUE__) == LL_PKA_MODE_ECDSA_SIGNATURE)           ||\
                                      ((__VALUE__) == LL_PKA_MODE_ECDSA_VERIFICATION)        ||\
                                      ((__VALUE__) == LL_PKA_MODE_POINT_CHECK)               ||\
                                      ((__VALUE__) == LL_PKA_MODE_RSA_CRT_EXP)               ||\
                                      ((__VALUE__) == LL_PKA_MODE_MODULAR_INV)               ||\
                                      ((__VALUE__) == LL_PKA_MODE_ARITHMETIC_ADD)            ||\
                                      ((__VALUE__) == LL_PKA_MODE_ARITHMETIC_SUB)            ||\
                                      ((__VALUE__) == LL_PKA_MODE_ARITHMETIC_MUL)            ||\
                                      ((__VALUE__) == LL_PKA_MODE_COMPARISON)                ||\
                                      ((__VALUE__) == LL_PKA_MODE_MODULAR_REDUC)             ||\
                                      ((__VALUE__) == LL_PKA_MODE_MODULAR_ADD)               ||\
                                      ((__VALUE__) == LL_PKA_MODE_MODULAR_SUB)               ||\
                                      ((__VALUE__) == LL_PKA_MODE_ECC_DOUBLE_BASE_LADDER)    ||\
                                      ((__VALUE__) == LL_PKA_MODE_ECC_COMPLETE_ADDITION)     ||\
                                      ((__VALUE__) == LL_PKA_MODE_MONTGOMERY_MUL))
/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/

#if PKA_OLD_API_NOT_USED
/**
  * @brief  Internal Utility for PKA key range check
  * @param  a: pka key
  *         b: reference key
  *         bufferSize: key size
  * @retval check result 
  */
static int rev_memcmp(uint8_t *a, const uint8_t *b, uint8_t  bufferSize)
{
    uint_fast8_t i = bufferSize;
    int retval = 0;

    do
    {
        i--;
        retval = (int)a[i] - (int)b[i];
        if (retval !=0)
        {
            break;
        }
    } while (i != 0U);

   return retval;
}
#endif

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PKA_LL_Exported_Functions
  * @{
  */

/** @addtogroup PKA_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize PKA registers (Registers restored to their default values).
  * @param  PKAx PKA Instance.
  * @retval ErrorStatus
  *          - SUCCESS: PKA registers are de-initialized
  *          - ERROR: PKA registers are not de-initialized
  */
ErrorStatus LL_PKA_DeInit(PKA_TypeDef *PKAx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_PKA_ALL_INSTANCE(PKAx));

  if (PKAx == PKA)
  {
    /* Force PKA reset */
    LL_AHB_ForceReset(LL_AHB_PERIPH_PKA);

    /* Release PKA reset */
    LL_AHB_ReleaseReset(LL_AHB_PERIPH_PKA);
  }
  else
  {
    status = ERROR;
  }

  return (status);
}

/**
  * @brief  Initialize PKA registers according to the specified parameters in PKA_InitStruct.
  * @param  PKAx PKA Instance.
  * @param  PKA_InitStruct pointer to a @ref LL_PKA_InitTypeDef structure
  *         that contains the configuration information for the specified PKA peripheral.
  * @retval ErrorStatus
  *          - SUCCESS: PKA registers are initialized according to PKA_InitStruct content
  *          - ERROR:   Not applicable
  */
ErrorStatus LL_PKA_Init(PKA_TypeDef *PKAx, LL_PKA_InitTypeDef *PKA_InitStruct)
{
  assert_param(IS_PKA_ALL_INSTANCE(PKAx));
  assert_param(IS_LL_PKA_MODE(PKA_InitStruct->Mode));

  LL_PKA_Config(PKAx, PKA_InitStruct->Mode);

  return (SUCCESS);
}

/**
  * @brief Set each @ref LL_PKA_InitTypeDef field to default value.
  * @param PKA_InitStruct pointer to a @ref LL_PKA_InitTypeDef structure
  *                       whose fields will be set to default values.
  * @retval None
  */
void LL_PKA_StructInit(LL_PKA_InitTypeDef *PKA_InitStruct)
{
  /* Reset PKA init structure parameters values */
  PKA_InitStruct->Mode       = LL_PKA_MODE_MONTGOMERY_PARAM_MOD_EXP;
}


#if defined CONFIG_DEVICE_BLUENRG_LPS

void LL_PKA_WriteSingleInput( uint32_t index, uint32_t word )
{
  /* Write the single word into PKA RAM */
  PKA_RAM->RAM[index] = word;
}

#endif

#if defined CONFIG_DEVICE_BLUENRG_LPS

void LL_PKA_WriteOperand( uint32_t index, int size, const uint32_t* in )
{
  uint32_t* pka_ram = (uint32_t*)&PKA_RAM->RAM[index];
  /* Write the input data into PKA RAM */
  for ( ; size > 0; size-- )
  {
    *pka_ram++ = *in++;
  }
  /* Write extra zeros into PKA RAM */
  *pka_ram = 0;
}

#endif

void LL_PKA_ReadResult( uint32_t index, int size, uint32_t* out )
{
  uint32_t* pka_ram = (uint32_t*)&PKA_RAM->RAM[index];
  /* Read from PKA RAM */
  for ( ; size > 0; size-- )
  {
    *out++ = *pka_ram++;
  }
}


#if defined CONFIG_DEVICE_BLUENRG_LPS

/** 
  * @brief  
  * @param  
  * @param  
  * 
  */
uint32_t LL_PKA_ReadSingleOutput( uint32_t index )
{
  /* Read a single word from PKA RAM */
  return PKA_RAM->RAM[index];
}


#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (PKA) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

