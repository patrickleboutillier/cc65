.export _timer_ticks, _timer_init, _timer_irq_int
.import _ACR, _T1CL, _T1CH


; 32 bit tick counter.
.segment  "DATA"

_timer_ticks:  .byte $00, $00, $00, $00


.segment  "CODE"

; Set timer to interrupt every 998 (0x03E6) microseconds 
_timer_init:  CLI
              LDA #%01000000
              STA _ACR
              LDA #$E6
              STA _T1CL
              LDA #$03
              STA _T1CH
              RTS

; ---------------------------------------------------------------------------
; Maskable interrupt (IRQ) service routine

_timer_irq_int:  BIT _T1CL
                 INC _timer_ticks
                 BNE end_irq
                 INC _timer_ticks + 1
                 BNE end_irq
                 INC _timer_ticks + 2
                 BNE end_irq
                 INC _timer_ticks + 3
                 BNE end_irq
end_irq:         RTI
