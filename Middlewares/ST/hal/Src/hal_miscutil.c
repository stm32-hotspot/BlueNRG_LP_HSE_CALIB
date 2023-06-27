/**
******************************************************************************
* @file    hal_miscutils.c 
* @author  AMG - RF Application Team
* @version V1.1.0
* @date    3-April-2018
* @brief   Miscellaneous utilities for interfacing to  HW
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2017 STMicroelectronics</center></h2>
******************************************************************************
*/ 
/* Includes ------------------------------------------------------------------*/
#include "rf_driver_ll_system.h"
#include "rf_driver_ll_utils.h"
#include "system_BlueNRG_LP.h"
#include "hal_miscutil.h"
#include "rf_driver_ll_pwr.h"
#include "rf_driver_ll_bus.h"

NO_INIT_SECTION(crash_info_t CrashInfoRam, ".crash_info_ram_vr");

/** @addtogroup BlueNRG_LP_Miscellaneous_Utilities
* @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined(RRM_LDO_ANA_ENG_RFD_LDO_TRANSFO_BYPASS)
uint8_t high_power = FALSE;
#endif

/*---------------------------------------------------------------------------*/

void HAL_GetPartInfo(PartInfoType *partInfo)
{ 
  uint32_t jtag_id;
  
  partInfo->die_id = DIE_SW_ID_UNKOWN;
  
  jtag_id = LL_SYSCFG_GetDeviceJTAG_ID();
  if(jtag_id == JTAG_ID_CODE_LP)
  {
    partInfo->die_id = DIE_SW_ID_BLUENRG_LP;
  }
  else if(jtag_id == JTAG_ID_CODE_LPS)
  {
    partInfo->die_id = DIE_SW_ID_BLUENRG_LPS;
  } 

  
  partInfo->die_major     =  LL_SYSCFG_GetDeviceVersion(); 
  partInfo->die_cut       =  LL_SYSCFG_GetDeviceRevision(); 
  partInfo->jtag_id_code  =  LL_SYSCFG_GetDeviceJTAG_ID(); // Duplicated
  partInfo->flash_size    =  (LL_GetFlashSize() + 1) * 4;

  if (LL_GetRAMSize() != LL_UTILS_RAMSIZE_24K) {
    partInfo->ram_size    =  (LL_GetRAMSize() + 1) * 16 * 1024;
  } else {
    partInfo->ram_size    =  24*1024;
  }

}

/**
 * @brief Get Crash Information utility
 */
void HAL_GetCrashInfo(crash_info_t *crashInfo)
{
  *crashInfo = CrashInfoRam;
  /* Reset crash info value */
  CrashInfoRam.signature = 0;
}
void HAL_CrashHandler(uint32_t msp, uint32_t signature)
{
  volatile uint32_t * crash_info = (volatile uint32_t *)&CrashInfoRam;
  register uint32_t reg_content;
  /* Init to zero the crash_info RAM locations */
  for (reg_content=0; reg_content<NMB_OF_EXCEP_RAM_WORD; reg_content++) {
    crash_info[reg_content] = 0;
  }
  /* Store Crash Signature */
  CrashInfoRam.signature = signature;
  /* Store SP register */
  CrashInfoRam.SP = msp;
  for (reg_content=2; reg_content<NMB_OF_EXCEP_RAM_WORD; reg_content++) {
    uint32_t *ptr = ((uint32_t *)msp)+(reg_content-2);
    if ((ptr >= ((uint32_t *)  _MEMORY_RAM_BEGIN_)) && 
        (ptr <= ((uint32_t *) _MEMORY_RAM_END_)))
      crash_info[reg_content] = *ptr;
  }
  NVIC_SystemReset();
}

void HAL_SetHighPower(FunctionalState state)
{
#if defined(RRM_LDO_ANA_ENG_RFD_LDO_TRANSFO_BYPASS)
  if(state != DISABLE)
  {
    if(high_power == FALSE)
    {
      high_power = TRUE;    
      
      LL_APB0_EnableClock(LL_APB0_PERIPH_SYSCFG);
      LL_SYSCFG_BLERXTX_SetTrigger(LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE, LL_SYSCFG_BLE_TX_EVENT);
      LL_SYSCFG_BLERXTX_SetType(LL_SYSCFG_BLERXTX_DET_TYPE_EDGE, LL_SYSCFG_BLE_TX_EVENT);
      LL_SYSCFG_BLERXTX_EnableIT(LL_SYSCFG_BLE_TX_EVENT);
      LL_SYSCFG_BLERXTX_ClearInterrupt(LL_SYSCFG_BLE_TX_EVENT);
      NVIC_EnableIRQ(BLE_SEQ_IRQn);
    }
  }
  else
  {
    if(high_power == TRUE)
    {
      high_power = FALSE;
      
      LL_SYSCFG_BLERXTX_DisableIT(LL_SYSCFG_BLE_TX_EVENT);
      NVIC_DisableIRQ(BLE_SEQ_IRQn);
      LL_SYSCFG_BLERXTX_ClearInterrupt(LL_SYSCFG_BLE_TX_EVENT);
    }
  }
#endif
  
  if (LL_PWR_IsEnabledSMPSPrechargeMode() || (LL_PWR_GetSMPSMode() == LL_PWR_NO_SMPS))
    return;

  /* Bypass SMPS */  
  LL_PWR_SetSMPSPrechargeMode(LL_PWR_SMPS_PRECHARGE);
  while(LL_PWR_IsSMPSReady());
  /* Change level */
  if(state != DISABLE)
  {
    LL_PWR_SetSMPSOutputLevel(LL_PWR_SMPS_OUTLVL_1V9);    
  }
  else
  {
    LL_PWR_SetSMPSOutputLevel(LL_PWR_SMPS_OUTLVL_1V4);
  }
  /* Disable bypass*/
  LL_PWR_SetSMPSPrechargeMode(LL_PWR_NO_SMPS_PRECHARGE);
  while(!LL_PWR_IsSMPSReady());  
}

void HAL_RXTX_SEQ_IRQHandler(void)
{
#if defined(RRM_LDO_ANA_ENG_RFD_LDO_TRANSFO_BYPASS)
  if(high_power == FALSE)
    return;

  if(LL_SYSCFG_BLERXTX_IsInterruptPending(LL_SYSCFG_BLE_TX_EVENT)){
    if(RRM->FSM_STATUS_DIG_OUT & RRM_FSM_STATUS_DIG_OUT_STATUS_4)
    {
      // Rising edge
      MODIFY_REG_FIELD(RRM->LDO_ANA_ENG, RRM_LDO_ANA_ENG_RFD_LDO_TRANSFO_BYPASS, 1);
    }
    else
    {
      // Falling edge
      MODIFY_REG_FIELD(RRM->LDO_ANA_ENG, RRM_LDO_ANA_ENG_RFD_LDO_TRANSFO_BYPASS, 0);
    }
    LL_SYSCFG_BLERXTX_ClearInterrupt(LL_SYSCFG_BLE_TX_EVENT);
  }
#endif
}



/** 
 *@
} */ /* End of group BlueNRG_LP_Miscellaneous_Utilities */
