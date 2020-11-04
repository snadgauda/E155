// STM32F401RE_TIM.h
// Header for TIM functions

#ifndef STM32F4_TIM_H
#define STM32F4_TIM_H

#include <stdint.h> // Include stdint header

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile
#define TIM2_BASE (0x40000000UL) // #Base address of TIM2
#define TIM3_BASE (0x40000400UL) // #Base address of TIM2

///////////////////////////////////////////////////////////////////////////////
// Bitfield struct for TIM
///////////////////////////////////////////////////////////////////////////////

// TIM register structs here
typedef struct {
    volatile uint32_t scale   :32;   // 16 bit prescaler
    // volatile uint32_t         :16;   // reserved
} PRESCALER_bits;

typedef struct {
    volatile uint32_t arr     :32;   // 16 bit prescaler
    // volatile uint32_t         :16;   // reserved
} ARR_bits;

typedef struct {
    volatile uint32_t ccr     :32;   // 16 bit 
    // volatile uint32_t         :16;   // reserved
} CCR_bits;

typedef struct {
    volatile uint32_t CEN   :1;   // Counter Enable
    volatile uint32_t UDIS  :1;   // Update Disable
    volatile uint32_t URS   :1;   // Update Request SRC
    volatile uint32_t OPM   :1;   // One Pulse Mode
    volatile uint32_t DIR   :1;   // Direction
    volatile uint32_t CMS   :2;   // Center Aligned Mode Selection
    volatile uint32_t ARPE  :1;   // Auto Preload Enable
    volatile uint32_t CKD   :2;   // Clock Division
    volatile uint32_t RES1  :22;  // Reserved
} CR1_bits;

typedef struct {
    volatile uint32_t CC1S  :2;   // Capture/Compare 1
    volatile uint32_t OC1FE :1;   // Output compare 1 fast en
    volatile uint32_t OC1PE :1;   // Output compare 1 preload en
    volatile uint32_t OC1M  :3;   // Output compare 1 mode
    volatile uint32_t OC1CE :1;   // Output compare 1 clear enable
    volatile uint32_t CC2S  :2;   // Capture/Compare 2
    volatile uint32_t OC2FE :1;   // Output compare 2 fast en
    volatile uint32_t OC2PE :1;   // Output compare 2 preload en
    volatile uint32_t OC2M  :3;   // Output compare 2 mode
    volatile uint32_t OC2CE :1;   // Output compare 2 clear enable
    volatile uint32_t RES1  :16;  // Reserved
} CMMR1_bits;

typedef struct {
    volatile uint32_t UG    :1;   // Update Generation
    volatile uint32_t CC1G  :1;   // Capture/Compare 1 Generation
    volatile uint32_t CC2G  :1;   // Capture/Compare 2 Generation
    volatile uint32_t CC3G  :1;   // Capture/Compare 3 Generation
    volatile uint32_t CC4G  :1;   // Capture/Compare 4 Generation
    volatile uint32_t RES1  :1;   // Reserved
    volatile uint32_t TG    :1;   // Trigger generation
    volatile uint32_t RES2  :25;   // Reserved
} EGR_bits;

typedef struct {
    volatile uint32_t CNT     :16;   // 16 bit counter
    volatile uint32_t HCNT    :16;   // high counter bits
} CNT_bits;

typedef struct {
    volatile uint32_t CC1E  :1;   // Capture/Compare 1 output enable
    volatile uint32_t CC1P  :1;   // Capture/Compare 1 output polarity
    volatile uint32_t RES1  :1;   // Reserved
    volatile uint32_t CC1NP :1;   // Capture/Compare 1 output 
    volatile uint32_t CC2E  :1;   // Capture/Compare 2 output enable
    volatile uint32_t CC2P  :1;   // Capture/Compare 2 output polarity
    volatile uint32_t RES2  :1;   // Reserved
    volatile uint32_t CC2NP :1;   // Capture/Compare 2 output 
    volatile uint32_t CC3E  :1;   // Capture/Compare 3 output enable
    volatile uint32_t CC3P  :1;   // Capture/Compare 3 output polarity
    volatile uint32_t RES3  :1;   // Reserved
    volatile uint32_t CC3NP :1;   // Capture/Compare 3 output 
    volatile uint32_t CC4E  :1;   // Capture/Compare 4 output enable
    volatile uint32_t CC4P  :1;   // Capture/Compare 4 output polarity
    volatile uint32_t RES4  :1;   // Reserved
    volatile uint32_t CC4NP :1;   // Capture/Compare 4 output 
    volatile uint32_t RES5  :16;  // Reserved
} CCER_bits;

typedef struct {
    volatile uint32_t UIF     :1;   // Update Interupt
    volatile uint32_t CC1IF   :1;   // Capture/Compare 1 interrupt flag
    volatile uint32_t CC2IF   :1;   // Capture/Compare 2 interrupt flag
    volatile uint32_t CC3IF   :1;   // Capture/Compare 3 interrupt flag
    volatile uint32_t CC4IF   :1;   // Capture/Compare 4 interrupt flag
    volatile uint32_t COMIF   :1;   // COM interrupt flag
    volatile uint32_t TIF     :1;   // Trigger interrupt flag
    volatile uint32_t BIF     :1;   // Break interrupt flag
    volatile uint32_t RES1    :1;   // reserved
    volatile uint32_t CC1OF   :1;   //  Capture/Compare 1 overcapture flag
    volatile uint32_t CC2OF   :1;   //  Capture/Compare 2 overcapture flag
    volatile uint32_t CC3OF   :1;   //  Capture/Compare 3 overcapture flag
    volatile uint32_t CC4OF   :1;   //  Capture/Compare 4 overcapture flag 
} SR_bits;

// 328
typedef struct {
    __IO CR1_bits       CR1;        /*!< TIM control register 1,            Address offset: 0x00 */
    __IO uint32_t       CR2;        /*!< TIM control register 2,            Address offset: 0x04 */
    __IO uint32_t       SMCR;       /*!< Slave mode control register,       Address offset: 0x08 */
    __IO uint32_t       DIER;       /*!< DMA/Interrupt enable register,     Address offset: 0x0C */
    __IO SR_bits        SR;         /*!< Status register,                   Address offset: 0x10 */
    __IO EGR_bits       EGR;        /*!< Event generation register,         Address offset: 0x14 */
    __IO CMMR1_bits     CCMR1;      /*!< Capture/Compare mode register 1,   Address offset: 0x18 */
    __IO uint32_t       CCMR2;      /*!< Capture/Compare mode register 2,   Address offset: 0x1C */
    __IO CCER_bits      CCER;       /*!< Capture/Compare enable register 2, Address offset: 0x20 */
    __IO uint32_t       CNT;        /*!< Counter register,                  Address offset: 0x24 */
    __IO PRESCALER_bits PSC;        /*!< Prescaler register,                Address offset: 0x28 */
    __IO ARR_bits       ARR;        /*!< Auto Reload register,              Address offset: 0x2C */
    uint32_t            RESERVED1;  /*!< Reserved, 0x30                                          */
    __IO CCR_bits       CCR1;       /*!< Capture/Compare register 1,        Address offset: 0x34 */
    __IO uint32_t       CCR2;       /*!< Capture/Compare register 2,        Address offset: 0x38 */    
    __IO uint32_t       CCR3;       /*!< Capture/Compare register 3,        Address offset: 0x3C */
    __IO uint32_t       CCR4;       /*!< Capture/Compare register 4,        Address offset: 0x40 */
    uint32_t            RESERVED2;  /*!< Reserved, 0x44                                          */
    __IO uint32_t       DCR;        /*!< DMA Control register,              Address offset: 0x48 */
    __IO uint32_t       DMAR;       /*!< DMA Address register,              Address offset: 0x4C */
    __IO uint32_t       OR2;        /*!< Option register TIM2,              Address offset: 0x50 */
} TIM;

// Pointers to GPIO-sized chunks of memory for each peripheral
#define TIM2 ((TIM*) TIM2_BASE)
#define TIM3 ((TIM*) TIM3_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////
void setFrequency(uint16_t freq, int resolution, int duty);
void setFrequencyPWM(uint16_t freq, int resolution, float duty);
void setupTIM();
#endif

