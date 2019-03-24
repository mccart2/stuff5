/*
 * GccApplication2b.c

 * Author : Tom McCarroll
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{	sei();// Enables interrupts
	
	DDRB = _BV(PINB2); //Pins on Port B are input, except PIN2
	
	OCR0A = 0xC7;// Sets value we are comparing to
	
	TCCR0B = (1<<CS02) | (1<<CS00);//Setting Pre-scaler to 1024

	TIMSK0 = (1<<TOIE0);// Timer/Counter-Interrupt mask register, set to Output Compare Match

	PORTD |= (1 << PORTD2); // Pull up enabled
	
	EICRA |= (1 << ISC00);  // Set INT0 to trigger on any rising edge
	
	EIMSK |= (1 << INT0);   // Turns on both Interrupts
				
	while (1)
		{
		}
	
}

ISR(TIMER0_OVF_vect)// Our Interrupt Timer 0
{
	while(1) // Repeating Loop
	
	{
		
		int interrupt_counter = 0;// Sets variable for counting interrupts and initializes to zero
		
		if(PINC & _BV(PINC2)) // if the button is pressed then perform the following events
		
		{
			PORTB = _BV(PINB2);// Loop as long as interrupt counter is less than desired value
			interrupt_counter = 0;// Sets counter to zero
			while(interrupt_counter < 50 ) // while the clock is less than 1.25 s
			{
				if (TIFR0 & (1 << OCR0A))// Loop condition checking for interrupt flag, and value Compare register
				{
					interrupt_counter +=1;// Increments our interrupt counter
						
						TIFR0 = 0x01;// Resets flag to 1
						
						TCNT0 = 0x00;//Resets our clock to zero
				}
			}

		}
		PORTB = 0x00;// Once the specified amount of time has passed through the timers turn off LED

	}
}

