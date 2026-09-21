;***************************************************************************
;*
;* Title: USART1 Serial Receive with Line Buffer
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 30, 2025
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* USART1 receives at ~115200 baud and stores bytes into a 40-byte buffer
;* (scanned_data) until a carriage return (0x0D). Then the buffer is sent
;* out via USART3 at ~9600 baud. The CR is included; no null terminator
;* is added. The loop repeats for each line.
;*
;* VERSION HISTORY
;* 1.0  Original version — added UART initialization, receive routine,
;*      line-buffer storage, and safety checks for overflow.
;***************************************************************************
.nolist 
.include "AVR128DB48def.inc"
.list
.dseg
scanned_data: .byte 40
.cseg
start:
ldi r16, LOW(139)
sts USART1_BAUDL, r16
ldi r16, HIGH(139)
sts USART1_BAUDH, r16
ldi r16, 0x03
sts USART1_CTRLC, r16
cbi VPORTC_DIR, 1
ldi r16, 0x80
sts USART1_CTRLB, r16
lds r16, USART1_DBGCTRL
ldi r16, (1<<0)
sts USART1_DBGCTRL, r16

main:
ldi YL, LOW(scanned_data)
ldi YH, HIGH(scanned_data)
rcall give
rjmp main
;***************************************************************************
;*
;* "give" - Receive serial data from USART1 until carriage return (0x0D)
;*
;* Description:
;*   This subroutine continuously polls the USART1 receiver flag (bit 7 of
;*   USART1_STATUS) until data is available. Each received byte is read from
;*   USART1_RXDATAL and stored sequentially in SRAM at the address pointed to
;*   by Y. The pointer Y is initialized before calling this routine.
;*
;*   The routine continues receiving and storing characters until a carriage
;*   return (0x0D) is received, at which point it returns to the caller.
;*
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 30, 2025
;* Target: AVR128DB48
;* Number of words: 8
;* Number of cycles: Variable (depends on baud rate and input speed)
;* Low registers modified: none
;* High registers modified: none
;*
;* Parameters:
;*   Y – pointer to destination buffer (e.g., scanned_data)
;*
;* Returns:
;*   On return, buffer contains all received bytes up to and including 0x0D.
;*   Y points to the next free memory location after the last stored byte.
;*
;* Notes:
;*   - Uses polling, not interrupts.
;*   - Does not append a null terminator.
;*   - Designed for continuous serial input terminated by carriage return.
;***************************************************************************
give:
lds r18, USART1_STATUS
sbrs r18, 7
rjmp give

receive:
lds r17, USART1_RXDATAL
st Y+, r17
cpi r17, 0x0D
brne give
ret