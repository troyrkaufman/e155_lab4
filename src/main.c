
// lab4_starter.c
// Fur Elise, E155 Lab 4
// Updated Fall 2024

#include <stdint.h> 
#include "RCC.h"
#include "GPIO_h.h"
#include "TIMER.h"

#define SYS_CLK_FRQ 1000000 // 1 MHz

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

// Delay function 
/*int delay_mill (int time){
    TIM15 -> PSC = (SYS_CLK_FRQ / 1000) - 1; // Creating one ms resolution from system clock

    TIM15 -> ARR = time - 1;               // ARR = time in ms because the counter counts from 0 to ARR

    TIM15 -> CNT = 0;                      // Ensures counter starts at zero everytime

    TIM15 -> SR &= ~(1<<0);                // Resets interupt flag upon counter reset

    TIM15 -> CR1 |= (1<<0);                // Start tIM15 counter

    while (!(TIM15 -> SR & (1<<0)));       // Wait until flag is triggered (Counter == ARR)

    TIM15 -> CR1 &= ~(1<<0);               // Disable counter

    TIM15 -> SR &= ~ (1<<0);               // Clear the interupt flag

    return 1;                              // Signal that the timer is finished
} */

// Square wave function
/*void pwm (int freq){
   
    TIM16 -> PSC = 9;                      // Setting prescaler to 9 to get CK_CNT = 100k Hz from 1 MHz clock input
    
    TIM16 -> EGR |= (1<<0);                // Initialize all registers to allow preload registers to transfer to shadow registers during an update event
    
    TIM16 -> CCMR1_OUTPUT |= (0b110<<4);   // Setting to OUPUT PWM mode TIMx_CNT < TIMx_CCR1 else inactive
    TIM16 -> CCMR1_OUTPUT |= (1<<3);

    TIM16 -> CR1 |= (1<<7);                // Auto-reload preload enabled. The ARR is now buffered
    
    TIM16 -> CCER &= ~(1<<1);              // Configure output as active HIGH

    volatile int arr = (SYS_CLK_FRQ/freq) - 1; // Calculation for ARR
    TIM16 -> ARR = arr;                    // Sets PWM frequency to requested amount
    TIM16 -> CCR1 = arr/2;                 // Sets duty cycle to 50%

    TIM16 -> CR1 |= (1<<0);                // Enables clock input after timer configuration ***LAST STEP***

    // While statement?

} */

int main(void) {
    ///////////////////////////////////////////////////////////////////////////////////////////////
    //Must configure AHB PRESC and APB1 PRESC to divisors (1) before giving input clock to TIMx 
    ///////////////////////////////////////////////////////////////////////////////////////////////
    RCC -> CFGR |= (0b1001 << 4); // SYSCLK is divided by 4 from the AHB PRESC in clock tree (to get to 1MHz)
    RCC -> CFGR |= (0b000 << 8);  // HCLK (formerly SYSCLK)is not divided by APB1 PRESC 

    // Missing x1 or x2 ??????????
    

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

     for (int i=0; i < num_notes; i++){
        pwm_update(TIM16, notes[i][0]);                       // Produces PWM signal
        delay_update(TIM15, notes[i][1]);                // Delays the specified amont of time
    }

    //while(1);                            // Don't play anything after song is finished
}

 /*for (int i=0; i < num_notes; i++){
        if (notes[i][0] == 0) {
          TIM16->CR1 &= ~(1<<0);
          delay_update(TIM15, notes[i][1]);
        } else {
          pwm_update(TIM16, notes[i][0]);
          TIM16->CR1 |= (1<<0);
          delay_update(TIM15, notes[i][1]);
        } 
    } */