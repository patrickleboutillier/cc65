/*****************************************************************************/
/*                                                                           */
/*                               be6502.h                                    */
/*                                                                           */
/*                 Ben Eater's 6502 specific definitions                     */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* 2022 Patrick LeBoutillier (patrick.leboutillier@gmail.com)                */
/*                                                                           */
/*                                                                           */
/* This software is provided "as-is," without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter and redistribute it       */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software.  If you use this software  */
/*    in a product, an acknowledgment, in the product's documentation,       */
/*    would be appreciated, but is not required.                             */
/* 2. Alterred source versions must be marked plainly as such,               */
/*    and must not be misrepresented as being the original software.         */
/* 3. This notice may not be removed or alterred                             */
/*    from any source distribution.                                          */
/*                                                                           */
/*****************************************************************************/


#ifndef _BE6502_H
#define _BE6502_H

#include <stdint.h>

/* Check for errors */
#if !defined(__BE6502__)
#  error This module may only be used when compiling for Ben Eater's 6502!
#endif

extern uint8_t PORTA ;
extern uint8_t PORTB ;
extern uint8_t DDRA ;
extern uint8_t DDRB ;
extern uint8_t T1CL ;
extern uint8_t T1CH ;
extern uint8_t T1LL ;
extern uint8_t T1LH ;
extern uint8_t T2CL ;
extern uint8_t T2CH ;
extern uint8_t SR ;
extern uint8_t ACR ;
extern uint8_t PCR ; 
extern uint8_t IFR ;
extern uint8_t IER ;


/* LCD functions */
#define LCD_E    0b10000000
#define LCD_RW   0b01000000
#define LCD_RS   0b00100000

void __fastcall__ lcd_init() ;
void __fastcall__ lcd_wait() ;
void __fastcall__ lcd_instruction(uint8_t) ;
void __fastcall__ lcd_print(char c) ;


/* Timer symbols */
extern unsigned long timer_ticks ;
void timer_irq_int() ;
void __fastcall__ timer_init() ;


/* Interrupt function pointers. You can use these to set different interrupt handlers .
   Note: These handlers MUST be assembly labels, NOT C functions! */
extern void (*nmi_int_fptr)() ;
extern void (*irq_int_fptr)() ;

/* Default interrupt functions (which do nothing). The pointers above point to these at startup. */
void def_nmi_int() ;
void def_irq_int() ;

/* End of be6502.h */
#endif
