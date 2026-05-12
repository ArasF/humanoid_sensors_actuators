#include <atmega32/io.h>
#include <atmega32/uart.h>
#include <stdlib.h>
#include <util/delay.h>

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

static void uart_write_string(const char *str)
{
    while (*str != '\0')
    {
        uart_writeByteBlocking((uint8_t)*str);
        str++;
    }
}

static void uart_write_uint16(uint16_t value)
{
    char buffer[6];
    utoa(value, buffer, 10);
    uart_write_string(buffer);
}

int main (void)
{
    uart_setBaudrateReg(CALC_BAUD_VAL(62500));
    uart_setFormat();
    uart_enable();

    adc_init();

    while (1)
    {
        uint16_t value = adc_read(0);
        uart_write_uint16(value);
        uart_write_string("\r\n");
        _delay_ms(20);
    }

    return 0;
}
