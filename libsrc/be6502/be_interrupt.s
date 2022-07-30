.export   nmi_int_bs, irq_int_bs, _nmi_int_fptr, _nmi_int_def, _irq_int_fptr, _irq_int_def


; Pointers to the interrupt handlers. These will allow the handlers to be changed on the fly.
; Initially setup with the default handlers.
.segment  "DATA"

_nmi_int_fptr:  .addr _nmi_int_def
_irq_int_fptr:  .addr _irq_int_def

.segment  "CODE"

; Interrupt bootstrap handlers. Just jump to the address in the pointers.
nmi_int_bs:   jmp(_nmi_int_fptr)
irq_int_bs:   jmp(_irq_int_fptr)


; ---------------------------------------------------------------------------
; Default interrupt handlers.
;
; Checks for a BRK instruction and returns from all valid interrupts.

; ---------------------------------------------------------------------------
; Non-maskable interrupt (NMI) service routine

_nmi_int_def:  RTI                    ; Return from all NMI interrupts

; ---------------------------------------------------------------------------
; Maskable interrupt (IRQ) service routine

_irq_int_def:  PHX                    ; Save X register contents to stack
               TSX                    ; Transfer stack pointer to X
               PHA                    ; Save accumulator contents to stack
               INX                    ; Increment X so it points to the status
               INX                    ;   register value saved on the stack
               LDA $100,X             ; Load status register contents
               AND #$10               ; Isolate B status bit
               BNE break              ; If B = 1, BRK detected

; ---------------------------------------------------------------------------
; IRQ detected, return

irq:       PLA                    ; Restore accumulator contents
           PLX                    ; Restore X register contents
           RTI                    ; Return from all IRQ interrupts

; ---------------------------------------------------------------------------
; BRK detected, return

break:     PLA                    ; Restore accumulator contents
           PLX                    ; Restore X register contents
           RTI                    ; Return from all IRQ interrupts
