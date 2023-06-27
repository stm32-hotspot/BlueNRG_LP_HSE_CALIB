/******************** (C) COPYRIGHT 2021 STMicroelectronics ********************
* File Name          : system_BlueNRG_LP.c
* Author             : AMG - RF Application team
* Version            : V1.0.0
* Date               : 22-November-2021
* Description        : BlueNRG-LP Low Level Init function
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lpx.h"
#include "system_BlueNRG_LP.h"
#include "rf_driver_ll_rcc.h"
#include "rf_driver_ll_pwr.h"
#include "rf_driver_ll_flash.h"
#include "rf_driver_ll_bus.h"
#include "rf_driver_ll_system.h"

/* Private constants ---------------------------------------------------------*/

#ifndef CONFIG_NUM_MAX_LINKS
#define CONFIG_NUM_MAX_LINKS 8
#endif 

#define SYSCLK_EQUAL_BLECLK          0x28
#define SYSCLK_DOUBLE_BLECLK         0x29
#define SYSCLK_FOURFOLD_BLECLK       0x2A

#define AHB_STALLED   0x08

/* TRIMMING Defines */
#define VALIDITY_TAG 0xFCBCECCC

#define VALIDITY_LOCATION    0x10001EF8
#define TRIMMING_LOCATION    0x10001EE4
#define MR_TRIMMING_LOCATION 0x10001EE8

#define MAIN_REGULATOR_TRIM_Pos (0)
#define MAIN_REGULATOR_TRIM_Msk (0x0F << MAIN_REGULATOR_TRIM_Pos)
#define SMPS_TRIM_Pos           (4)
#define SMPS_TRIM_Msk           (0x07 << SMPS_TRIM_Pos)
#define LSI_LPMU_TRIM_Pos       (8)
#define LSI_LPMU_TRIM_Msk       (0x0F << LSI_LPMU_TRIM_Pos)
#define LSI_BW_TRIM_Pos         (12)
#define LSI_BW_TRIM_Msk         (0x0F << LSI_BW_TRIM_Pos)
#define HSI_TRIM_Pos            (16)
#define HSI_TRIM_Msk            (0x3F << HSI_TRIM_Pos)

#define MR_BLE_IBIAS_TRIM_Pos         (8)
#define MR_BLE_IBIAS_TRIM_Msk         (0x0F << MR_BLE_IBIAS_TRIM_Pos)
#define MR_BLE_IPTAT_TRIM_Pos         (12)
#define MR_BLE_IPTAT_TRIM_Msk         (0x0F << MR_BLE_IPTAT_TRIM_Pos)
#define MR_BLE_VBG_TRIM_Pos           (16)
#define MR_BLE_VBG_TRIM_Msk           (0x0F << MR_BLE_VBG_TRIM_Pos)
#define MR_BLE_RXADC_DELAY_I_TRIM_Pos (20)
#define MR_BLE_RXADC_DELAY_I_TRIM_Msk (0x07 << MR_BLE_RXADC_DELAY_I_TRIM_Pos)
#define MR_BLE_RXADC_DELAY_Q_TRIM_Pos (24)
#define MR_BLE_RXADC_DELAY_Q_TRIM_Msk (0x07 << MR_BLE_RXADC_DELAY_Q_TRIM_Pos)

/* AGC Configuration */
#define AGC_THR0 (0x0A)
#define AGC_THR1 (0x04)
#define AGC_ATT0 (0x00)
#define AGC_ATT1 (0x10)
#define AGC_ATT2 (0x20)
#define AGC_ATT3 (0x30)
#define AGC_ATT4 (0x38)
#define AGC_ATT5 (0x39)
#define AGC_ATT6 (0x3A)
#define AGC_ATT7 (0x3B)
#define AGC_ATT8 (0x3C)
#define AGC_ATT9 (0x3D)
/* AFC Configuration */
#define AFC_DELAY_BEFORE    (0x05)
#define AFC_DELAY_AFTER     (0x05)   
#define CR_GAIN_BEFORE      (0x06)
#define CR_GAIN_AFTER       (0x06)
#define CR_LR_GAIN_BEFORE   (0x05)
#define CR_LR_GAIN_AFTER    (0x05)
#define LR_RSSI_THR         (0x1D)
#define LR_PD_THR           (0x59)
#define LR_AAC_THR          (0x32)
/* Fine tuning values for antenna switching and IQ samplig */
#define RX_TIME_TO_SAMPLE   (0x1F)
#define RX_TIME_TO_SWITCH   (0x09)


/* Private types -------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
uint32_t SystemCoreClock  = 64000000U; /*CPU: HSI clock after startup (64MHz)*/

/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t SmpsTrimConfig(void);
static uint8_t LSConfig(void);

/* Exported function prototypes -----------------------------------------------*/

/* Exported variables ---------------------------------------------------------*/
NO_INIT_SECTION(REQUIRED(RAM_VR_TypeDef RAM_VR), ".ram_vr");

/* BLUE RAM, reserved for radio communication. Not usable from the application */
SECTION(".bss.__blue_RAM")
#if defined(CONFIG_DEVICE_BLUENRG_LPS)
REQUIRED(uint8_t __blue_RAM[CONFIG_NUM_MAX_LINKS*92+28]) = {0,};
#else /* BlueNRG_LP */
REQUIRED(uint8_t __blue_RAM[CONFIG_NUM_MAX_LINKS*80+28]) = {0,};
#endif


/*************************************************************************************
 **
 ** Should add all the variable to manage the Context restore and OTA procedures!!!!!!!! 
 **
 **************************************************************************************/
/* Exported function prototypes ---------------------------------------------*/


/**
  * @brief System Timer timeout configuration
  * @param system_clock System Clock Frequency
  * @param timeout Timeout expressed in ms (max (2**24)/(system_clock/1000))
  * @param enable TRUE enables the System Timer, FALSE disable the System Timer
  * @retval None
  */
void SystemTimer_TimeoutConfig(uint32_t system_clock_freq, uint32_t timeout, uint8_t enable)
{
  if (enable) {
  SysTick->LOAD  = (uint32_t)(((system_clock_freq/1000) - 1UL)*timeout);                         /* set reload register */
  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
  } else {
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;    
  }
}

/**
  * @brief System Timer Timeout Expired information
  * @retval True if the timout configured with the SystemTimer_TimeoutConfig() 
  *         is expired, FALSE otherwise
  */                               
uint8_t SystemTimer_TimeoutExpired(void)
{
  if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
    return TRUE;
  
  return FALSE;
}

/**
  * @brief Wait for a peripheral to be ready or not.
  *
  * This function waits until the value returned by the checking function, i.e.
  * ready_func(), returns the specified value. The function returns also after
  * the given timeout.
  * @param timeout_ms Interval (in milliseconds) after which the function will
  *        returns even if the checking function has not returned the desired
  *        value.
  * @param ready_func Pointer to the function checking for the readiness of a
  *        peripheral.
  * @param ready_val The SystemReadyWait() function returns tot he caller after
  *        the ready_func() has returned the value specified in ready_val.
  * @retval TRUE if the ready_func() returned the value specified in ready_val
  *         before the given timeout. It returns FALSE if the timeout expired.
  */ 
uint8_t SystemReadyWait(uint32_t timeout_ms, uint32_t (*ready_func)(void), uint32_t ready_val)
{
  uint8_t ret_val = TRUE;
  
  SystemTimer_TimeoutConfig(SystemCoreClock, timeout_ms, TRUE);
  
  while((*ready_func)() != ready_val) 
  {
    if (SystemTimer_TimeoutExpired()) {
      ret_val = FALSE;
      break;
    }
  }
  SystemTimer_TimeoutConfig(0, 0, FALSE);
  
  return ret_val;
}

/**
  * @brief  SMPS and Trimming value Configuration 
  */
static uint8_t SmpsTrimConfig(void)
{
  uint8_t ret_val=SUCCESS;
  uint32_t main_regulator, smps_out_voltage, lsi_bw, hsi_calib;
  uint8_t eng_lsi_bw_flag;
#ifdef CONFIG_DEVICE_BLUENRG_LP
  uint32_t lsi_lpmu;
#endif /* CONFIG_DEVICE_BLUENRG_LP */

#ifndef CONFIG_HW_SMPS_NONE
  /* After reset wait until SMPS is ready */
  
  if(SystemReadyWait(200, LL_PWR_IsSMPSReady, 1) == FALSE)
  {
    ret_val = SYSTEM_CONFIG_SMPS_READY_ERROR;
    return ret_val;
  }
#endif
  
  /* Configure SMPS BOM */
#ifdef CONFIG_HW_SMPS_10uH
  LL_PWR_SetSMPSBOM(LL_PWR_SMPS_BOM3);
  /* SMPS clock 4 MHz configuration */
  LL_RCC_SetSMPSPrescaler(LL_RCC_SMPS_DIV_4);
#elif defined(CONFIG_HW_SMPS_2_2uH)
  LL_PWR_SetSMPSBOM(LL_PWR_SMPS_BOM2);
  /* SMPS clock 8 MHz configuration  */
  LL_RCC_SetSMPSPrescaler(LL_RCC_SMPS_DIV_2);
#elif defined(CONFIG_HW_SMPS_1_5uH)
  LL_PWR_SetSMPSBOM(LL_PWR_SMPS_BOM1);
    /* SMPS clock 8 MHz configuration  */
  LL_RCC_SetSMPSPrescaler(LL_RCC_SMPS_DIV_2);
#elif defined(CONFIG_HW_SMPS_NONE)
  /* SMPS NONE configuration will be done after the trimming configuration values */
#else
#ifndef SUPPRESS_CONFIG_HW_WARNINGS
	#warning "No SMPS Configuration!!!"
#endif
#endif

  /* Retrieve Trimming values from engineering flash locations */
  if (*(volatile uint32_t*)VALIDITY_LOCATION == VALIDITY_TAG) {
    main_regulator    = ((*(volatile uint32_t*)TRIMMING_LOCATION) & MAIN_REGULATOR_TRIM_Msk) >> MAIN_REGULATOR_TRIM_Pos;
    smps_out_voltage  = ((*(volatile uint32_t*)TRIMMING_LOCATION) & SMPS_TRIM_Msk) >> SMPS_TRIM_Pos;
#ifdef CONFIG_DEVICE_BLUENRG_LP
    lsi_lpmu          = ((*(volatile uint32_t*)TRIMMING_LOCATION) & LSI_LPMU_TRIM_Msk) >> LSI_LPMU_TRIM_Pos;
#endif /* CONFIG_DEVICE_BLUENRG_LP */
    lsi_bw            = ((*(volatile uint32_t*)TRIMMING_LOCATION) & LSI_BW_TRIM_Msk) >> LSI_BW_TRIM_Pos;
    hsi_calib         = ((*(volatile uint32_t*)TRIMMING_LOCATION) & HSI_TRIM_Msk) >> HSI_TRIM_Pos;
    eng_lsi_bw_flag   = TRUE;
  } else {
#ifdef CONFIG_DEVICE_BLUENRG_LP
    main_regulator    = 0x08;
    lsi_lpmu          = 0x08;
    hsi_calib         = 0x1E;
    eng_lsi_bw_flag   = FALSE;
#endif
#if defined(CONFIG_DEVICE_BLUENRG_LPS)
    main_regulator    = 0x0A;
    hsi_calib         = 0x1F;
    lsi_bw            = 8;
    eng_lsi_bw_flag   = TRUE;
#endif
    smps_out_voltage  = 0x03;
  }
  
  /* Set HSI Calibration Trimming value */
  LL_RCC_HSI_SetCalibTrimming(hsi_calib);

  /* Low speed internal RC trimming value set by software */
  if (eng_lsi_bw_flag)
    LL_RCC_LSI_SetTrimming(lsi_bw);
  
#ifdef CONFIG_DEVICE_BLUENRG_LP
  /* Set LSI LPMU Trimming value */
  LL_PWR_SetLSILPMUTrim(lsi_lpmu);
#endif /* CONFIG_DEVICE_BLUENRG_LP */
	
  /* Set Main Regulator voltage Trimming value */ 
  LL_PWR_SetMRTrim(main_regulator);

  /* Set SMPS output voltage Trimming value */
  LL_PWR_SetSMPSTrim(smps_out_voltage);
  
  /* Set SMPS in LP Open */
  LL_PWR_SetSMPSOpenMode(LL_PWR_SMPS_LPOPEN);
  
#ifdef CONFIG_HW_SMPS_NONE
  /* No SMPS configuration */
  LL_PWR_SetSMPSMode(LL_PWR_NO_SMPS);
#endif

  return ret_val;
}

/**
  * @brief  Low Speed Configuration
  */
static uint8_t LSConfig(void)
{
  uint8_t ret_val=SUCCESS;
  
  /* Low speed crystal configuration */
#ifdef CONFIG_HW_LS_XTAL
  LL_PWR_SetNoPullB(LL_PWR_PUPD_IO12|LL_PWR_PUPD_IO13);
  LL_RCC_LSCO_SetSource(LL_RCC_LSCO_CLKSOURCE_LSE);
  
   /* Set LSE oscillator drive capability */
  LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_HIGH);
  
  LL_RCC_LSI_Disable();
  
  /* Need to explicitly disable LSE to make LSERDY flag go to 0 even without
    POR, in case it was enabled. */
  LL_RCC_LSE_Disable();  
  if(SystemReadyWait(300, LL_RCC_LSE_IsReady, 0) == FALSE)
  {
    ret_val = SYSTEM_CONFIG_LSE_READY_ERROR;
  }

  LL_RCC_LSE_Enable();
  if(SystemReadyWait(300, LL_RCC_LSE_IsReady, 1) == FALSE)
  {
    ret_val = SYSTEM_CONFIG_LSE_READY_ERROR;
  }
#elif defined(CONFIG_HW_LS_RO)
  LL_RCC_LSI_Disable();
  if(SystemReadyWait(300, LL_RCC_LSI_IsReady, 0) == FALSE)
  {
    ret_val = SYSTEM_CONFIG_LSI_READY_ERROR;
  }  
  LL_RCC_LSE_Disable();
  LL_RCC_LSCO_SetSource(LL_RCC_LSCO_CLKSOURCE_LSI);
  
  LL_RCC_LSI_Enable();
  if(SystemReadyWait(300, LL_RCC_LSI_IsReady, 1) == FALSE)
  {
    ret_val = SYSTEM_CONFIG_LSI_READY_ERROR;
  } 
#else
#ifndef SUPPRESS_CONFIG_HW_WARNINGS
  #warning "No Low Speed Crystal definition!!!"
#endif
#endif
  
  return ret_val;
}

/**
  * @brief  MR_BLE BIAS current Trimming value Configuration 
  */
void MrBleBiasTrimConfig(uint8_t coldStart)
{  
  uint32_t mr_ble_ibias, mr_ble_iptat, mr_ble_vbg, mr_ble_rxadc_delay_i, mr_ble_rxadc_delay_q;
  uint8_t mr_ble_rxadc_delay_flag;
  
  if (coldStart) {
    /* Change system's clock frequency from 16MHz to 32MHz */
    LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_2);
    
    /* Set MR_BLE frequency to 32MHz (HSI/2) */
    LL_RCC_SetRFClockSource(LL_RCC_RF_RC64MPLL_DIV2);

    /* Peripheral reset */
    LL_APB2_ForceReset(LL_APB2_PERIPH_MRBLE);
    LL_APB2_ReleaseReset(LL_APB2_PERIPH_MRBLE);
    
    /* Enable MR_BLE's clock */
    LL_APB2_EnableClock(LL_APB2_PERIPH_MRBLE);    
  }
  
  
  /* Retrieve Trimming values from engineering flash locations */
  if (*(volatile uint32_t*)VALIDITY_LOCATION == VALIDITY_TAG) {
    mr_ble_ibias            = ((*(volatile uint32_t*)MR_TRIMMING_LOCATION) & MR_BLE_IBIAS_TRIM_Msk) >> MR_BLE_IBIAS_TRIM_Pos;
    mr_ble_iptat            = ((*(volatile uint32_t*)MR_TRIMMING_LOCATION) & MR_BLE_IPTAT_TRIM_Msk) >> MR_BLE_IPTAT_TRIM_Pos;
    mr_ble_vbg              = ((*(volatile uint32_t*)MR_TRIMMING_LOCATION) & MR_BLE_VBG_TRIM_Msk) >> MR_BLE_VBG_TRIM_Pos;
    mr_ble_rxadc_delay_i    = ((*(volatile uint32_t*)MR_TRIMMING_LOCATION) & MR_BLE_RXADC_DELAY_I_TRIM_Msk) >> MR_BLE_RXADC_DELAY_I_TRIM_Pos;
    mr_ble_rxadc_delay_q    = ((*(volatile uint32_t*)MR_TRIMMING_LOCATION) & MR_BLE_RXADC_DELAY_Q_TRIM_Msk) >> MR_BLE_RXADC_DELAY_Q_TRIM_Pos;
    mr_ble_rxadc_delay_flag = TRUE;
  } else {
    mr_ble_ibias = 0x08;
    mr_ble_iptat = 0x07;
    mr_ble_vbg   = 0x08;
    mr_ble_rxadc_delay_flag = FALSE;
#if defined(CONFIG_DEVICE_BLUENRG_LPS)
    mr_ble_rxadc_delay_i    = 3;
    mr_ble_rxadc_delay_q    = 3;
    mr_ble_rxadc_delay_flag = TRUE;
#endif /* CONFIG_DEVICE_BLUENRG_LPS/F */
  }

  /* Write MR_BLE Trimming values in the registers: Cbias' VBG, Cbias' IPTAT, Cbias' IBIAS, RxAnaUsr Delay Trim I & Q */
  MODIFY_REG_FIELD(RRM->CBIAS1_ANA_ENG, RRM_CBIAS1_ANA_ENG_RFD_CBIAS_VBG_TRIM, mr_ble_vbg);
  MODIFY_REG_FIELD(RRM->CBIAS0_ANA_ENG, RRM_CBIAS0_ANA_ENG_RFD_CBIAS_IPTAT_TRIM, mr_ble_iptat);
  MODIFY_REG_FIELD(RRM->CBIAS0_ANA_ENG, RRM_CBIAS0_ANA_ENG_RFD_CBIAS_IBIAS_TRIM, mr_ble_ibias);
  if (mr_ble_rxadc_delay_flag) {
    MODIFY_REG_FIELD(RRM->RXADC_ANA_USR, RRM_RXADC_ANA_USR_RFD_RXADC_DELAYTRIM_I, mr_ble_rxadc_delay_i);
    MODIFY_REG_FIELD(RRM->RXADC_ANA_USR, RRM_RXADC_ANA_USR_RFD_RXADC_DELAYTRIM_Q, mr_ble_rxadc_delay_q);
  }

  /* AFC configuration */
  MODIFY_REG(RRM->AFC1_DIG_ENG, RRM_AFC1_DIG_ENG_AFC_DELAY_AFTER|RRM_AFC1_DIG_ENG_AFC_DELAY_BEFORE,
             ((AFC_DELAY_BEFORE << RRM_AFC1_DIG_ENG_AFC_DELAY_BEFORE_Pos) & RRM_AFC1_DIG_ENG_AFC_DELAY_BEFORE_Msk) |
               ((AFC_DELAY_AFTER << RRM_AFC1_DIG_ENG_AFC_DELAY_AFTER_Pos) & RRM_AFC1_DIG_ENG_AFC_DELAY_AFTER_Msk));
  MODIFY_REG(RRM->CR0_DIG_ENG, RRM_CR0_DIG_ENG_CR_GAIN_BEFORE|RRM_CR0_DIG_ENG_CR_GAIN_AFTER,
             ((CR_GAIN_BEFORE << RRM_CR0_DIG_ENG_CR_GAIN_BEFORE_Pos) & RRM_CR0_DIG_ENG_CR_GAIN_BEFORE_Msk) |
               ((CR_GAIN_AFTER << RRM_CR0_DIG_ENG_CR_GAIN_AFTER_Pos) & RRM_CR0_DIG_ENG_CR_GAIN_AFTER_Msk));
  MODIFY_REG(RRM->CR0_LR, RRM_CR0_LR_CR_LR_GAIN_BEFORE|RRM_CR0_LR_CR_LR_GAIN_AFTER,
             ((CR_LR_GAIN_BEFORE << RRM_CR0_LR_CR_LR_GAIN_BEFORE_Pos) & RRM_CR0_LR_CR_LR_GAIN_BEFORE_Msk) |
               ((CR_LR_GAIN_AFTER << RRM_CR0_LR_CR_LR_GAIN_AFTER_Pos) & RRM_CR0_LR_CR_LR_GAIN_AFTER_Msk));
  
  MODIFY_REG_FIELD(RRM->LR_RSSI_THR_DIG_ENG, RRM_LR_RSSI_THR_DIG_ENG_LR_RSSI_THR, LR_RSSI_THR);
  MODIFY_REG_FIELD(RRM->LR_PD_THR_DIG_ENG, RRM_LR_PD_THR_DIG_ENG_LR_PD_THR, LR_PD_THR);
  MODIFY_REG_FIELD(RRM->LR_AAC_THR_DIG_ENG, RRM_LR_AAC_THR_DIG_ENG_LR_AAC_THR, LR_AAC_THR);
  
  /* Enable Viterbi */
  SET_BIT(RRM->VIT_CONF_DIG_ENG, RRM_VIT_CONF_DIG_ENG_VIT_CONF_0);
  
#if defined(CONFIG_DEVICE_BLUENRG_LPS)
  MODIFY_REG_FIELD(RRM->ANTSW_DIG0_USR, RRM_ANTSW0_DIG_USR_RX_TIME_TO_SAMPLE, RX_TIME_TO_SAMPLE);
  MODIFY_REG_FIELD(RRM->ANTSW_DIG1_USR, RRM_ANTSW1_DIG_USR_RX_TIME_TO_SWITCH, RX_TIME_TO_SWITCH);
#endif  

}

/**
  * @brief Function to update the variable SystemCoreClock  
  */
void SystemCoreClockUpdate(void)
{  
  switch(LL_RCC_GetRC64MPLLPrescaler())
  {
  case LL_RCC_RC64MPLL_DIV_1:
    SystemCoreClock = 64000000;
    break;
  case LL_RCC_RC64MPLL_DIV_2:
    SystemCoreClock = 32000000;
    break;
  case LL_RCC_RC64MPLL_DIV_4:
    SystemCoreClock = 16000000;
    break;
  case LL_RCC_RC64MPLL_DIV_8:
    SystemCoreClock = 8000000;
    break;
  case LL_RCC_RC64MPLL_DIV_16:
    SystemCoreClock = 4000000;
    break;
  case LL_RCC_RC64MPLL_DIV_32:
    SystemCoreClock = 2000000;
    break;
  case LL_RCC_RC64MPLL_DIV_64:
    SystemCoreClock = 1000000;
    break;
  }
}


/**
  * @brief  System Clock Configuration for System Core, low speed
  *         BLE RF and AHB bus
  * @param  SysClk system clock divided factor from HSI64MPLL
  *         This parameter can be one of the following values:
  *         SYSCLK_64M
  *         SYSCLK_32M
  *         SYSCLK_16M
  *         SYSCLK_8M
  *         SYSCLK_4M
  *         SYSCLK_2M
  *         SYSCLK_1M
  *         SYSCLK_DIRECT_HSE
  * @retval SUCCESS or error code
  */
uint8_t SystemClockConfig(uint8_t SysClk)
{ 
  uint8_t ret_val=SUCCESS;
    
  /* High speed crystal configuration: BlueNRG-LP supports only HSE 32 MHz */
  LL_RCC_HSE_Enable();
  
  if(SystemReadyWait(100, LL_RCC_HSE_IsReady, 1) == FALSE)
  {
    ret_val = SYSTEM_CONFIG_HSE_READY_ERROR;
    return ret_val;
  }
  
#ifdef CONFIG_DEVICE_BLUENRG_LP
  /* BlueNRG_LP cut 1.0 not support DIRECT HSE configuration */
  if ((SysClk == SYSCLK_DIRECT_HSE) && (((LL_SYSCFG_GetDeviceVersion()<<4)|LL_SYSCFG_GetDeviceRevision()) == LL_BLUENRG_LP_CUT_10)) {
    return SYSTEM_CONFIG_DIRECT_HSE_NOT_SUPPORTED;
  }
#endif
  
  if (SysClk != SYSCLK_DIRECT_HSE) {
    /* System PLL Clock configuration */
    switch(SysClk)
    {
    case SYSCLK_64M:
      LL_FLASH_SetWaitStates(FLASH, LL_FLASH_WAIT_STATES_1);
      LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_1);
      SystemCoreClock = 64000000;
      break;
    case SYSCLK_32M:
      LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_2);
      SystemCoreClock = 32000000;
      break;
    case SYSCLK_16M:
      LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_4);
      SystemCoreClock = 16000000;
      break;
    case SYSCLK_8M:
      LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_8);
      SystemCoreClock = 8000000;
      break;
    case SYSCLK_4M:
      LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_16);
      SystemCoreClock = 4000000;
      break;
    case SYSCLK_2M:
      LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_32);
      SystemCoreClock = 2000000;
      break;
    case SYSCLK_1M:
      LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_64);
      SystemCoreClock = 1000000;
      break;
    default:
      /* Error, wrong choice */
      while(1);
    }
    LL_RCC_RC64MPLL_Enable();
    
    if(SystemReadyWait(200, LL_RCC_RC64MPLL_IsReady, 1) == FALSE)
    {
      ret_val = SYSTEM_CONFIG_PLL_READY_ERROR;
      return ret_val;
    }  
  } else { // DIRECT HSE configuration
    LL_RCC_SetRC64MPLLPrescaler(LL_RCC_RC64MPLL_DIV_2);
    LL_RCC_DIRECT_HSE_Enable();
    SystemCoreClock = 32000000;
  }
  
  /* FLASH Wait State configuration */
  if (SystemCoreClock != 64000000) {
    LL_FLASH_SetWaitStates(FLASH, LL_FLASH_WAIT_STATES_0);
  }
  
  return SUCCESS;
}

/**
  * @brief  Radio Clock Configuration
  * @param  BleSysClk BLE System Clock 
  *         This parameter can be one of the following values:
  *         BLE_SYSCLK_32M
  *         BLE_SYSCLK_16M
  * @param  SysClk system clock divided factor from HSI64MPLL
  *         This parameter can be one of the following values:
  *         SYSCLK_64M
  *         SYSCLK_32M
  *         SYSCLK_16M
  *         SYSCLK_8M
  *         SYSCLK_4M
  *         SYSCLK_2M
  *         SYSCLK_1M
  *         SYSCLK_DIRECT_HSE
  * @retval None
  */
uint8_t RadioClockConfig(uint8_t BleSysClk, uint8_t SysClk)
{
    /* No radio configuration required */
  if (BleSysClk == BLE_SYSCLK_NONE) {
    return SUCCESS;
  }

  /* The system clock shall be greater than 8 MHz with the radio enabled */
  if ((SysClk == SYSCLK_8M) || (SysClk == SYSCLK_4M) ||
      (SysClk == SYSCLK_2M) || (SysClk == SYSCLK_1M)) {
    return ERROR;
  }

  /* The System clock shall be greater than or equal to the BLE Radio Clock */
  if ((SysClk == SYSCLK_16M) && (BleSysClk == BLE_SYSCLK_32M)) {
    return ERROR;
  }
  
  /* RF clock source configuration according System Clock Frequency*/
  if ((BleSysClk == BLE_SYSCLK_16M) || (SysClk == SYSCLK_16M))
  {
    LL_RCC_SetRFClockSource(LL_RCC_RF_RC64MPLL_DIV4);
    BleSysClk = BLE_SYSCLK_16M;
  }
  else
  {
    LL_RCC_SetRFClockSource(LL_RCC_RF_RC64MPLL_DIV2);
  }

#if defined(AHBUPCONV)
  /* AHBUPCONV management is allowed only for BlueNRG-LP cut 1.0 */ 
  if (((LL_SYSCFG_GetDeviceVersion()<<4)|LL_SYSCFG_GetDeviceRevision()) == LL_BLUENRG_LP_CUT_10)
  {
    /* Configure AHBUPCONV */
    /* Configuration with System Clock four time faster than the MR_BLE clock */
    if ((SysClk == SYSCLK_64M) && (BleSysClk == BLE_SYSCLK_16M))
    {
      AHBUPCONV->COMMAND = SYSCLK_FOURFOLD_BLECLK;
    }
    /* Configuration with System Clock two time faster than the MR_BLE clock */
    else if (((SysClk == SYSCLK_64M) && (BleSysClk == BLE_SYSCLK_32M)) ||
	     ((SysClk == SYSCLK_32M) && (BleSysClk == BLE_SYSCLK_16M)))
    {
      AHBUPCONV->COMMAND = SYSCLK_DOUBLE_BLECLK;
    }
    /* Configuration with System Clock is the same of the MR_BLE clock */
    else
    {
      AHBUPCONV->COMMAND = SYSCLK_EQUAL_BLECLK;
    }
    while(AHBUPCONV->STATUS & AHB_STALLED);
  }
#endif /* defined(AHBUPCONV) */

  return SUCCESS;
}

/**
  * @brief  System Init
  * @param  SysClk system clock divided factor from HSI64MPLL
  *         This parameter can be one of the following values:
  *         SYSCLK_64M
  *         SYSCLK_32M
  *         SYSCLK_16M
  *         SYSCLK_8M
  *         SYSCLK_4M
  *         SYSCLK_2M
  *         SYSCLK_1M
  *         SYSCLK_DIRECT_HSE
  * @param  BleSysClk BLE System Clock 
  *         This parameter can be one of the following values:
  *         BLE_SYSCLK_NONE
  *         BLE_SYSCLK_32M
  *         BLE_SYSCLK_16M
  * @Note   The radio not works if the SYSCLK is lower than 16 MHz 
  * @retval SUCCESS or Error code
  */
uint8_t SystemInit(uint8_t SysClk, uint8_t BleSysClk)
{
  uint8_t ret_val;
  
  /* Vector Table Offset Register */
  SCB->VTOR = (uint32_t) (__vector_table);

  /* Store in RAM the AppBase information */
  RAM_VR.AppBase = (uint32_t) (__vector_table);
	
  /* Enable all the RAM banks in retention during DEEPSTOP */
  LL_PWR_EnableRAMBankRet(LL_PWR_RAMRET_1);
#if defined(LL_PWR_RAMRET_2)
  LL_PWR_EnableRAMBankRet(LL_PWR_RAMRET_2);
#endif
#if defined(LL_PWR_RAMRET_3)
  LL_PWR_EnableRAMBankRet(LL_PWR_RAMRET_3);
#endif
  
#if defined(PWR_CR2_GPIORET)
      /* Disable the GPIO retention in DEEPSTOP configuration */
      LL_PWR_DisableGPIORET();
#endif
	
  /* HW SMPS and HW Trimming value Configuration */
  ret_val = SmpsTrimConfig();
  if (ret_val!= SUCCESS)
    return ret_val;

  /* Low Speed Crystal Configuration */
  ret_val = LSConfig();
  if (ret_val!= SUCCESS)
      return ret_val;
  
  /* MR_BLE BIAS current Trimming Configuration */
  if (BleSysClk != BLE_SYSCLK_NONE) {
    MrBleBiasTrimConfig(TRUE);
  }

  /* Set current and capacitors for High Speed Crystal Oscillator */
#ifdef CONFIG_HW_HSE_TUNE
  LL_RCC_HSE_SetCapacitorTuning(CONFIG_HW_HSE_TUNE);
#else
#ifndef SUPPRESS_CONFIG_HW_WARNINGS
	#warning "No HSE Tune configuration!!!"
#endif	
#endif
  LL_RCC_HSE_SetCurrentControl(LL_RCC_HSE_CURRENTMAX_3);

  /* System Clock Configuration */
  ret_val = SystemClockConfig(SysClk);
  if (ret_val!= SUCCESS)
    return ret_val;

  /* Radio Clock Configuration */
  ret_val = RadioClockConfig(BleSysClk, SysClk);
  if (ret_val!= SUCCESS)
    return ret_val;
    
  /* Set all the IRQ priority with a default value */
  setInterruptPriority();

  __enable_irq();
  
  return SUCCESS;
}


/******************* (C) COPYRIGHT 2018 STMicroelectronics *****END OF FILE****/
