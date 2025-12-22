#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

// 7-segment digit patterns (a,b,c,d,e,f,g) 
//10 rows 0 to 9
const uint8_t digits[10][7] = {
    {1,1,1,1,1,1,0}, {0,1,1,0,0,0,0},
    {1,1,0,1,1,0,1}, {1,1,1,1,0,0,1},
    {0,1,1,0,0,1,1}, {1,0,1,1,0,1,1},
    {1,0,1,1,1,1,1}, {1,1,1,0,0,0,0},
    {1,1,1,1,1,1,1}, {1,1,1,1,0,1,1}
};

// display function
void displayDigit(uint8_t num) {
    if(digits[num][0]) PORTB |= (1<<PB1); else PORTB &= ~(1<<PB1); // a
    if(digits[num][1]) PORTB |= (1<<PB0); else PORTB &= ~(1<<PB0); // b
    if(digits[num][2]) PORTD |= (1<<PD7); else PORTD &= ~(1<<PD7); // c
    if(digits[num][3]) PORTD |= (1<<PD6); else PORTD &= ~(1<<PD6); // d
    if(digits[num][4]) PORTD |= (1<<PD5); else PORTD &= ~(1<<PD5); // e
    if(digits[num][5]) PORTD |= (1<<PD3); else PORTD &= ~(1<<PD3); // f
    if(digits[num][6]) PORTD |= (1<<PD4); else PORTD &= ~(1<<PD4); // g
}

// global state
volatile uint8_t counter = 0;
volatile uint8_t paused = 0;
volatile uint8_t button_lock = 0; // software debounce

// Timer1 compare match isr every 0.5 sec
ISR(TIMER1_COMPA_vect)
{
    if (!paused) {
        counter++;
        if (counter > 9) counter = 0;
    }
    button_lock = 0; // unlock button for next press
}

// INT0 ISR button
ISR(INT0_vect)
{
    if (!button_lock) {
        paused ^= 1;   // toggle pause/resume
        button_lock = 1;
    }
}

int main(void)
{
    // 7-segment pins as outputs
    DDRB |= (1<<PB0) | (1<<PB1);
    DDRD |= (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7);

    // Button on PD2 (INT0)
    DDRD &= ~(1<<PD2);   // input
    PORTD |= (1<<PD2);   // pull-up

    // External interrupt INT0 on falling edge
    EICRA = (1<<ISC01);  // falling edge only
    EIMSK |= (1<<INT0);  // enable INT0

 
    TCCR1A = 0;
    TCCR1B = (1<<WGM12); //ctc mode
    OCR1A  = 7812;                 
    TIMSK1 = (1<<OCIE1A);          // enable compare match interrupt
    TCCR1B |= (1<<CS12) | (1<<CS10); // prescaler 1024

    sei(); // enable global interrupts

    while(1)
    {
        displayDigit(counter); // refresh 7-segment
    }
}
