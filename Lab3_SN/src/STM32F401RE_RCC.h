// STM32F401RE_RCC.h
// Header for RCC functions

#ifndef STM32F4_RCC_H
#define STM32F4_RCC_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base addresses
#define RCC_BASE (0x40023800UL) // base address of RCC

// PLL
#define PLLSRC_HSI 0
#define PLLSRC_HSE 1

// Clock configuration
#define SW_HSI  0
#define SW_HSE  1
#define SW_PLL  2

///////////////////////////////////////////////////////////////////////////////
// Bitfield structs
///////////////////////////////////////////////////////////////////////////////
typedef struct {
    volatile uint32_t HSION     : 1;
    volatile uint32_t HSIRDY    : 1;
    volatile uint32_t RES1      : 1;
    volatile uint32_t HSITRIM   : 5;
    volatile uint32_t HSICAL    : 8;
    volatile uint32_t HSEON     : 1;
    volatile uint32_t HSERDY    : 1;
    volatile uint32_t HSEBYP    : 1;
    volatile uint32_t CSSON     : 1;
    volatile uint32_t RES2      : 4;
    volatile uint32_t PLLON     : 1;
    volatile uint32_t PLLRDY    : 1;
    volatile uint32_t PLLI2SON  : 1;
    volatile uint32_t PLLI2SRDY : 1;
    volatile uint32_t RES3      : 4;
} CR_bits;

typedef struct {
    volatile uint32_t PLLM      : 6;
    volatile uint32_t PLLN      : 9;
    volatile uint32_t RES4      : 1;
    volatile uint32_t PLLP      : 2;
    volatile uint32_t RES22     : 4;
    volatile uint32_t PLLSRC    : 1;
    volatile uint32_t RES6      : 1;
    volatile uint32_t PLLQ      : 4;
    volatile uint32_t RES7      : 4;
    // TODO: Finish filling this out
} PLLCFGR_bits;

typedef struct {
    volatile uint32_t SW        : 2;
    volatile uint32_t SWS       : 2;
    volatile uint32_t HPRE      : 4;
    volatile uint32_t RES8      : 2;
    volatile uint32_t PPRE1     : 3; 
    volatile uint32_t PPRE2     : 3;
    volatile uint32_t RTCPRE    : 5;
    volatile uint32_t MCO1      : 2;
    volatile uint32_t I2SSC     : 1;
    volatile uint32_t MCO1PRE   : 3;
    volatile uint32_t MCO2PRE   : 3;
    volatile uint32_t MCO2      : 2;
} CFGR_bits;

typedef struct {
    volatile uint32_t GPIOAEN   : 1;
    volatile uint32_t GPIOBEN   : 1;
    volatile uint32_t GPIOCEN   : 1;
    volatile uint32_t GPIODEN   : 1;
    volatile uint32_t GPIOEEN   : 1;
    volatile uint32_t RES9      : 2;
    volatile uint32_t GPIOHEN   : 1;
    volatile uint32_t RES10     : 4;
    volatile uint32_t CRCEN     : 1;
    volatile uint32_t RES11     : 3;
    volatile uint32_t RES12     : 5;
    volatile uint32_t DMA1EN    : 1;
    volatile uint32_t DMA2EN    : 1;
    volatile uint32_t RES13     : 9;
} AHB1ENR_bits;

typedef struct {
    volatile uint32_t TIM_2     : 1;
    volatile uint32_t TIM_3     : 1;
    volatile uint32_t TIM4      : 1;
    volatile uint32_t TIM5      : 1;
    volatile uint32_t RES14     : 7;
    volatile uint32_t WWDGEN    : 1;
    volatile uint32_t RES15     : 2;
    volatile uint32_t SPI1EN    : 1;
    volatile uint32_t SPI2EN    : 1;
    volatile uint32_t RES16     : 1;
    volatile uint32_t USART2EN  : 1;
    volatile uint32_t RES17     : 3;
    volatile uint32_t I2C1EN    : 1;
    volatile uint32_t I2C2EN    : 1;
    volatile uint32_t I2C3EN    : 1;
    volatile uint32_t RES18     : 4;
    volatile uint32_t PWREN     : 1;
    volatile uint32_t RES19     : 3;
} APB1ENR_bits;

typedef struct {
    volatile uint32_t RES20     : 24;
    volatile uint32_t TIMPRE    : 1;
    volatile uint32_t RES22     : 7;
} DCKCFGR_bits;

// 375, 39, 374

typedef struct {
  __IO CR_bits      CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
  __IO PLLCFGR_bits PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
  __IO CFGR_bits    CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
  __IO uint32_t     CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
  __IO uint32_t     AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
  __IO uint32_t     AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
  __IO uint32_t     AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32_t          RESERVED0;     /*!< Reserved, 0x1C                                                                    */
  __IO uint32_t     APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
  __IO uint32_t     APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32_t          RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  __IO AHB1ENR_bits AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
  __IO uint32_t     AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
  __IO uint32_t     AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32_t          RESERVED2;     /*!< Reserved, 0x3C                                                                    */
  __IO APB1ENR_bits APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
  __IO uint32_t     APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32_t          RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  __IO uint32_t     AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  __IO uint32_t     AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  __IO uint32_t     AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32_t          RESERVED4;     /*!< Reserved, 0x5C                                                                    */
  __IO uint32_t     APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  __IO uint32_t     APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32_t          RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  __IO uint32_t     BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
  __IO uint32_t     CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
  uint32_t          RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  __IO uint32_t     SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
  __IO uint32_t     PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
  uint32_t          RESERVED7[1];  /*!< Reserved, 0x88                                                                    */
  __IO DCKCFGR_bits DCKCFGR;       /*!< RCC Dedicated Clocks configuration register,                 Address offset: 0x8C */
} RCC_TypeDef;

#define RCC ((RCC_TypeDef *) RCC_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void configurePLL();
void configureClock();

#endif
