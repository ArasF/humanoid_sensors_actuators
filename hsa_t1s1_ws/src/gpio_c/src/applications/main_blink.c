#define F_CPU 1000000UL

// Get register definitions with auto complete
#include <atmega32/io.h>

// For delay functions: F_CPU has to be defined
#include <util/delay.h>


int main(void)
{
    DDRC |= (1 << PC0);

    while (1) {
        PORTC |= (1 << PC0);
        _delay_ms(1000);

        PORTC &= ~(1 << PC0);
        _delay_ms(1000);
    }

    return 0;
}


