;
; keypad_test.asm
.nolist
.include "AVR128DB48def.inc"
.list
; Replace with your application code
.equ PORTE_VECTOR = 0x005C

reset: 
jmp start
;VECTOR FOR PORTES
.org PORTE_VECTOR
jmp function

; Replace with your application code
start:
;PC0-PC7 AS INPUTS
    ldi r16, 0x00
    out VPORTC_DIR, r16

;PD0-PD7 AS OUTPUTS (BARGRAPH)
    ldi r16, 0xFF
    out VPORTD_DIR, r16
    ;TURNING OFF BARAGRAPH
    out VPORTD_OUT, r16 

;PE (DATA AVAILABLE) AS INPUTS
    cbi VPORTE_DIR, 0

;ENABLING PE0 INTERUPT
    lds r16, PORTE_PIN0CTRL
    ori r16, 0x02
    sts PORTE_PIN0CTRL, r16 

;TURNING ON GLOBAL INTERUPT
    sei

main: 
    nop
    rjmp main

function: 
    cli
    push r16
    in r16, CPU_SREG
    push r16 

    lds r16, PORTE_INTFLAGS
    sbrc r16, 0
    rcall VP_0

    pop r16
    out CPU_SREG, r16
    pop r16
    sei
    reti

VP_0: 
    nop
    ;CLEARS INT0 FLAG
    ldi r16, PORT_INT0_bm
    sts PORTE_INTFLAGS, r16 
    ;SAVES VPORTE_IN information
    in r16, VPORTC_IN
    com r16
    andi r16, 0xF0
    lsr r16
    lsr r16
    lsr r16
    lsr r16
    out VPORTD_OUT, r16
    ret 
