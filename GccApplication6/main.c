 /*
 * GccApplication1a.c

 * Author : Tom McCarroll
 */ 
 


#include <avr/io.h>

int main (void)
{
	DDRB = 0xFF; //All ports on Port B as output
	
	int counter = 0; //Counter for outer loop.
	
	int flag_high = 0;  //Counter used in loop when LED is in HIGH/ON state
	
	int flag_low = 0;  //Counter used in loop when LED is in LOW/OFF state
		
	OCR0A = 0xDC; // Amount of time/cycles on flag needs to be on
	
	OCR0B = 0x96; // Amount of time/cycles on flag needs to be off
		
	TCCR0A = (1<<COM0A1)|(1<<COM0B1); //Clear on Compare Match
	
	TCCR0B = (1<<CS02) | (1<<CS00); //Setting Pre-scaler to 1024
	
	TIMSK0 = (1 << OCIE0B)| (1 << OCIE0A); // Timer/Counter-Interrupt mask register, set to Output Compare Match 
	
	while (1) // Our Repeating loop
	
	{
	
		if (counter %2 == 0)//Main control if statement for which the LED will be on
	
		{
		
			PORTB = 0x01;//Sets the output of Port B to high
		
			while (flag_high<2) // Loop for how long our LED will be on for.
		
			{
			
				if (TIFR0 & (1 << OCR0A)) //Inner loop that cycles until our flag hits given value.
			
				{
			
					flag_high +=1;  
			
					TCNT0 = 0x00; //Resets our counter to zero
			
					TIFR0 = 0x01; // Sets our Interrupt register to 1
			
				}
			
			}
			
			flag_high = 0;//Resets our Flag Counter
			
			counter+=1;// Increases our main counter by incrementing by 1
		
		}
		else // Loop used for keeping/turning the LED off
		
		{
		
			PORTB = 0x00;//Sets the output of Port B to low
		
			while (flag_low<2)// How long we will be looping for to keep the LED off
		
			{
		
				if (TIFR0 & (1<<OCR0B)) // Inner loop that cycles until our flag_low hits desired value
		
				{
		
					TCNT0 = 0x00;//Resets our counter to zero
		
					flag_low += 1;// Increments our off counter by 1
		
					TIFR0 = 0x0;// Resets interrupt flag to zero
		
				}
		
			}
		
			flag_low = 0;//Resets flag counter to zero
		
			counter+=1;// Increments counter preparing for LED to be powered on again.
	
		}
	
	}
	
return 0;}
