.nolist
.include "avr128DB48def.inc"
.list

;***************************************************************************
;*
;* Title: Inventory System Display – USART3 Transmission
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: 11/20
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* This program builds a 4-line (80-character) text page in SRAM, loads
;* the Home Page strings into that page buffer, and then sends all 80
;* characters over USART3 using the Data Register Empty (DRE) interrupt.
;* After all characters are sent, it waits for a short time and then
;* sends a simple screen reset sequence ('|', '-') using a blocking send.
;*
;*
;* VERSION HISTORY
;* 1.0 Original version
;***************************************************************************

.org 0x0000
	rjmp init_system

.org USART3_DRE_vect
    rjmp usart3_dre_isr_handler

; Defining the main buffer
.dseg
page_1_buff: .byte 80	;80 ASCII character buffer
tx_ptr:      .byte 2    ; pointer into buffer
tx_count:    .byte 1    ; remaining bytes to send
.cseg
sbi VPORTB_DIR, 0
line2:
	.db " Inventory System I "

line3:
	.db "  ESE280 Fall 2025  "

init_system:
	; Defining variables
	.def temp = r16
	.def loop_counter = r17

	; Loading the pointer to the buffer
	ldi YH, high(page_1_buff)
	ldi YL, low(page_1_buff)

	; Line 1: blank
	rcall clear_buff

	; Line 2: Inventory System I (centered)
	ldi ZH, high(line2 * 2)
	ldi ZL, low(line2 * 2)
	rcall home_page

	; Line 3: ESE280 Fall 2025 (centered)
	ldi ZH, high(line3 * 2)
	ldi ZL, low(line3 * 2)
	rcall home_page

	; Line 4: blank
	rcall clear_buff

	; --------------------------------
	; USART3 Transmit Initialization
	; --------------------------------

	; 9600 baud
	ldi temp, low(1667)
	sts USART3_BAUDL, temp
	ldi temp, high(1667)
	sts USART3_BAUDH, temp

	; Setting Frame Format
	ldi temp, 0x03
	sts USART3_CTRLC, temp

	; Enable Transmitter
	ldi temp, 0x40
	sts USART3_CTRLB, temp

	; initialize transmit state
	ldi temp, high(page_1_buff)
	sts tx_ptr+1, temp
	ldi temp, low(page_1_buff)
	sts tx_ptr, temp
	ldi temp, 80
	sts tx_count, temp

	; enable DRE interrupt
	lds temp, USART3_CTRLA
	ori temp, (1<<5)           ; DREIE bit
	sts USART3_CTRLA, temp

	; Enable Global Interrupt Flags
	sei

main_wait_for_tx:
	lds temp, tx_count
	tst temp
	breq post_tx_delay
	rjmp main_wait_for_tx

post_tx_delay:
	rcall delay_1s_nested
	rcall delay_1s_nested

	;clear screen and reset cursor
	ldi temp, '|'
	rcall usart3_send_char_blocking
	ldi temp, '-'
	rcall usart3_send_char_blocking

	rjmp idle_forever

idle_forever:
	nop
	rjmp idle_forever

; ---------------------------------------------------------------
; Subroutines
; ---------------------------------------------------------------

;***************************************************************************
;*
;* Title: home_page 
;* Author: Jeffery Wang 
;* Version: 1.0
;* Last updated: 11/20
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* Copies exactly 20 characters from program memory (pointed to by Z)
;* into the SRAM display buffer (pointed to by Y). Each call writes one
;* formatted line of the Home Page into the 80-byte page buffer.
;*
;*
;* VERSION HISTORY
;* 1.0 Original version
;***************************************************************************
home_page:
	ldi loop_counter, 20
copy_line:
	lpm temp, Z+
	st  Y+, temp
	dec loop_counter
	brne copy_line
	ret

;***************************************************************************
;*
;* Title: clear_buff 
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: 11/20
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* Writes 20 space characters (' ') into SRAM starting at the address in Y.
;* This is used to create a blank 20-character line inside the 80-byte
;* page buffer for the Home Page display.
;*
;*
;* VERSION HISTORY
;* 1.0 Original version
;***************************************************************************
clear_buff:
	ldi temp, ' '
	ldi loop_counter, 20

loop_for_line:
	st  Y+, temp
	dec loop_counter
	brne loop_for_line
	ret

;***************************************************************************
;*
;* Title: delay_1s_nested 
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: 11/20
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* Creates about a 1-second pause using three nested software loops,
;* assuming the intended system clock frequency. Registers r18–r20 are
;* used as loop counters but are saved on the stack at the start and
;* restored before returning so other code can safely use them.
;*
;*
;* VERSION HISTORY
;* 1.0 Original version
;***************************************************************************
delay_1s_nested:
		; save to stack
		push r18
		push r19
		push r20

		ldi r18, 20        ; outer loop count
outer_loop:
		ldi r19, 200       ; middle loop count
middle_loop:
		ldi r20, 200       ; inner loop count
inner_loop:
		dec r20            ; 1 cycle
		brne inner_loop    ; 2 cycles when branch taken
		                   ; 1 cycle when done
		dec r19
		brne middle_loop
		dec r18
		brne outer_loop

		; recover from stack
		pop r20
		pop r19
		pop r18

		ret

;***************************************************************************
;*
;* Title: usart3_send_char_blocking 
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: 11/20
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* Waits until the USART3 Data Register Empty flag is set, meaning the
;* transmitter is ready, and then writes the byte in r16 to TXDATAL.
;* This is used to send individual control characters outside the main
;* interrupt-driven transmission of the 80-byte page buffer.
;*
;*
;* VERSION HISTORY
;* 1.0 Original version
;***************************************************************************
usart3_send_char_blocking:
		push r17

wait_DRE:
		lds r17, USART3_STATUS
		sbrs r17, USART_DREIF_bp
		rjmp wait_DRE

		sts USART3_TXDATAL, r16

		pop r17
		ret

; ---------------------------------------------------------------
; Interrupt Service Routines
; ---------------------------------------------------------------

;***************************************************************************
;*
;* Title: usart3_dre_isr_handler 
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: 11/20
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* This interrupt runs whenever the USART3 transmit data register becomes
;* empty. On each interrupt it reads the next byte from the page buffer
;* in SRAM (using tx_ptr), writes it to TXDATAL, and decreases tx_count.
;* When all 80 bytes have been sent (tx_count reaches zero), it turns off
;* the DRE interrupt so it no longer fires.
;*
;*
;* VERSION HISTORY
;* 1.0 Original version
;***************************************************************************
usart3_dre_isr_handler:
		; Save registers
		push r16
		push r17

		; Load remaining count
		lds r17, tx_count
		tst r17
		breq tx_done             ; disable interrupt if done

		; Load pointer
		lds r30, tx_ptr        ; ZL
		lds r31, tx_ptr+1      ; ZH

		; Load next byte from SRAM and transmit it
		ld  r16, Z+
		sts USART3_TXDATAL, r16

		; Store updated pointer
		sts tx_ptr, r30
		sts tx_ptr+1, r31

		; Decrement count
		dec r17
		sts tx_count, r17

		rjmp tx_exit            ; continue until done

tx_done:
		; Disable DRE interrupt once all bytes sent
		lds r16, USART3_CTRLA
		andi r16, ~(1<<5)
		sts USART3_CTRLA, r16

tx_exit:
		; Restore registers
		pop r17
		pop r16

		reti
