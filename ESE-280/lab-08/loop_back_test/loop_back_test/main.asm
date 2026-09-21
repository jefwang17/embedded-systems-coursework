;***************************************************************************
;*
;* Title: loop back test 
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 23 2025
;* Target: AVR128DB48
;*
;* DESCRIPTION
;*   Configures USART3 for 9600 baud, 8N1, and enables internal loopback
;*   (LBME) so TX is internally routed to RX. The program repeatedly sends
;*   test characters ('A'..'Z'), waits for the received character, verifies
;*   it matches what was sent, and displays the byte on VPORTD LEDs
;*   (active-low). LED D7 indicates match status: ON = match (C=1),
;*   OFF = mismatch (C=0).
;*
;* VERSION HISTORY
;*   1.0  Original version
;***************************************************************************

.nolist
.include "AVR128DB48def.inc"
.list

start:
	ldi r16, LOW(1667)
	sts USART3_BAUDL, r16 ;step 1
	ldi r16, HIGH(1667)
	sts USART3_BAUDH, r16

	ldi r16, 0x03
	sts USART3_CTRLC, r16; step 2

	sbi VPORTB_DIR, 0; step 3

	ldi r16, 0xC0 ; step 4
	sts USART3_CTRLB, r16

	ldi r16, 0x08
	sts USART3_CTRLA, r16

	ldi r16, 0xFF
	out VPORTD_DIR, r16
	out VPORTD_OUT, r16

main:
	ldi r16, 'A'
	lds r17, USART3_STATUS
	sbrs r17, 5
	rjmp main

	sts USART3_TXDATAL, r16
 rxflag:
	lds r18, USART3_STATUS
	sbrs r18, 7
	rjmp rxflag
	lds r18, USART3_RXDATAL
	cp r16, r18
	

;***************************************************************************
;* Subroutine Name: display
;*
;* Description:
;*   Displays the received byte (r16) on VPORTD LEDs (active-low).
;*   LED D7 indicates compare result from usart3_txrx_blocking:
;*     C=1 ? LED D7 ON (match), C=0 ? LED D7 OFF (mismatch).
;*
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 23 2025
;* Target: AVR128DB48 
;*
;* Number of words: ~10
;* Low registers modified: none
;* High registers modified: None
;***************************************************************************
display:
    rol   r17                   ; preserve C through COM/OUT using rol/ror
    com   r16
    out   VPORTD_OUT, r16
    ror   r17
    brcs  turn_led_on
    brcc  turn_led_off
turn_led_on:
    cbi   VPORTD_OUT, 7
    ret
turn_led_off:
    sbi   VPORTD_OUT, 7
    ret
