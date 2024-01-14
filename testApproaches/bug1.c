#define F_CPU 16000000UL 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/**
 * Interrupt for new game
 */
ISR( TIMER0_COMPA_vect ) {
  PORTB |= (1<<PB0);
  _delay_ms(150);
  PORTB &= ~(1<<PB0);

}

/**
 * Interrupt for for increasing points bug#1
 */
ISR( TIMER0_COMPB_vect ) {
  PORTB |= (1<<PB0);
  _delay_ms(50);
  PORTB &= ~(1<<PB0);
  OCR0B =+ 1;
}
int main (void)
{
    DDRB |= (1 << DDB0);      // set pin 0 of port B as an output pin, for WIRE
    PORTB &= ~(1 << PB0);

    /**
     * Counter0(TCNT0) for counting LED number from 'point' char array bug#1
     *
     */
    DDRD &= ~(1<<PD4);					// T0 as input
    OCR0A = 3;						// Value that TCNT0 would compare with COMPA for generating interrupt. Interrupt would be generated on next clock after Value is reached.
    OCR0B = 1;						// Value that TCNT0 would compare with COMPB for generating interrupt. Interrupt would be generated on next clock after Value is reached.
    TCNT0 = 0;						// Default value that would be comparing
    TCCR0B |= (1<<CS02) | (1<<CS01) | (1<<CS00);	// CTC mode, external clock source on T0 pin, on rising edge
    TIMSK0 |= (1<<OCIE0A) | (1<<OCIE0B);		// Enable Counter interrupt

    sei();				// enable interrupt routine

    while (1) {
    }

}

