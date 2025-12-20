#define F_CPU 16000000UL
#include <avr/io.h>

void UART_init() {
    UBRR0H = 0;
    UBRR0L = 103;                        // 9600 baud
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); //enabeling the tx rx 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //bit format 8 bit
}

uint8_t UART_receive() {
    while (!(UCSR0A & (1 << RXC0))); //waiting for the status flag
    return UDR0;
}

void UART_send(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0))); //again waiting to see if the register is empty
    UDR0 = data;
}

int main() {
    UART_init();

    while (1) {
        uint8_t c = UART_receive();   // typed in Serial Monitor

        if (c == '1' || c == '2' || c == '3') {
            UART_send(c);             // forward to receiver
        }
    }
}
