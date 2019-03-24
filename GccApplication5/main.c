/*
 * GccApplication3b.c

 * Author : Tom McCarroll
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
int main(void)
{	
	
	sei(); 	//Turns on Interrupts
	
	OCR0A = 0xFF; //Number we will be comparing to
	
	DDRB = _BV(PINB2);//We are setting Pin2 as output
	
	TCCR0A = (1<<COM0B1)|(1<<WGM01); //Clear on Compare Match
	
	TCCR0B |= (1 << CS02)|(1 << CS00); //Setting Pre-scaler to 1024 and turning on CTC mode
	
	TIMSK0 = (1 << OCIE0B);// Timer/Counter-Interrupt mask register turned on
	
	while(1)
	
	{
	

ISR (TIMER0_COMPA_vect)//Saves us the trouble of turning the LED off after our checks, 

{
	int interrupt_counter = 0;// Sets variable for counting interrupts and initializes to zero
	
	if(PINC & _BV(PINC2))//Upon button activation preform the following
	
	{
		
		PORTB ^= (1<<2); //Turn on PINB 2 for output
		
		interrupt_counter = 0;// Set interrupt counter to zero
		
		while(interrupt_counter < 49 ) // Loop as long as interrupt counter is less than desired value
		
		{
			
			if (TIFR0 & (1 << OCR0A))// Loop condition checking for interrupt flag, and value Compare register
			
			{
				
				interrupt_counter +=1;// Increments our interrupt counter
				
				TIFR0 = 0x01;// Resets flag to 1
				
				TCNT0 = 0x00;//Resets our clock to zero
		}

	}
	
	PORTB = 0x00; // After desired time period turn LED off again as long as button is not activated
	}
	}
	}
}