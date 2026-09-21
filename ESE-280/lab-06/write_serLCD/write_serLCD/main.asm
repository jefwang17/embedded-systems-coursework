;
; write_ASCII_character.asm
;
; Created: 10/15/2025 4:11:51 PM
; Author : jeffe
;
.nolist
.include "AVR128DB48def.inc"
.list


start:
	sbi VPORTB_DIR, 0	; set pin 0 as TX pin
	sbi VPORTB_OUT, 0	; 1 to copy idle
	rcall delay_500ms

main_loop:
	ldi r18, '|' ;
	rcall serial_send
	ldi r18, '-' ;
	rcall serial_send
	ldi r18, 'H' ;
	rcall serial_send
	ldi r18, 'e' ;
	rcall serial_send
	ldi r18, 'l' ;
	rcall serial_send
	ldi r18, 'l' ;
	rcall serial_send
	ldi r18, 'o' ;
	rcall serial_send
	ldi r18, ' ' ;
	rcall serial_send
	ldi r18, 'W' ;
	rcall serial_send
	ldi r18, 'o' ;
	rcall serial_send
	ldi r18, 'r' ;
	rcall serial_send
	ldi r18, 'l' ;
	rcall serial_send
	ldi r18, 'd' ;
	rcall serial_send
	ldi r18, 0x0D ;
	rcall serial_send
	ldi r18, 0x0A
	rcall serial_send
	ldi r18, 'W' ;
	rcall serial_send
	ldi r18, 'h' ;
	rcall serial_send
	ldi r18, 'a' ;
	rcall serial_send
	ldi r18, 't' ;
	rcall serial_send
	ldi r18, ' ' ;
	rcall serial_send
	ldi r18, 'h' ;
	rcall serial_send
	ldi r18, 'a' ;
	rcall serial_send
	ldi r18, 'p' ;
	rcall serial_send
	ldi r18, 'p' ;
	rcall serial_send
	ldi r18, 'e' ;
	rcall serial_send
	ldi r18, 'n' ;
	rcall serial_send
	ldi r18, 's' ;
	rcall serial_send
	ldi r18, ' ' ;
	rcall serial_send
	ldi r18, 'n' ;
	rcall serial_send
	ldi r18, 'o' ;
	rcall serial_send
	ldi r18, 'w' ;
	rcall serial_send

end:
	rjmp end
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
	ldi r16, 136			// 1 clock
bt_loop:
	dec r16					// 1 clock
	brne bt_loop			// 2/1 clocks
	nop						// 2 clocks padding
	nop
	ret						// 4

delay_500ms:
    ldi r30, LOW(2600)     ; values det. exper. using scope
    ldi r31, HIGH(2600)
outer_loop:
    ldi r16, $FF
inner_loop:
    dec r16
    brne inner_loop
    sbiw r31:r30, 1
    brne outer_loop
    ret                     ; return to caller

	
