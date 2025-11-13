/*
*
* Configure ADC with potentiometer
* Potentiometer -> ADC -> LED
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

int main(void) {
	uint16_t PotentiometerValue;
	uint16_t threshold_level;
	threshold_level = 0b10000000;
	DDRB |= (1 << PB0);						   	// Enable output on PB0

	initADC0();

	while(1) {
		ADCSRA |= (1 << ADSC);				   	// start ADC conversion
		loop_until_bit_is_clear(ADCSRA, ADSC); 	// wait until ADC conversion is done
		PotentiometerValue = ADC;			   	//read ADC value in

		if (PotentiometerValue > threshold_level) {
			PORTB = 0b00000001;					// turn on LED attached to PB0
		} else {
			PORTB = 0b00000000; 				// turn off LED attached to PB0
		}
	}

	return 0;
}
