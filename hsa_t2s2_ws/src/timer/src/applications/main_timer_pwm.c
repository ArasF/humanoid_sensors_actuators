#include <atmega32/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_OVF_vect)
{
    PORTC |= (1 << PC0);
}

ISR(TIMER0_COMP_vect)
{
    PORTC &= ~(1 << PC0);
}

int main (void)
{
    cli();

    DDRC |= (1 << PC0);
    PORTC &= ~(1 << PC0);

    TCCR0 = (1 << CS02) | (1 << CS00);
    TCNT0 = 0;
    OCR0 = 64;

    TIMSK |= (1 << TOIE0);
    TIMSK |= (1 << OCIE0);

    sei();

    while (1)
    {
    }

    return 0;
}
