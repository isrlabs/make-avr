/*
 * Playing around with a TMP-36 temperature sensor. It spits out the
 * temperature in C every second via serial.
 */
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>


static void
init_USART(void)
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0A &= ~(1 << U2X0);
	UCSR0B = ((1 << TXEN0)|(1 << RXEN0));
	UCSR0C = ((1 << UCSZ01)|(1 << UCSZ00));
}


static void
init(void)
{
	ADMUX  |= (1<<REFS0);
	ADCSRA |= ((1<<ADPS1)|(1<<ADPS0)|(1<<ADEN));
	init_USART();
}


static uint16_t
adc_to_c(uint16_t t)
{
	return ((t / 6) + (t / 7)) / 2;
}


int
main(void)
{
	char		temp[10];
	uint8_t		chars = 0;
	uint8_t		i = 0;
	uint16_t	adc_value;

	init();

	while (1) {
		_delay_ms(1000);

		ADCSRA |= (1<<ADSC);
		loop_until_bit_is_clear(ADCSRA, ADSC);
		adc_value = adc_to_c(ADC);
		snprintf(temp, 9, "%d\r\n", adc_value);
		chars = (uint8_t)strlen(temp);

		for (i = 0; i < chars; i++) {
			loop_until_bit_is_set(UCSR0A, UDRE0);
			UDR0 = temp[i];
		}
	}
}

