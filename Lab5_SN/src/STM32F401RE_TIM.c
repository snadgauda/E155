// STM32F401RE_TIM.c
// Source code for TIM functions

#include "STM32F401RE_TIM.h"

void setFrequency(uint16_t freq, int resolution, int duty){
    int arr = 0;
    if (resolution == 8){
        TIM2->ARR.arr = 255;
        arr = 255;
    }
    else if (resolution == 12){
        TIM2->ARR.arr = 4095;
        arr = 4095;
    }
    else { // resolution == 16
        TIM2->ARR.arr = 65535;
        arr = 65535;
    }

    TIM2->PSC.scale = 84000000/(freq*arr)-1; // for frequency
    TIM2->CCR1.ccr = duty; // decides duty cycle
}

void setFrequencyPWM(uint16_t freq, int resolution, float duty){
    int arr = 0;
    if (resolution == 8){
        TIM2->ARR.arr = 255;
        arr = 255;
    }
    else if (resolution == 12){
        TIM2->ARR.arr = 4095;
        arr = 4095;
    }
    else { // resolution == 16
        TIM2->ARR.arr = 65535;
        arr = 65535;
    }

    TIM2->PSC.scale = 84000000/(freq*arr)-1; // for frequency
    TIM2->CCR1.ccr = (1-duty)*arr; // decides duty cycle
}

void setupTIM(){
    TIM2->CCMR1.OC1M = 0b110; // set PWM Mode 1
    TIM2->CCMR1.OC1PE = 1; // changes when preload register changes are used
    TIM2->CCMR1.OC1FE = 1; // fast preload

    TIM2->CR1.ARPE = 1; // buffer ARR 
    TIM2->EGR.UG = 1; // initalize registers
    TIM2->CCER.CC1E = 1; // enable chanel 1 output

    TIM2->CR1.CEN = 1; // called last - starts counter
}
