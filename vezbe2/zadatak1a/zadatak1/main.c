#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//treptanje f=2Hz
	DDRB |= 1 << 5; //izlaz za diodu

	while(1) {
		PORTB |= 1 << 5; //led on
		_delay_ms(500);
		PORTB &= ~(1 << 5); //lef off
		_delay_ms(500);
	}
	return 0;
}
