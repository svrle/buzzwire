#define F_CPU 16000000UL 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define CONTACT_DELAY 500

ISR( INT1_vect ) {
  //cli();
  _delay_ms(CONTACT_DELAY);
  PORTB ^= (1 << PB0);	// togle pin 0 of port B
  //sei();
}

int main (void)
{
    DDRB |= (1 << DDB0);      // set pin 0 of port B as an output pin

    /**
     * Enable interrupt 
     */
    EICRA = (1<<ISC11) | (1<<ISC10); 	// INT1 rising edge
    EIMSK |= (1<<INT1);			// Set INT1 as input and pull-up
    DDRD &= ~(1<<PD3);			// INT1 input
    PORTD = (1<<PD3);			// INT1 pull-up 
    sei();				// enable interrupt routine
    /* Enable interruptt */

    // Set by default PB0 low
    DDRB |= ~(1<<DDB0);
    while (1) {
      //sei();
      //_delay_ms(5000);

    }

}
