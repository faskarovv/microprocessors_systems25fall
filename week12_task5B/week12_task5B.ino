#include <avr/io.h>
#include <util/delay.h>

#define my_add 0x20 //slave adress in week12_task5A
#define led_on 0x01
#define led_off 0x00


uint8_t twi_wait() {
    while (!(TWCR & (1<<TWINT)));
    return (TWSR & 0xF8);
}

int main(){
    PORTC |= (1 << PC4) | (1 << PC5);

    DDRB |= (1 << PB5); //set pin 13 as an output
    DDRD &= ~(1 << PD2); //set pin 2 as input for button
    PORTD |= (1 << PD2); //enable internal pull up resistor for button 

    TWAR = (my_add << 1); //setting slaves address
    TWCR = (1<<TWEA)|(1<<TWEN)|(1<<TWINT); //enable ack

    while(1){
      uint8_t status = twi_wait();

      
        if (status == 0x60) {              // SLA+W received
            TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
        }
        else if (status == 0x80) {         // data received
            uint8_t msg = TWDR;

            if (msg == led_on)  PORTB |= (1<<PB5);
            else                PORTB &= ~(1<<PB5);

            TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
        }

      
        else if (status == 0xA8) {         // SLA+R received
            uint8_t btn = !(PIND & (1<<PD2));  // active low
            TWDR = btn ? led_on : led_off;     // load data to send
            TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
        }

        
        else {
            TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
        }

    }
}