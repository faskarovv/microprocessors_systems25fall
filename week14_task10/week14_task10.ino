/*
  TASK 10 – XOR Brute Force (Corrected)
  DR ALEXZ FARRALL
*/

#include <Arduino.h>

const uint8_t encrypted[] = {
  87, 26, 72, 13, 67, 95, 89, 23, 72, 22, 73, 11, 87, 30, 73
};

#define LEN (sizeof(encrypted))

char decrypted[LEN + 1];

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Starting brute-force attack...");
  Serial.print("Encrypted Length: ");
  Serial.println(LEN);

  unsigned long startTime = millis();

  // Brute force all possible single-byte keys (0 to 255)
  for (uint16_t key = 0; key < 256; key++) {

    bool valid = true;
    bool hasSpace = false;
    
    // Decrypt the message with the current key
    for (uint8_t i = 0; i < LEN; i++) {
      uint8_t p = encrypted[i] ^ key;

      // Check for common printable ASCII characters
      // Range 32 (' ') to 126 ('~')
      if (p >= 32 && p <= 126) {
          if (p == ' ') {
            hasSpace = true;
          }
      } 
      // Allow newline/carriage return characters as well, just in case
      else if (p == '\r' || p == '\n') {
          // Newline characters are valid but don't count as 'hasSpace'
      }
      else {
        // If it's outside the common printable range, discard the key
        valid = false;
        break;
      }

      decrypted[i] = (char)p;
    }

    // Only print if the decryption is valid and contains at least one space
    // (A space is a very strong indicator of real English text)
    if (valid && hasSpace) {
      decrypted[LEN] = '\0'; // Null-terminate the string

      unsigned long elapsed = millis() - startTime;

      Serial.println("\n=== PLAINTEXT FOUND ===");
      Serial.print("Effective XOR Key: ");
      Serial.println(key);
      Serial.print("Plaintext: ");
      Serial.println(decrypted);
      Serial.print("Time taken (ms): ");
      Serial.println(elapsed);

      // In a real attack, you might want to print ALL valid keys, but for this task,
      // we assume the first one found is the correct one.
      while (1); // stop
    }
  }

  Serial.println("\nNo valid plaintext found within printable ASCII range.");
}

void loop() {}