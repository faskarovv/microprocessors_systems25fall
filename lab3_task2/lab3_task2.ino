void setup() {

  Serial.begin(9600); //needed to see the output on serial monitor

  uint8_t sum;

  asm volatile(
    "ldi r16, 1       \n\t"  // counter = 1
    "ldi r17, 0       \n\t"  // sum = 0
    "ldi r18, 11      \n\t"  // limit = 11



    "loop_asm:        \n\t"
    "add r17, r16     \n\t"  // sum += counter
    "inc r16          \n\t"  // counter++
    "cp r16, r18      \n\t"  // compare counter to limit
    "brne loop_asm    \n\t"  // if not equal, loop

    "mov %0, r17      \n\t"  // store sum in variable 'sum'
    : "=r" (sum)             // output
    :                        // no inputs
    : "r16","r17","r18"  // clobbered registers
  );

  Serial.print("Sum = ");
  Serial.println(sum);
}

void loop() {
}
