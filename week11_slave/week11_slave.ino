
#define DDR_SPI DDRB
#define DD_MOSI DDB3
#define DD_MISO DDB4
#define DD_SCK  DDB5
#define DD_SS   DDB2

volatile byte receivedValue = 0;

void SPI_SlaveInit(void) {
    // Set MISO as output, rest input
    DDR_SPI |= (1 << DD_MISO);
    DDR_SPI &= ~((1<<DD_MOSI) | (1<<DD_SCK) | (1<<DD_SS));

    // Enable SPI in slave mode
    SPCR = (1 << SPE);
}

ISR(SPI_STC_vect) {       // Interrupt when transfer complete
    receivedValue = SPDR; // Read received byte
}

void setup() {
    Serial.begin(9600);
    SPI_SlaveInit();
    SPCR |= (1 << SPIE);   // Enable SPI interrupt
    sei();                 // Enable global interrupts
}

void loop() {
    Serial.println(receivedValue);
    delay(200);
}
