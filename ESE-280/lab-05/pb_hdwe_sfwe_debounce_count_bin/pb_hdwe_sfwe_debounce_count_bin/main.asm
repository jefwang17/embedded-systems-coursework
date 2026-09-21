; Created: 10/1/2025 8:56:07 PM
; Author : jeffe
;
.nolist
.include "AVR128DB48def.inc"
.list

start:
    ldi r18, 0x00        ; set the register to 0
    cbi VPORTE_DIR, 0    ; set to input 
	sbi VPORTE_DIR, 1	 ; set reset to 1
	cbi VPORTE_DIR, 2	 ; 
	cbi VPORTE_OUT, 1	 ; 
	sbi VPORTE_OUT, 1	 ; 
    ldi r16, 0xFF        ; set the register to 1
    out VPORTD_DIR, r16  ; move the 1s from r16 in
    out VPORTD_OUT, r16  ; set the led to 1 so the led is off
	sbis VPORTE_IN, 0
	rjmp see_if_1

see_if_0:
	sbic VPORTE_IN, 2 ; if the button is still press 0
	rjmp see_if_0	;
	cbi VPORTE_OUT, 1	;set the 
	ldi r16, 100		;
	rcall var_delay		;
	sbi VPORTE_OUT, 1	;
	sbic VPORTE_IN, 2 ; skip 0
	rjmp see_if_0	;is 1 tsay in function beginneing
see_if_1:
	sbis VPORTE_IN, 0 ;skip is 1
	rjmp see_if_1
	inc r18
	com r18
	out VPORTD_OUT, r18
	com r18
	rjmp see_if_0
var_delay:              ; delay for AVR128DB48 @ 4.00 MHz = r16 * 0.100475 ms
outer_loop:
    ldi r17, 133
inner_loop:
    dec r17
    brne inner_loop
    dec r16
    brne outer_loop
    ret






 
