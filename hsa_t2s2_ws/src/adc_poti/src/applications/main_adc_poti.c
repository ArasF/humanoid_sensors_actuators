#include <atmega32/io.h>

#include <atmega32/uart.h>
#include <util/delay.h>


void adc_readBlocking(uint8_t* b, uint8_t ch);

int main (void)
{            
    uart_setBaudrateReg(CALC_BAUD_VAL(62500));
    uart_setFormat();
    uart_enable();

    uint8_t val;

    while(1)
    {
        _delay_ms(10);

        adc_readBlocking(&val,0);
        uart_writeByteBlocking(val);
    }

    return 0;
}



void adc_readBlocking(uint8_t* b, uint8_t ch)
{
    *b = 0x00;
}