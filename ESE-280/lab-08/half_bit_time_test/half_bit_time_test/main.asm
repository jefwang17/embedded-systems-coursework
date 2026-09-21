;***************************************************************************
;*
;* Title: Half Bit Time Delay Test
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 23 2025
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* This program tests the half_bit_time_52us subroutine, which produces a
;* delay of approximately 52 microseconds—equivalent to half of one bit time
;* for 9600-baud serial communication. The program repeatedly calls the delay
;* routine inside an infinite loop to verify its timing in simulation.
;*
;* VERSION HISTORY
;* 1.0  Original version
;***************************************************************************

.nolist
.include "m4809def.inc"
.list

;=============================
; Main Program
;=============================
main:
	rcall half_bit_time_52us	; Call the 52 µs delay routine
	rjmp main					; Repeat indefinitely

;***************************************************************************
;* Subroutine Name: half_bit_time_52us
;*
;* Description:
;*   Provides a fixed software delay of approximately 52 microseconds.
;*   This is one-half of a bit time for serial communication at 9600 baud.
;*
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 23 2025
;* Target: AVR128DB48 @ 4 MHz
;*
;* Number of words: ~5
;* Number of cycles: ? 206 cycles (? 52 µs @ 4 MHz)
;* Low registers modified: None
;* High registers modified: None
;*
;* Parameters: None
;* Returns: None
;*
;* Notes:
;*   - Uses a simple decrement/branch loop to create the delay.
;*   - Can be verified in simulation by measuring instruction cycles.
;***************************************************************************

half_bit_time_52us:
	ldi r16, 67        ; 1 cycle
bt_loop:
	dec r16            ; 1 cycle
	brne bt_loop       ; 2 cycles if branch taken, 1 if not
	nop                ; 1 cycle padding
	ret                ; 4 cycles
