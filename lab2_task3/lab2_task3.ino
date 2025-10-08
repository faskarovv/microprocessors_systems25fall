void setup() {
  Serial.begin(9600);

  uint8_t R18;
  uint8_t SREG_value;

  asm volatile (
    "ldi r16, 50      \n\t"  // Load X = 50
    "ldi r17, 200     \n\t"  // Load Y = 200
    "sub r16, r17     \n\t"  // R16 = R16 - R17
    "mov r18, r16     \n\t"  // Store result in R18
    "in r19, __SREG__ \n\t"  // Read SREG into R19
    "mov %[sreg], r19 \n\t"  // Move SREG into C variable
    : [sreg] "=r" (SREG_value), [res] "=r" (R18)
    :
    : "r16","r17","r18","r19"
  );

  Serial.print("R18 (Result): ");
  Serial.println(R18);              
  Serial.print("Zero flag (Z): ");
  Serial.println((SREG_value >> 1) & 1);
  Serial.print("Carry flag (C): ");
  Serial.println(SREG_value & 1);
}

void loop() {}
