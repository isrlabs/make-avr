/*
 * Playing around with a piezoelectric speaker
 *  (i.e. https://www.sparkfun.com/products/7950).
 */
#define BAUD	9600

#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>


#define LED	PB0
#define SPEAKER	PB1


int	main(void) __attribute__((noreturn));


void beep() {
	int i;

	for (i = 0; i < 10; i++) {
		PORTB |= (1 << SPEAKER);
		_delay_ms(156);
		PORTB &= ~(1 << SPEAKER);
		_delay_ms(156);
	}
}


int
main(void)
{
	DDRB = (1 << PB0) | (1 << PB1);
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0A &= ~(1 << U2X0);
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

	PORTB |= (1 << PB0);
	_delay_ms(1000);

	while (1) {
		if (bit_is_set(UCSR0A, RXC0)) {
			break;
		}
	}
	beep();

	while (1) ;
}
