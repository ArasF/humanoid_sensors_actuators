#include <atmega32/io.h>

#include <atmega32/uart.h>
#include <util/delay.h>

#define SAMPLE_COUNT 1024
#define TX_CHUNK_SIZE 255

static void adc_init(void);
static void adc_readBlocking(uint8_t* b, uint8_t ch);


int main (void)
{            
    uint8_t samples[SAMPLE_COUNT];
    uint16_t i;
    uint16_t remaining;
    uint16_t offset;
    uint8_t chunk_size;

    DDRC |= (1 << PC1);
    PORTC &= ~(1 << PC1);

    uart_setBaudrateReg(CALC_BAUD_VAL(62500));
    uart_setFormat();
    uart_enable();

    adc_init();

    while(1)
    {
        PORTC &= ~(1 << PC1);
        _delay_ms(10);

        PORTC |= (1 << PC1);

        for(i = 0; i < SAMPLE_COUNT; ++i)
        {
            adc_readBlocking(&samples[i], 0);
        }

        PORTC &= ~(1 << PC1);

        remaining = SAMPLE_COUNT;
        offset = 0;

        while(remaining > 0)
        {
            chunk_size = (remaining > TX_CHUNK_SIZE) ? TX_CHUNK_SIZE : (uint8_t)remaining;
            uart_writeBlocking(&samples[offset], chunk_size);
            offset += chunk_size;
            remaining -= chunk_size;
        }

        _delay_ms(100);
    }

    return 0;
}

static void adc_init(void)
{
    ADMUX = (1 << REFS0) | (1 << ADLAR);
    SFIOR &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADPS0);
}

static void adc_readBlocking(uint8_t* b, uint8_t ch)
{
    ADMUX = (ADMUX & 0xE0) | (ch & 0x1F);

    while ((ADCSRA & (1 << ADIF)) == 0)
    {
    }

    *b = ADCH;
    ADCSRA |= (1 << ADIF);
}
