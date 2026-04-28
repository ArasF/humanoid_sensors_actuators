#define F_CPU 1000000UL

#include <atmega32/io.h>
#include <util/delay.h>

static void uart_init(void)
{
    UCSRA = 0x00;
    UBRRH = 0x00;
    UBRRL = 0x00;
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

static void uart_send_blocking(unsigned char value)
{
    while ((UCSRA & (1 << UDRE)) == 0)
    {
    }

    UDR = value;
}

static void uart_send_string(const char *text)
{
    while (*text != '\0')
    {
        uart_send_blocking((unsigned char)*text);
        text++;
    }
}

int main(void)
{
    uart_init();

    while (1)
    {
        uart_send_string("Hello world!\n");
        _delay_ms(1000);
    }

    return 0;
}
