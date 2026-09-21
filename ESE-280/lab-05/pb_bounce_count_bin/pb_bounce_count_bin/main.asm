;
; pb_bounce_count_bin.asm
;
; Created: 10/1/2025 4:41:30 PM
; Author : jeffe
;


; Replace with your application code
.nolist
.include "AVR128DB48def.inc"
.list

start:
ldi r17, 0x00 ; set the register to 0
cbi VPORTE_DIR, 0 ; set the input to 0
ldi r16, 0xFF ; set the register to 1
out VPORTD_DIR, r16 ; move the 1s from r16 in VPORTD
out VPORTD_OUT, r16 ; set the led to 1 so the led are off


wait_for_0:
sbic VPORTE_IN, 0 ; if 0 it goes to wait for 1
rjmp wait_for_0 ;	if 0 go back to the wair for 0 loop


wait_for_1:
sbis VPORTE_IN, 0 ; check if 1
rjmp wait_for_1 ; jump back to wait for 1
inc r17 ; add a 1 to the counter
com r17 ; change it to a 0 
out VPORTD_OUT, r17 ; move the 0s to Portd out to turn the leds on
com r17 ; change it to 1
rjmp wait_for_0 ; jump to wait for 0 loop
