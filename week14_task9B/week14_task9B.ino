#define KEY 0xA5
#define IV  0x3C

uint8_t prev = IV;

static inline uint8_t rotr8(uint8_t x) {
    return (x >> 3) | (x << 5);
}

uint8_t decrypt(uint8_t c) {
    uint8_t p = rotr8(c) ^ KEY;
    p ^= prev;
    prev = c;
    return p;
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        uint8_t c = Serial.read();
        uint8_t p = decrypt(c);
        Serial.println(p);
    }
}
