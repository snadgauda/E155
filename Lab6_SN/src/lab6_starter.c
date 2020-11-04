// /**
//     Main file
//     @file lab6_starter.c
//     @author Josh Brake
//     @version 1.0 10/1/2020
// */

#include "STM32F401RE.h"
#include <string.h>
#include <math.h> 

#define USART_ID USART2_ID

int main(void) {
    configureFlash();
    configureClock();

    RCC->AHB1ENR.GPIOAEN = 1;
    // Initialize timer
    RCC->APB1ENR |= (1 << 0); // TIM2EN

    initUSART(USART_ID);

    // TODO: Setup 1-Wire
    pinMode(GPIOx, ONEWIRE_PIN, GPIO_OUTPUT);
    setupOneWire();

    // Send initialization sequence
    init();
    
    // while(1){
        // Send Read ROM command code
        write_byte(0x33);
    // }
    

    uint8_t rom_code[8];
    // Read out ROM code
    for(int i = 0; i < 8; i++){
        rom_code[i] = read_byte();
    }

    while(1){
        // Send initialization sequence
        init();

        write_rom(rom_code);

        // read temp
        write_byte(0x44);

        write_rom(rom_code);

        // get temp
        uint8_t scratchpad[8];
        read_scratchpad(scratchpad);

        // Temp Converstion
        int temperature_whole = 0;
        double temperature_frac = 0;
        uint8_t sign = (scratchpad[1] >> 7);
        uint8_t temp = 0;
        // temp =  ((scratchpad[1] << 5)>>3);
        temp =  scratchpad[1];
        for(int i = 0; i < 3; ++i){
            temperature_whole += (temp & 1) * pow(2,4 + i);
            temp = temp >> 1;
        }
        temp = scratchpad[0] >> 4;
        for(int i = 0; i < 4; ++i){
            temperature_whole += (temp & 1) * pow(2, i);
            temp = temp >> 1;
        }

        uint8_t frac = 0;
        frac = ((scratchpad[0] << 4) >> 4);

        if (sign == 1){
            temperature_whole= temperature_whole * -1;
        }

        for(int i = 1; i < 4; i++){
            temperature_frac += (frac & 1) * pow(2, -i);
            frac = frac >> 1;
        }

        int print_frac = temperature_frac * 1000;

        // Print out message to serial port
        uint8_t msg[64];
        sprintf(msg, "Temperature is: %d.%d deg C\n\r", temperature_whole, print_frac);

        uint8_t i = 0;
        do
        {
            sendChar(USART_ID, msg[i]);
            i += 1;
        } while (msg[i]);

        
        
        delay_millis(ONEWIRE_TIMx, 500);
    }
}