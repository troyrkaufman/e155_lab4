// Header for TIMER functions

#include <stdint.h>

#define TIM15_BASE (0x40014000)
#define TIM16_BASE (0x40014400)
//#define TIM15_BASE (0x40014000)

typedef struct{
    volatile uint32_t CR1;           // 0x00
    volatile uint32_t CR2;           // 0x04
    volatile uint32_t reserved;      // 0x08
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
    volatile uint32_t reserved1;     // 0x3C
    volatile uint32_t reserved2;     // 0x40
    volatile uint32_t BDTR;          // 0x44
    volatile uint32_t DCR;
    volatile uint32_t OR1;           // 0x50
    volatile uint32_t reserved4;     // 0x54
    volatile uint32_t reserved5;     // 0x58
    volatile uint32_t reserved6;     // 0x5C
    volatile uint32_t OR2;           // 0x^0
} TIMx_TypeDef;

#define TIM16 ((TIMx_TypeDef *) TIM16_BASE)
#define TIM15 ((TIMx_TypeDef *) TIM15_BASE)

