// lab3_starter.c
// Fur Elise, E155 Lab 3
// Updated Spring 2020

#define LED 5 // D8
#define DELAY_MS  2000

#include "STM32F401RE_GPIO.h"
#include "STM32F401RE_RCC.h"
#include "STM32F401RE_FLASH.h"
#include "STM32F401RE_TIM.h"

// Pitch in Hz, duration in ms
const int notes[][2] = {
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	250},
{  0,	125},
{494,	125},
{523,	125},
{587,	125},
{659,	375},
{392,	125},
{699,	125},
{659,	125},
{587,	375},
{349,	125},
{659,	125},
{587,	125},
{523,	375},
{330,	125},
{587,	125},
{523,	125},
{494,	250},
{  0,	125},
{330,	125},
{659,	125},
{  0,	250},
{659,	125},
{1319,	125},
{  0,	250},
{623,	125},
{659,	125},
{  0,	250},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	500},
{  0,	0}};

const int notes2[][2] = {
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{  0,	0}};

void ms_delay(int ms) {
   while (ms-- > 0) {
      volatile int x=1000;
      while (x-- > 0)
         __asm("nop");
   }
}

int main(void) {
    // Prescalers
    RCC->CFGR.PPRE2 = 0;
    RCC->CFGR.PPRE1 = 0b100;

    configureFlash(); // so we can go faster
    configureClock(); // set up clock to run at 84 MHz
    RCC->AHB1ENR.GPIOAEN = 1; // enable GPIOA

    // Prescale Clock
    RCC->CFGR.MCO1PRE = 0b110;
    RCC->CFGR.MCO1 = 0b11;

    // Set PA8 so we can see clock
    pinMode(GPIO_PA8, GPIO_ALT);
    // Set LED output
    pinMode(LED, GPIO_OUTPUT);

    // Configure output for PWN on PA0
    GPIOA->AFRL |= 0b0001;
    pinMode(GPIO_PA0, GPIO_ALT);

    // Configure pins for high speed output
    GPIOA->OSPEEDR |= (0b11 << 2*LED);
    GPIOA->OSPEEDR |= (0b11 << 2*GPIO_PA8);
    GPIOA->OSPEEDR |= (0b11 << 2*GPIO_PA0);

    // start timers
    RCC->APB1ENR.TIM_2 |= 1;
    RCC->APB1ENR.TIM_3 |= 1;

    // CLK / (scale * arr)
    // set scale and arr to -1 what u want the value to be
    // ccr = 0.5 * arr
    TIM2->PSC.scale = 63; // gives 20 MHz lowest value
    TIM2->ARR.arr = 1;
    TIM2->CCR1.ccr = 1; // 50% for duty cycle

    TIM2->CCMR1.OC1M = 0b110; // set PWM Mode 1
    TIM2->CCMR1.OC1PE = 1; // changes when preload register changes are used
    TIM2->CCMR1.OC1FE = 1; // fast preload

    TIM2->CR1.ARPE = 1; // buffer ARR 
    TIM2->EGR.UG = 1; // initalize registers
    TIM2->CCER.CC1E = 1; // enable chanel 1 output

    TIM2->CR1.CEN = 1; // called last - starts counter

    // TIM3 Setup for Delay
    TIM3->PSC.scale = 8399; // 10,000 Hz

    // loop through notes
    int i = 0; // note counter
    int done = 0; // end of array reached
    while(!done) {
        uint32_t freq = notes2[i][0];
        int delay = notes2[i][1];

        if (freq == 0){
            TIM2->ARR.arr = 1; // shhhhhh
            TIM2->CCR1.ccr = 0; // 50% for duty cycle
        } else {
            TIM2->ARR.arr = 1312500/freq - 1; // play note (-1 cuz that's how its set up)
            TIM2->CCR1.ccr = (1312500/freq - 1) /2 ; // 50% for duty cycle
        }
        
        // delay for delay val
        TIM3->CR1.CEN = 0; // turn off
        TIM3->CNT = 0; // reset counter
        TIM3->SR.UIF = 0; // reset overflow flag
        TIM3->ARR.arr = delay * 10; // 10 * delay value (each 10 counts 1 ms), when arr overflows, next freq
        TIM3->CCR1.ccr = delay * 5;
        TIM3->CR1.CEN = 1; // turn on
        while (TIM3->SR.UIF == 0);
        togglePin(LED);
        i++;
        if (notes2[i][0] == 0 && notes2[i][1] == 0){ // ends in 0,0
            done = 1;
        }
    }

    i = 0;
    done = 0; // end of array reached

    while(!done) {
        uint32_t freq = notes[i][0];
        int delay = notes[i][1];

        if (freq == 0){
            TIM2->ARR.arr = 1; // shhhhhh
            TIM2->CCR1.ccr = 0; // 50% for duty cycle
        } else {
            TIM2->ARR.arr = 1312500/freq - 1; // play note (-1 cuz that's how its set up)
            TIM2->CCR1.ccr = (1312500/freq - 1) /2 ; // 50% for duty cycle
        }
        
        // delay for delay val
        TIM3->CR1.CEN = 0; // turn off
        TIM3->CNT = 0; // reset counter
        TIM3->SR.UIF = 0; // reset overflow flag
        TIM3->ARR.arr = delay * 10; // 10 * delay value (each 10 counts 1 ms), when arr overflows, next freq
        TIM3->CCR1.ccr = delay * 5;
        TIM3->CR1.CEN = 1; // turn on
        while (TIM3->SR.UIF == 0);
        togglePin(LED);
        i++;
        if (notes[i][0] == 0 && notes[i][1] == 0){ // ends in 0,0
            done = 1;
        }
    }
    

    // Blink LED
    // while(1) {
    //     ms_delay(DELAY_MS);
    //     togglePin(SPEAKER);
    // }
    return 0;
	
};
