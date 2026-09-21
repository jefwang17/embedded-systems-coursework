;
; USART_write_message.asm
;
; Created: 10/15/2025 9:48:58 PM
; Author : jeffe
;
.nolist
.include "AVR128DB48def.inc"
.list
start:
	ldi r16, LOW(1667)
	sts USART3_BAUDL, r16 ;step 1
	ldi r16, HIGH(1667)
	sts USART3_BAUDH, r16

	ldi r16, 0b00000011
	sts USART3_CTRLC, r16; step 2

	sbi VPORTB_DIR, 0; step 3

	ldi r16, 0x40 ; step 4
	sts USART3_CTRLB, r16
	
	rcall delay_500ms
main:
	ldi r16, '|'
	rcall send_a_character
	ldi r16, '-'
	rcall send_a_character
	ldi r16, 'H'
	rcall send_a_character
	ldi r16, 'e'
	rcall send_a_character
	ldi r16, 'l'
	rcall send_a_character
	ldi r16, 'l'
	rcall send_a_character
	ldi r16, 'o'
	rcall send_a_character
	ldi r16, ' '
	rcall send_a_character
	ldi r16, 'W'
	rcall send_a_character
	ldi r16, 'o'
	rcall send_a_character
	ldi r16, 'r'
	rcall send_a_character
	ldi r16, 'l'
	rcall send_a_character
	ldi r16, 'd'
	rcall send_a_character
	ldi r16, 0x0D
	rcall send_a_character
	ldi r16, 0x0A
	rcall send_a_character
	ldi r16, 'W'
	rcall send_a_character
	ldi r16, 'h'
	rcall send_a_character
	ldi r16, 'a'
	rcall send_a_character
	ldi r16, 't'
	rcall send_a_character
	ldi r16, ' '
	rcall send_a_character
	ldi r16, 'h'
	rcall send_a_character
	ldi r16, 'a'
	rcall send_a_character
	ldi r16, 'p'
	rcall send_a_character
	ldi r16, 'p'
	rcall send_a_character
	ldi r16, 'e'
	rcall send_a_character
	ldi r16, 'n'
	rcall send_a_character
	ldi r16, 's'
	rcall send_a_character
	ldi r16, ' '
	rcall send_a_character
	ldi r16, 'n'
	rcall send_a_character
	ldi r16, 'o'
	rcall send_a_character
	ldi r16, 'w'
	rcall send_a_character
end:
	rjmp end

send_a_character: ;build a charcter, send become a function
	lds r17, USART3_STATUS ;
	sbrs r17, 5
	rjmp send_a_character
	sts USART3_TXDATAL, r16
waiting_til_done:; wait for the charcter to be doning sending 
	lds r17, USART3_STATUS
	sbrs r17, 6
	rjmp waiting_til_done
	ret

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
