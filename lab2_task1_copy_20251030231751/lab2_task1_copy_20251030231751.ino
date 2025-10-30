#include <avr/io.h>
#include <util/delay.h>

#define button_pin PD2  // Pin 2
#define led_pin PB5     // Onboard LED pin 13

void setup() {
    // Configure button as input with internal pull-up
    DDRD &= ~(1 << button_pin);  // Input
    PORTD |= (1 << button_pin);  // enabling internal pull-up

    // configuring LED as output
    DDRB |= (1 << led_pin); // setting pin 13
}

void loop() {
    static uint8_t lastButtonState = 1;  // HIGH initially 
    static uint8_t ledState = 0;         // LED off initially

    // if hifg state is 1 otherwise 0
    uint8_t currentButtonState = (PIND & (1 << button_pin)) ? 1 : 0;

    // checking if button has been pressed
    if (lastButtonState == 1 && currentButtonState == 0) {
        ledState ^= 1;  // Toggle LED state

        // updating led state
        if (ledState)
            PORTB |= (1 << led_pin);   // LED ON
        else
            PORTB &= ~(1 << led_pin);  // LED OFF
    }

    lastButtonState = currentButtonState;

    _delay_ms(50);  //debounce so it would ignore walse triggers
}
