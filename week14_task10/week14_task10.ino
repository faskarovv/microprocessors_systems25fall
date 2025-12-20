/*
  TASK 10 – XOR Brute Force with Timing
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

  Serial.println("Starting XOR brute force...");
  Serial.print("Encrypted length: ");
  Serial.println(LEN);

  // ----- START TIMING -----
  unsigned long startTime = millis();

  // Brute force all possible XOR keys (0–255)
  for (uint16_t key = 0; key < 256; key++) {

    bool printable = true;

    for (uint8_t i = 0; i < LEN; i++) {
      uint8_t p = encrypted[i] ^ key;

      // Accept only printable ASCII characters
      if (p < 32 || p > 126) {
        printable = false;
        break;
      }

      decrypted[i] = (char)p;
    }

    if (printable) {
      decrypted[LEN] = '\0';

      Serial.println("\n=== POSSIBLE PLAINTEXT ===");
      Serial.print("Effective XOR key: ");
      Serial.println(key);
      Serial.print("Decrypted text: ");
      Serial.println(decrypted);
    }
  }

  // ----- STOP TIMING -----
  unsigned long elapsed = millis() - startTime;

  Serial.println("\n=========================");
  Serial.print("Brute-force time (ms): ");
  Serial.println(elapsed);
  Serial.println("=========================");
}

void loop() {}
