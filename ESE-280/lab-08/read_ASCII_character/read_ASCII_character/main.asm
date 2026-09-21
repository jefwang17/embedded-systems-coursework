;***************************************************************************
;*
;* Title: read ascii character
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 23 2025
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* Software UART receiver on PB1 at 9600 baud. Waits for a start bit,
;* then samples 8 data bits (LSB first) using cycle-accurate delay
;* subroutines. The received byte is shown on VPORTD LEDs (active-low),
;* and LED D7 mirrors the stop-bit validity (Carry=1 ? good stop).
;*
;* VERSION HISTORY
;* 1.0  Original version
;***************************************************************************

.nolist
.include "AVR128DB48def.inc"
.list

start:
cbi VPORTB_DIR, 1
ldi r16, 0xFF
out VPORTD_DIR, r16
out VPORTD_OUT, r16

main:
rcall serial_receive
rcall display
rjmp main
;***************************************************************************
;* Subroutine Name: serial_receive
;* 
;*
;* Description:
;*   Waits for a valid start bit on PB1 (RX line) and then samples
;*   8 data bits (LSB first) at 9600 baud using timing subroutines
;*   half_bit_time_52us and bit_time_104us. After receiving all bits,
;*   it samples the stop bit to determine validity and sets the carry flag
;*   accordingly (C=1 ? valid stop bit, C=0 ? invalid stop bit).
;*
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 23 2025
;* Target: AVR128DB48
;* Number of words: ~45
;* Low registers modified: none
;* High registers modified: None
;*
;* Parameters:
;*   RX input: PB1 (VPORTB_IN bit 1)
;*
;* Returns:
;*   r16 = received byte (ASCII character)
;*   C = stop-bit status (1 = good stop bit, 0 = framing error)
;*
;* Notes: 
;*   - Uses bit_time_104us for sampling each data bit.
;*   - Uses half_bit_time_52us to align with middle of start bit.
;*   - The received byte in r16 is inverted and displayed on LEDs
;*     via the display subroutine.
;***************************************************************************
serial_receive:
sbis VPORTB_IN, 1  ; check if it is 0
rjmp serial_receive
waitfor0:
sbic VPORTB_IN, 1; check if it is negative 
rjmp waitfor0
rcall half_bit_time_52us
sbic VPORTB_IN, 1
rjmp serial_receive
clr r16
rcall bit_time_104us
in r17, VPORTB_IN
bst r17, 1
bld r18, 0

rcall bit_time_104us
in r17, VPORTB_IN
bst r17, 1
bld r18, 1

rcall bit_time_104us
in r17, VPORTB_IN
bst r17, 1
bld r18, 2

rcall bit_time_104us
in r17, VPORTB_IN
bst r17, 1
bld r18, 3

rcall bit_time_104us
in r17, VPORTB_IN
bst r17, 1
bld r18, 4

rcall bit_time_104us
in r17, VPORTB_IN
bst r17, 1
bld r18, 5

rcall bit_time_104us
in r17, VPORTB_IN
bst r17, 1
bld r18, 6

rcall bit_time_104us
in r17, VPORTB_IN
bst r17, 1
bld r18, 7

rcall bit_time_104us

sbis VPORTB_IN, 1 ;check to see if it is a 1
clc 
sbic VPORTB_IN, 1 ; check for 0
sec
ret
;***************************************************************************
;* 
;* Subroutine Name: display
;* Description:
;*   Takes the received ASCII character stored in r16 and displays it on the
;*   VPORTD LED bargraph. Because the LEDs are active-low, the data is first
;*   complemented before being output. The carry flag (set by serial_receive)
;*   indicates whether the stop bit was valid:
;*       - If Carry = 1 ? turn LED D7 ON (valid stop bit)
;*       - If Carry = 0 ? turn LED D7 OFF (framing error)
;*
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 23 2025
;* Target: AVR128DB48
;* Number of words: ~10
;* Number of cycles: Variable (depends on branch path)
;* Low registers modified:none
;* High registers modified: None
;*
;* Parameters:
;*   r16 = received ASCII character
;*   Carry flag (C) = stop-bit validity (1 = valid, 0 = invalid)
;*
;* Returns:
;*   Updates LED outputs on VPORTD.
;*
;* Notes: 
;*   - LED D7 acts as a “status” indicator showing framing validity.
;*   - LEDs on VPORTD[6:0] show the inverted ASCII data bits.
;***************************************************************************

display:
rol r17
com r18
out VPORTD_OUT, r18
ror r17
brcs turn_led_on
brcc turnledoff
turn_led_on:
cbi VPORTD_OUT, 7
ret
turnledoff:
sbi VPORTD_OUT, 7
ret
;***************************************************************************
;* Subroutine Name: half_bit_time_52us
;*
;* Description:
;*   Provides a fixed software delay of approximately 52 microseconds.
;*   This is one-half of a bit time for serial communication at 9600 baud.
;*
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 2025
;* Target: AVR128DB48 @ 4 MHz
;*
;* Number of words: ~5
;* Low registers modified: none
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
;***************************************************************************
;* Subroutine Name: bit_time_104us
;*
;* Description:
;*   Provides a fixed software delay of approximately 104 microseconds.
;*   This corresponds to one full bit time for serial communication at 
;*   9600 baud when the CPU clock is 4 MHz.
;*
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 23 2025
;* Target: AVR128DB48 
;*
;* Number of words: ~6
;* Low registers modified: none
;* High registers modified: None
;*
;* Parameters: None
;* Returns: None
;*
;***************************************************************************
bit_time_104us: 
	ldi r16, 136 // 1 clock 
bt1_loop: 
	dec r16 // 1 clock 
	brne bt1_loop // 2/1 clocks 
	nop // 2 clocks padding 
	nop 
	ret // 4
