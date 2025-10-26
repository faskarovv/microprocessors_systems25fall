#include <avr/io.h>
#include <util/delay.h>

void setup() {
  // Set LED pins as outputs
  DDRD |= (1 << PD6);  // OC0A  / pin 6 / Timer0
  DDRB |= (1 << PB1);  // OC1A / pin 9 /   Timer1
  DDRB |= (1 << PB3);  // OC2A  / pin 11 / Timer2

  // timer 0
  TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
  TCCR0B = (1 << CS01); // prescaler = 8

  // timer 1
  TCCR1A = (1 << WGM10) | (1 << COM1A1);
  TCCR1B = (1 << WGM12) | (1 << CS11); // prescaler = 8

  // timer 2
  TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2A1);
  TCCR2B = (1 << CS21); // prescaler = 8
}

void loop() {
  for (uint8_t i = 0; i <= 255; i++) {
    OCR0A = (uint8_t)(i * 0.3); // up to 30%
    OCR1A = (uint8_t)(i * 0.5); // up to 50%
    OCR2A = (uint8_t)(i * 0.8); // up to 80%
    _delay_ms(10);
  }

  _delay_ms(1000);
}
