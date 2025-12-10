// MASTER CODE — sends: 85 → 170 → 255 → repeat

#define DDR_SPI DDRB
#define DD_MOSI DDB3
#define DD_MISO DDB4
#define DD_SCK  DDB5
#define DD_SS   DDB2

void SPI_MasterInit(void) {
    // Set MOSI, SCK, SS as outputs
    DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);

    // SS must be high initially (inactive)
    PORTB |= (1 << DD_SS);

    // Enable SPI, Master, clock = f/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_MasterTransmit(unsigned char data) {
    PORTB &= ~(1 << DD_SS); // SS LOW → enable slave

    SPDR = data;            // Start transmission
    while (!(SPSR & (1 << SPIF))); // Wait for complete

    PORTB |= (1 << DD_SS); // SS HIGH → release slave
}

void setup() {
    SPI_MasterInit();
}

void loop() {
    SPI_MasterTransmit(85);
    delay(1000);

    SPI_MasterTransmit(170);
    delay(1000);

    SPI_MasterTransmit(255);
    delay(1000);
}
