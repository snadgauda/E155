#include "STM32F401RE_SPI.h"
#include "STM32F401RE_GPIO.h"
#include "STM32F401RE_TIM.h"
#define LED 5 // D8

void initSPI(){
   SPI2->CR1.SPE = 0;
   // define serial clock baud rate
   SPI2->CR1.BR = 0b111; //  divide clock by 256 ; clock is 31,250

   SPI2->CR1.CPOL = 0; // clock is 0 when idle
   SPI2->CR1.CHPA = 0; // The first clock transition is the first data capture edge

   SPI2->CR1.DFF = 1; // 16-bit transmission/reception
   SPI2->CR1.LSBFIRST = 0; // MSB trasmitted first

   SPI2->CR1.SSM = 1; // Control NSS with software
   SPI2->CR1.SSI = 1; // pretend ssi is high
   SPI2->CR1.MSTR = 1; // master config
   SPI2->CR1.SPE = 1; // enable peripherals
}

void writeSquare(int freq){
   // vout = 2.048 * d / 2^8 * 1
   float delay = 500/freq;
   while(1){
   digitalWrite(GPIOB, GPIO_PB1, GPIO_LOW); // NSS low

   // write high: 0011 1000 0000 0000 // writes 2.048 v out
   SPI2->DR = 0x3111;

   while (SPI2->SR.TXE == 0); // wait for write to go to reg
   while (SPI2->SR.BSY); // wait for write to go out
   digitalWrite(GPIOB, GPIO_PB1, GPIO_HIGH);
   // ms_delay(delay);

   // wait for half the frequency
   TIM3->CR1.CEN = 0; // turn off
   TIM3->CNT = 0; // reset counter
   TIM3->SR.UIF = 0; // reset overflow flag
   TIM3->ARR.arr = delay; // 10 * delay value (each 10 counts 1 ms), when arr overflows, next freq
   TIM3->CCR1.ccr = delay * 0.5;
   TIM3->CR1.CEN = 1; // turn on
   while (TIM3->SR.UIF == 0);
   togglePin(GPIOA, LED);

   // write low: 0000 0000 0000 0000
   digitalWrite(GPIOB, GPIO_PB1, GPIO_LOW); // NSS low
   SPI2->DR = 0x3FFF;
   while (SPI2->SR.TXE == 0);
   while (SPI2->SR.BSY);   
   digitalWrite(GPIOB, GPIO_PB1, GPIO_HIGH);
   // ms_delay(delay);

   // wait for half the frequency
   TIM3->CR1.CEN = 0; // turn off
   TIM3->CNT = 0; // reset counter
   TIM3->SR.UIF = 0; // reset overflow flag
   TIM3->ARR.arr = delay; // 10 * delay value (each 10 counts 1 ms), when arr overflows, next freq
   TIM3->CCR1.ccr = delay * 0.5;
   TIM3->CR1.CEN = 1; // turn on
   while (TIM3->SR.UIF == 0);
   togglePin(GPIOA, LED);

   //set not chip select high
   }

}

void writeSin(int freq){
   // uint16_t sine [] = {0x3000, 0x301F, 0x303F, 0x305F, 0x303F, 0x301F};
   uint16_t sine [] = {2000, 1999, 1998, 1995, 1992, 1987, 1982, 1975, 1968, 1960, 1951, 1940, 1929, 1917, 1904, 1891, 1876, 1860, 1844, 1827, 1809, 1790, 1770, 1750, 1728, 1707, 1684, 1661, 1637, 1612, 1587, 1562, 1535, 1509, 1481, 1453, 1425, 1397, 1368, 1338, 1309, 1278, 1248, 1218, 1187, 1156, 1125, 1094, 1062, 1031, 1000, 968, 937, 905, 874, 843, 812, 781, 751, 721, 690, 661, 631, 602, 574, 546, 518, 490, 464, 437, 412, 387, 362, 338, 315, 292, 271, 249, 229, 209, 190, 172, 155, 139, 123, 108, 95, 82, 70, 59, 48, 39, 31, 24, 17, 12, 7, 4, 1, 0, 0, 0, 1, 4, 7, 12, 17, 24, 31, 39, 48, 59, 70, 82, 95, 108, 123, 139, 155, 172, 190, 209, 229, 249, 271, 292, 315, 338, 362, 387, 412, 437, 464, 490, 518, 546, 574, 602, 631, 661, 690, 721, 751, 781, 812, 843, 874, 905, 937, 968, 999, 1031, 1062, 1094, 1125, 1156, 1187, 1218, 1248, 1278, 1309, 1338, 1368, 1397, 1425, 1453, 1481, 1509, 1535, 1562, 1587, 1612, 1637, 1661, 1684, 1707, 1728, 1750, 1770, 1790, 1809, 1827, 1844, 1860, 1876, 1891, 1904, 1917, 1929, 1940, 1951, 1960, 1968, 1975, 1982, 1987, 1992, 1995, 1998, 1999};
   // vout = 2.048 * d / 2^n & G
   float delay = 500/(freq*100);
   while(1){
      // have array of 20 values that makes up a sin wave
      // for loop
      // write value
      // wait for 1/20 of freq
      // repeat untilall values have been written
      // start again
      for(int i = 0; i < 100; i++){
         digitalWrite(GPIOB, GPIO_PB1, GPIO_LOW); // NSS low
         uint16_t val = 0x3000 | sine[i];
         SPI2->DR = val;
         while (SPI2->SR.TXE == 0);
         while (SPI2->SR.BSY);   
         digitalWrite(GPIOB, GPIO_PB1, GPIO_HIGH);
         // ms_delay(delay);
         TIM3->CR1.CEN = 0; // turn off
         TIM3->CNT = 0; // reset counter
         TIM3->SR.UIF = 0; // reset overflow flag
         TIM3->ARR.arr = delay; // 10 * delay value (each 10 counts 1 ms), when arr overflows, next freq
         TIM3->CCR1.ccr = delay * 0.5;
         TIM3->CR1.CEN = 1; // turn on
         while (TIM3->SR.UIF == 0);
      }
      for(int i = 99; i >= 0; i--){
         digitalWrite(GPIOB, GPIO_PB1, GPIO_LOW); // NSS low
         uint16_t val = 0x3000 | sine[i];
         SPI2->DR = val;
         while (SPI2->SR.TXE == 0);
         while (SPI2->SR.BSY);   
         digitalWrite(GPIOB, GPIO_PB1, GPIO_HIGH);
         // ms_delay(delay);
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