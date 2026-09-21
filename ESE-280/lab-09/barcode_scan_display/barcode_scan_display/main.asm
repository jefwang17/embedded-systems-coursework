;***************************************************************************
;*
;* Title: USART1 to USART3 Serial Echo with Line Buffer
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 30, 2025
;* Target: AVR128DB48
;*
;* DESCRIPTION
;* This program configures USART1 as a receiver and USART3 as a transmitter.
;* Characters received on USART1 are stored sequentially in a 40-byte SRAM
;* buffer (scanned_data). When a carriage return (0x0D) is received, the
;* program resets the buffer pointer and transmits the stored characters
;* out through USART3, echoing the received line. The process then repeats,
;* continuously relaying serial input from USART1 to USART3.
;*
;*
;* VERSION HISTORY
;* 1.0  Original version — added dual-USART setup, receive-store-echo routine,
;*      and polling-based serial handling.
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
ldi r16, LOW(1667)
sts USART3_BAUDL, r16
ldi r16, HIGH(1667)
sts USART3_BAUDH, r16
ldi r16, 0x03
sts USART3_CTRLC, r16
sbi VPORTB_DIR, 0
sbi VPORTB_OUT, 0
ldi r16, 0x40
sts USART3_CTRLB, r16
lds r16, USART3_DBGCTRL
ldi r16, (1<<0)
sts USART3_DBGCTRL, r16
main:
ldi YL, LOW(scanned_data)
ldi YH, HIGH(scanned_data)
rcall give
rjmp main
;***************************************************************************
;* 
;* Subroutine_name: give
;*
;* Description:
;*   Polls USART1 until data is available. Each received byte is stored
;*   sequentially in SRAM at [Y+]. When a carriage return (0x0D) is received,
;*   the buffer pointer is reset to the start of scanned_data, and the
;*   program transmits all stored bytes through USART3, echoing the full line.
;*
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated: October 30, 2025
;* Target: AVR128DB48
;* Number of words: ~18
;* Number of cycles: Variable (depends on serial speed and data length)
;* Low registers modified: none
;* High registers modified: none
;*
;* Parameters:
;*   Y – pointer to the SRAM buffer (scanned_data)
;*
;* Returns:
;*   After RET, scanned_data contains one full CR-terminated line.
;*   The same data has been transmitted through USART3.
;*
;* Notes:
;*   - Uses polling for both receive (RXCIF bit7) and transmit (DREIF bit5).
;*   - Carriage return (0x0D) is included in the buffer and echoed as-is.
;*   - No null terminator is added.
;*   - Suitable for serial debugging or loopback testing between ports.
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
ldi YL, LOW(scanned_data)
ldi YH, HIGH(scanned_data)

see_if_ready:
lds r19, USART3_STATUS
sbrs r19, 5
rjmp see_if_ready
ld r20, Y+
sts  USART3_TXDATAL, r20
cpi r20, 0x0D
brne see_if_ready
ret


