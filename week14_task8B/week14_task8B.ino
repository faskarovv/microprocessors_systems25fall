#include <avr/io.h>

#define KEY 0xA5

uint8_t rotr8(uint8_t x, uint8_t r) {
    return (x >> r) | (x << (8 - r));
}

uint8_t decrypt(uint8_t c) {
    return rotr8(c, 3) ^ KEY;
}

void uart_init(void) {
    uint16_t ubrr = 103;

    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;

    UCSR0B = (1 << RXEN0);                 // Enable RX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

uint8_t uart_receive(void) {
    while (!(UCSR0A & (1 << RXC0)));   // Wait for full frame
    return UDR0;
}

int main(void) {
    uart_init();

    while (1) {
        uint8_t cipher = uart_receive();
        uint8_t plain  = decrypt(cipher);

        // place breakpoint here or output via another UART
        (void)plain;
    }
}
