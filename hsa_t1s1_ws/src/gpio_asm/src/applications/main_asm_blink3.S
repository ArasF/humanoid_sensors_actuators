#include <atmega32/asm/io.h>

.global main

main:
    sbi DDRC, PC0
    sbi DDRC, PC1
    sbi DDRC, PC2

loop:
    sbi PORTC, PC0
    cbi PORTC, PC1
    cbi PORTC, PC2
    rcall wait_1s

    cbi PORTC, PC0
    sbi PORTC, PC1
    cbi PORTC, PC2
    rcall wait_1s

    cbi PORTC, PC0
    cbi PORTC, PC1
    sbi PORTC, PC2
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