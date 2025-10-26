#include <avr/io.h>
#include <util/delay.h>



void setup() {
  // output pins
  DDRD |= (1 << PD6);  // OC0A  /  pin 6   /timer 0 
  DDRB |= (1 << PB1);  // OC1A  / pin 9  / timer 1
  DDRB |= (1 << PB3);  // OC2A  /  pin 11 / timer 2

  DDRB &= ~(1 << PB0); // input
  PORTB |= (1 << PB0); // enable internal pull-up

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

// tracking button presses
uint8_t press_count = 0;

//to detect button presses correctly
uint8_t readButton() {
  static uint8_t prev = 1;
  uint8_t current = (PINB & (1 << PB0)) ? 1 : 0;
  if (prev == 1 && current == 0) { // falling edge (button press)
    _delay_ms(20); // debounce delay
    if ((PINB & (1 << PB0)) == 0) {
      prev = current;
      return 1;
    }
  }
  prev = current;
  return 0;
}

void loop() {
  if (readButton()) {
    press_count++;
    if (press_count > 12) press_count = 1;  // wrap after 12 presses

    uint8_t level = ((press_count - 1) % 4) + 1;

    uint8_t brightness = (level * 64) - 1; // 63, 127, 191, 255

    if (press_count <= 4) {
      OCR0A = brightness;  // LED 1 active
      OCR1A = 0;
      OCR2A = 0;
    } else if (press_count <= 8) {
      OCR0A = 0;
      OCR1A = brightness;  // LED 2 active
      OCR2A = 0;
    } else {
      OCR0A = 0;
      OCR1A = 0;
      OCR2A = brightness;  // LED 3 active
    }
  }
}
