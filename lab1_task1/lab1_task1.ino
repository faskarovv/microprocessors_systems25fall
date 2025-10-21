#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PD2  // Pin 2
#define LED_PIN PB5     // Onboard LED pin 13

void setup() {
    // Configure button as input with internal pull-up
    DDRD &= ~(1 << BUTTON_PIN);  // Input
    PORTD |= (1 << BUTTON_PIN);  // enabling internal pull-up

    // configuring LED as output
    DDRB |= (1 << LED_PIN);
}

void loop() {
    static uint8_t lastButtonState = 1;  // HIGH initially 
    static uint8_t ledState = 0;         // LED off initially

    // if hifg state is 1 otherwise 0
    uint8_t currentButtonState = (PIND & (1 << BUTTON_PIN)) ? 1 : 0;

    
    if (lastButtonState == 1 && currentButtonState == 0) {
        ledState ^= 1;  // Toggle LED state

        // updating led state
        if (ledState)
            PORTB |= (1 << LED_PIN);   // LED ON
        else
            PORTB &= ~(1 << LED_PIN);  // LED OFF
    }

    lastButtonState = currentButtonState;

    _delay_ms(50);  //debounce so it would ignore walse triggers
}
