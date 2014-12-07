/*
 * Blink an LED. This is used to vet the toolchain and USB programmer
 * connection with a simple, immediately-obvious result.
 */
#include <avr/io.h>
#include <util/delay.h>


#define DELAY_S	300
#define DELAY_O 600

int	main(void) __attribute__((noreturn));


static void
s(void)
{
	unsigned char	i = 0;

	for (i = 0; i < 3; i++) {
		PORTB ^= _BV(PB0);
		_delay_ms(DELAY_S);
		PORTB ^= _BV(PB0);
		_delay_ms(DELAY_S);
	}
	PORTB = ~_BV(PB0);
	_delay_ms(500);
}


static void
o(void)
{
	unsigned char	i = 0;

	for (i = 0; i < 3; i++) {
		PORTB ^= _BV(PB0);
		_delay_ms(DELAY_O);
		PORTB ^= _BV(PB0);
		_delay_ms(DELAY_O);
	}
	PORTB = ~_BV(PB0);
	_delay_ms(500);
}


int
main(void)
{
	PORTB |= _BV(PB0);

	while (1) {
		s();
		o();
		s();
		_delay_ms(1200);
	}
}
