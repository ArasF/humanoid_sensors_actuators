#include <atmega32/io.h>
#include <stdint.h>

static void adc_init(void)
{
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);
}

static uint16_t adc_read(uint8_t channel)
{
    ADMUX = (ADMUX & 0xE0) | (channel & 0x1F);
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC))
    {
    }

    return ADCW;
}

int main (void)
{
    DDRD |= (1 << PD5);

    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
    ICR1 = 2499;
    OCR1A = 188;

    adc_init();

    while (1)
    {
        uint16_t adc_value = adc_read(0);
        OCR1A = 125 + (uint16_t)(((uint32_t)adc_value * 125U) / 1023U);
    }

    return 0;
}
