; Created: 10/8/2025 8:56:07 PM
; Author : jeffe
;
.nolist
.include "AVR128DB48def.inc"
.list

start:
	sbi VPORTB_DIR, 0
	sbi VPORTB_OUT, 0
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

see_if_01:
	sbic VPORTE_IN, 2
	rjmp see_if_01

see_if_1:
	sbis VPORTE_IN, 0 ;skip is 1
	rjmp see_if_1
	in r18, VPORTC_IN    ; read switch values
    rcall serial_send

see_if_02:
	sbic VPORTE_IN, 2 ; if the button is still press 0
	rjmp see_if_02	;
	cbi VPORTE_OUT, 1	;set the 
	ldi r16, 100		;
	rcall var_delay		;
	sbi VPORTE_OUT, 1	;
	sbic VPORTE_IN, 2 ; skip 0
	rjmp see_if_01	;is 1 tsay in function beginneing

var_delay:              ; delay for AVR128DB48 @ 4.00 MHz = r16 * 0.100475 ms
outer_loop:
    ldi r17, 133
inner_loop:
    dec r17
    brne inner_loop
    dec r16
    brne outer_loop
    ret

serial_send:
	ldi r17, 8

start_bit:
    cbi VPORTB_OUT, 0    ;beginning of start bit
    rcall bit_time_104us ;delay one bit time
next_bit:
    lsr r18                 ; shift next data bit to C

set_bit:
    brcc clr_bit            ; if C = 1, set PB0
    sbi VPORTB_OUT, 0
	rjmp bit_delay

clr_bit:
    brcs bit_delay          ; if C = 0, clear PB0
    cbi VPORTB_OUT, 0

bit_delay:
    rcall bit_time_104us          ; delay one bit time
    dec r17
    brne next_bit

stop_bit:
    sbi VPORTB_OUT, 0       ; send stop bit
    rcall bit_time_104us         ; delay one bit time
    ret

bit_time_104us: 
	ldi r16, 136 ; 1 clock 
bt_loop: 
	dec r16 ; 1 clock 
	brne bt_loop ; 2/1 clocks 
	nop ; 2 clocks padding 
	nop 
	ret ; 4





 
