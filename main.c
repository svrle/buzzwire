#define F_CPU 16000000UL 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define CONTACT_DELAY 500

char point[10] = {95, 3, 214, 220, 153, 205, 207, 88, 223, 221};

ISR( INT1_vect ) {
  cli();
  PORTB |= (1 << PB0);	// pin on 0 of port B
  _delay_ms(CONTACT_DELAY); // delay between contacts in case that probe moving is with unstable hand
  PORTB &= ~(1 << PB0);	// pin off 0 of port B
  sei();
}

int main (void)
{
    DDRB |= (1 << DDB0);      // set pin 0 of port B as an output pin
    /**
     * Enable pins for SN74CH595N
     */
    DDRC |= (1 << DDC3);      // set pin 3 of port C as an output pin SER
    DDRC |= (1 << DDC2);      // set pin 2 of port C as an output pin SRCLK RCLK

    /**
     * Enable interrupt 
     */
    EICRA = (1<<ISC11) | (1<<ISC10); 	// INT1 rising edge
    EIMSK |= (1<<INT1);			// Set INT1 as input and pull-up
    DDRD &= ~(1<<PD3);			// INT1 input
    PORTD = (1<<PD3);			// INT1 pull-up 
    sei();				// enable interrupt routine
    /* Enable interrupt */

    // Set by default PB0 low
    DDRB |= ~(1<<DDB0);

    while (1) {
      /**
       * 7Segment display driven by SN74CH595N
       */
      char i;
      for(i=0; i<8; i++) {
      	PORTC &= ~(1 << PC2); 	// Clock low
        			// If bit in number is 1 send 1 to SER, if it's 0 send 0 to SER
        if(point[0] & (1 << i)) {
	  PORTC |= (1 << PC3);
	} else {  
          PORTC &= ~(1 << PC3);
	}
      	PORTC |= (1 << PC2); 	// Clow high
      }
      /* 7Segment display driven by SN74CH595N */
      _delay_ms(1000);
    }

}
