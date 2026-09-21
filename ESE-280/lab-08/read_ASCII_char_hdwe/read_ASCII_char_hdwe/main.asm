;***************************************************************************
;*
;* Title: read ascii char hdwe
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 23 2025
;* Target: AVR128DB48 
;*
;* DESCRIPTION
;*   This program initializes USART3 on the AVR128DB48 for asynchronous
;*   serial communication at 9600 baud using the hardware UART module.
;*   It continuously receives incoming ASCII characters from the serial
;*   interface (PB1 = RXD3) and displays their bit pattern on the LED
;*   bargraph connected to VPORTD. LED D7 indicates stop-bit validity:
;*       - ON  ? valid stop bit (C = 1)
;*       - OFF ? framing error (C = 0)
;*
;* VERSION HISTORY
;* 1.0 Original version
;***************************************************************************




.nolist 
.include "AVR128DB48def.inc"
.list

start:
    ldi r16, LOW(1667) ;step 1
    sts USART3_BAUDL, r16
    ldi r16, HIGH(1667)
    sts USART3_BAUDH, r16
    ldi r16, 0b00000011;step 2
    sts USART3_CTRLC, r16
    cbi VPORTB_DIR, 1;step 3
    ldi r16, 0x80;step 4
    sts USART3_CTRLB, r16
	; LEDs on VPORTD active-low
    ldi  r16, 0xFF
    out  VPORTD_DIR, r16
    out  VPORTD_OUT, r16

main:
	rcall serial_receive_hdwe
	rcall display
	rjmp main

;***************************************************************************
;* Subroutine Name: serial_receive_hdwe
;*
;* Description:
;*   Waits for a received character from the hardware USART3 module.
;*   Monitors the RX Complete flag (bit 7) in USART3_STATUS until a
;*   character has been fully received. Once data is available, it checks
;*   for a framing error (bit 2) in USART3_RXDATAH and sets or clears
;*   the Carry flag accordingly. The received ASCII character is then
;*   loaded from USART3_RXDATAL into r16.
;*
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 23 2025
;* Target: AVR128DB48 
;*
;* Number of words: ~10
;* Low registers modified:none
;* High registers modified: None
;*
;* Parameters: None
;*
;* Returns:
;*   r16 = received ASCII character
;*   Carry flag (C) = stop-bit validity
;*       (1 = valid stop bit, 0 = framing error)
;*
;* Notes:
;*   - Uses USART3 hardware RX line (PB1).
;*   - Bit 7 of USART3_STATUS indicates data ready (RXCIF).
;*   - Bit 2 of USART3_RXDATAH indicates framing error (FERR).
;***************************************************************************

serial_receive_hdwe:
	  ; wait for RXCIF (STATUS bit7)
sr_wait:
    lds  r17, USART3_STATUS
    sbrs r17, 7
    rjmp sr_wait

    ; read RXDATAH first (captures FERR), then set C accordingly
    lds  r17, USART3_RXDATAH     ; bit2 = FERR (1 = error)
    bst  r17, 2                  ; T = FERR
    brts sr_bad                  ; if error -> C=0
    sec                          ; good frame -> C=1
    rjmp sr_read
sr_bad:
    clc                          ; bad frame -> C=0

sr_read:
    lds  r16, USART3_RXDATAL     ; read received byte
    ret
;***************************************************************************
;* Subroutine Name: display
;*
;* Description:
;*   Displays the received ASCII character (stored in r16) on the LED 
;*   bargraph connected to VPORTD. Because the LEDs are active-low, 
;*   the character bits are complemented before being written to the port.
;*   The carry flag from serial_receive_hdwe indicates framing validity:
;*       - Carry = 1 ? LED D7 ON (valid stop bit)
;*       - Carry = 0 ? LED D7 OFF (framing error)
;*
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 23 2025
;* Target: AVR128DB48 
;*
;* Number of words: ~10
;* Low registers modified: none
;* High registers modified: None
;*
;* Parameters:
;*   r16 = received ASCII character
;*   Carry flag = stop-bit validity (1 = valid, 0 = framing error)
;*
;* Returns:
;*   Updates LED outputs on VPORTD (active-low).
;*
;* Notes:
;*   - LED D7 functions as a “status indicator” for stop-bit validity.
;*   - VPORTD[6:0] display the inverted binary value of the ASCII data.
;***************************************************************************

display:
	rol r17
	com r16
	out VPORTD_OUT, r16
	ror r17
	brcs turn_led_on
	brcc turnledoff
	turn_led_on:
	cbi VPORTD_OUT, 7
	ret
	turnledoff:
	sbi VPORTD_OUT, 7
	ret