.nolist
.include "AVR128DB48def.inc"
.list

;***************************************************************************
;*
;* Title: send_inventory
;* Author: Jeffery Wang
;* Version: 1.0
;* Last updated:
;* Target: avr128db48
;*
;* DESCRIPTION
;* Display page 1 to LCD for 2 sec, display page 2, ask for input,
;* scan barcode, then send inventory data to base station via RYLR896
;*
;* VERSION HISTORY
;* 1.0 Original version
;***************************************************************************

.equ PAGE_SIZE = 80

.dseg

page_1_buff: .byte PAGE_SIZE        ;80-byte page buffer
page_2_buff: .byte PAGE_SIZE        ;80-byte page buffer
number: .byte 2
scanned_data: .byte 40
unsigned: .byte 1
at_send_cmd: .byte 50               ;buffer for AT+SEND command
x_pointer: .byte 2


.cseg

reset:
	jmp init

.org PORTE_PORT_vect                ;vector all PORTE pin change IQRs
	jmp porte_isr
.org USART1_RXC_vect                ;vector for usart1 rx register
	jmp USART1_RXC_ISR
.org USART3_DRE_vect                ;vector for usart3 data register
	jmp USART3_DRE_ISR


init:
	sbi VPORTB_DIR, 0               ;set PB0 as output, tx signal
	sbi VPORTB_OUT, 0               ;set PB0 to 1

    rcall build_page_1
	ldi r17, 0                      ;use r17 as option control, 0 => first page

    rcall USART3_init               ;initialize USART3
	rcall clear_page
    rcall start_tx                  ;transmit cover page
	ldi r20, 200                    ;loop var_delay 200 times
	rcall delay_loop


end:
	rcall clear_page
	rcall build_page_2                  ;build page 2 in the given format without the entries
	ldi r17, 1                          ;load r17 so it goes into page 2 line 1, 1 => page 2 line 1
	rcall start_tx                      ;transmit page 2 line 1
	rcall clear_number
	rcall get_number                    ;get and display entered numbers
	rcall convert_str_to_unsign
	ldi r17, 2                          ;load r17 so it goes into page 2 line 3, 2 => page 2 line 3
	rcall start_tx                      ;transmit page 2 line 3
	rcall USART1_init                   ;initialize USART1 for barcode scanner
	rcall scan_to_LCD                   ;display scanned code to LCD

	;Send inventory data via RYLR896
	rcall send_to_base_station
	rjmp end

build_page_1:

	ldi XL, low(page_1_buff)
	ldi XH, high(page_1_buff)
	ldi r18, 20							;lcv r18
	line1:
		ldi r16, ' '
		st X+, r16
		dec r18
		brne line1
		rcall line2
		rcall line3
		rcall line4
		ret

	line2:
		ldi ZL, low(line2str << 1)
		ldi ZH, high(line2str << 1)
		ldi r18, 20
		loop_line2:						;get line 2 from RRAM
			lpm r16, Z+
			st X+, r16
			dec r18
			brne loop_line2
			ret

	line2str: .db " Inventory System I "

	line3:
		ldi ZL, low(line3str << 1)
		ldi ZH, high(line3str << 1)
		ldi r18, 20
		loop_line3:						;get line 3 from RRAM
			lpm r16, Z+
			st X+, r16
			dec r18
			brne loop_line3
			ret

	line3str: .db "  ESE280 Fall 2025  "

	line4:								;get line 4 from RRAM
		ldi ZL, low(line4str << 1)
		ldi ZH, high(line4str << 1)
		ldi r18, 20
		loop_line4:
			lpm r16, Z+
			st X+, r16
			dec r18
			brne loop_line4
			ret

	line4str: .db "  < Jeffery Wang >   "

build_page_2:							;Build page 2 without the entry and store in the buffer
	ldi XL, low(page_2_buff)
	ldi XH, high(page_2_buff)
	rcall p2line1                       ;get page 2 line 1 from RRAM
	ldi r18, 20                         ;lcv r18

	p2line2:								;get page 2 line 2 => blank for now
		ldi r16, ' '
		st X+, r16
		dec r18
		brne p2line2
		rcall p2line3                       ;get page 2 line 3 from RRAM
		ldi r18, 20                         ;lcv r18
	p2line4:								;get page 2 line 4 => blank for now
		ldi r16, ' '
		st X+, r16
		dec r18
		brne p2line4
		ret

	p2line1:
		ldi ZL, low(p2line1str << 1)
		ldi ZH, high(p2line1str << 1)
		ldi r18, 20
	loop_p2line1:
		lpm r16, Z+
		st X+, r16
		dec r18
		brne loop_p2line1
		ret

	p2line1str: .db "Enter item count:   "   ;item count

	p2line3:
		ldi ZL, low(p2line3str << 1)
		ldi ZH, high(p2line3str << 1)
		ldi r18, 20
	loop_p2line3:
		lpm r16, Z+
		st X+, r16
		dec r18
		brne loop_p2line3
		ret

	p2line3str: .db "Scan barcode:       "  ;barcode scanning

USART3_init:
	ldi r16, LOW(1667)                  ;load baud register for 9600 baud @ 4MHz
	sts USART3_BAUDL, r16
	ldi r16, HIGH(1667)
	sts USART3_BAUDH, r16

	ldi r16, 0b00000011                 ;load the 8N1 format to CTRLC register
	sts USART3_CTRLC, r16

	ldi r16, 0b01000000                 ;enable the TX transmitter
	sts USART3_CTRLB, r16

	ldi r16, 0b00000001
	sts USART3_DBGCTRL, r16

	ret

USART1_init:
	cbi VPORTC_DIR, 1                   ;clear PC1, RX as an input

	ldi r16, LOW(139)                   ;load baud register for 115200 baud @ 4MHz
	sts USART1_BAUDL, r16
	ldi r16, HIGH(139)
	sts USART1_BAUDH, r16

	ldi r16, 0b00000011                 ;load the 8N1 format to CTRLC register
	sts USART1_CTRLC, r16

	ldi r16, 0b10000000                 ;enable the RX receiver
	sts USART1_CTRLB, r16

	ldi r16, 0b00000000
	sts USART1_CTRLA, r16

	ldi r16, 0b00000001
	sts USART1_DBGCTRL, r16

	ret

start_tx:
	cpi r17, 0
	breq page_1
	cpi r17, 1
	breq page_2_line1
	cpi r17, 2
	breq page_2_line3

	page_1:
		ldi XL, low(page_1_buff)
		ldi XH, high(page_1_buff)
		ldi r18, 1
		rjmp enable_DREIF
	page_2_line1:
		ldi XL, low(page_2_buff)
		ldi XH, high(page_2_buff)
		ldi r18, 1
		rjmp enable_DREIF
	page_2_line3:
		ldi XL, low(page_2_buff+40)
		ldi XH, high(page_2_buff+40)
		ldi r18, 2
		rjmp enable_DREIF

	enable_DREIF:
		ldi r16, 0b00100000                 ;enable DREIF
		sts USART3_CTRLA, r16
		sei                                 ;enable global interrupt flag
	wait_disable_DREIF:
		lds r21, USART3_CTRLA
		sbrc r21, 5
		rjmp wait_disable_DREIF

		ret

USART3_DRE_ISR:
	cli
	cpi r17, 0
	breq page_1_tx
	cpi r17, 1
	breq page_2_l1_tx
	cpi r17, 2
	breq page_2_l3_tx
	page_1_tx:
		ld r16, X+
		sts USART3_TXDATAL, r16
		cpi r18, PAGE_SIZE
		brge done_tx
		inc r18
		sei
		reti
	page_2_l1_tx:
		ld r16, X+
		sts USART3_TXDATAL, r16
		cpi r18, 20
		brge done_tx
		inc r18
		sei
		reti
	page_2_l3_tx:
		ld r16, X+
		sts USART3_TXDATAL, r16
		cpi r18, 20
		brge done_tx
		inc r18
		sei
		reti

	done_tx:
		ldi r16, 0b00000000                 ;disable DREIF
		sts USART3_CTRLA, r16
		sei
		reti


get_number:
	ldi r22, 0                          ;use r22 as a digit count
	cbi VPORTE_DIR, 3                   ;set PE3 as input
	sei                                 ;enable global interrupts
	ldi r16, 0x00
	out VPORTC_DIR, r16                 ;set PC as input
	lds r16, PORTE_PIN3CTRL             ;set ISC for PE3, pos. edge
	ori r16, 0x02                       ;set ISC for rising edge
	sts PORTE_PIN3CTRL, r16
	ldi XL, low(page_2_buff+20)
	ldi XH, high(page_2_buff+20)
	ldi YL, low(number)
	ldi YH, high(number)

	wait_enter_press:
	cpi r16, 0x0c
	brne wait_enter_press

	ldi r16, 0x0D                       ;back space
	rcall send_USART3
	ldi r16, 0x0A
	rcall send_USART3

	ret

clear_number:
	ldi r18, 2
	ldi YL, low(number)
	ldi YH, high(number)
	ldi r16, 0
clear_loop:
	st Y+, r16
	dec r18
	brne clear_loop
	ret

convert_str_to_unsign:
	ldi r16, 0                          ;use r16 for intermediate operation
	ldi YL, low(number)
	ldi YH, high(number)
convert_loop:
	mov r23, r16
	ldi r18, 9
multiply_loop:
	add r16, r23
	dec r18
	brne multiply_loop
	ld r23, Y+
	add r16, r23
	dec r22
	brne convert_loop
	ldi YL, low(unsigned)
	ldi YH, high(unsigned)
	st Y, r16

	ret

porte_isr:
	cli                                 ;clear global interrupt

	in r16, VPORTC_IN                   ;load the keypad value to r16
	lsr r16
	lsr r16
	lsr r16
	lsr r16
	andi r16, 0x0F                      ;mask out 4 ms bits
	rcall scan_to_value                 ;convert the keypad value to the actual value
	ori r16, 0x30
	rcall send_USART3
	andi r16, 0x0f
	cpi r16, 0x0c
	breq done_enter
	st Y+, r16
	inc r22
	ori r16, 0x30
	st X+, r16
done_enter:
	push r16
	ldi r16, PORT_INT3_bm               ;clear INT3
	sts PORTE_INTFLAGS, r16
	pop r16
	sei                                 ;enable global interrupts
	reti

scan_to_value:
	ldi ZH, high(table * 2)             ;set Z to point to start of table
	ldi ZL, low(table * 2)
	ldi r21, 0x00                       ;add offset to Z pointer
	add ZL, r16
	adc ZH, r21
	lpm r16, Z                          ;load byte from table pointed to by Z
	ret

;keypad scan code lookup table
table: .db 0x01, 0x02, 0x03, 0x0F, 0x04, 0x05, 0x06, 0x0E, 0x07, 0x08, 0x09, 0x0D, 0x0A, 0x00, 0x0B, 0x0C

send_USART3:
    ;Wait until transmit buffer is empty
	wait_data_empty:
		lds R21, USART3_STATUS
		sbrs R21, 5                     ;Data Register Empty Flag
		rjmp wait_data_empty
		;Write data to transmit register
		sts USART3_TXDATAL, R16
		ret

clear_page:
	ldi r16, 0x7C                       ;load r16 with | and send in serial
	rcall send_USART3

	ldi r16, 0x2D                       ;load r16 with - and send in serial
	rcall send_USART3
	ret

receive_USART1:
	wait_receive:
	lds r21, USART1_STATUS
	sbrs r21, 7                         ;skip if the RXCIF is set
	rjmp wait_receive

	lds r16, USART1_RXDATAL             ;load received data to r16
	ret

scan_to_LCD:
	ldi YL, LOW(scanned_data)
	ldi YH, HIGH(scanned_data)          ;load the memory location of scanned_data array to Y
store_until_CR:
	rcall receive_USART1                ;receive data from the scanner
	st Y+, r16                          ;input the data to Y and increment Y to the next memory location
	cpi r16, 0x0D
	brne store_until_CR                 ;continue storing until CR

	ldi YL, LOW(scanned_data)
	ldi YH, HIGH(scanned_data)          ;reset the Y pointer to point at the start of the array
send_until_CR:
	ld r16, Y+                          ;store the data at Y from the array and post increment Y
	rcall send_USART3                   ;send data in R16 to the LCD
	cpi r16, 0x0D
	brne send_until_CR                  ;continue sending until CR
wait_for_keypad:
	sbis VPORTE_IN, 3
	rjmp wait_for_keypad
	ret

;***************************************************************************
;* send_to_base_station
;* Builds and sends AT+SEND command with inventory data to base station
;* Format: AT+SEND=<Address>,<Payload Length>,<Data>
;* Where <Data> = Count=<value>,ID=<barcode>
;***************************************************************************
send_to_base_station:
    ;Build AT+SEND command
    ldi XL, LOW(at_send_cmd)
    ldi XH, HIGH(at_send_cmd)
    
    ;Add "AT+SEND="
    ldi ZL, low(at_send_header << 1)
    ldi ZH, high(at_send_header << 1)
    ldi r18, 8                      ;length of "AT+SEND="
build_header:
    lpm r16, Z+
    st X+, r16
    dec r18
    brne build_header
    
    ;Add address "100,"
    ldi r16, '1'
    st X+, r16
    ldi r16, '0'
    st X+, r16
    st X+, r16
    ldi r16, ','
    st X+, r16
    
    ;Calculate payload length
    ;Format: "Count=XX,ID=<barcode>" where barcode ends with CR (0x0D)
    ;Count the barcode characters
    ldi YL, LOW(scanned_data)
    ldi YH, HIGH(scanned_data)
    ldi r19, 0                      ;barcode length counter
count_barcode:
    ld r16, Y+
    cpi r16, 0x0D
    breq done_counting
    inc r19
    rjmp count_barcode
done_counting:
    ;Total length = 6 ("Count=") + count_digits + 4 (",ID=") + barcode_length
    subi r19, -2
	ldi r18, 10                     ;base length "Count=XX,ID="
    add r18, r19                    ;add barcode length
    
    ;Convert length to ASCII (assuming < 100)
    mov r16, r18
    ldi r17, 10
length_tens:
    cp r16, r17
    brlo length_ones_only
    sub r16, r17
    rjmp length_tens
length_ones_only:
    ;r16 now has ones, calculate tens
    mov r20, r18
    sub r20, r16
    ;Convert tens to ASCII
    ldi r17, 10
    ldi r21, 0                      ;tens digit
calc_tens:
    cp r20, r17
    brlo store_length
    sub r20, r17
    inc r21
    rjmp calc_tens
store_length:
    ;Store tens if non-zero
    cpi r21, 0
    breq skip_tens
    ori r21, 0x30
    mov r16, r21
    st X+, r16
skip_tens:
    ;Store ones
    mov r16, r18
    subi r16, -(-10)                ;get remainder
    andi r16, 0x0F
    ori r16, 0x30
    st X+, r16
    ldi r16, ','
    st X+, r16
    
    ;Add "Count="
    ldi ZL, low(count_str << 1)
    ldi ZH, high(count_str << 1)
    ldi r18, 6
add_count:
    lpm r16, Z+
    st X+, r16
    dec r18
    brne add_count
    
    ;Add count value from 'unsigned' variable
    ldi YL, LOW(unsigned)
    ldi YH, HIGH(unsigned)
    ld r16, Y
    ;Convert to ASCII (assuming < 100)
    ldi r17, 10
    ldi r21, 0                      ;tens digit
count_tens:
    cp r16, r17
    brlo count_ones
    sub r16, r17
    inc r21
    rjmp count_tens
count_ones:
    ;Store tens if non-zero
    cpi r21, 0
    breq skip_count_tens
    ori r21, 0x30
    mov r20, r21
    st X+, r20
skip_count_tens:
    ;Store ones
    ori r16, 0x30
    st X+, r16
    
    ;Add ",ID="
    ldi ZL, low(id_str << 1)
    ldi ZH, high(id_str << 1)
    ldi r18, 4
add_id:
    lpm r16, Z+
    st X+, r16
    dec r18
    brne add_id
    
    ;Add barcode data (without CR)
    ldi YL, LOW(scanned_data)
    ldi YH, HIGH(scanned_data)
add_barcode:
    ld r16, Y+
    cpi r16, 0x0D
    breq done_building
    st X+, r16
    rjmp add_barcode
    
done_building:
    ;Add CR+LF and null terminator
    ldi r16, 0x0D
    st X+, r16
    ldi r16, 0x0A
    st X+, r16
    ldi r16, 0x00                   ;null terminator
    st X, r16
    
    ;Initialize USART2 for transmission
    rcall USART2_init
    
    ;Send command via polling
    ldi YL, LOW(at_send_cmd)
    ldi YH, HIGH(at_send_cmd)
send_loop:
    ld r16, Y+
    cpi r16, 0x00                   ;check for null terminator
    breq send_complete
    rcall send_USART2
    rjmp send_loop
    
send_complete:
    ret

;***************************************************************************
;* USART2_init - Initialize USART2 for RYLR896 (115200 baud, 8N1)
;* USART2 is on PORTF: PF4=TX, PF5=RX
;***************************************************************************
USART2_init:
    sbi VPORTF_DIR, 4               ;set PF4 as output (TX)
    cbi VPORTF_DIR, 5               ;set PF5 as input (RX)
    
	lds r16, PORTMUX_USARTROUTEA
	ori r16, 0x10
	sts PORTMUX_USARTROUTEA, r16

    ldi r16, LOW(1667)               ;load baud register for 115200 baud @ 4MHz
    sts USART2_BAUDL, r16
    ldi r16, HIGH(1667)
    sts USART2_BAUDH, r16
    
    ldi r16, 0b00000011             ;8N1 format
    sts USART2_CTRLC, r16
    
    ldi r16, 0b01000000             ;enable TX transmitter
    sts USART2_CTRLB, r16
    
    ldi r16, 0b00000001
    sts USART2_DBGCTRL, r16
    
    ret

;***************************************************************************
;* send_USART2 - Send byte in r16 via USART2 using polling
;***************************************************************************
send_USART2:
wait_usart2_dre:
  lds r21, USART2_STATUS
   sbrs r21, 5                     ;skip if DREIF (bit 5) is set
   rjmp wait_usart2_dre
    sts USART2_TXDATAL, r16         ;send the byte
    ret

;String constants
at_send_header: .db "AT+SEND="
count_str: .db "Count="
id_str: .db ",ID="

USART1_RXC_ISR:
	reti

delay_loop:
	ldi r19, 100                        ;load r19 the var_delay to be 10ms
	rcall var_delay
	dec r20
	brne delay_loop
	ret


var_delay:								;delay for AVR128DB48 @ 4.00 MHz = r19 * 0.1 ms
	outer_loop:
		ldi r16, 133
	inner_loop:
		dec r16
		brne inner_loop
		dec r19
		brne outer_loop
	ret


