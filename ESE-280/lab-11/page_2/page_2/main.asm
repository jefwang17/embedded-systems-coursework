.nolist
.include "avr128DB48def.inc"
.list 
.equ PAGE_SIZE = 80
.dseg
page_1_buff: .byte PAGE_SIZE ;80-byte page buffer
page_2_buff: .byte PAGE_SIZE ;80-byte page buffer
number: .byte 2
scanned_data: .byte 40
unsigned: .byte 1
.cseg
reset:
jmp init
.org USART1_RXC_vect //vector for usart1 rx register
jmp USART1_RXC_ISR
.org PORTE_PORT_vect //vector all PORTE pin change IQRs
jmp porte_isr
.org USART3_DRE_vect //vector for usart3 data register
jmp USART3_DRE_ISR


init:
sbi VPORTB_DIR, 0 ;set PB0 as output, tx signal
sbi VPORTB_OUT, 0 ;set PB0 to 1
rcall build_page_1
ldi r17, 0 ;0 => first page
rcall USART3_init
rcall clear_page
rcall start_tx
ldi r20, 200
rcall delay_loop


end:
rcall clear_page
rcall build_page_2
ldi r17, 1


rcall start_tx
rcall clear_number
rcall get_number
rcall convert_str_to_unsign
ldi r17, 2
rcall start_tx
rcall USART1_init
rcall scan_to_LCD
rjmp end
build_page_1:
ldi XL, low(page_1_buff)
ldi XH, high(page_1_buff)
ldi r18, 20
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
ldi ZL, low(line2str<<1)
ldi ZH, high(line2str<<1)
ldi r18, 20
loop_line2:
lpm r16, Z+
st X+, r16
dec r18
brne loop_line2
ret
line2str: .db " Inventory System I                    "
line3:
ldi ZL, low(line3str<<1)
ldi ZH, high(line3str<<1)
ldi r18, 20


loop_line3:
lpm r16, Z+
st X+, r16
dec r18
brne loop_line3
ret
line3str: .db " ESE280 Fall 2025                    "
line4:
ldi ZL, low(line4str<<1)
ldi ZH, high(line4str<<1)
ldi r18, 20
loop_line4:
lpm r16, Z+
st X+, r16
dec r18
brne loop_line4
ret
line4str: .db " jeff                    "


build_page_2:
ldi XL, low(page_2_buff)
ldi XH, high(page_2_buff)
rcall p2line1
ldi r18, 20
p2line2:
ldi r16, ' '
st X+, r16
dec r18
brne p2line2
rcall p2line3
ldi r18, 20
p2line4:
ldi r16, ' '
st X+, r16


dec r18
brne p2line4
ret
p2line1:
ldi ZL, low(p2line1str<<1)
ldi ZH, high(p2line1str<<1)
ldi r18, 20
loop_p2line1:
lpm r16, Z+
st X+, r16
dec r18
brne loop_p2line1
ret
p2line1str: .db "Enter item count:                    "
p2line3:
ldi ZL, low(p2line3str<<1)
ldi ZH, high(p2line3str<<1)
ldi r18, 20
loop_p2line3:
lpm r16, Z+
st X+, r16
dec r18
brne loop_p2line3
ret
p2line3str: .db "Scan barcode:                    "


USART3_init:
ldi r16, LOW(1667)
sts USART3_BAUDL, r16
ldi r16, HIGH(1667)
sts USART3_BAUDH, r16
ldi r16, 0b00000011
sts USART3_CTRLC, r16
ldi r16, 0b01000000
sts USART3_CTRLB, r16


ldi r16, 0b00000001
sts USART3_DBGCTRL, r16
ret
USART1_init:
cbi VPORTC_DIR, 1
ldi r16, LOW(139)
sts USART1_BAUDL, r16
ldi r16, HIGH(139)
sts USART1_BAUDH, r16
ldi r16, 0b00000011
sts USART1_CTRLC, r16
ldi r16, 0b10000000
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
ldi r16, 0b00100000
sts USART3_CTRLA, r16
sei
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
ldi r16, 0b00000000
sts USART3_CTRLA, r16
sei
reti


get_number:
ldi r22, 0
cbi VPORTE_DIR, 3
sei
ldi r16, 0x00
out VPORTC_DIR, r16
lds r16, PORTE_PIN3CTRL
ori r16, 0x02
sts PORTE_PIN3CTRL, r16
ldi XL, low(page_2_buff+20)
ldi XH, high(page_2_buff+20)
ldi YL, low(number)
ldi YH, high(number)
wait_enter_press:
cpi r16, 0x0c
brne wait_enter_press
ldi r16, 0x0D
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
ldi r16, 0
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
   cli
  
   ; Read keypad nibble
   in r16, VPORTC_IN
   lsr r16
   lsr r16
   lsr r16
   lsr r16
   andi r16, 0x0F


   rcall scan_to_value   ; look up actual key value


   mov r20, r16          ; save key for comparisons


   ; --------- ENTER KEY (0x0D) ----------
   cpi r20, 0x0D
   breq handle_enter


   ; --------- CLEAR KEY (0x0E) ----------
   cpi r20, 0x0E
   breq handle_clear


   ; --------- NORMAL DIGIT OR HELP ----------
   ; convert to ASCII and send to LCD
   ori r16, 0x30
   rcall send_USART3


   ; store numeric value in buffer
   andi r20, 0x0F
   st Y+, r20
   inc r22
   ori r20, 0x30
   st X+, r20
   rjmp done_key


handle_clear:
   ; do not clear if buffer already empty
   tst r22
   breq done_key


   dec r22       ; one less digit entered
   dec YL        ; move pointer back
   dec XL        ; move LCD pointer back


   ; send backspace to LCD
   ldi r16, 0x08
   rcall send_USART3
   rjmp done_key


handle_enter:
   ; ENTER pressed ? finish input
   rjmp done_enter


done_key:
   ; clear interrupt flag and return
   push r16
   ldi r16, PORT_INT3_bm
   sts PORTE_INTFLAGS, r16
   pop r16
   sei
   reti


done_enter:
   push r16
   ldi r16, PORT_INT3_bm
   sts PORTE_INTFLAGS, r16
   pop r16
   sei
   reti




scan_to_value:
ldi ZH, high(table*2)
ldi ZL, low(table*2)
ldi r21, 0x00
add ZL, r16
adc ZH, r21
lpm r16, Z


ret
table:
   .db 0x01, 0x02, 0x03, 0x0A   ; 1, 2, 3, A
   .db 0x04, 0x05, 0x06, 0x0B   ; 7, 5, 6, B
   .db 0x07, 0x08, 0x09, 0x0C   ; 4, 8, 9, C
   .db 0x0E, 0x00, 0x0F, 0x0D   ; Clear, 0, Help, Enter




send_USART3:
wait_data_empty:
lds R21, USART3_STATUS
sbrs R21, 5
rjmp wait_data_empty
sts USART3_TXDATAL, R16
ret


clear_page:
ldi r16, 0x7C
rcall send_USART3
ldi r16, 0x2D
rcall send_USART3
ret


receive_USART1:
wait_receive:
lds r21, USART1_STATUS
sbrs r21, 7
rjmp wait_receive
lds r16, USART1_RXDATAL
ret


scan_to_LCD:
ldi YL, low(scanned_data)
ldi YH, high(scanned_data)
store_until_CR:
rcall receive_USART1
st Y+, r16
cpi r16, 0x0D


brne store_until_CR
ldi YL, low(scanned_data)
ldi YH, high(scanned_data)
send_until_CR:
ld r16, Y+
rcall send_USART3
cpi r16, 0x0D
brne send_until_CR
wait_for_keypad:
sbis VPORTE_IN, 3
rjmp wait_for_keypad
ret


USART1_RXC_ISR:
reti


delay_loop:
   ldi r19, 100
   rcall var_delay
   dec r20
   brne delay_loop
   ret


var_delay:
   outer_loop:
   ldi r16, 133
   inner_loop:
   dec r16
   brne inner_loop
   dec r19
   brne outer_loop
   ret








