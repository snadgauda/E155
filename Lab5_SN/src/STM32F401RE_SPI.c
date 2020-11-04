// #include "STM32F401RE_TIM.h"
// #include "math.h"
// #include <stdint.h>
// #define LED 5 // D8
// void writeSin(uint16_t freqOut, uint16_t freq, int resolution, float duty, int* table){
   
//    // float val [] = {0.0, 0.3090169943749474, 0.5877852522924731, 0.8090169943749473, 0.9510565162951535, 1.0, 0.9510565162951535, 0.8090169943749473, 0.5877852522924731,0.3090169943749474};
//    // float delay = 500/(freqOut*10);

//    float val = 0;
//    for (int i = 0; i < (1 << resolution); i++){
//       val = 0.5*(sin(2*M_PI/(1<<resolution) * i) + 1);
//       table[i] = (int)(val * (1<<resolution));
//    }

//    float samplee = freqOut * (1 << resolution);
//    int delay = 10000/samplee;

//    while(1){
//       for(int i = 0; i < (1 << resolution); i++){
//          setFrequency(samplee*10, resolution, table[i]);
//          TIM3->CR1.CEN = 0; // turn off
//          TIM3->CNT = 0; // reset counter
//          TIM3->SR.UIF = 0; // reset overflow flag
//          TIM3->ARR.arr = delay; // 10 * delay value (each 10 counts 1 ms), when arr overflows, next freq
//          TIM3->CCR1.ccr = delay * 0.5;
//          TIM3->CR1.CEN = 1; // turn on
//          while (TIM3->SR.UIF == 0);
//       }
//    }

// }