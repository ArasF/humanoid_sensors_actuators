#include <atmega32/io.h>

static void uart_init(void)
{
    UCSRA = 0x00;
    UBRRH = 0x00;
    UBRRL = 0x00;
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

static unsigned char uart_receive_blocking(void)
{
    while ((UCSRA & (1 << RXC)) == 0)
    {
    }

    return UDR;
}

static void uart_send_blocking(unsigned char value)
{
    while ((UCSRA & (1 << UDRE)) == 0)
    {
    }

    UDR = value;
}

int main(void)
{
    uart_init();

    while (1)
    {
        unsigned char value = uart_receive_blocking();
        uart_send_blocking(value);
    }

    return 0;
}
