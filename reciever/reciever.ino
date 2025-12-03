#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

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
    PORTD &= ~((1<<PD2)|(1<<PD3)|(1<<PD4));  // OFF

    if (v == 1) PORTD |= (1<<PD2);
    if (v == 2) PORTD |= (1<<PD3);
    if (v == 3) PORTD |= (1<<PD4);
}

int main() {
    UART_init();
    DDRD |= (1<<PD2) | (1<<PD3) | (1<<PD4);

    uint16_t addr = 0;  // FIX: bigger address space

    while (1) {
        uint8_t rx = UART_receive();

        // FIX: ignore CR/LF or garbage
        if (rx < '1' || rx > '4') continue;

        // STORE VALUES 1, 2, 3
        if (rx == '1' || rx == '2' || rx == '3') {
            uint8_t val = rx - '0';

            // prevent overflow
            if (addr < 1024) {
                eeprom_update_byte((uint8_t*)addr, val);  // faster write
                addr++;
            }
        }

        // PLAYBACK
        else if (rx == '4') {
            for (uint16_t i = 0; i < addr; i++) {
                uint8_t v = eeprom_read_byte((uint8_t*)i);
                showLED(v);
                _delay_ms(500);
            }

            PORTD &= ~((1<<PD2)|(1<<PD3)|(1<<PD4));
            addr = 0;   // reset for new sequence
        }
    }
}