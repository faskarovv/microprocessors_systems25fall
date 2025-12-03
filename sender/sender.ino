// Transmitter - Arduino A

void uart_init() {
    UBRR0H = 0;
    UBRR0L = 103;                   // 9600 baud @ 16 MHz
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);  // enable RX and TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8N1
}

uint8_t uart_read() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void uart_write(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void setup() {
    uart_init();
}

void loop() {
    uint8_t c = uart_read(); // read from PC via USB (type 1,2,3,4)
    if (c == '1' || c == '2' || c == '3' || c == '4') {
        uart_write(c);       // send to Arduino B
    }
}
