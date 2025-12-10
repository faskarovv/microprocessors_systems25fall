#include <Wire.h>

#define slave_add 0x20

unsigned long startTime;
unsigned long endTime;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  TWSR = 0;     // prescaler = 1

  TWBR = 255;  // ~31 kHz
  // TWBR = 72;   // 100 kHz
  // TWBR = 12;    // 400 kHz
  // ---------------------------
  delay(500);
}

void loop() {
  startTime = micros();

  for (int i = 0; i < 50; i++) {

    // Send a byte
    Wire.beginTransmission(slave_add);
    Wire.write(1);
    Wire.endTransmission();

    // Read reply
    Wire.requestFrom(slave_add, 1);
    while (!Wire.available());
    uint8_t x = Wire.read();
  }

  endTime = micros();
  Serial.print("I2C time for 50 messages = ");
  Serial.print(endTime - startTime);
  Serial.println(" us");

  delay(5000);
}
