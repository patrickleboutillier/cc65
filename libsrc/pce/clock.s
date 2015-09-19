;
; clock_t clock (void);
;

        .include        "pce.inc"
        .include        "extzp.inc"

        .forceimport    ticktock
        .export         _clock
        .importzp       sreg

.proc   _clock

        lda     tickcount+3
        sta     sreg+1
        lda     tickcount+2
        sta     sreg
        ldx     tickcount+1
        lda     tickcount
        rts

.endproc

        .constructor initclock, 24

initclock:
        lda     #0
        ldx     #3
@lp:    sta     tickcount,x
        dex
        bpl     @lp
        rts
