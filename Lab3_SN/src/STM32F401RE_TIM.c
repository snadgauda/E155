// STM32F401RE_TIM.c
// Source code for TIM functions

#include "STM32F401RE_TIM.h"

// void setPrescale(int x){
//     TIM2->PSC.scale = 0b1;
// }

// void setArr(int x){
//     TIM2->ARR.arr |= 0b1000; // how long counter is
//     TIM2->CCR1.ccr |= 0b0100; // Duty cycle (1/2 ARR)
// }

// void counter() {
//     TIM2->CR1.CEN = 1; // enable
// }

// void setMode() {
//     TIM2->CCMR1.OC1M = 0b110; // set PWM Mode 1
//     TIM2->CCMR1.OC1PE = 1; // changes when preload register changes are used
//     TIM2->CCMR1.OC1FE = 1;

//     // do this somewhere else?
//     TIM2->CR1.ARPE = 1; // buffer ARR 
//     TIM2->EGR.UG = 1; // initalize registers
//     TIM2->CCER.CC1E = 1; // enable chanel 1 output
// }