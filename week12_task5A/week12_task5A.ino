#include <avr/io.h>
#include <util/delay.h>

#define slave_adress 0x20
#define led_on  0x01
#define led_off  0x00


void twi_start() {
    TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT); //twsta register used to start
    while (!(TWCR & (1<<TWINT)));
}

void twi_stop(){
  TWCR = (1<<TWSTO) | (1<<TWEN) | (1<<TWINT); //twisto register used to stop
}

void twi_write(uint8_t data){
  TWDR = data;
  TWCR = (1<<TWEN) | (1<<TWINT);
  while (!(TWCR & (1<<TWINT)));
}

uint8_t twi_read_nack() {
    TWCR = (1<<TWEN)|(1<<TWINT);
    while (!(TWCR & (1<<TWINT)));
    return TWDR;
}

int main(){

  PORTC |= (1 << PC4) | (1 << PC5);

  DDRB |= (1 << PB5); //set pin 13 as an output
  DDRD &= ~(1 << PD2); //set pin 2 as input for button
  PORTD |= (1 << PD2); //enable internal pull up resistor for button 

  TWSR &= ~(1 << TWPS1) | (1 << TWPS0); //set prescaler to 1 
  TWBR = 32; //setting scl frequency to 200khz
  TWCR = (1 << TWEN); //enables twi(i2c)

  while(1){
    uint8_t buttonState = !(PIND & (1 << PD2)); //always 0 when pressed 1

    //sending button state
    twi_start();
    twi_write((slave_adress << 1) | 0);

    if(buttonState) twi_write(led_on);
    else twi_write(led_off);

    twi_stop();
    _delay_ms(10);

    //reading button state
    twi_start();
    twi_write((slave_adress << 1) | 1);
    uint8_t rx = twi_read_nack();
    twi_stop();

    //led based on slave response
    if (rx == led_on) PORTB |= (1<<PB5);
    else              PORTB &= ~(1<<PB5);

    _delay_ms(50);
  }


}
