/*
 * Econet-clock
 * Version: 1
 */

#include <inttypes.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/delay.h>

void init()
{

	DDRB = _BV(PB4) | _BV(PB3);		// OC1B (PB4) and /OC1B (PB3) as output

	PLLCSR = _BV(PLLE);			// PLL on
	while ( ! (PLLCSR & _BV(PLOCK)));	// Wait for PLL lock

	GTCCR = _BV(PWM1B) | /*_BV(COM1B1) |*/ _BV(COM1B0);	// PWM B on timer 1 (8-bit PWM)
	OCR1B = 75;				// PWM value

	PLLCSR |= _BV(PCKE);			// Timer 1 clock source = PLL
	TCCR1 = _BV(CS10);			// Timer 1 on, no divider


}

int main ()
{
	init ();

	while(1)
	{
	}


    return (0);
}




