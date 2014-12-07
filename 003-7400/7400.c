/*
 * This was an early start at trying to get an AVR interface to a 7400
 * IC.
 */
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>


#define INPUTA	PB0
#define INPUTB	PB1
#define OUTPUT	PB2
#define LED	PB3


static void
int(void)
{
	DDRB = ((1<<INPUTA)|(1<<INPUTB)|(0<<OUTPUT)|(1<<INPUTB));
}


static void
init_USART(void)
{
	UBRR0H = UBRR0H_VALUE;
	UBRR0L = UBRR0L_VALUE;
	UCSR0A &= ~(1 << U2X0);
	UCSR0B = ((1 << TXEN0)|(1 << RXEN0));
	UCSR0C = ((1 << UCSZ01)|(1 << UCSZ00));
}


void
main(void)
{

}
