/*
*
* Configure PWM and ADC
* Potentiometer -> ADC -> PWM -> LED
*
* Xiaolou Huang (Lor)
* 9/26/2019
*/

#include <avr/io.h>
#include <util/delay.h>

static inline void initADC0(void) {
	ADMUX |= (1 << REFS0); 						// reference voltage on AVCC
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);	  	// ADC clock prescaler 8
	ADCSRA |= (1 << ADEN); 					   	// enables the ADC
}

static inline void initPWM(void) {
	TCCR1A |= (1 << COM1A1);					// clear on compare match
	TCCR1A |= (1 << WGM11) | (1 << WGM10);		// fast PWM, 10-bit
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS11);						// prescaler 8
}

int main(void) {
	uint16_t potentiometerValue;
	DDRB |= (1 << PB1);						   	// Enable output on PB1

	initADC0();
	initPWM();

	while(1) {
		ADCSRA |= (1 << ADSC);				   	// start ADC conversion
		loop_until_bit_is_clear(ADCSRA, ADSC); 	// wait until ADC conversion is done
		potentiometerValue = ADC;			   	// read ADC value in

		OCR1A = potentiometerValue;				// set duty cycle
	}

	return 0;
}