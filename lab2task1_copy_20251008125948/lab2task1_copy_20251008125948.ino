#include <avr/io.h>
#include <util/delay.h>

void setup() {
    DDRB |= (1 << DDB5);   // Pin 13 as OUTPUT
    DDRD &= ~(1 << DDD2);  // Pin 2 as INPUT
    PORTD &= ~(1 << PORTD2); // Disable internal pull-up
}

void loop() {
    static uint8_t prevState = 0;  // Previous button state
    static uint8_t ledState = 0;   // LED state

    uint8_t currentState = (PIND & (1 << PIND2)) ? 1 : 0;

    // Detect rising edge: button released (0) -> pressed (1)
    if (prevState == 0 && currentState == 1) {
        ledState ^= 1;  // Toggle LED

        if (ledState) {
            PORTB |= (1 << PORTB5);   // Turn LED ON
        } else {
            PORTB &= ~(1 << PORTB5);  // Turn LED OFF
        }

        _delay_ms(50);  // Simple debounce
    }

    prevState = currentState;
}
