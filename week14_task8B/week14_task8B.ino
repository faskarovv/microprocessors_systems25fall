#include <avr/io.h>
#include <Arduino.h>   // ONLY for Serial Monitor

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

    UCSR0B = (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

uint8_t uart_receive(void) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

int main(void) {
    uart_init();

    Serial.begin(9600);   // For monitor only

    while (1) {
        uint8_t cipher = uart_receive();
        uint8_t plain  = decrypt(cipher);

        Serial.println(plain);
    }
}
