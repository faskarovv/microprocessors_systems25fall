#include <avr/io.h>
#include <avr/interrupt.h>

void setup() {
  // Set pins 9, 10, 11 as outputs
  DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3);

  // Timer1 for pins 9 & 10
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);          // CTC mode
  OCR1A = 15624;                    // pin 9 toggle rate
  OCR1B = 7812;                     // pin 10 toggle rate
  TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); // enable compare match interrupts
  // TCCR1B |= (1 << CS12) | (1 << CS10);    // prescaler 1024

  // Timer2 for pin 11
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  TCCR2A |= (1 << WGM21);           // CTC mode
  OCR2A = 249;                       // pin 11 toggle rate
  TIMSK2 |= (1 << OCIE2A);           // enable compare match interrupt
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // prescaler 1024

  sei(); // Enable global interrupts
}

void loop() {
  // Nothing needed here
}

// Timer1 Compare Match A → toggle pin 9
ISR(TIMER1_COMPA_vect) {
  PORTB ^= (1 << PB1);
}

// Timer1 Compare Match B → toggle pin 10
ISR(TIMER1_COMPB_vect) {
  PORTB ^= (1 << PB2);
}

// Timer2 Compare Match A → toggle pin 11
ISR(TIMER2_COMPA_vect) {
  PORTB ^= (1 << PB3);
}
