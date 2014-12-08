#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>


static void	write_string(char *);


ISR(TIMER1_COMPB_vect)
{
	write_string("tick\r\n");
	TCNT1 = 0;
}


void
init_USART(void)
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0A &= ~(1 << U2X0);

	UCSR0B = ((1 << TXEN0)|(1 << RXEN0));
	UCSR0C = ((1 << UCSZ01)|(1 << UCSZ00));
}


void
init_timer(void)
{
	TCCR1B |= ((1 << CS12)|(1 << CS10));
	TIMSK1 |= (1 << OCIE1B);
	OCR1B = (1 << 15);
}


void
write_string(char *s)
{
	int	i;
	int	l;

	l = strlen(s);
	for (i = 0; i < l; i++) {
		loop_until_bit_is_set(UCSR0A, UDRE0);
		UDR0 = s[i];
	}
}


int
main(void)
{
	init_USART();
	write_string("serial init\r\n");

	init_timer();
	write_string("timer init\r\n");

	sei();

	while (1) {
		_delay_ms(1000);
		write_string("tock\r\n");
	}
}


