#include <avr/io.h>

volatile uint8_t counter0 = 0;
volatile uint8_t counter2 = 0;

void setup() {
  //making pins 9, 11 and 6 as output
  DDRB |= (1 << PB1) | (1 << PB3);
  DDRD |= (1 << PD6);

  //timer 0 for the pin 6
  TCCR0A = 0;
  TCCR0B = 0;
  TCCR0A =  (1 << WGM01);
  TCCR0B = (1 << CS02) | (1 << CS00); // prescaler 1024 
  OCR0A = 195;
  TIMSK0 |= (1 << OCIE0A);


  //timer 1 for pin 9 
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1A =  (1 << COM1A0); //toggle 
  TCCR1B = (1 << WGM12) | (1 << CS12); //ctc mode and prescaler 256
  OCR1A = 31250; //blink rate

  //timer 2 for pin 11
  TCCR2A = 0;
  TCCR2B = 0;
  TCCR2A = (1 << WGM21);
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20); //1024
  OCR2A = 124;
  TIMSK2 |= (1 << OCIE2A);

  sei();
}

void loop() {

}

ISR(TIMER0_COMPA_vect) {
    counter0++;
    if(counter0 >=2) { // toggle every 4 interrupts ≈ 0.5 Hz
        PORTD ^= (1 << PD6);
        counter0 = 0;
    }
}

ISR(TIMER2_COMPA_vect) {
    counter2++;
    if(counter2 >= 2) { // toggle every 2 interrupts ≈ 2 Hz
        PORTB ^= (1 << PB3);
        counter2 = 0;
    }
}