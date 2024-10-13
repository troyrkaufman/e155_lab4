// Author: Troy Kaufman
// Email: tkaufman@hc.edu
// Date: 10/3/24

#include <stdint.h> 
#include "RCC.h"
#include "GPIO_h.h"
#include "TIMER.h"
#include "STM32L432KC_FLASH.h"

// Pitch in Hz, duration in ms
const int notes[][2] = {
{220, 125},
{1000, 125},
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
/*
// Happy Birthday Song Notes
const uint16_t notes[][2] = {
   {262, 250},  // C4, 250 ms - "Happy"
    {262, 250},  // C4, 250 ms - "Birth"
    {294, 500},  // D4, 500 ms - "day"
    {262, 500},  // C4, 500 ms - "to"
    {349, 500},  // F4, 500 ms - "you"
    {330, 500},  // E4, 500 ms - (pause)

    {262, 250},  // C4, 250 ms - "Happy"
    {262, 250},  // C4, 250 ms - "Birth"
    {294, 500},  // D4, 500 ms - "day"
    {262, 500},  // C4, 500 ms - "to"
    {392, 500},  // G4, 500 ms - "you"
    {349, 500},  // F4, 500 ms - (pause)

    {262, 250},  // C4, 250 ms - "Happy"
    {262, 250},  // C4, 250 ms - "Birth"
    {523, 500},  // C5, 500 ms - "day"
    {440, 500},  // A4, 500 ms - "dear"
    {349, 500},  // F4, 500 ms - "Name"
    {330, 500},  // E4, 500 ms - (pause)

    {466, 250},  // A#4, 250 ms - "Happy"
    {466, 250},  // A#4, 250 ms - "Birth"
    {440, 500},  // A4, 500 ms - "day"
    {349, 500},  // F4, 500 ms - "to"
    {392, 500},  // G4, 500 ms - "you"
    {349, 500},   // F4, 500 ms - (end)
    {0,0}};
*/

int main(void) {
    ///////////////////////////////////////////////////////////////////////////////////////////////
    //Must configure AHB PRESC and APB1 PRESC to divisors (1) before giving input clock to TIMx 
    ///////////////////////////////////////////////////////////////////////////////////////////////
    RCC -> CFGR |= (0b1001 << 4); // SYSCLK is divided by 4 from the AHB PRESC in clock tree (to get to 1MHz)
    RCC -> CFGR |= (0b000 << 8);  // HCLK (formerly SYSCLK)is not divided by APB1 PRESC (Setting this to 0b0xx avoids 2x multiplier)

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Peripheral Configuration
    ///////////////////////////////////////////////////////////////////////////////////////////////
    RCC -> AHB2ENR |= (1<<0);    // GPIOA enable

    RCC -> APB2ENR |= (1 << 17); // TIM16 clock enable
    RCC -> APB2ENR |= (1 << 16); // TIM15 clock enable

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // GPIO Alternate Function Configuration
    ///////////////////////////////////////////////////////////////////////////////////////////////

    GPIOA -> MODER &= ~(1<<12); // Make pin 12 (PA6) an alternate function
    GPIOA -> MODER |= (1<<13);  // Make pin 12 (PA6) an alternate function 

    GPIOA -> AFRL |= (0b1110 << 24); // Configure pin 12 (PA6) to be an alternate function of type TIM16.....

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Play Music
    ///////////////////////////////////////////////////////////////////////////////////////////////
    pwm_init(TIM16);           // Initialize PWM related configuration registers
    delay_init(TIM15);         // Initialize delay related configuration registers

    int num_notes = sizeof(notes) / sizeof(notes[0]); // Calculates number of pairs

    int freq; 
    int duration;
    int x = 0; 

     for (int i=0; i < num_notes; i++){
        pwm_update(TIM16, notes[i][0]);                  // Produces PWM signal
        delay_update(TIM15, notes[i][1]);                // Delays the specified amont of time
    }
    while(1);                                            // Prevent PC to go to forever loop handler
}

