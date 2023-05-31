/*
 ============================================================================
 Name        : Stop Watch system.c
 Author      : Basel Dawoud
 ============================================================================
 */

// Libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Switching delay (Multiplexing method)
#define d 10

// The Timer1 Compare Value
#define COMP 1024

// global variable contain the ticks count of the timer
unsigned int g_tick = 0;

// Timer1 Function
void Timer1_Init_CTC_Mode()
{
	TIMSK|=(1<<OCIE1A);
	TCCR1A = 0;    // Set Timer initial value to 0
	OCR1A  = COMP; // Set Compare Value
	TCCR1B |= (1<<WGM12)| (1<<CS12) | (1<<CS10);
}

/* ISRs */

// Timer1 interrupt (incrementing the seconds)
ISR(TIMER1_COMPA_vect)
{
	g_tick++;
}

// Resetting the segments to read from zero again
ISR(INT0_vect)
{
	g_tick=0;
}

// Pausing the timer
ISR(INT1_vect)
{
	TCCR1B &= ~(1<<CS12) & ~(1<<CS10);
}

// Resuming the timer
ISR(INT2_vect)
{
	TCCR1B |= (1<<CS12) | (1<<CS10);
}

int main(void)
{
	unsigned int sec=0,h=0,min=0;	// Hours & Minutes & Seconds initialization
	DDRA |= 0b00111111;				// Configure the enable pins as output pins.
	DDRC |= 0x0F;           		// Configure the decoder pins as output pins.
	DDRD &= ~(1<<PD2) & ~(1<<PD3);	// Configure the buttons pins as input pins.
	DDRB &= ~(1<<PB2);				// Configure the Resuming button pin as an input pin.

	// Setting initial values to the pins
	PORTC |= 0x00; 			// Segments read zero at the beginning
	PORTA |= 0b00111111; 	// Segments are on at the beginning
	SREG  |= (1<<7);        // Enable global interrupts in MC.

	// External Interrupt INT0 with falling edge
	GICR |=(1<<INT0);
	MCUCR|=(1<<ISC01);

	// External Interrupt INT1 with raising edge
	GICR |=(1<<INT1);
	SFIOR |=(1<<PUD);
	MCUCR|=(1<<ISC01);
	MCUCR|=(1<<ISC11);

	// External Interrupt INT1 with raising edge
	GICR |=(1<<INT2);

	Timer1_Init_CTC_Mode(1024);    // Start the timer.


	while(1)
    {
		// Representing the ticks into H:Min:Sec
    	h=g_tick/3600;
    	min=(g_tick/60)%60;
    	sec=g_tick%60;

		PORTA &= (0xC0);
		PORTA |= (1<<0) ;
		PORTC &= (0xF0);
		PORTC|= (sec%10);
		_delay_us(d);
		PORTA &= (0xC0);
		PORTA |= (1<<1) ;
		PORTC &= (0xF0);
		PORTC|= (sec/10);
		_delay_us(d);
		PORTA &= (0xC0);
		PORTA |= (1<<2) ;
		PORTC &= (0xF0);
		PORTC|= (min%10);
		_delay_us(d);
		PORTA &= (0xC0);
		PORTA |= (1<<3) ;
		PORTC &= (0xF0);
		PORTC|= (min/10);
		_delay_us(d);
		PORTA &= (0xC0);
		PORTA |= (1<<4) ;
		PORTC &= (0xF0);
		PORTC|= (h%10);
		_delay_us(d);
		PORTA &= (0xC0);
		PORTA |= (1<<5) ;
		PORTC &= (0xF0);
		PORTC|= (h/10);
		_delay_us(d);
    }
}
