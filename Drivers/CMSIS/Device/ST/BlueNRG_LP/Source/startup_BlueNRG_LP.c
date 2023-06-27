/******************** (C) COPYRIGHT 2021 STMicroelectronics ********************
* File Name          : startup_Bluenrg_LP.c
* Author             : AMG - RF Application team
* Version            : V1.0.0
* Date               : 22-November-2021
* Description        : BlueNRG-LP startup function
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
 

/* OTA tag used to  tag a  valid application on interrupt vector table*/
#if defined (CONFIG_OTA_SERVICE_MANAGER)
#define OTA_VALID_APP_TAG (0xAABBCCDD) /* OTA Service Manager has a special valid tag */
#else
#define OTA_VALID_APP_TAG (0xAA5555AA) 
#endif


/* Private types -------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void RESET_HANDLER(void);
void CS_contextRestore(void);
int __low_level_init(void);

/* Exported function prototypes ---------------------------------------------*/
/* Weak Function declaration for all the Interrupt Handler */
WEAK_FUNCTION(void NMI_IRQHandler(void)) {}
WEAK_FUNCTION(void HardFault_IRQHandler(void)) {}
WEAK_FUNCTION(void SVC_IRQHandler(void)) {}
WEAK_FUNCTION(void PendSV_IRQHandler(void)) {}                         
WEAK_FUNCTION(void SysTick_IRQHandler(void)) {}
WEAK_FUNCTION(void FLASH_IRQHandler(void)) {}
WEAK_FUNCTION(void RCC_IRQHandler(void)) {}
WEAK_FUNCTION(void PVD_IRQHandler(void)) {}
WEAK_FUNCTION(void I2C1_IRQHandler(void)) {}
#if defined(I2C2) 
WEAK_FUNCTION(void I2C2_IRQHandler(void)) {}
#endif
#if defined(SPI1) 
WEAK_FUNCTION(void SPI1_IRQHandler(void)) {}
#endif
#if defined(SPI2) 
WEAK_FUNCTION(void SPI2_IRQHandler(void)) {}
#endif
WEAK_FUNCTION(void SPI3_IRQHandler(void)) {}
WEAK_FUNCTION(void USART1_IRQHandler(void)) {}
WEAK_FUNCTION(void LPUART1_IRQHandler(void)) {}
#if defined(TIM1)
WEAK_FUNCTION(void TIM1_IRQHandler(void)) {}
#endif
#if defined(TIM2)
WEAK_FUNCTION(void TIM2_IRQHandler(void)) {}
#endif
WEAK_FUNCTION(void RTC_IRQHandler(void)) {}
WEAK_FUNCTION(void ADC_IRQHandler(void)) {}
WEAK_FUNCTION(void PKA_IRQHandler(void)) {}
WEAK_FUNCTION(void UPCONV_IRQHandler(void)) {}
WEAK_FUNCTION(void GPIOA_IRQHandler(void)) {}
WEAK_FUNCTION(void GPIOB_IRQHandler(void)) {}
WEAK_FUNCTION(void DMA_IRQHandler(void)) {}
WEAK_FUNCTION(void BLE_TX_RX_IRQHandler(void)) {}
WEAK_FUNCTION(void BLE_AES_IRQHandler(void)) {}
WEAK_FUNCTION(void BLE_ERROR_IRQHandler(void)) {}
WEAK_FUNCTION(void RADIO_CTRL_IRQHandler(void)) {}
WEAK_FUNCTION(void MR_BLE_IRQHandler(void)) {}
WEAK_FUNCTION(void CPU_WKUP_IRQHandler(void)) {}
WEAK_FUNCTION(void BLE_WKUP_IRQHandler(void)) {}
WEAK_FUNCTION(void BLE_RXTX_SEQ_IRQHandler(void)) {}
#if defined(TIM16)
WEAK_FUNCTION(void TIM16_IRQHandler(void)) {}
#endif
#if defined(TIM17)
WEAK_FUNCTION(void TIM17_IRQHandler(void)) {}
#endif

/* Weak Function declaration for the Context Restore */
WEAK_FUNCTION(void CS_contextRestore(void)) {} 

/* Exported variables ---------------------------------------------------------*/

/*************************************************************************************
 **
 ** Should add all the variable to manage the Context restore and OTA procedures!!!!!!!! 
 **
 **************************************************************************************/
/* Exported function prototypes ---------------------------------------------*/
/* Low Level Init function */
int __low_level_init(void) 
{
  /* If the reset reason is a wakeup from DEEPSTOP restore the context */
  if ((RCC->CSR == 0) && ((PWR->SR1 != 0)||(PWR->SR3 != 0))) {
#ifndef NO_SMART_POWER_MANAGEMENT
    RAM_VR.WakeupFromSleepFlag = 1; /* A wakeup from DEEPSTOP occurred */
    CS_contextRestore();            /* Restore the context */
    /* if the context restore worked properly, we should never return here */
    while(1) { 
      NVIC_SystemReset(); 
    }
#else
    return 0;
#endif   
  }
  return 1;
}

#if defined(__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100))
__attribute__((noreturn)) void RESET_HANDLER(void)
{
  if(__low_level_init()==1)
    __main();
  else {
    __set_MSP((uint32_t)_INITIAL_SP);
    main();
  }
  while(1);
}

#else
#ifdef __GNUC__

#include <stdint.h>
#include <errno.h>

extern unsigned long _etext;
extern unsigned long _sidata;       /* start address for the initialization values of the .data section. Defined in linker script */
extern unsigned long _sdata;        /* start address for the .data section. Defined in linker script */
extern unsigned long _edata;        /* end address for the .data section. Defined in linker script */
extern unsigned long _sbss;         /* start address for the .bss section. Defined in linker script */
extern unsigned long _ebss;         /* end address for the .bss section. Defined in linker script */
extern unsigned long _sbssblue;     /* start address for the section reserved for the Blue controller. Defined in linker script */
extern unsigned long _ebssblue;     /* end address for the section reserved for the Blue controller. Defined in linker script */
extern unsigned long _estack;       /* init value for the stack pointer. Defined in linker script */
extern unsigned long _sidata2;      /* start address for the initialization values of the special ram_preamble */
extern unsigned long _sdata2;       /* start address the special ram_preamble defined in linker script */
extern unsigned long _edata2;       /* end address the special ram_preamble defined in linker script */
extern uint8_t _sheap;              /* start address for the .heap section. Defined in linker script */
extern uint8_t _eheap;              /* end address for the .heap section. Defined in linker script */

extern int main(void);

void RESET_HANDLER(void)
{
  if(__low_level_init()==1) {
    unsigned long *pulSrc, *pulDest;

    // Copy the data segment initializers from flash to SRAM.
    pulSrc = &_sidata;
    for(pulDest = &_sdata; pulDest < &_edata; )
    {
      *(pulDest++) = *(pulSrc++);
    }

    // Zero fill the bss segment.
    for(pulDest = &_sbssblue; pulDest < &_ebssblue; )
    {
      *(pulDest++) = 0;
    }

    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
      *(pulDest++) = 0;
    }
  }
  // Call the application's entry point.
  __set_MSP((uint32_t)_INITIAL_SP);
  main();
}

void * _sbrk(int32_t incr)
{
  static uint8_t *heap_end;
  uint8_t *prev_heap_end;

  if (heap_end == 0)
    heap_end = &_sheap;

  prev_heap_end = heap_end;
  if ((heap_end + incr) > (&_eheap))
  {
//    write(1, "Heap and stack collision\n", 25);
//    abort();
    errno = ENOMEM;
    return (void *) -1;
  }

  heap_end += incr;

  return prev_heap_end;
}

#endif /* __GNUC__ */
#endif /* __CC_ARM */

/* Interrupt Vector Table */
SECTION(".intvec")
REQUIRED(const intvec_elem __vector_table[]) = {
    {.__ptr = _INITIAL_SP},                   /* Stack address                      */
    {RESET_HANDLER},                    /* Reset handler is C initialization. */
    {NMI_IRQHandler},                         /* The NMI handler                    */
    {HardFault_IRQHandler},                   /* The hard fault handler             */
    {(intfunc) OTA_VALID_APP_TAG},            /* OTA Application                    */
    {(intfunc) BLUE_FLAG_TAG},                /* Reserved for blue flag DTM updater */
    {0x00000000},                             /* Reserved                           */
    {0x00000000},                             /* Reserved                           */
    {0x00000000},                             /* Reserved                           */
    {0x00000000},                             /* Reserved                           */
    {0x00000000},                             /* Reserved                           */
    {SVC_IRQHandler},                         /* SVCall                             */
    {0x00000000},                             /* Reserved                           */
    {0x00000000},                             /* Reserved                           */
    {PendSV_IRQHandler},                      /* PendSV                             */
    {SysTick_IRQHandler},                     /* SysTick_IRQHandler                 */
    {FLASH_IRQHandler},                       /* IRQ0:  FLASH Controller            */
    {RCC_IRQHandler},                         /* IRQ1:  RCC                         */
    {PVD_IRQHandler},                         /* IRQ2:  PVD                         */
    {I2C1_IRQHandler},                        /* IRQ3:  I2C1                        */
#if defined(I2C2)
    {I2C2_IRQHandler},                        /* IRQ4:  I2C2                        */
#else
    {0x00000000},                             /* IRQ4                               */
#endif
#if defined(SPI1)
    {SPI1_IRQHandler},                        /* IRQ5:  SPI1                        */
#else
    {0x00000000},                             /* IRQ5                               */
#endif
#if defined(SPI2)
    {SPI2_IRQHandler},                        /* IRQ6:  SPI2                        */
#else
    {0x00000000},                             /* IRQ6                               */
#endif
    {SPI3_IRQHandler},                        /* IRQ7:  SPI3                        */
    {USART1_IRQHandler},                      /* IRQ8:  USART1                      */
    {LPUART1_IRQHandler},                     /* IRQ9:  LPUART1                     */
#if defined(TIM1)
    {TIM1_IRQHandler},                        /* IRQ10: TIM1                        */
#endif
#if defined(TIM2)
    {TIM2_IRQHandler},                        /* IRQ10: TIM2                        */
#endif
    {RTC_IRQHandler},                         /* IRQ11: RTC                         */
    {ADC_IRQHandler},                         /* IRQ12: ADC                         */
    {PKA_IRQHandler},                         /* IRQ13: PKA                         */
    {UPCONV_IRQHandler},                      /* IRQ14: AHB_UP_CONVERTER            */
    {GPIOA_IRQHandler},                       /* IRQ15: GPIOA                       */
    {GPIOB_IRQHandler},                       /* IRQ16: GPIOB                       */
    {DMA_IRQHandler},                         /* IRQ17: DMA                         */
    {BLE_TX_RX_IRQHandler},                   /* IRQ18: BLE TX RX                   */
    {BLE_AES_IRQHandler},                     /* IRQ19: BLE AES                     */
    {BLE_ERROR_IRQHandler},                   /* IRQ20: BLE Error                   */
    {RADIO_CTRL_IRQHandler},                  /* IRQ21: Radio Control               */
    {MR_BLE_IRQHandler},                      /* IRQ22: RRM and Radio FSM           */
    {CPU_WKUP_IRQHandler},                    /* IRQ23: CPU Wakeup                  */
    {BLE_WKUP_IRQHandler},                    /* IRQ24: BLE Wakeup                  */
    {BLE_RXTX_SEQ_IRQHandler},                /* IRQ25: BLE RX/TX Sequence          */
#if defined(TIM16)
    {TIM16_IRQHandler},                       /* IRQ26: TIM16                       */
#else
    {0x00000000},                             /* IRQ26                              */
#endif
#if defined(TIM17)
    {TIM17_IRQHandler},                       /* IRQ27: TIM17                       */
#else    
    {0x00000000},                             /* IRQ27                              */
#endif
    {0x00000000},                             /* IRQ28                              */
    {0x00000000},                             /* IRQ29                              */
    {0x00000000},                             /* IRQ30                              */
    {0x00000000}                              /* IRQ31                              */
};



/* Configure all the interrupts priority. 
 * The application can modify the interrupts priority.
 * The BLE_TX_RX_IRQn SHALL maintain the highest priority
 */
void setInterruptPriority(void)
{
  NVIC_SetPriority(FLASH_IRQn,       IRQ_LOW_PRIORITY);
  NVIC_SetPriority(RCC_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(PVD_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(I2C1_IRQn,        IRQ_LOW_PRIORITY);
#if defined(I2C2) 
  NVIC_SetPriority(I2C2_IRQn,        IRQ_LOW_PRIORITY);
#endif
#if defined(SPI1) 
  NVIC_SetPriority(SPI1_IRQn,        IRQ_LOW_PRIORITY);
#endif
#if defined(SPI2) 
  NVIC_SetPriority(SPI2_IRQn,        IRQ_LOW_PRIORITY);
#endif
  NVIC_SetPriority(SPI3_IRQn,        IRQ_LOW_PRIORITY);
  NVIC_SetPriority(USART1_IRQn,      IRQ_LOW_PRIORITY);
  NVIC_SetPriority(LPUART1_IRQn,     IRQ_LOW_PRIORITY);
#if defined(TIM1)
  NVIC_SetPriority(TIM1_IRQn,        IRQ_LOW_PRIORITY);
#endif
#if defined(TIM2)
  NVIC_SetPriority(TIM2_IRQn,        IRQ_LOW_PRIORITY);
#endif
  NVIC_SetPriority(RTC_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(ADC_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(PKA_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(UPCONV_IRQn,      IRQ_LOW_PRIORITY);
  NVIC_SetPriority(GPIOA_IRQn,       IRQ_LOW_PRIORITY);
  NVIC_SetPriority(GPIOB_IRQn,       IRQ_LOW_PRIORITY);
  NVIC_SetPriority(DMA_IRQn,         IRQ_LOW_PRIORITY);
  NVIC_SetPriority(BLE_TX_RX_IRQn,   IRQ_CRITICAL_PRIORITY);
  NVIC_SetPriority(BLE_AES_IRQn,     IRQ_LOW_PRIORITY);
  NVIC_SetPriority(BLE_ERROR_IRQn,   IRQ_LOW_PRIORITY);
  NVIC_SetPriority(RADIO_CTRL_IRQn,  IRQ_LOW_PRIORITY);
  NVIC_SetPriority(MR_BLE_IRQn,      IRQ_LOW_PRIORITY);
  NVIC_SetPriority(CPU_WKUP_IRQn,    IRQ_HIGH_PRIORITY);
  NVIC_SetPriority(BLE_WKUP_IRQn,    IRQ_CRITICAL_PRIORITY);
  NVIC_SetPriority(BLE_SEQ_IRQn,     IRQ_LOW_PRIORITY);
#if defined(TIM16)
  NVIC_SetPriority(TIM16_IRQn,       IRQ_LOW_PRIORITY);
#endif
#if defined(TIM17)
  NVIC_SetPriority(TIM17_IRQn,       IRQ_LOW_PRIORITY);
#endif
}


/******************* (C) COPYRIGHT 2021 STMicroelectronics *****END OF FILE****/
