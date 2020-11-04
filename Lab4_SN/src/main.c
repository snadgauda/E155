#include "STM32F401RE_FLASH.h"
#include "STM32F401RE_GPIO.h"
#include "STM32F401RE_RCC.h"
#include "STM32F401RE_SPI.h"
#include "STM32F401RE_TIM.h"

int main(){

     // Prescalers
    RCC->CFGR.PPRE2 = 0;
    RCC->CFGR.PPRE1 = 0b100;

    configureFlash(); // so we can go faster
    // configureClock(); // set up clock to run at 84 MHz
    configureHSEClock(); // set up clock to run at 8 MHz
    RCC->AHB1ENR.GPIOAEN = 1; // enable GPIOA
    RCC->AHB1ENR.GPIOBEN = 1;
    RCC->APB1ENR.TIM_3 |= 1;

    // Set PA8 so we can see clock
    pinMode(GPIOA, GPIO_PA8, GPIO_ALT);
    // Set LED output
    pinMode(GPIOA, 5, GPIO_OUTPUT);
    
    pinMode(GPIOB, GPIO_PB1, GPIO_OUTPUT); // set NSS as GPIO output
    GPIOB->AFRH.AFRH13 = 0b0101;
    pinMode(GPIOB, GPIO_PB13, GPIO_ALT); // setup clock 
    GPIOB->AFRH.AFRH14 = 0b0101;
    pinMode(GPIOB, GPIO_PB14, GPIO_ALT); // setup MISO
    GPIOB->AFRH.AFRH15 = 0b0101;
    pinMode(GPIOB, GPIO_PB15, GPIO_ALT); // setup MOSI

    // configure SPI
    RCC->APB1ENR.SPI2EN = 1;
    initSPI();
    // TIM3 Setup for Delay
    TIM3->PSC.scale = 7999; // 1,000 Hz

    // set NSS manually at some point (pg 563)
    digitalWrite(GPIOB, GPIO_PB1, GPIO_LOW);

    // writeSquare(10);
    writeSin(2);
    // while(1);
    return 1; 
}   