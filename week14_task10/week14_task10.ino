#include <Arduino.h>

const uint8_t encrypted[] = {87, 26, 72, 13, 67, 95, 89, 23, 72, 22, 73, 11, 87, 30, 73}; //encrypted data as constant array
const uint8_t len = sizeof(encrypted); //array length

void setup() {
  Serial.begin(9600);
  while (!Serial) {;} //waits for serial monitor to connect

  Serial.println("Searching for printable messages \n");

  unsigned long startTime = millis(); //starting time

  //brute forcing all the possible keys
  for (uint16_t key_even = 0; key_even < 256; key_even++) { //0,2,4,6...
    for (uint16_t key_odd = 0; key_odd < 256; key_odd++) { //1,3,5,7...

      //creating a buffer to store the decrypted message
      char msg[16] = {0};
      bool valid = true; //for tracking whether whole message is printable 

      for (uint8_t i = 0; i < len; i++) { //loop through each byte of ciphertext
        uint8_t key = (i % 2 == 0) ? key_even : key_odd; //choose key based on position
        uint8_t p = encrypted[i] ^ key; //xor
        if (p < 32 || p > 126) { //checking if printable ascii
          valid = false; 
          break; //breaking early if not
        }
        msg[i] = p; //storing decrypted byte
      }

      if (valid && strchr(msg, ' ') != nullptr) {  // Only print if has space as said in hint
        Serial.print("Keys (even: ");
        Serial.print(key_even);
        Serial.print(", odd: ");
        Serial.print(key_odd);
        Serial.print("): ");
        Serial.println(msg);
        Serial.println();
      }
    }
  }
  unsigned long endTime = millis(); //recording the end time
  unsigned long elapsedTime = endTime - startTime; //difference start and end time
  Serial.print("Total time taken: ");
  Serial.print(elapsedTime);
  Serial.println();

  Serial.println("Done.");
}

void loop() {}