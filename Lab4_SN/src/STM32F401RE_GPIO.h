// STM32F401RE_GPIO.h
// Header for GPIO functions

#ifndef STM32F4_GPIO_H
#define STM32F4_GPIO_H

#include <stdint.h> // Include stdint header

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

// Values for GPIO pins ("val" arguments)
#define GPIO_LOW    0
#define GPIO_HIGH   1

// Base addresses for GPIO ports
#define GPIOA_BASE  (0x40020000UL)
#define GPIOB_BASE  (0x40020400UL)

// Arbitrary GPIO functions for pinMode()
#define GPIO_INPUT  0
#define GPIO_OUTPUT 1
#define GPIO_ALT    2
#define GPIO_ANALOG 3

// Pin definitions for every GPIO pin
#define GPIO_PA0    0
#define GPIO_PA1    1
#define GPIO_PA2    2
#define GPIO_PA3    3
#define GPIO_PA4    4
#define GPIO_PA5    5
#define GPIO_PA6    6
#define GPIO_PA7    7
#define GPIO_PA8    8
#define GPIO_PA9    9
#define GPIO_PA10   10
#define GPIO_PA11   11
#define GPIO_PA12   12
#define GPIO_PA13   13
#define GPIO_PA14   14
#define GPIO_PA15   15

#define GPIO_PB0    0
#define GPIO_PB1    1
#define GPIO_PB2    2
#define GPIO_PB3    3
#define GPIO_PB4    4
#define GPIO_PB5    5
#define GPIO_PB6    6
#define GPIO_PB7    7
#define GPIO_PB8    8
#define GPIO_PB9    9
#define GPIO_PB10   10
#define GPIO_PB11   11
#define GPIO_PB12   12
#define GPIO_PB13   13
#define GPIO_PB14   14
#define GPIO_PB15   15

///////////////////////////////////////////////////////////////////////////////
// Bitfield struct for GPIO
///////////////////////////////////////////////////////////////////////////////

// GPIO register structs here
typedef struct {
    volatile uint32_t AFRL0     : 4;
    volatile uint32_t AFRL1     : 4;
    volatile uint32_t AFRL2     : 4;
    volatile uint32_t AFRL3     : 4;
    volatile uint32_t AFRL4     : 4;
    volatile uint32_t AFRL5     : 4;
    volatile uint32_t AFRL6     : 4;
    volatile uint32_t AFRL7     : 4;
} AFRL_bits;

typedef struct {
    volatile uint32_t AFRH8     : 4;
    volatile uint32_t AFRH9     : 4;
    volatile uint32_t AFRH10    : 4;
    volatile uint32_t AFRH11    : 4;
    volatile uint32_t AFRH12    : 4;
    volatile uint32_t AFRH13    : 4;
    volatile uint32_t AFRH14    : 4;
    volatile uint32_t AFRH15    : 4;
} AFRH_bits;

typedef struct {
    volatile uint32_t   MODER;   // GPIO Offset 0x00 GPIO port mode register
    volatile uint32_t   OTYPER;  // GPIO Offset 0x04
    volatile uint32_t   OSPEEDR; // GPIO Offset 0x08
    volatile uint32_t   PURPDR;  // GPIO Offset 0x0C
    volatile uint32_t   IDR;     // GPIO Offset 0x10
    volatile uint32_t   ODR;     // GPIO Offset 0x14
    volatile uint32_t   BSRR;    // GPIO Offset 0x18
    volatile uint32_t   LCKR;    // GPIO Offset 0x1C
    volatile AFRL_bits  AFRL;    // GPIO Offset 0x20
    volatile AFRH_bits  AFRH;    // GPIO Offset 0x24
} GPIO;

// Pointers to GPIO-sized chunks of memory for each peripheral
#define GPIOA ((GPIO*) GPIOA_BASE)
#define GPIOB ((GPIO*) GPIOB_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void pinMode(GPIO* gpio, int pin, int function);

int digitalRead(GPIO* gpio, int pin);

void digitalWrite(GPIO* gpio, int pin, int val);

void togglePin(GPIO* gpio, int pin);

#endif