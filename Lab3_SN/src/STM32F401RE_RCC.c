// STM32F401RE_RCC.c
// Source code for RCC functions

#include "STM32F401RE_RCC.h"

void configurePLL() {
    /* TODO: Set clock to 24 MHz
     Output freq = (src_clk) * (N/M) / P
     (8 MHz) * (N/M) / P = 24 MHz
     M:8, N:192, P:8
     Use HSE as PLLSRC
     // HSE is 8 MHZ so M = 8
     // 492 <= N <= 192
    */
    RCC->CR.PLLON = 0; // Turn off PLL
    while (RCC->CR.PLLRDY != 0); // Wait till PLL is unlocked (e.g., off)

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
    while(!(RCC->CFGR.SWS == 0b10));

    // RCC->DCKCFGR.TIMPRE = 1;
}
