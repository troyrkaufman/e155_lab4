// Author: Troy Kaufman
// Email: tkaufman@hmc.edu
// Date: 10/3/24

// Header for RCC Functions

#include <stdint.h>

#define RCC_BASE (0x40021000)

//#define 

typedef struct {
    volatile uint32_t CR;            // RCC Offset 0x00
    volatile uint32_t ICSCR;         // RCC Offset 0x04;
    volatile uint32_t CFGR;          // RCC Offset 0x08;
    volatile uint32_t PLLCFGR;       // RCC Offset 0x0C;
    volatile uint32_t PLLSAI1CFGR;   // RCC Offset 0x10;
             uint32_t reserved;      // RCC Offset 0x14
    volatile uint32_t CIER;          // RCC Offset 0x18;
    volatile uint32_t RCC_CIFR;      // RCC Offset 0x1C
    volatile uint32_t CICR;          // RCC Offset 0x20;
             uint32_t reserved0;     // RCC Offset 0x24
    volatile uint32_t AHB1RSTR;      // RCC Offset 0x28;
    volatile uint32_t AHB2RSTR;      // RCC Offset 0x2C;
    volatile uint32_t AHB3RSTER;     // RCC Offset 0x30;
             uint32_t reserved1;     // RCC Offset 0x34
    volatile uint32_t APB1RSTR1;     // RCC Offset 0x38;
    volatile uint32_t APB1RSTR2;     // RCC Offset 0x3C;
    volatile uint32_t APB2RSTR;      // RCC Offset 0x40;
             uint32_t reserved2;     // RCC Offset 0x44
    volatile uint32_t AHB1ENR;       // RCC Offset 0x48;
    volatile uint32_t AHB2ENR;       // RCC Offset 0x4C;
    volatile uint32_t AHB3ENR;       // RCC Offset 0x50;
             uint32_t reserved3;     // RCC Offset 0x54
    volatile uint32_t APB1ENR1;      // RCC Offset 0x58;
    volatile uint32_t APB1ENR2;      // RCC Offset 0x5C;
    volatile uint32_t APB2ENR;       // RCC Offset 0x60;
             uint32_t reserved4;     // RCC Offset 0x64
    volatile uint32_t AHB1SMENR;     // RCC Offset 0x68;
    volatile uint32_t AHB2SMENR;     // RCC Offset 0x6C;
    volatile uint32_t AHB3SMENR;     // RCC Offset 0x70;
             uint32_t reserved5;     // RCC Offset 0x74
    volatile uint32_t APB1SMENR1;    // RCC Offset 0x78;
    volatile uint32_t APB1SMENR2;    // RCC Offset 0x7C;
    volatile uint32_t APB2SMENR;     // RCC Offset 0x80;
             uint32_t reserved6;     // RCC Offset 0x84
    volatile uint32_t CCIPR;         // RCC Offset 0x88;
             uint32_t reserved7;     // RCC Offset 0x8C
    volatile uint32_t BDCR;          // RCC Offset 0x90;
    volatile uint32_t CSR;           // RCC Offset 0x94;
    volatile uint32_t CRRCR;         // RCC Offset 0x98;
    volatile uint32_t CCIPR2;        // RCC Offset 0x9C;
} RCC_TypeDef; 

#define RCC ((RCC_TypeDef *) RCC_BASE)




