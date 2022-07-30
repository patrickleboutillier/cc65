.export _lcd_init, _lcd_instruction, _lcd_wait, _lcd_print

.include "be6502.inc"


.segment "CODE"


_lcd_init:
  lda #%11111111 ; Set all pins on port B to output
  sta _DDRB
  lda #%11100000 ; Set top 3 pins on port A to output
  sta _DDRA

  lda #%00111000 ; Set 8-bit mode; 2-line display; 5x8 font
  jsr _lcd_instruction
  lda #%00001110 ; Display on; cursor on; blink off
  jsr _lcd_instruction
  lda #%00000110 ; Increment and shift cursor; don't shift display
  jsr _lcd_instruction
  lda #$00000001 ; Clear display
  jsr _lcd_instruction


_lcd_wait:
  pha
  lda #%00000000  ; Port B is input
  sta _DDRB
lcdbusy:
  lda #LCD_RW
  sta _PORTA
  lda #(LCD_RW | LCD_E)
  sta _PORTA
  lda _PORTB
  and #%10000000
  bne lcdbusy

  lda #LCD_RW
  sta _PORTA
  lda #%11111111  ; Port B is output
  sta _DDRB
  pla
  rts

_lcd_instruction:
  jsr _lcd_wait
  sta _PORTB
  lda #0         ; Clear RS/RW/E bits
  sta _PORTA
  lda #LCD_E    ; Set E bit to send instruction
  sta _PORTA
  lda #0         ; Clear RS/RW/E bits
  sta _PORTA
  rts

_lcd_print:
  jsr _lcd_wait
  sta _PORTB
  lda #LCD_RS              ; Set RS; Clear RW/E bits
  sta _PORTA
  lda #(LCD_RS | LCD_E)   ; Set E bit to send instruction
  sta _PORTA
  lda #LCD_RS              ; Clear E bits
  sta _PORTA
  rts
