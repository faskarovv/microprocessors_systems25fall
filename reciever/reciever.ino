//week10 task3 reciever
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

uint8_t UART_receive() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

//simple if else to light the leds on
void ledOn(uint8_t v) {
    PORTD &= ~((1<<PD2)|(1<<PD3)|(1<<PD4));

    if (v == 1) PORTD |= (1<<PD2);
    if (v == 2) PORTD |= (1<<PD3);
    if (v == 3) PORTD |= (1<<PD4);
}

uint8_t read_eeprom_byte(uint8_t addr){
    while(EECR & (1 << EEPE));
    EEAR = addr; //set the address to read
    EECR |= (1<<EERE); //initalize read 
    return EEDR;
}
void eeprom_write(uint8_t addr, uint8_t data){
    while(EECR & (1 << EEPE));

    EEAR = addr; //addres to write to
    EEDR = data; //data that is gonna be written
    uint8_t sreg = SREG;
    cli();

    EECR |= (1 << EEMPE); 
    EECR |= (1 << EEPE); 

    SREG = sreg;
}

int main() {
    UBRR0H = 0;
    UBRR0L = 103; //baud rate 9600
    UCSR0B = (1 << RXEN0); //enable reciever
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //8 bit data frame
 
    DDRD |= (1<<PD2)|(1<<PD3)|(1<<PD4); //setting as output for leds

    uint16_t addr = 0;

    while (1) {
        uint8_t rx = UART_receive(); 

        if (rx == '1' || rx == '2' || rx == '3') {
            if (addr < 1024) {
                eeprom_write((uint8_t*)addr, rx - '0'); //writing to eeprom
                addr++;
            }
        }
        else if (rx == '4') {
            for (uint16_t i = 0; i < addr; i++) {
                uint8_t v = read_eeprom_byte((uint8_t*)i); //when pressed 4 do the playback
                ledOn(v);
                _delay_ms(500);
            }
            PORTD &= ~((1<<PD2)|(1<<PD3)|(1<<PD4));
            addr = 0;
        }
    }
}
