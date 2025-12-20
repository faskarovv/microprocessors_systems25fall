#include <avr/io.h>
#include <util/delay.h>

#define KEY 0xA5

uint8_t counter = 0;

//rotating left 
uint8_t rotl8(uint8_t x, uint8_t r) {
    return (x << r) | (x >> (8 - r));
}

//encrypt
uint8_t encrypt(uint8_t p) {
    return rotl8(p ^ KEY, 3);
}

//baud rate 9600
void uart_init(void) {
    uint16_t ubrr = 103;   // 16MHz / (16*9600) - 1

    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;

    UCSR0B = (1 << TXEN0);                 // Enable TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop, no parity
}

//send one byte
void uart_send(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0)));  // WAIT until data register empty
    UDR0 = data;                       // Send byte
}

int main(void) {
    uart_init();

    //sending loop
    while (1) {
        uint8_t cipher = encrypt(counter);
        uart_send(cipher);     

        counter++;
        _delay_ms(100);
    }
}
