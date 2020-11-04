#include "STM32F401RE_FLASH.h"
#include "STM32F401RE_GPIO.h"
#include "STM32F401RE_RCC.h"
#include "STM32F401RE_TIM.h"
#include "math.h"

#define LED 5

void writeSin(uint16_t freqOut, uint16_t freq, int resolution, float duty, int* table){
   
   // float val [] = {0.0, 0.3090169943749474, 0.5877852522924731, 0.8090169943749473, 0.9510565162951535, 1.0, 0.9510565162951535, 0.8090169943749473, 0.5877852522924731,0.3090169943749474};
   // float delay = 500/(freqOut*10);

   float val = 0;
   for (int i = 0; i < (1 << resolution); i++){
      val = 0.5*(sin(2*M_PI/(1<<resolution) * i) + 1);
      table[i] = (int)(val * (1<<resolution));
   }

   float samplee = freqOut * (1 << resolution);
   int delay = 10000/samplee;

   while(1){
      for(int i = 0; i < (1 << resolution); i++){
         setFrequency(samplee*10, resolution, table[i]);
         TIM3->CR1.CEN = 0; // turn off
         TIM3->CNT = 0; // reset counter
         TIM3->SR.UIF = 0; // reset overflow flag
         TIM3->ARR.arr = delay; // 10 * delay value (each 10 counts 1 ms), when arr overflows, next freq
         TIM3->CCR1.ccr = delay * 0.5;
         TIM3->CR1.CEN = 1; // turn on
         while (TIM3->SR.UIF == 0);
      }
   }

}

int main(){

     // Prescalers
    RCC->CFGR.PPRE2 = 0;
    RCC->CFGR.PPRE1 = 0b100;

    configureFlash(); // so we can go faster
    configureClock(); // set up clock to run at 84 MHz
    // configureHSEClock(); // set up clock to run at 8 MHz
    RCC->AHB1ENR.GPIOAEN = 1; // enable GPIOA
    RCC->APB1ENR.TIM_2 |= 1; // enable timer
    RCC->APB1ENR.TIM_3 |= 1; // enable timer

    // Set PA8 so we can see clock
    pinMode(GPIOA, GPIO_PA8, GPIO_ALT);
    
    // Set LED output
    pinMode(GPIOA, LED, GPIO_OUTPUT);
    // Configure output for PWN on PA0
    GPIOA->AFRL |= 0b0001;
    pinMode(GPIOA, GPIO_PA0, GPIO_ALT);

    // Configure pins for high speed output
    GPIOA->OSPEEDR |= (0b11 << 2*LED);
    GPIOA->OSPEEDR |= (0b11 << 2*GPIO_PA8);
    GPIOA->OSPEEDR |= (0b11 << 2*GPIO_PA0);

    uint16_t freq = 100;
    int resolution = 8;
    float duty = 0.75; // as a decimal
    setFrequencyPWM(freq, resolution, duty); // set timer for given freq, res, and duty cycle
    setupTIM(); // finish timer setup
    TIM3->PSC.scale = 8399; // 10,000 Hz
    
    int* table[ (1 << resolution)] ;
    writeSin(10, freq, resolution, duty, table);
    while (1){};
    return 1; 
}