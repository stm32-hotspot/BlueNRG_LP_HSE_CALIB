/** 
  ******************************************************************************
  * @file    steval_idb012V1_config.h
  * @author  RF Application Team
  * @brief   This file contains definitions for:
  *          Resources available on a specific BlueNRG-LPS QFN48 Eval Kit from STMicroelectronics
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2022 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STEVAL_IDB012V1_CONFIG_H
#define __STEVAL_IDB012V1_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup BSP
  * @{
  */

/** @addtogroup BSP_STEVAL_IDB012V1 BSP STEVAL-IDB012V1
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_lpx.h"
#include "rf_driver_ll_bus.h"
#include "rf_driver_ll_exti.h"
#include "rf_driver_ll_gpio.h"
#include "rf_driver_ll_usart.h"
#include "rf_driver_ll_i2c.h"
#include "rf_driver_ll_spi.h"
#include "rf_driver_hal_power_manager.h"


/** @addtogroup BSP_STEVAL_IDB012V1_Exported_Types
  * @{
  */
   
typedef enum 
{
  BSP_LED1 = 0,
  BSP_LED2 = 1,
  BSP_LED3 = 2,
  /* Color LED aliases */
  BSP_LED_RED    = BSP_LED3,
  BSP_LED_GREEN  = BSP_LED2,
  BSP_LED_BLUE   = BSP_LED1,
}Led_TypeDef;


typedef enum 
{  
  BSP_PUSH1 = 0,
  BSP_PUSH2 = 1,
}Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
}ButtonMode_TypeDef;

/**
  * @}
  */

/** @defgroup BSP_STEVAL_IDB012V1_Exported_Definitions Exported Definitions
  * @{
  */

/* LED on if GPIO output is low */
#define BSP_LED_INVERTED_LOGIC                    1 
#define BSP_LED_PULL_MODE                         LL_GPIO_PULL_NO

/* BSP_LED1 is the component U5 - Multicolor LED */
#define BSP_LED1_PIN                              LL_GPIO_PIN_1
#define BSP_LED1_GPIO_PORT                        GPIOB
#define BSP_LED1_GPIO_CLK_ENABLE()                LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_LED1_GPIO_CLK_DISABLE()               LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOB)

#define BSP_LED2_PIN                              LL_GPIO_PIN_4
#define BSP_LED2_GPIO_PORT                        GPIOB
#define BSP_LED2_GPIO_CLK_ENABLE()                LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_LED2_GPIO_CLK_DISABLE()               LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOB)

#define BSP_LED3_PIN                              LL_GPIO_PIN_2
#define BSP_LED3_GPIO_PORT                        GPIOB
#define BSP_LED3_GPIO_CLK_ENABLE()                LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_LED3_GPIO_CLK_DISABLE()               LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOB)

#define BSP_PUSH1_PIN                             LL_GPIO_PIN_10
#define BSP_PUSH1_GPIO_PORT                       GPIOA
#define BSP_PUSH1_GPIO_CLK_ENABLE()               LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOA)
#define BSP_PUSH1_GPIO_CLK_DISABLE()              LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOA)
#define BSP_PUSH1_EXTI_IRQn                       GPIOA_IRQn
#define BSP_PUSH1_IRQHandler(void)                GPIOA_IRQHandler(void)
#define BSP_PUSH1_EXTI_LINE                       LL_EXTI_LINE_PA10
#define BSP_PUSH1_EXTI_LINE_TRIGGER               LL_EXTI_TRIGGER_RISING_EDGE
#define BSP_PUSH1_PUSHED                          ((uint32_t)(1))
#define BSP_PUSH1_WAKEUP                          WAKEUP_PA10

#define BSP_PUSH2_PIN                             LL_GPIO_PIN_5
#define BSP_PUSH2_GPIO_PORT                       GPIOB
#define BSP_PUSH2_GPIO_CLK_ENABLE()               LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_PUSH2_GPIO_CLK_DISABLE()              LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_PUSH2_EXTI_IRQn                       GPIOB_IRQn
#define BSP_PUSH2_IRQHandler(void)                GPIOB_IRQHandler(void)
#define BSP_PUSH2_EXTI_LINE                       LL_EXTI_LINE_PB5
#define BSP_PUSH2_EXTI_LINE_TRIGGER               LL_EXTI_TRIGGER_RISING_EDGE
#define BSP_PUSH2_PUSHED                          ((uint32_t)(1))
#define BSP_PUSH2_WAKEUP                          WAKEUP_PB5


#define BSP_I2C                                   I2C1
#define BSP_I2C_CLK_ENABLE()                      LL_APB1_EnableClock(LL_APB1_PERIPH_I2C1)
#define BSP_I2C_CLK_DISABLE()                     LL_APB1_DisableClock(LL_APB1_PERIPH_I2C1)

#define BSP_I2C_DATA_PIN                          LL_GPIO_PIN_7
#define BSP_I2C_DATA_GPIO_PORT                    GPIOB
#define BSP_I2C_DATA_GPIO_PULL                    LL_GPIO_PULL_NO
#define BSP_I2C_DATA_GPIO_AF()                    LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_7, LL_GPIO_AF_0)
#define BSP_I2C_DATA_GPIO_CLK_ENABLE()            LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_I2C_DATA_GPIO_CLK_DISABLE()           LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOB)

#define BSP_I2C_CLK_PIN                           LL_GPIO_PIN_0
#define BSP_I2C_CLK_GPIO_PORT                     GPIOA
#define BSP_I2C_CLK_GPIO_PULL                     LL_GPIO_PULL_NO
#define BSP_I2C_CLK_GPIO_AF()                     LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_0, LL_GPIO_AF_0)
#define BSP_I2C_CLK_GPIO_CLK_ENABLE()             LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOA)
#define BSP_I2C_CLK_GPIO_CLK_DISABLE()            LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOA)


#define BSP_UART                                   USART1
#define BSP_UART_IRQn                              USART1_IRQn
#ifndef BSP_UART_BAUDRATE 
#define BSP_UART_BAUDRATE                          (115200)
#endif
#define BSP_UART_CLK_ENABLE()                      LL_APB1_EnableClock(LL_APB1_PERIPH_USART)
#define BSP_UART_CLK_DISABLE()                     LL_APB1_DisableClock(LL_APB1_PERIPH_USART)
#define BSP_UART_GPIO_CLOCK_ENABLE()               LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOA|LL_AHB_PERIPH_GPIOB)
#define BSP_UART_GPIO_CLOCK_DISABLE()              LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOA|LL_AHB_PERIPH_GPIOB)

#define BSP_UART_TX_PIN                           LL_GPIO_PIN_1
#define BSP_UART_TX_GPIO_PORT                     GPIOA
#define BSP_UART_TX_GPIO_AF_N                     LL_GPIO_AF_2
#define BSP_UART_TX_GPIO_AF()                     LL_GPIO_SetAFPin_0_7(BSP_UART_TX_GPIO_PORT, BSP_UART_TX_PIN, BSP_UART_TX_GPIO_AF_N)
#define BSP_UART_TX_GPIO_CLK_ENABLE()             LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOA)
#define BSP_UART_TX_GPIO_CLK_DISABLE()            LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOA)

#define BSP_UART_RX_PIN                           LL_GPIO_PIN_0
#define BSP_UART_RX_GPIO_PORT                     GPIOB
#define BSP_UART_RX_GPIO_AF_N                     LL_GPIO_AF_0
#define BSP_UART_RX_GPIO_AF()                     LL_GPIO_SetAFPin_0_7(BSP_UART_RX_GPIO_PORT, BSP_UART_RX_PIN, BSP_UART_RX_GPIO_AF_N)
#define BSP_UART_RX_GPIO_CLK_ENABLE()             LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_UART_RX_GPIO_CLK_DISABLE()            LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_USART_RX_WAKEUP                       WAKEUP_PB0


#define BSP_SPI                                   SPI3
#define BSP_SPI_CLK_ENABLE()                      LL_APB1_EnableClock(LL_APB1_PERIPH_SPI3)
#define BSP_SPI_CLK_DISABLE()                     LL_APB1_DisableClock(LL_APB1_PERIPH_SPI3)
#define BSP_SPI_GPIO_CLOCK_ENABLE()               LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOA)
#define BSP_SPI_CLK_POLARITY                      LL_SPI_POLARITY_HIGH
#define BSP_SPI_CLK_PHASE                         LL_SPI_PHASE_2EDGE
#define BSP_SPI_TX_DMA_REQ                        LL_DMAMUX_REQ_SPI3_TX
#define BSP_SPI_RX_DMA_REQ                        LL_DMAMUX_REQ_SPI3_RX

#define BSP_SPI_MISO_PIN                          LL_GPIO_PIN_8
#define BSP_SPI_MISO_GPIO_PORT                    GPIOA
#define BSP_SPI_MISO_GPIO_AF_N                    LL_GPIO_AF_3
#define BSP_SPI_MISO_GPIO_AF()                    LL_GPIO_SetAFPin_8_15(BSP_SPI_MISO_GPIO_PORT, BSP_SPI_MISO_PIN, BSP_SPI_MISO_GPIO_AF_N)
#define BSP_SPI_MISO_GPIO_CLK_ENABLE()            LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOA)
#define BSP_SPI_MISO_GPIO_CLK_DISABLE()           LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOA)

#define BSP_SPI_MOSI_PIN                          LL_GPIO_PIN_11
#define BSP_SPI_MOSI_GPIO_PORT                    GPIOA
#define BSP_SPI_MOSI_GPIO_AF_N                    LL_GPIO_AF_3
#define BSP_SPI_MOSI_GPIO_AF()                    LL_GPIO_SetAFPin_8_15(BSP_SPI_MOSI_GPIO_PORT, BSP_SPI_MOSI_PIN, BSP_SPI_MOSI_GPIO_AF_N)
#define BSP_SPI_MOSI_GPIO_CLK_ENABLE()            LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOA)
#define BSP_SPI_MOSI_GPIO_CLK_DISABLE()           LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOA)

#ifdef STEVAL_IDB012V1_ALPHA /* Alpha STEVAL-IDB012V1 kit: SPI Clock on Pin PA3, AF3 */ 
#define BSP_SPI_SCK_PIN                           LL_GPIO_PIN_3
#define BSP_SPI_SCK_GPIO_PORT                     GPIOA
#define BSP_SPI_SCK_GPIO_AF_N                     LL_GPIO_AF_3
#define BSP_SPI_SCK_GPIO_AF()                     LL_GPIO_SetAFPin_0_7(BSP_SPI_SCK_GPIO_PORT, BSP_SPI_SCK_PIN, BSP_SPI_SCK_GPIO_AF_N)
#define BSP_SPI_SCK_GPIO_CLK_ENABLE()             LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOA)
#define BSP_SPI_SCK_GPIO_CLK_DISABLE()            LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOA)

#else /* Official STEVAL-IDB012V1 kit: SPI Clock on Pin PB3, AF4 */
#define BSP_SPI_SCK_PIN                           LL_GPIO_PIN_3
#define BSP_SPI_SCK_GPIO_PORT                     GPIOB
#define BSP_SPI_SCK_GPIO_AF_N                     LL_GPIO_AF_4
#define BSP_SPI_SCK_GPIO_AF()                     LL_GPIO_SetAFPin_0_7(BSP_SPI_SCK_GPIO_PORT, BSP_SPI_SCK_PIN, BSP_SPI_SCK_GPIO_AF_N)
#define BSP_SPI_SCK_GPIO_CLK_ENABLE()             LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_SPI_SCK_GPIO_CLK_DISABLE()            LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOB)
#endif

#define BSP_SPI_CS_PIN                            LL_GPIO_PIN_9
#define BSP_SPI_CS_GPIO_PORT                      GPIOA
#define BSP_SPI_CS_GPIO_AF_N                      LL_GPIO_AF_3
#define BSP_SPI_CS_GPIO_AF()                      LL_GPIO_SetAFPin_8_15(BSP_SPI_CS_GPIO_PORT, BSP_SPI_CS_PIN, BSP_SPI_CS_GPIO_AF_N)
#define BSP_SPI_CS_GPIO_CLK_ENABLE()              LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOA)
#define BSP_SPI_CS_GPIO_CLK_DISABLE()             LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOA)
#define BSP_SPI_EXTI_CS_PIN                       LL_EXTI_LINE_PA9
#define BSP_SPI_EXTI_CS_IRQn                      GPIOA_IRQn
#define BSP_SPI_WAKEUP_PIN                        WAKEUP_PA9

#define BSP_SPI_IRQ_PIN                           LL_GPIO_PIN_10
#define BSP_SPI_IRQ_GPIO_PORT                     GPIOA
#define BSP_SPI_IRQ_GPIO_CLK_ENABLE()             LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOA)
#define BSP_SPI_IRQ_GPIO_CLK_DISABLE()            LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOA)

#define BSP_SPI_CS_SENSOR1_PIN                    LL_GPIO_PIN_15
#define BSP_SPI_CS_SENSOR1_GPIO_PORT              GPIOB
#define BSP_SPI_CS_SENSOR1_GPIO_CLK_ENABLE()      LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_SPI_CS_SENSOR1_GPIO_CLK_DISABLE()     LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOB)

#define BSP_SENSOR1_INT_PIN                       LL_GPIO_PIN_14
#define BSP_SENSOR1_INT_GPIO_PORT                 GPIOB
#define BSP_SENSOR1_INT_GPIO_CLK_ENABLE()         LL_AHB_EnableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_SENSOR1_INT_GPIO_CLK_DISABLE()        LL_AHB_DisableClock(LL_AHB_PERIPH_GPIOB)
#define BSP_SENSOR1_INT_EXTI_IRQn                 GPIOB_IRQn
#define BSP_SENSOR1_INT_EXTI_LINE                 LL_EXTI_LINE_PB14
#define BSP_SENSOR1_INT_EXTI_LINE_TRIGGER         LL_EXTI_TRIGGER_RISING_EDGE

#define BSP_SENSOR1_INT_WAKEUP                    WAKEUP_PB14

#include "bluenrg_lp_evb_led.h"
#include "bluenrg_lp_evb_button.h"
#include "bluenrg_lp_evb_i2c.h"
#include "bluenrg_lp_evb_spi.h"
#include "bluenrg_lp_evb_com.h"
#include "bluenrg_lp_evb_io.h"


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STEVAL_IDB012V1_CONFIG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

