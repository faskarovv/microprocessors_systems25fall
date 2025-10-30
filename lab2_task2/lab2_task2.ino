void task2() {
  uint8_t R18;

  asm volatile (
    "ldi r16, 5\n\t" // loaded 5 into r16
    "ldi r17, 8\n\t" // loadded 8 into r17
    "add r16, r17\n\t" // add destination register + source register both are operands
    "mov r18, r16\n\t" // moved the value stored in r16 in previous line to r18
    "mov %[cavab], r18\n\t"
    : [cavab] "=r" (R18)  //storing the result to the R18 variable
    :
    : "r16","r17","r18"
  );

  Serial.print("Result in R18 is: "); //just printing
  Serial.println(R18);
}

void setup() {
  Serial.begin(9600);
  task2(); 
}

void loop() {}
