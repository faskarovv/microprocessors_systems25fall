#include <avr/io.h>
#include <util/delay.h>

#define KEY 0xA5
#define IV  0x3C

uint8_t counter = 0;
uint8_t prev = IV;

static inline uint8_t rotl8(uint8_t x) {
    return (x << 3) | (x >> 5);
}

uint8_t encrypt(uint8_t p) {
    p ^= prev;                 // CBC chaining
    uint8_t c = rotl8(p ^ KEY);
    prev = c;
    return c;
}

void uart_init(void) {
    uint16_t ubrr = 103;
    UBRR0H = ubrr >> 8;
    UBRR0L = ubrr;
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_send(uint8_t d) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = d;
}

int main(void) {
    uart_init();

    while (1) {
        uart_send(encrypt(counter));
        counter++;
        _delay_ms(100);
    }
}
