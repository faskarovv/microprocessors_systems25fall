#include <avr/io.h>
#include <util/delay.h>

void setup() {
  // Set LED pins as outputs
  DDRD |= (1 << PD6);  // OC0A - Timer0
  DDRB |= (1 << PB1);  // OC1A - Timer1
  DDRB |= (1 << PB3);  // OC2A - Timer2

  // ----- TIMER0: Fast PWM (OC0A on D6) -----
  TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
  TCCR0B = (1 << CS01); // prescaler = 8

  // ----- TIMER1: Fast PWM 8-bit (OC1A on D9) -----
  TCCR1A = (1 << WGM10) | (1 << COM1A1);
  TCCR1B = (1 << WGM12) | (1 << CS11); // prescaler = 8

  // ----- TIMER2: Fast PWM (OC2A on D11) -----
  TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2A1);
  TCCR2B = (1 << CS21); // prescaler = 8
}

void loop() {
  // Fade each LED from 0 up to its target brightness
  for (uint8_t i = 0; i <= 255; i++) {
    OCR0A = (uint8_t)(i * 0.3); // up to 30%
    OCR1A = (uint8_t)(i * 0.5); // up to 50%
    OCR2A = (uint8_t)(i * 0.8); // up to 80%
    _delay_ms(10);
  }

  // Hold steady for a while
  _delay_ms(1000);
}
