/*
 * GccApplication2a.c

 * Author : Tom McCarroll
 */ 

#include <avr/io.h>

int main (void)

{
	
	DDRB = 0xFF; //All ports on Port B as output
	
	int interrupt_counter = 0; // Sets variable for counting interrupts and initializes to zero

	TCCR0A = (1<<COM0B1); //Clear on Compare Match

	TCCR0B = (1<<CS02) | (1<<CS00);//Setting Pre-scaler to 1024

	TIMSK0 = (1 << OCIE0B);// Timer/Counter-Interrupt mask register turned on

	while (1) // Out main repeating loop

	{
	
		if(PINC & _BV(PINC2)) //Upon button activation preform the following
	
		{
	
			PORTB = _BV(PINB2); //Turn on PINB 2 for output
	
			interrupt_counter = 0; // Set interrupt counter to zero
		
			while(interrupt_counter < 50 )// Loop while interrupt counter is lesss than desired value
	
			{
		
				if (TIFR0 & (1 << OCR0B))// Loop condition checking for interrupt flag, and value Compare register
		
				{
		
					interrupt_counter +=1;// Increments our interrupt counter
					
					TIFR0 = 0x01;// Resets flag to 1
					
					TCNT0 = 0x00;//Resets our clock to zero
					
				}
	
			}

		}
	
		PORTB = 0x00;// After desired time period turn LED off again as long as button is not activated

	}

	return 0;// Return Statement
}