/*
 * GccApplication1b.c

 * Author : Tom McCarroll
 */ 

#include <avr/io.h>

int main (void)
{
	DDRB = _BV(PINB2); //We are setting Pin2 as output
	
	int interrupt_counter = 0;// Sets variable for counting interrupts and initializes to zero
	
	OCR0A = 0xC7;// Sets our compare register to value we wish to look for 
	
	TCCR0A = (1<<COM0B1); //Clear on compare match
	
	TCCR0B = (1<<CS02) | (1<<CS00);//Setting Pre-scaler to 1024
	
	TIMSK0 = (1 << OCIE0B);// Enables Compare on match
	
	while (1)// Repeating main loop
	
	{
	
		if(PINC & _BV(PINC2)) // Loop statement, upon button activation preform the following actions
			
			{
				
			PORTB = _BV(PINB2);// Sets Port B as output using _bv operation (bit value)
			
			interrupt_counter = 0;// Sets counter to zero
			
			while(interrupt_counter < 50 )// Loop for condition if counter is less than enter value (50)
			
				{
					
				if (TIFR0 & (1 << OCR0A)) // Loop condition checking for interrupt flag, and value Compare register
					
					{
					
					interrupt_counter +=1; // Increments our interrupt counter
					
					TIFR0 = 0x01;// Resets flag to 1
				
					TCNT0 = 0x00;//Resets our clock to zero
					
				}
			}

		}
		PORTB = 0x00;// After desired time period turn LED off again as long as button is not activated
	}

	return 0; // Return statement
}