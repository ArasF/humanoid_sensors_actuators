#include <atmega32/io.h>
#include <avr/interrupt.h>

volatile uint8_t adc_value = 0;

ISR(TIMER0_OVF_vect)
{
    OCR0 = adc_value;
    PORTC |= (1 << PC0);
}

ISR(TIMER0_COMP_vect)
{
    PORTC &= ~(1 << PC0);
}

ISR(ADC_vect)
{
    adc_value = ADCH;
    ADCSRA |= (1 << ADSC);
}

int main (void)
{
    cli();

    DDRC |= (1 << PC0);
    PORTC &= ~(1 << PC0);

    TCCR0 = (1 << CS02) | (1 << CS00);
    TCNT0 = 0;
    OCR0 = 0;

    TIMSK |= (1 << TOIE0);
    TIMSK |= (1 << OCIE0);

    ADMUX = (1 << REFS0) | (1 << ADLAR);
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    sei();
    ADCSRA |= (1 << ADSC);

    while (1)
    {
    }

    return 0;
}
