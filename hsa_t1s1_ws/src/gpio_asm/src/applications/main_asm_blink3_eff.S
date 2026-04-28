#include <atmega32/asm/io.h>

.global main

main:
    sbi DDRC, PC0
    sbi DDRC, PC1
    sbi DDRC, PC2

loop:
    in   r16, PORTC
    andi r16, 0b11111000
    ori  r16, 0b00000001
    out  PORTC, r16
    rcall wait_1s

    in   r16, PORTC
    andi r16, 0b11111000
    ori  r16, 0b00000010
    out  PORTC, r16
    rcall wait_1s

    in   r16, PORTC
    andi r16, 0b11111000
    ori  r16, 0b00000100
    out  PORTC, r16
    rcall wait_1s

    rjmp loop

wait_1s:
    ldi r18, 0x3F
    ldi r24, 0x0D
    ldi r25, 0x03
1:
    subi r18, 0x01
    sbci r24, 0x00
    sbci r25, 0x00
    brne 1b
    rjmp 1f
1:
    nop
    ret

.end