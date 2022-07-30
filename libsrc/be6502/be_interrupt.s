.export   nmi_int_bs, irq_int_bs, _nmi_int_fptr, _def_nmi_int, _irq_int_fptr, _def_irq_int


; Pointers to the interrupt handlers. These will allow the handlers to be changed on the fly.
; Initially setup with the default handlers.
.segment  "DATA"

_nmi_int_fptr:  .addr _def_nmi_int
_irq_int_fptr:  .addr _def_irq_int

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

_def_nmi_int:  RTI                    ; Return from all NMI interrupts

; ---------------------------------------------------------------------------
; Maskable interrupt (IRQ) service routine

_def_irq_int:  RTI
