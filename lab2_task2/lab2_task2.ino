void myTask2() {
  uint8_t result;

  asm volatile (
    "ldi r16, 5\n\t"
    "ldi r17, 8\n\t"
    "add r16, r17\n\t"
    "mov r18, r16\n\t"
    "mov %[res], r18\n\t"
    : [res] "=r" (result)
    :
    : "r16","r17","r18"
  );

  Serial.print("Result in R18: ");
  Serial.println(result);
}

void setup() {
  Serial.begin(9600);
  myTask2(); // call your assembly task
}

void loop() {}
