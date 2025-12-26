#define F_CPU 16000000UL
#include <avr/io.h>

void UART_init() {
    UBRR0H = 0;
    UBRR0L = 103; //baud rate 9600
    UCSR0B = (1 << RXEN0); //enabling reciever
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //data frame 8 bit 
}

uint8_t UART_receive() {
    while (!(UCSR0A & (1 << RXC0))); //waiting for the status flag
    return UDR0; //returning the data registers value
}

//simple if else to light the leds up 
void showLED(uint8_t v) {
    PORTD &= ~((1<<PD2)|(1<<PD3)|(1<<PD4));

    if (v == '1') PORTD |= (1<<PD2);
    if (v == '2') PORTD |= (1<<PD3);
    if (v == '3') PORTD |= (1<<PD4);
}

int main() {
    UART_init();
    DDRD |= (1<<PD2)|(1<<PD3)|(1<<PD4); //sets as output

    while (1) {
        uint8_t rx = UART_receive();
        showLED(rx);
    }
}
