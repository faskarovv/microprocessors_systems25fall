#include <Wire.h>

void setup() {
  Wire.begin(0x20); //setting the slaves adress
  Wire.onReceive(receiveEvent); //this function is gonna be triggered when reciveing data
  Wire.onRequest(requestEvent); // when master requests a data 
}

uint8_t lastByte = 0; //storing the last recived data

void receiveEvent(int howMany) {
  if (Wire.available())
    lastByte = Wire.read(); //reading and saving 
}

void requestEvent() {
  Wire.write(lastByte); //sending back the last recived data 
}

void loop() {}
