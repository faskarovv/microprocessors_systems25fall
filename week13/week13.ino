#include <Arduino.h>  

#define segment_size 1024 //size of each number segment
#define target_primes 2000 //goal


uint16_t basePrimes[64];
uint8_t baseCount = 0; //how many small primes were found 
uint8_t segment[(segment_size / 8) + 1];  //bit array for one segment

static inline void setComposite(uint16_t idx) {
    segment[idx >> 3] |= (1 << (idx & 7)); //set bit to 1 (marking as composite)
}

static inline uint8_t isComposite(uint16_t idx) {
    return segment[idx >> 3] & (1 << (idx & 7)); //return 1 if the bit is composite
}

void generateBasePrimes(void) {
    uint8_t small[200];
    for (uint16_t i = 2; i < 200; i++) small[i] = 1; //setting all as prime 
    for (uint16_t p = 2; p * p < 200; p++)
        if (small[p])
            for (uint16_t m = p * p; m < 200; m += p) 
                small[m] = 0; //not prime 
    for (uint16_t i = 2; i < 200; i++) //marking pultiples as not prime
        if (small[i])
            basePrimes[baseCount++] = i; //storing primes
}

void setup() {
    Serial.begin(115200); //fast serial for accurate timing 
    while (!Serial); // Wait for serial 

    DDRB |= (1 << PB5); //setting PB5 pin13 LED as output

    generateBasePrimes(); //precomputing small primes

    Serial.println("Starting prime search for 2000 primes...");

    unsigned long startTime = micros();  // Start timing

    uint16_t primeCount = 0; //how many primes found so far 
    uint32_t low = 2, high = low + segment_size; //low is the start of the current segment and high is end 

    while (primeCount < target_primes) {
        // Clear segment bit array
        for (uint16_t i = 0; i < sizeof(segment); i++)
            segment[i] = 0;

        // Mark multiples of base primes in this segment
        for (uint8_t i = 0; i < baseCount; i++) {
            uint16_t p = basePrimes[i];
            //finding first multiple of p
            uint32_t startVal = ((low + p - 1) / p) * p;
            if (startVal < (uint32_t)p * p)
                startVal = (uint32_t)p * p;
            for (uint32_t m = startVal; m < high; m += p) {
                if (m >= low) {
                    setComposite(m - low);
                }
            }
        }

        // Count primes in segment and toggle LED
        for (uint16_t i = 0; i < segment_size && primeCount < target_primes; i++) {
            if (!isComposite(i)) {
                uint32_t number = low + i;
                if (number >= 2) {
                    primeCount++;
                    PINB = (1 << PB5); // Toggle LED
                }
            }
        }

        low += segment_size;
        high += segment_size;
    }

    unsigned long endTime = micros();
    unsigned long elapsedMicros = endTime - startTime;
    double elapsedSeconds = elapsedMicros / 1000000.0;

    Serial.print("Found 2000 primes! Time taken: ");
    Serial.print(elapsedSeconds, 6);
    Serial.println(" seconds");
}

void loop() {}