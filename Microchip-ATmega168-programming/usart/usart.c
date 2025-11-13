//
// Using USART between ATmega168 and PC
//
// Xiaolou Huang
// 10/26/2019
//

#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>

void USART_init();
void USART_transmit(unsigned char data);
void USART_receive();
void RGBled_7Segment_init();

unsigned char data;

//==========================================
// main
int main(void) {

	// initialization
	USART_init();
	RGBled_7Segment_init();

	while(1) {
		USART_receive();  // receive data
		// data = 0x39;

		USART_transmit(data);  // transmit the data back

		// if it's "R", "G", "B"
		if (data == 0x52 || data == 0x72) {  		// if it's "R"
			PORTD |= (1 << PD5);
		} else if (data == 0x47 || data == 0x67) {  // if it's "G"
			PORTD |= (1 << PD6);
		} else if (data == 0x42 || data == 0x62) {  // if it's "B"
			PORTD |= (1 << PD7);
		}

		// if it's number 0 to 9
		// PC0 = a, PC1 = b, PC2 = c, PC3 = d, PC4 = e, PC5 = f, PB1 = g
		if (data == 0x30) {  		// if it's 0
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC2) \
					| (1 << PC3) | (1 << PC4) | (1 << PC5);
			PORTB = ~(1 << PB1);
		} else if (data == 0x31) {  // if it's 1
			PORTC = (1 << PC1) | (1 << PC2);
		} else if (data == 0x32) {	// if it's 2
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC3) | (1 << PC4);
			PORTB = (1 << PB1);
		} else if (data == 0x33) {  // if it's 3
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);
			PORTB = (1 << PB1);
		} else if (data == 0x34) {  // if it's 4
			PORTC = (1 << PC1) | (1 << PC2) | (1 << PC5);
			PORTB = (1 << PB1);
		} else if (data == 0x35) {	// if it's 5
			PORTC = (1 << PC0) | (1 << PC2) | (1 << PC3) | (1 << PC5);
			PORTB = (1 << PB1);
		} else if (data == 0x36) {	// if it's 6
			PORTC = (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5);
			PORTB = (1 << PB1);
		} else if (data == 0x37) {	// if it's 7
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC2);
		} else if (data == 0x38) {	// if it's 8
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC2) \
					| (1 << PC3) | (1 << PC4) | (1 << PC5);
			PORTB = (1 << PB1);
		} else if (data == 0x39) {	// if it's 9
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC5);
			PORTB = (1 << PB1);
		}

	}

	return 0;
}
//==========================================

// Initialize USART with 8 data bits packet size and 1 stop bit.
void USART_init() {
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);		// enable USART transmitter/receiver
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);  	// set packet size to 8 data bits
	UCSR0C &= ~(1 << USBS0);					// set stop bit amount to 1 stop bit

	// automatically adjust settings for BAUD rate depending on CPU clock speed and selected rate
	#if USE_2X
		UCSR0A |= (1 << U2X0);
	#else
		UCSR0A &= ~(1 << U2X0);
	#endif
}

// Transmit data when the transmit buffer is ready.
void USART_transmit(unsigned char data) {
	// wait if the transmit buffer is not ready
	while (!(UCSR0A & (1 << UDRE0)));

	// if the transmit buffer ready to transmit data
	UDR0 = data;
}

// 
void USART_receive() {
	// wait if the receive buffer has no data
	while(!(UCSR0A & (1 << RXC0)));

	// if there is unread data in the receive buffer
	data = UDR0;
	// return data;
}

// Initialize 7 segment display and RGB LED.
void RGBled_7Segment_init() {
	// 7 segment display
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2) \
			| (1 << PC3) | (1 << PC4) | (1 << PC5);
	DDRB |= (1 << PB1) | (1 << PB2);

	// RGB LED
	DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
}

