;
; USART3_asynch_test.asm
;
; Created: 10/15/2025 9:15:09 PM
; Author : jeffe
;
.nolist
.include "AVR128DB48def.inc"
.list

start:
	ldi r16, LOW(1667)
	sts USART3_BAUDL, r16
	ldi r16, HIGH(1667)
	sts USART3_BAUDH, r16
	ldi r16, 0b00000011
	sts USART3_CTRLC, r16
	sbi VPORTB_DIR, 0
	ldi r16, 0b01000000
	sts USART3_CTRLB, r16
	ldi r16, 'A'

main_loop: ;build a charcter
ldi r18, (1<<6)
	sts USART3_STATUS, r18

wait_for_dre:
	lds r17, USART3_STATUS
	sbrs r17, 5              ; wait until DREIF (bit 5) = 1
	rjmp wait_for_dre

	sts USART3_TXDATAL, r16  ; now write the byte

waiting_til_done: ; wait for the charcter to be doning sending 
	lds r17, USART3_STATUS
	sbrs r17, 6              ; wait until TXC (bit 6) = 1
	rjmp waiting_til_done

	cpi r16, 'Z'             ;check if z
	breq change_to_A         ;if it is z change it to a
	inc r16                  ; change it to the next letter
	rjmp main_loop

change_to_A:
	ldi r16, 'A'
	rjmp main_loop