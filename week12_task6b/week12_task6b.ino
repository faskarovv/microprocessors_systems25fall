#include <Wire.h>

void setup() {
  Wire.begin(0x20);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

uint8_t lastByte = 0;

void receiveEvent(int howMany) {
  if (Wire.available())
    lastByte = Wire.read();
}

void requestEvent() {
  Wire.write(lastByte);
}

void loop() {}
