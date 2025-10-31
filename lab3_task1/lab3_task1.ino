
void setup() {
    DDRB |= (1 << PB5);

}

void loop() {
  // method1();
  // method2();
  // method3();  
  method4();
}

// in this method each bit is assigned zero except one
void method1(){
  //directly assigning 

  PORTB = 0b00100000;
  delay(100);

  PORTB = 0b00000000;
  delay(100);
}

// Safer when multiple pins in the same port are used
void method2(){
  PORTB |= (1 << PB5);
  delay(500);

  PORTB &= ~(1<<PB5);
  delay(500);
}

// XOR flips the bit state each time it's executed
void method3(){
  PORTB ^= (1 << PB5);
  delay(500);

  PORTB ^= (1 << PB5);
  delay(500);
}
// Directly sets or clears the bit by writing a shifted 1 or 0
void method4(){

  PORTB = (1 << PB5);
  delay(500);

  PORTB = (0 << PB5);
  delay(500);
}
