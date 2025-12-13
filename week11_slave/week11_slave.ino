//PB3 -> port for the mosi
//PB4 -> port for the miso
//PB5 -> port for the sck
//PB2 -> port for slave select

volatile byte receivedValue = 0;

void spi_slave_init(void) {
    // setting miso as output
    DDRB |= (1 << PB4); //PB4 is the port for mosi
    //rest as input
    DDRB &= ~((1<<PB3) | (1<<PB5) | (1<<PB2));

    // Enable SPI in slave mode
    SPCR = (1 << SPE);
}

ISR(SPI_STC_vect) {       // intterupting when transfer is complete
    receivedValue = SPDR; // read received byte
}

void setup() {
    Serial.begin(9600);
    spi_slave_init(); //initalizing the spi
    SPCR |= (1 << SPIE);   // Enable SPI interrupt
    sei();                 // Enable global interrupts
}

void loop() {
    Serial.println(receivedValue);
    delay(200);
}
