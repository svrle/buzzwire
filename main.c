#define F_CPU 16000000UL 
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>

/**
* Function declaration
*/
void LedNumber(char PointNumber);
/* Function declaration */

char point[10] = {126, 6, 109, 121, 51, 91, 95, 112, 127, 123}; // Numbers for 7segment display: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
volatile uint8_t LedIncrease = 0;


ISR( INT1_vect ) {
  cli();
  LedIncrease++;
  LedNumber(point[LedIncrease]);
  if(LedIncrease > 9) {
    LedIncrease = 0;
    LedNumber(point[LedIncrease]);
  }
}


int main (void)
{
    DDRB |= (1 << DDB0);      // set pin 0 of port B as an output pin, for WIRE

    /**
     * Enable interrupt 
     */
    EICRA |= (1<<ISC11) | (1<<ISC10); 	// INT1 rising edge
    EIMSK |= (1<<INT1);			// Set INT1 as input and pull-up
    DDRD &= ~(1<<PD3);			// INT1 input
    PORTD = (1<<PD3);			// INT1 pull-up 
    sei();				// enable interrupt routine
    /* Enable interrupt */

    /**
     * Enable pins for SN74CH595N
     */
    DDRC |= (1 << DDC3);      // set pin 3 of port C as an output pin SER
    DDRC |= (1 << DDC2);      // set pin 2 of port C as an output pin SRCLK RCLK
    LedNumber(point[LedIncrease]);      // Show initial number 0 when game start
    /* Enable pins for SN74CH595N */

    // Set by default PB0 low
    DDRB |= ~(1<<DDB0);

    while (1) {

    }

}

void LedNumber(char PointNumber) {
      /**
       * 7Segment display driven by SN74CH595N
       */
      volatile uint8_t i;
      for(i=0; i<8; i++) {
      	PORTC &= ~(1 << PC2); 	// Clock low
        			// If bit in number is 1 send 1 to SER, if it's 0 send 0 to SER
        if(PointNumber & (1 << i)) {
	  PORTC |= (1 << PC3);
	} else {  
          PORTC &= ~(1 << PC3);
	}
      	PORTC |= (1 << PC2); 	// Clock high
      }
      /* 7Segment display driven by SN74CH595N */
}
