// Header for TIMER functions

#include <stdint.h>

#define TIM15_BASE (0x40014000)
#define TIM16_BASE (0x40014400)
#define CK_CNT 10000

typedef struct{
    volatile uint32_t CR1;           // 0x00
    volatile uint32_t CR2;           // 0x04
             uint32_t reserved;      // 0x08
    volatile uint32_t DIER;          // 0x0C
    volatile uint32_t SR;
    volatile uint32_t EGR;           // 
    volatile uint32_t CCMR1_OUTPUT;  // 0x18 First 32 bits
    volatile uint32_t CCMR1_INPUT;   // 0x1C Second 32 bits
    volatile uint32_t CCER;          // 0x20
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t RCR;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;          // 0x38
             uint32_t reserved1;     // 0x3C
    volatile uint32_t reserved2;     // 0x40
    volatile uint32_t BDTR;          // 0x44
    volatile uint32_t DCR;
    volatile uint32_t OR1;           // 0x50
             uint32_t reserved4;     // 0x54
             uint32_t reserved5;     // 0x58
             uint32_t reserved6;     // 0x5C
    volatile uint32_t OR2;           // 0x^0
} TIMx_TypeDef;

#define TIM16 ((TIMx_TypeDef *) TIM16_BASE)
#define TIM15 ((TIMx_TypeDef *) TIM15_BASE)

void pwm_init(TIMx_TypeDef * TIMx){
    TIMx->PSC = 99;                      // Setting prescaler to 19 to get CK_CNT = 50k Hz from 1 MHz clock input
    TIMx->CCMR1_OUTPUT |= (0b110<<4);   // Setting to OUPUT PWM mode TIMx_CNT < TIMx_CCR1 else inactive
    TIMx->CCMR1_OUTPUT |= (1<<3);       // Preload register on TIMxCCR1 is enabled
    TIMx->BDTR |= (1<<15);              // (MOE) OC and OCN outputs are enabled if their respective enable bits are set (CCxE, CCxNE, in TIMx_CCER register)
    TIMx->CCER |= (1<<0);               // Configure Channel 1 as output
    TIMx->CR1 |= (1<<7);                // Auto-reload preload enabled. The ARR is now buffered
    TIMx->CCER &= ~(1<<1);               // Configure output as active HIGH
    TIMx->EGR |= (1<<0);                // Initialize all registers to allow preload registers to transfer to shadow registers during an update event
    TIMx->CR1 |= (1<<0);                // Enables clock input after timer configuration ***LAST STEP*** 
}

void pwm_update(TIMx_TypeDef * TIMx, int freq){
    int arr;
    if (freq == 0){
      TIMx->CR1 &= ~(1<<0);
    } else {
      TIMx->CR1 |= (1<<0);
      arr = (CK_CNT / freq) - 1;       // Calculation for ARR
      TIMx->ARR = arr;                    // Sets PWM frequency to requested amount
      TIMx->CCR1 = arr/2;                 // Sets duty cycle to 50%
      TIMx->EGR &= ~(1<<0);               // Resets the flag
    }
}

void delay_init(TIMx_TypeDef * TIMx){
   TIMx->PSC = (CK_CNT / 1000) - 1; // Creating one ms resolution from system clock
   TIMx->BDTR |= (1<<15);               // (MOE) OC and OCN outputs are enabled if their respective enable bits are set (CCxE, CCxNE, in TIMx_CCER register)
   TIMx->CCER |= (1<<0);                // Configure Channel 1 as output
   TIMx->CR1 |= (1<<0);                  // Start tIM15 counter
}

void delay_update(TIMx_TypeDef * TIMx, int duration){
   TIMx->ARR = duration - 1;            // ARR = time in ms because the counter counts from 0 to ARR
   TIMx->CNT = 0;                       // Ensures counter starts at zero everytime
   TIMx->SR &= ~(1<<0);                 // Resets interupt flag upon counter reset
   while (!(TIMx -> SR & (1<<0)));      // Wait until flag is triggered (Counter == ARR)
  // TIMx -> CR1 &= ~(1<<0);            // Disable counter
   TIMx->SR &= ~ (1<<0);                // Clear the interupt flag
}

/*
OCx polarity is software programmable using the CCxP bit in the TIMx_CCER register. It
can be programmed as active high or active low. OCx output is enabled by a combination of
the CCxE, CCxNE, MOE, OSSI and OSSR bits (TIMx_CCER and TIMx_BDTR registers).
Refer to the TIMx_CCER register description for more details.
*/


   

   

    

   

    

   

    

   




