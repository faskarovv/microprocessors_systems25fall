#include <avr/io.h>
#include <util/delay.h>

#define KEY 0xA5 //secret key
#define IV  0x3C //initilization vector

uint8_t counter = 0; //8 bit int (255)
uint8_t prev = IV;  //for the first ciphertext 

static inline uint8_t rotl8(uint8_t x) {
    return (x << 3) | (x >> 5); //rotating to the left
}

uint8_t encrypt(uint8_t p) {
    p ^= prev;                 // CBC chaining
    uint8_t c = rotl8(p ^ KEY); //encrypt xor then rotate
    prev = c; //new ciphertext is the next previous val
    return c;
}

void uart_init(void) {
    uint16_t ubrr = 103;
    UBRR0H = ubrr >> 8; //baud rate 9600
    UBRR0L = ubrr;
    UCSR0B = (1 << TXEN0); //enabling the transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //8 bit format data frame
}

void uart_send(uint8_t d) {
    while (!(UCSR0A & (1 << UDRE0))); //wating for the status flag to write when it is empty
    UDR0 = d; //writing to the data register
}

int main(void) {
    uart_init();

    while (1) {
        uart_send(encrypt(counter));
        counter++; //counts 0-255 and again
        _delay_ms(100); //emulating 0.1 sec each time it sends (arduino c level was acceptable so i did not use timers)
    }
}
