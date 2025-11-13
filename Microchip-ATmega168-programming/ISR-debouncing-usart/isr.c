//
// Use USART serial communication between ATmega168 and PC
// Use external interrupt INT0 and INT1 on ATmega168
// Use Interrupt Service Routine (ISR)
//
// Connecting ATmega168 with PC use USB serial adaptor (for Mac)
//     1. In terminal, type: ls /dev/*usbserial*
//     2. Find: cu.usbserial-XXXX
//     3. connect: screen [adapterName] 9600
//
// Xiaolou Huang
// 11/9/2019
//

#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>

void USART_init();
void USART_transmit(unsigned char data);
unsigned char USART_receive();
void RGBled_7Segment_init();
void Interrupt_init();
void Timer_init();

unsigned char data;

// main
int main(void) {

	// initialization
	USART_init();
	RGBled_7Segment_init();
	Interrupt_init();
	Timer_init();

	while(1) {
		data = USART_receive();  // receive data

		// if it's "R,r", "G, g", "B, b", light up that color on RGB LED
		if (data == 0x52 || data == 0x72) {  		// if it's "R" or "r"
			PORTD |= (1 << PD5);
		} else if (data == 0x47 || data == 0x67) {  // if it's "G" or "g"
			PORTD |= (1 << PD6);
		} else if (data == 0x42 || data == 0x62) {  // if it's "B" or "b"
			PORTD |= (1 << PD7);
		}

		// if it's number 0 to 9, show that number on 7-segment display
		// PC0 = a, PC1 = b, PC2 = c, PC3 = d, PC4 = e, PC5 = f, PB1 = g
		if (data == 0x30) {  		// if it's 0, show 1 on 7-segment display
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC2) \
					| (1 << PC3) | (1 << PC4) | (1 << PC5);
			PORTB = ~(1 << PB1);
		} else if (data == 0x31) {  // if it's 1, show 1 on 7-segment display
			PORTC = (1 << PC1) | (1 << PC2);
			PORTB = ~(1 << PB1);
		} else if (data == 0x32) {	// if it's 2, show 2 on 7-segment display
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC3) | (1 << PC4);
			PORTB = (1 << PB1);
		} else if (data == 0x33) {  // if it's 3, show 3 on 7-segment display
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);
			PORTB = (1 << PB1);
		} else if (data == 0x34) {  // if it's 4, show 4 on 7-segment display
			PORTC = (1 << PC1) | (1 << PC2) | (1 << PC5);
			PORTB = (1 << PB1);
		} else if (data == 0x35) {	// if it's 5, show 5 on 7-segment display
			PORTC = (1 << PC0) | (1 << PC2) | (1 << PC3) | (1 << PC5);
			PORTB = (1 << PB1);
		} else if (data == 0x36) {	// if it's 6, show 6 on 7-segment display
			PORTC = (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5);
			PORTB = (1 << PB1);
		} else if (data == 0x37) {	// if it's 7, show 7 on 7-segment display
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC2);
			PORTB = ~(1 << PB1);
		} else if (data == 0x38) {	// if it's 8, show 8 on 7-segment display
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC2) \
					| (1 << PC3) | (1 << PC4) | (1 << PC5);
			PORTB = (1 << PB1);
		} else if (data == 0x39) {	// if it's 9, show 9 on 7-segment display
			PORTC = (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC5);
			PORTB = (1 << PB1);
		}

	}

	return 0;
}
//==========================================
// When INT0 is rising edge, transmit the character back to PC
ISR(INT0_vect) {
	if (TCNT1 > 1000) {  // for debouncing. If count is greater than 1000, transmit data
		USART_transmit(data);  // transmit the data back
		TCNT1 = 0x00;
	}
}

// Timer record time elapsed for button debounce purpose
// OCRn =  [ (clock_speed / Prescaler_value) * Desired_time_in_Seconds ] - 1
void Timer_init() {
	// set prescaler to /1024 to start the timer
	// In this case, count of 976 in TCNT1 will be 1s
	TCCR1B |= (1 << CS12) | (1 << CS10);  // set prescaler to 1024 to start the timer
}

// Initialize external interrupt on ATmega168 (INT0, INT1)
void Interrupt_init() {
	EICRA |= (1 << ISC01) | (1 << ISC00);  // use rising edge of INT0 generates interrupts
	EIMSK |= (1 << INT0);  // activate INT0 external interrupts
	sei();
}

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

// Initialize 7 segment display and RGB LED.
void RGBled_7Segment_init() {
	// 7 segment display
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2) \
			| (1 << PC3) | (1 << PC4) | (1 << PC5);
	DDRB |= (1 << PB1) | (1 << PB2);

	// RGB LED
	DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
}

// Transmit data when the transmit buffer is ready.
void USART_transmit(unsigned char data) {
	// wait if the transmit buffer is not ready
	while (!(UCSR0A & (1 << UDRE0)));

	// if the transmit buffer ready to transmit data
	UDR0 = data;
}

// Receive data when the receive buffer has data
unsigned char USART_receive() {
	// wait if the receive buffer has no data
	while(!(UCSR0A & (1 << RXC0)));

	// if there is unread data in the receive buffer
	return UDR0;
}



