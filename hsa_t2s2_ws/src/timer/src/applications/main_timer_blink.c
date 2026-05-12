#include <atmega32/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow_count = 0;

ISR(TIMER2_OVF_vect)
{
    overflow_count++;

    if (overflow_count >= 61)
    {
        PORTC ^= (1 << PC0);
        overflow_count = 0;
    }
}

int main (void)
{        
    cli();

    TCCR2 = (1 << CS22);
    TIMSK |= (1 << TOIE2);
    TCNT2 = 0;
    DDRC |= (1 << PC0);

    sei();

    while(1)
    {
    }

    // Should never be reached    
    return 0;
}
