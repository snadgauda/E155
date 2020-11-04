/**
    1WIRE Library: Initializes and controls data acquisition over a 1-Wire interface
    @file STM32F401RE_1WIRE.c
    @author Josh Brake
    @version 1.0 10/1/2020
*/

#include "STM32F401RE_1WIRE.h"


void setupOneWire(void){
    initTIM(ONEWIRE_TIMx);
    GPIOx->OTYPER |= (1 << ONEWIRE_PIN);
    GPIOx->OSPEEDR |= (0b11 << ONEWIRE_PIN * 2);
}

uint8_t init(void){
    // pull the pin low 
    digitalWrite(GPIOx, ONEWIRE_PIN, 0);
    
    // delay > 480 microseconds
    delay_micros(ONEWIRE_TIMx, 500);

    // stop driving the pin low
    digitalWrite(GPIOx, ONEWIRE_PIN, 1);

    // wait for a response
    // while(digitalRead(GPIOx, ONEWIRE_PIN) == 1); // device waits for input to float back up
    delay_micros(ONEWIRE_TIMx, 70);

    if (digitalRead(GPIOx, ONEWIRE_PIN) == 0){
        delay_micros(ONEWIRE_TIMx, 480);    
        return 0;
    }
    while(digitalRead(GPIOx, ONEWIRE_PIN) == 1); // wait for input to float back up
    delay_micros(ONEWIRE_TIMx, 480);

    return 1;
}

void write_bit(uint8_t val){
    digitalWrite(GPIOx, ONEWIRE_PIN, 0);
    if (val == 0){
        delay_micros(ONEWIRE_TIMx, 70);
        digitalWrite(GPIOx, ONEWIRE_PIN, 1);
        delay_micros(ONEWIRE_TIMx, 15);
    } else{
        delay_micros(ONEWIRE_TIMx, 5);
        digitalWrite(GPIOx, ONEWIRE_PIN, 1);
        delay_micros(ONEWIRE_TIMx, 60);
    }
}

uint8_t read_bit(void){
    digitalWrite(GPIOx, ONEWIRE_PIN, 0); // write low
    delay_micros(ONEWIRE_TIMx, 2); // wait at least 1 microsecond
    digitalWrite(GPIOx, ONEWIRE_PIN, 1); // write high
    delay_micros(ONEWIRE_TIMx, 10); // wait at least 10 microseconds
    uint8_t val = digitalRead(GPIOx, ONEWIRE_PIN);
    delay_micros(ONEWIRE_TIMx, 55); // wait at least 60 microseconds
    return val;
}

void write_byte(uint8_t val){
    for(int i = 0; i < 8; i++){
        write_bit(val & 1);
        val = val >> 1;
    }
}

uint8_t read_byte(void){
    uint8_t val = 0;
    for(int i = 0; i < 8; i++){
        val |= (read_bit() << i);
    }
    return val;
}

void write_rom(uint8_t rom_code[8]){
    init();

    write_byte(0x55); // match rom command
    // rom sequence
    for(int i = 0; i < 8; i++){
        write_byte(rom_code[i]);
    }
    
}

void read_scratchpad(uint8_t scratchpad[8]) {
    // Send Read Scratchpad command
    write_byte(0xBE);
    // Read out scratchpad
    for(int i = 0 ; i < 8; ++i){
        scratchpad[i] = read_byte();
    }
}