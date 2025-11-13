/*
*
* Configure PWM with LED
* PWM -> LED
*
* Xiaolou Huang (Lor)
* 9/26/2019
*/

#include <avr/io.h>
#include <util/delay.h>


int main(void) {

	DDRB |= (1 << PB1);								// set PB1 as output

	TCCR1A |= (1 << COM1A1);						// clear on compare match

	TCCR1A |= (1 << WGM11) | (1 << WGM10);			// fast PWM, 10-bit
	TCCR1B |= (1 << WGM12);

	TCCR1B |= (1 << CS11);							// prescaler 8

	while (1) {
		OCR1A = 0x0F;								// duty cycle

	}

	return 0;
}