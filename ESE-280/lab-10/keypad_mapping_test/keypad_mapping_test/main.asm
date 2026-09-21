.nolist
.include "AVR128DB48def.inc"
.list

;*******************************************************
;* Title: Keypad_mapping_test
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: 11/13/2025
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* This program tests the MM74C922 keypad encoder and includes
;* a lookup table to map the raw scan codes (0–15) to keypad
;* values (0–F). The scan code is read on PORTA when a key is
;* pressed and can be converted using scan_to_value.
;*
;*******************************************************

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
    ; Clear PE0 interrupt flag
    ldi  r16, PORT_INT0_bm
    sts  PORTE_INTFLAGS, r16

    ; Read scan code from PORTC
    in   r16, VPORTC_IN
    andi r16, 0xF0        ; keep upper nibble
    lsr  r16
    lsr  r16
    lsr  r16
    lsr  r16              ; now r16 = scan code (0–15)

    ; Use scan code as index into segtable
    ldi  ZL, LOW(segtable*2)
    ldi  ZH, HIGH(segtable*2)
    clr  r17              ; zero helper for carry
    add  ZL, r16
    adc  ZH, r17          ; Z = address of segtable[scan_code]

    lpm  r18, Z           ; r18 = mapped value (1,2,3,F,...)

    ; If LEDs are active-low, invert before output
    com  r18
    out  VPORTD_OUT, r18

    ret



segtable: .db $1, $2, $3, $F, $4, $5, $6, $E, $7, $8, $9, $D, $A, $0, $B, $C 
    number: .db 0x00, 0x08, 0x04, 0x0C, 0x02, 0x0A, 0x06, 0x0E, 0xC1, 0x09, 0x05, 0x0D, 0x03, 0x0B, 0x07, 0x0F
                ;1        ;2     ;3   ;up   ;4        ;5    ;6  ;down  ;7        ;8    ;9      ;2ND  ;CLEAR ;0    ;HELP    ;ENTER
