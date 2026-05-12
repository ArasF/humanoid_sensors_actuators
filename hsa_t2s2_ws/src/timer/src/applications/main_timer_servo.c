#include <atmega32/io.h>
#include <stdint.h>
#include <util/delay.h>

int main (void)
{
    uint16_t pulse;

    DDRD |= (1 << PD5);

    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
    ICR1 = 2499;

    while (1)
    {
        for (pulse = 125; pulse <= 250; pulse += 1)
        {
            OCR1A = pulse;
            _delay_ms(20);
        }

        for (pulse = 250; pulse >= 125; pulse -= 1)
        {
            OCR1A = pulse;
            _delay_ms(20);
        }
    }

    return 0;
}
