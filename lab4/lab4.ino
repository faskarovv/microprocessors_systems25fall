#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <Arduino.h>   

#define F_CPU 16000000UL
#define BAUD 9600

#define BUTTON_PIN PD2
#define EEPROM_ADDR 0

// eeprom read
uint8_t eeprom_read(uint16_t addr) {
  EEAR = addr;
  EECR |= (1 << EERE);
  return EEDR;
}

//eeprom write
void eeprom_write(uint16_t addr, uint8_t data) {
  while (EECR & (1 << EEPE)); // wait for previous write
  EEAR = addr;  //address
  EEDR = data; //data that is going to be stored
  EECR |= (1 << EEMPE);
  EECR |= (1 << EEPE); //start to write
}

// ---------------- MAIN ----------------
int main(void) {
  // Init Arduino core (Serial etc.)
  init();

  // Configure button input with pull-up
  DDRD &= ~(1 << BUTTON_PIN);   // Input
  PORTD |= (1 << BUTTON_PIN);   // Enable internal pull-up

  // Init Serial
  Serial.begin(BAUD);

  // Load counter from EEPROM
  uint8_t counter = eeprom_read(EEPROM_ADDR);
  Serial.print("Starting counter from EEPROM: ");
  Serial.println(counter);

  uint8_t lastButtonState = 1;  // HIGH initially (pull-up)

  while (1) {
    uint8_t currentState = (PIND & (1 << BUTTON_PIN)) ? 1 : 0;

    // Detect press: HIGH → LOW
    if (lastButtonState == 1 && currentState == 0) {
      counter++;
      eeprom_write(EEPROM_ADDR, counter);

      Serial.print("Button pressed. Counter = ");
      Serial.println(counter);
    }

    lastButtonState = currentState;
    _delay_ms(30); // simple debounce
  }
}
