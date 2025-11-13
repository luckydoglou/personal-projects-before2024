// 
// Use ADC and PWM in Atmega168, with potentiometer as sensor and LED as actuator.
// For ADC, use manual mode instead of fast running mode
// For PWM, use PD6 8-bit timer/counter
//
// Xiaolou Huang (Lor)
// 10/9/2019
//

#include <avr/io.h>
#include <util/delay.h>

static inline initADC(void) {
	ADMUX |= (1 << REFS0);						// set reference voltage to AVCC pin
	ADMUX |= (1 << MUX0) | (1 << MUX1);			// select ADC3 pin to be used for ADC
	// ADMUX &= ~( (1 << MUX2) | (1 << MUX3) );
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1);		// ADC clock prescaler /8
	ADCSRA |= (1 << ADEN);						// enable ADC	
}

static inline initPWM(void) {
	TCCR0A |= (1 << COM0A1); 					// enable PWM on OCR0A; non-inverting mode
	TCCR0A |= (1 << WGM00) | (1 << WGM01);		// set fast PWM mode with 0xFF as TOP value
	TCCR0B |= (1 << CS01);						// set scaler for frequency: cpu clock / 8
	DDRD |= (1 << PD6);							// set PD6 as outout
}

int main(void) {
	uint16_t adcValue;

	// -------- Inits --------- //
	initADC();
	initPWM();

  	// ------ Event loop ------ //
	while(1) {
		ADCSRA |= (1 << ADSC);						// start first conversion
		loop_until_bit_is_clear(ADCSRA, ADSC); 		// wait until ADC conversion is done
		adcValue = ADC;								// get 10-bit adc analog value
		adcValue >>= 2;     						// shift right 2 to use most significant 8-bit value
		OCR0A = adcValue;   						// set the PWM duty cycle
	}

	return 0;
}

