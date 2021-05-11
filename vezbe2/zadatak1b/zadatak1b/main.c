#include <avr/io.h>
#include <avr/interrupt.h>
//treptanje f=2Hz
unsigned long t0=0;

ISR(TIMER0_COMPA_vect)
{
	t0++;
}


int main(void)
{
	//inicijalizacija tajmera 0:
	TCCR0A = 0x02; // CTC mod
	TCCR0B = 0x03; // fclk = fosc/64
	OCR0A = 249; //perioda tajmera 0: 250 Tclk (OCR0A + 1 = 250)
	TIMSK0 = 0x02; //dozvola prekida tajmera 0
	//usled dostizanja vrednosti registra OCR0A

	sei(); //I = 1 (dozvola prekida)

	DDRB |= 1 << 5; //PB5 je izlaz za diodu
	PORTB |= 1<<5; //setovanje diode na 1 (led ON)

	while(1) {
		if (t0 == 500) {
			t0=0;
			PORTB ^= 1<<5 ; //xor, invertuje stalno PB5
		}
	}
	return 0;
}
