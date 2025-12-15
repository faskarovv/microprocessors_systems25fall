// master sends 85 -> 170 -> 255 -> repeats
//PB3 -> port for the mosi
//PB4 -> port for the miso
//PB5 -> port for the sck
//PB2 -> port for slave select

void SPI_MasterInit(void) {
    // setting mosi sck and ss as outputs
    DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2);

    // ss must be high inactive
    PORTB |= (1 << PB2);

    // enabling spi, master, clock = f/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_MasterTransmit(unsigned char data) {
    PORTB &= ~(1 << PB2); //enabling slave setting low 

    SPDR = data;            // start transmission
    while (!(SPSR & (1 << SPIF))); // wait until complete

    PORTB |= (1 << PB2); // release slave
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
