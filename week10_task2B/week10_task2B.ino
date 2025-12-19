#define F_CPU 16000000UL
#include <avr/io.h>

void UART_init() {
    UBRR0H = 0;
    UBRR0L = 103;
    UCSR0B = (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

uint8_t UART_receive() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void showLED(uint8_t v) {
    PORTD &= ~((1<<PD2)|(1<<PD3)|(1<<PD4));

    if (v == '1') PORTD |= (1<<PD2);
    if (v == '2') PORTD |= (1<<PD3);
    if (v == '3') PORTD |= (1<<PD4);
}

int main() {
    UART_init();
    DDRD |= (1<<PD2)|(1<<PD3)|(1<<PD4);

    while (1) {
        uint8_t rx = UART_receive();
        showLED(rx);
    }
}
