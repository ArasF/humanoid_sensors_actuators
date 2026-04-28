#include <atmega32/asm/io.h>

.global main

main:
    sbi DDRC, PC3
    cbi DDRC, PC4

loop:
    rcall wait_1s

    sbic PINC, PC4
    rjmp set_pc3

clear_pc3:
    cbi PORTC, PC3
    rjmp loop

set_pc3:
    sbi PORTC, PC3
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
