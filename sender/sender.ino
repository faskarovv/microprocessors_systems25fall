//week 10 task3 sender
uint8_t uart_read() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void uart_write(uint8_t data) {
    After a full byte is received, the hardware stores it in the UDR0 register and sets the RXC0 flag to indicate that new data is available. The software waits for this flag and reads UDR0 only when RXC0 is set, which clears the flag and allows the next byte to be received. For transmission, the hardware sets the UDRE0 flag when the data register is empty and ready for new data. The software waits for this flag and then writes a byte to UDR0. The hardware then automatically adds the start and stop bits and sends the data bit by bit on the TX line. When the register becomes empty again, UDRE0 is set, indicating that another byte can be transmitted.

    UDR0 = data;
}

void setup() {

    UBRR0H = 0;
    UBRR0L = 103;                   // 9600 baud @ 16 MHz
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);  // enable RX and TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8N1
}

void loop() {
    uint8_t c = uart_read(); 
    if (c == '1' || c == '2' || c == '3' || c == '4') {
        uart_write(c);       // send to Arduino B
    }
}
