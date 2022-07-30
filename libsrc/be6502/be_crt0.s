; ---------------------------------------------------------------------------
; crt0.s
; ---------------------------------------------------------------------------
;
; Startup code for cc65 (Ben Eater 6502 version)


.PC02     ; be6502 uses WDC65C02

.import   _main
.import   nmi_int_bs, irq_int_bs

.export   __STARTUP__ : absolute = 1        ; Mark as startup
.import   __RAM_START__, __RAM_SIZE__       ; Linker generated

.include  "zeropage.inc"
.import    copydata, zerobss, initlib, donelib

.include  "be6502.inc"
.export _PORTB, _PORTA, _DDRB, _DDRA


; ---------------------------------------------------------------------------
; Place the startup code in a special segment

.segment  "STARTUP"

; ---------------------------------------------------------------------------
; A little light 6502 housekeeping

reset:     LDX     #$FF                 ; Initialize stack pointer to $FF
           TXS
           CLD                          ; Clear decimal mode

; ---------------------------------------------------------------------------
; Set cc65 argument stack pointer

          LDA     #<(__RAM_START__ + __RAM_SIZE__)
          STA     sp
          LDA     #>(__RAM_START__ + __RAM_SIZE__)
          STA     sp+1

; ---------------------------------------------------------------------------
; Initialize memory storage

          JSR     zerobss              ; Clear BSS segment
          JSR     copydata             ; Initialize DATA segment
          JSR     initlib              ; Run constructors

; ---------------------------------------------------------------------------
; Call main()

          JSR     _main

; ---------------------------------------------------------------------------
; Back from main (this is also the _exit entry):  force a software break

_exit:    JSR     donelib              ; Run destructors
          STP


; ---------------------------------------------------------------------------
; Defines the interrupt vector table.

.segment  "VECTORS"

.addr      nmi_int_bs    ; NMI vector bootstrap
.addr      reset         ; Reset vector
.addr      irq_int_bs    ; IRQ/BRK vector bootstrap
