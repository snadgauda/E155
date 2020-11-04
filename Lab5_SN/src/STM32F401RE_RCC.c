// STM32F401RE_RCC.c
// Source code for RCC functions

#include "STM32F401RE_RCC.h"

void configurePLL() {
    RCC->CR.PLLON = 0; // Turn off PLL
    while (RCC->CR.PLLRDY != 0); // Wait till PLL is unlocked (e.g., off)

    // sets clock to 84 MHz
    RCC->PLLCFGR.PLLSRC =  1; // pg 105 reference manual
    RCC->PLLCFGR.PLLM = 8;
    RCC->PLLCFGR.PLLN = 336;
    RCC->PLLCFGR.PLLP = 0b01;


    // TODO: Enable PLL and wait until it's locked (i.e., until PLLRDY goes high)
    RCC->CR.PLLON = 1; // turn on pll
    while(!(RCC->CR.PLLRDY));
}


void configureClock(){
    // Turn on and bypass for HSE from ST-LINK
    RCC->CR.HSEBYP = 1;
    RCC->CR.HSEON = 1;
    while(!RCC->CR.HSERDY);
    
    // Configure and turn on PLL
    configurePLL();

    // Select PLL as clock source
    RCC->CFGR.SW = SW_PLL;
    while(!(RCC->CFGR.SWS == SW_PLL));

    // RCC->DCKCFGR.TIMPRE = 1;
}

void configureHSEClock(){
    RCC->CR.HSEBYP = 1;
    RCC->CR.HSEON = 1;
    while(!RCC->CR.HSERDY);

    RCC->CFGR.SW = SW_HSE;
    while(!(RCC->CFGR.SWS == SW_HSE));

}
