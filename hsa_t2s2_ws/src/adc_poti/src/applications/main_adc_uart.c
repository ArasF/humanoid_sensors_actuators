#include <atmega32/io.h>

#include <atmega32/uart.h>
#include <atmega32/adc.h>

#include <util/delay.h>


int main (void)
{            
    uart_setBaudrateReg(CALC_BAUD_VAL(62500));
    uart_setFormat();
    uart_enable();

    adc_setStdConfig();
    adc_enable();

    uint8_t val;

    while(1)
    {
        _delay_ms(10);

        adc_readBlocking(&val,0);
        uart_writeByteBlocking(val);
    }

    return 0;
}
