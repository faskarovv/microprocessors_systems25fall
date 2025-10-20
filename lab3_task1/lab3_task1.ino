
void setup() {
    DDRB |= (1 << PB5);

}

void loop() {
  // method1();
  method4();
}

void method1(){
  //directly assigning 

  PORTB = 0b00100000;
  delay(100);

  PORTB = 0b00000000;
  delay(100);
}

void method2(){
  PORTB |= (1 << PB5);
  delay(500);

  PORTB &= ~(1<<PB5);
  delay(500);
}


void method3(){
  PORTB ^= (1 << PB5);
  delay(500);

  PORTB ^= (1 << PB5);
  delay(500);
}

void method4(){

  PORTB = (1 << PB5);
  delay(500);

  PORTB = (0 << PB5);
  delay(500);
}
