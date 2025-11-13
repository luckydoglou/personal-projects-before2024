/*
* SER456 Embedded System: Sensors & Actuators.
*
* Xiaolou Huang (Lor), 9/15/2019
* 
*/

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    
	/* set PB0-PB7 as LEDs output */
	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) 
	| (1 << DDB4) | (1 << DDB5) | (1 << DDB6) | (1 << DDB7);

	/* set PD0-PD7 as 7-Segment Display output */
	DDRD |= (1 << DDD0) | (1 << DDD1) | (1 << DDD2) | (1 << DDD3) 
	| (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
    
	while(1) {
        int i, j;
        _delay_ms(1000);
        
		/* Demo 1. Set bits */
		PORTD = 0x06; /* display 1 */
        PORTB = 0x00;
		for (i = 0; i <= 7; i++) {
			PORTB |= 1 << i;
			_delay_ms(1000);
		}

		/* Demo 2. Clear bits */
		PORTD = 0x5B; /* display 2 */
        _delay_ms(1000);
		for (i = 0; i <= 7; i++) {
			PORTB &= ~(1 << i);
			_delay_ms(1000);
		}

		/* Demo 3. Toggle bits */
		PORTD = 0x4F; /* display 3 */
		for (i = 0; i <= 7; i++) {
			/* toggle twice */
			for (j = 0; j < 2; j++) {
				PORTB ^= 1 << i;
                _delay_ms(500);
			}
			_delay_ms(1000);
		}

		/* Demo 4. Shift a bit pattern "1111 0000" */
		PORTD = 0x66; /* display 4 */
		PORTB = 0b11110000;
        _delay_ms(1000);
		for (i = 0; i <= 7; i++) {
			if (i <= 3) {
				PORTB <<= 1; /* shift a 0 in */
				PORTB ^= 1; /* toggle 0 to 1 */
			} else {
				PORTB <<= 1; /* shift a 0 in */
			}
			_delay_ms(1000);
		}

	}

	return 0;
}


