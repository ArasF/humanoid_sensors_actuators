#include <atmega32/io.h>

#include <atmega32/uart.h>
#include <util/delay.h>


void adc_init(void);
void adc_readBlocking(uint8_t* b, uint8_t ch);

int main (void)
{            
    uart_setBaudrateReg(CALC_BAUD_VAL(62500));
    uart_setFormat();
    uart_enable();
    adc_init();

    uint8_t val;

    while(1)
    {
        _delay_ms(10);

        adc_readBlocking(&val,0);
        uart_writeByteBlocking(val);
    }

    return 0;
}



void adc_init(void)
{
    ADMUX = (1 << REFS0) | (1 << ADLAR);
    SFIOR &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADPS0);
}

void adc_readBlocking(uint8_t* b, uint8_t ch)
{
    ADMUX = (ADMUX & 0xE0) | (ch & 0x1F);

    while ((ADCSRA & (1 << ADIF)) == 0)
    {
    }

    *b = ADCH;
    ADCSRA |= (1 << ADIF);
}
