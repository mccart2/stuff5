/*
 * GccApplication3a.c
 
 * Author : Tom McCarroll
 */ 


#include <avr/io.h>
#include <avr/interrupt.h> 
#include <util/delay.h> // Enables us to use delays
#define F_CPU 1000000UL  // Lets us set the clock speed



int main(void)
{
	DDRB |= (1 << 1);//Enables Port B pin 1 as output
	
	timer_not_slimer();// Calls our Timer Function
	
	while(1) // Repeating loop
	
	{
	}
}



void timer_not_slimer() // Function for our timer
{
	
	sei();//Enables Interrupts
	
	OCR0B = 0xD7;//How long the the LED will be on for 
	
	OCR0A = 0x91;// How long the LED  will be off for
	TCCR0B |= (1 << WGM02)|(1 << CS02)|(1 << CS00);// Pre-scaler set to 1024 and CTC mode enabled
	
	TIMSK0 |= (1 << OCIE1A)|(1 << OCIE1B);//Turns on Enable Compare Interrupt Mode
		
}




ISR (TIMER0_COMPA_vect) // Function for turning timer on
{
	PORTB = 0x01; //Turns LED on by setting the Port High
	
	_delay_ms(215);//Call delay for desired time .215 seconds

}



ISR (TIMER0_COMPB_vect)// Function for turning timer off
{
	PORTB = 0x00; // Turn off LED by setting the Port Low
	
	_delay_ms(145);//Call delay for desired time .145 seconds
}