/* Blinker Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


int main(void) {

  // -------- Inits --------- //

  DDRB |= (1 << PB0);


  // ------ Event loop ------ //
  while (1) {

    PORTB = 0b00000001;
    _delay_ms(5);

    PORTB = 0b00000000;
    _delay_ms(15);

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
