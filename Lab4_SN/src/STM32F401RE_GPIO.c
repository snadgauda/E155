// STM32F401RE_GPIO.c
// Source code for GPIO functions

#include "STM32F401RE_GPIO.h"

void pinMode(GPIO* gpio, int pin, int function) {
    gpio->MODER &= ~(0b11 << pin*2);
    gpio->MODER |= (function << pin*2);
}

int digitalRead(GPIO* gpio, int pin) {
    int pin_value = ((gpio->IDR) >> pin) & 1;
    return pin_value;
}

void digitalWrite(GPIO* gpio, int pin, int val) {
    if (val== 0){
        gpio->ODR &= ~(0b1 << pin);
    }else{
        gpio->ODR |= (0b1 << pin);
    }   
}

void togglePin(GPIO* gpio, int pin) {
    // int pin_value = digitalRead(gpio, pin);
    // digitalWrite(gpio, pin, !pin_value);
    GPIOA->ODR ^= (1 << pin);
}