#define F_CPU 1000000UL

// Get register definitions with auto complete
#include <atmega32/io.h>

// For delay functions: F_CPU has to be defined
#include <util/delay.h>


int main(void)
{
    DDRC |= (1 << PC3);
    DDRC &= ~(1 << PC4);

    while (1) {
        _delay_ms(1000);

        if (PINC & (1 << PC4)) {
            PORTC |= (1 << PC3);
        } else {
            PORTC &= ~(1 << PC3);
        }
    }

    return 0;
}

