#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <Arduino.h>   

#define F_CPU 16000000UL

#define BUTTON_PIN PD2        // pin 2 for button input
#define EEPROM_ADDR 0         //EEPROM adress

// EEPROM read function
uint8_t eeprom_read(uint16_t addr) {
  EEAR = addr;
  EECR |= (1 << EERE); //EERE triggers a read operation
  return EEDR;
}

//EEPROM write function 
void eeprom_write(uint16_t addr, uint8_t data) {
  while (EECR & (1 << EEPE));   // wait for previous write
  EEAR = addr;                  //address
  EEDR = data;                  //data that is going to be stored
  EECR |= (1 << EEMPE);         //master program enable (must be set before EEPE)
  EECR |= (1 << EEPE);          //start the write process
}


int main(void) {
  init();

  // Configure button input with pull-up
  DDRD &= ~(1 << BUTTON_PIN);   // Input pin 2
  PORTD |= (1 << BUTTON_PIN);   //  internal pull-up

  Serial.begin(9600);

  // Load counter from EEPROM
  uint8_t counter = eeprom_read(EEPROM_ADDR);
  Serial.print("counter at the location 0  EEPROM: ");
  Serial.println(counter);

  uint8_t lastButtonState = 1;  // HIGH initially (pull-up) when pressed set to 0

  while (1) {
    uint8_t currentState = (PIND & (1 << BUTTON_PIN)) ? 1 : 0; //read the button input

    
    // Detect press: HIGH → LOW
    if (lastButtonState == 1 && currentState == 0) {
      counter++;
      eeprom_write(EEPROM_ADDR, counter);

      Serial.print("Button pressed. Counter = ");
      Serial.println(counter);
    }

    lastButtonState = currentState;
    _delay_ms(30); //debounce so input wont be wrong (preventing false triggers)
  }
}
