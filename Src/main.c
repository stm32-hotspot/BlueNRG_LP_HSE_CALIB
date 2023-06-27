
/******************** (C) COPYRIGHT 2021 STMicroelectronics ********************
* File Name          : main.c
* Author             : RF Application Team
* Version            : 1.0.0
* Description        : HSE Tuning via Button Input
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

   
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define VERSION "1.0.0"
#define APP_DBG 0

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint32_t hsetune_val = 0;
uint8_t  tone_status = 0;

/* Private function prototypes -----------------------------------------------*/
static void LL_Init(void);
static void BSP_Init(void);
static void MCO_Init(void);
void ModulesInit(void);
void ModulesTick(void);
void Device_Init(void);

static void StartTone(void);
static void StopTone(void);

static void StartHSE(void);
static void StopHSE(void);
static void SetHSECalibration(uint32_t val);

static void App_Debug(const char * message, uint8_t ret);

/* Private user code ---------------------------------------------------------*/
NO_INIT(uint32_t dyn_alloc_a[DYNAMIC_MEMORY_SIZE>>2]);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* System initialization function */
  if (SystemInit(SYSCLK_32M, BLE_SYSCLK_32M) != SUCCESS)
  {
    /* Error during system clock configuration take appropriate action */
    while(1);
  }
  
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_Init();
  
  /* Set systick to 1ms using system clock frequency */
  LL_Init1msTick(SystemCoreClock);
  
  /* BSP Init */
  BSP_IO_Init();
  BSP_Init();
  
  /* Init the UART peripheral */
  BSP_COM_Init(NULL);
  
  /* Set HSE On */
  StartHSE();
  /* Output HSE clock on PA11 pin configured in MCO mode (for verification purpose) */
  MCO_Init();
  
  /* Send Start Message */
  printf("BlueNRG-LP HSE CALIB v%s\r\n", VERSION);
  
  /* Init BLE stack, HAL virtual timer and NVM modules */
  ModulesInit();
  
  /* Init the Bluetooth LE stack layesrs */
  Device_Init();
  
  /* Set Initial HSE Tune Value */
  SetHSECalibration(hsetune_val);
  
  /* Infinite loop */
  while (1) {
    ModulesTick();
  }
}


/**
  * @brief  Timer, BLE, & NVM Tick (while())
  * @param  None.
  * @retval None.
  */
void ModulesTick(void)
{
  /* Timer tick */
  HAL_VTIMER_Tick();
  
  /* Bluetooth stack tick */
  BLE_STACK_Tick();
  
  /* NVM manager tick */
  NVMDB_Tick();
}

/**
  * @brief  Low-Level Setup
  * @param  None
  * @retval None
  */
static void LL_Init(void)
{
  /* System interrupt init*/
  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, IRQ_HIGH_PRIORITY);
}

/**
  * @brief  LED and Push-buttons Setup
  * @param  None
  * @retval None
  */
static void BSP_Init(void)
{
   /* Initialize the LEDs */
  BSP_LED_Init(BSP_LED_GREEN);
  BSP_LED_Init(BSP_LED_BLUE);
  BSP_LED_Init(BSP_LED_RED);
  
  /* Initialize the Buttons */
  BSP_PB_Init(BSP_PUSH1, BUTTON_MODE_EXTI);
  BSP_PB_Init(BSP_PUSH2, BUTTON_MODE_EXTI);
}

/**
  * @brief MCO HSE Output Setup (PA11)
  * @param None
  * @retval None
  */
static void MCO_Init(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /* GPIO Ports Clock Enable */
  MCO_GPIO_CLK_ENABLE();
 
  /* MCO */
  GPIO_InitStruct.Pin = MCO_PIN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = MCO_GPIO_AF;
  LL_GPIO_Init(MCO_GPIO_PORT, &GPIO_InitStruct);
  
  /* Select MCO clock source and prescaler */
  LL_RCC_ConfigMCO(LL_RCC_MCOSOURCE_HSE, LL_RCC_MCO_DIV_1);
}

/**
  * @brief  Middleware Modules Setup
  * @param  None
  * @retval None
  */
void ModulesInit(void)
{
  uint8_t ret;
  BLE_STACK_InitTypeDef BLE_STACK_InitParams = BLE_STACK_INIT_PARAMETERS;
  
  LL_AHB_EnableClock(LL_AHB_PERIPH_PKA|LL_AHB_PERIPH_RNG);
  
  BLECNTR_InitGlobal();
  
  HAL_VTIMER_InitType VTIMER_InitStruct = {HS_STARTUP_TIME, INITIAL_CALIBRATION, CALIBRATION_INTERVAL};
  HAL_VTIMER_Init(&VTIMER_InitStruct);
  
  BLEPLAT_Init();
  
  if (RNGMGR_Init() != RNGMGR_SUCCESS)
  {
    while(1);
  }
  
  /* Init the AES block */
  AESMGR_Init();
  
  /* BlueNRG-LP stack init */
  ret = BLE_STACK_Init(&BLE_STACK_InitParams);
  if (ret != BLE_STATUS_SUCCESS) {
    App_Debug("Error in BLE_STACK_Init() 0x%02x\r\n", ret);
    while(1);
  }
}

/**
  * @brief  TX Power & GAP Setup
  * @param  None.
  * @retval None.
  */
void Device_Init(void)
{
  uint8_t ret;
  uint16_t service_handle;
  uint16_t dev_name_char_handle;
  uint16_t appearance_char_handle;
  uint8_t address[CONFIG_DATA_PUBADDR_LEN] = {0x66,0x77,0x88,0xE1,0x80,0x02};
  
  aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET, CONFIG_DATA_PUBADDR_LEN, address);
  
  /* Set the TX Power to 0 dBm */
  ret = aci_hal_set_tx_power_level(0, 24);
  if(ret != 0) {
    App_Debug("Error in aci_hal_set_tx_power_level() 0x%04xr\n", ret);
    while(1);
  }

  
  /* Init the GAP: broadcaster role */
  ret = aci_gap_init(GAP_BROADCASTER_ROLE, 0x00, 0x08, PUBLIC_ADDR, &service_handle, &dev_name_char_handle, &appearance_char_handle);
  if (ret != 0)
  {
    App_Debug("Error in aci_gap_init() 0x%04x\r\n", ret);
  }
  else
  {
    App_Debug("aci_gap_init() --> SUCCESS\r\n", ret);
  }
}

/**
  * @brief  Button Push Callback - Change HSE Tune Value
  * @param  button: button that was pressed
  * @retval None.
  */
void BSP_PUSH_IRQ_Callback(Button_TypeDef button)
{
  if (button == BSP_PUSH1)
  {
    if (hsetune_val < 0x3F) 
    {
      hsetune_val++;
    }
    SetHSECalibration(hsetune_val);
  }
  else if (button == BSP_PUSH2)
  {
    if (hsetune_val > 0)
    {
      hsetune_val--;
    }
    SetHSECalibration(hsetune_val);
  }
}

/**
  * @brief  Start RF Tone
  * @param  None.
  * @retval None.
  */
static void StartTone(void)
{
  if (tone_status == 0)
  {
    uint8_t ret = aci_hal_tone_start(0x0, 0x0);
    if (ret != 0)
    {
      App_Debug("Error in aci_hal_tone_start() 0x%04x\r\n", ret);
    }
    else
    {
      App_Debug("aci_hal_tone_start() --> SUCCESS\r\n", ret);
      tone_status = 1;
    }
  }
}

/**
  * @brief  Stop RF Tone
  * @param  None.
  * @retval None.
  */
static void StopTone(void)
{
  if (tone_status == 1)
  {
    uint8_t ret = aci_hal_tone_stop();
    if (ret != 0)
    {
      App_Debug("Error in aci_hal_tone_stop() 0x%04x\r\n", ret);
    }
    else
    {
      App_Debug("aci_hal_tone_stop() --> SUCCESS\r\n", ret);
      tone_status = 0;
    }
  }
}

/**
  * @brief  Start HSE clock
  * @param  None.
  * @retval None.
  */
static void StartHSE(void)
{
  LL_RCC_HSE_Enable();
}

/**
  * @brief  Stop HSE clock
  * @param  None.
  * @retval None.
  */
static void StopHSE(void)
{
  LL_RCC_HSE_Disable();
}

/**
  * @brief  Set load capacitance value in HSE config register.
  * @param  HSE capacitor tuning between 0 and 63
  * @retval None.
  */
static void SetHSECalibration(uint32_t val)
{
  StopTone();
  StopHSE();
  LL_RCC_HSE_SetCapacitorTuning(val);
  StartHSE();
  StartTone();
  
  printf("HSE Tune Value: %d (Min: 0 | Max: 63)\r\n", val);
}

/**
  * @brief  App Debug: Output Debug Message
  * @param  message: debug message
  * @param  ret: hci/aci return value
  * @retval None
  */
static void App_Debug(const char * message, uint8_t ret)
{
#if APP_DBG
  if (ret != 0)
  {
    printf(message, ret);
  }
  else
  {
    printf(message);
  }
#endif
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1);
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



