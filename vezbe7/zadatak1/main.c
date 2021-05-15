//PROVERITI SA NEKIM

#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "../usart/usart.h"

// Promena korisnickog imena i lozinke se vrsi unutar define

#define KORISNICKO_IME "Anja Tanovic"
#define DUZINA_IMENA 12
#define LOZINKA "anjatanovic123"
#define DUZINA_LOZINKE 14

int8_t Provera(int8_t string1[], int8_t string2[], int8_t duzina1, int8_t duzina2);

int main()
{
	usartInit(9600);
	int8_t tmp[50];
	int8_t ime[DUZINA_IMENA+1] = KORISNICKO_IME;
	int8_t lozinka[DUZINA_LOZINKE+1] = LOZINKA;


	while (1)
	{
		sprintf(tmp, "Unesite korisnicko ime\r\n\0");
		usartPutString(tmp);

		while (usartAvailable() == 0)
		;
		_delay_ms(100);

		int8_t duzina1 = usartGetString(tmp);
		int8_t duzina = DUZINA_IMENA;

		int8_t jednaki;  //postavlja se na 1 ako su jednaki, a na 0 ako su razliciti
		jednaki = Provera(tmp, ime, duzina1, duzina);

		if (jednaki)
		{
			sprintf(tmp, "Unesite lozinku\r\n\0");
			usartPutString(tmp);

			while (usartAvailable() == 0)
			;
			_delay_ms(100);

			int8_t duzina2 = usartGetString(tmp);
			int8_t duzina = DUZINA_LOZINKE;

			jednaki = Provera(tmp, lozinka, duzina2, duzina);

			if (jednaki)
			{
				sprintf(tmp, "Dobrodosao/la \0");
				usartPutString(tmp);
				usartPutString(ime);
				usartPutString("\r\n\0");
				_delay_ms(1000);
			}
			else
			{
				sprintf(tmp, "Pogresno uneta lozinka\r\n\0");
				usartPutString(tmp);
			}

		}
		else
		{
			sprintf(tmp, "Pogresno uneto korisnicko ime\r\n\0");
			usartPutString(tmp);
		}

		usartPutString("\r\n\0");
	}
	return 0;
}

int8_t Provera(int8_t string1[], int8_t string2[], int8_t duzina1, int8_t duzina2)
{
	int8_t jednaki = 1;
	if (duzina1 != duzina2)
	{
		jednaki = 0;
	}
	else
	{
		for (uint8_t i = 0; i < duzina1; i++)
		{
			if (string1[i] != string2[i])
			{
				jednaki = 0;
				break;
			}
		}
	}
	return jednaki;
}
