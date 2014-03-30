/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

void CPU_types_size(void)
{
	if (Serial)
	{
		Serial.println("Types size :");

		Serial.print("int, unsigned : ");
		Serial.println(sizeof(int));

		Serial.print("byte, (u) int8_t, char : ");
		Serial.println(sizeof(int8_t));

		Serial.print("long int : ");
		Serial.println(sizeof(long));

		Serial.print("long long int : ");
		Serial.println(sizeof(long long int));

		Serial.print("matrix (int) : ");
		Serial.println(sizeof(Matrix_t));

		Serial.print("matrix (float) : ");
		Serial.println(sizeof(fMatrix_t));

		Serial.print("vector (int) : ");
		Serial.println(sizeof(Vector_t));

		Serial.print("vector (float) : ");
		Serial.println(sizeof(fVector_t));

		Serial.print("coordinates system (fVector_t) : ");
		Serial.println(sizeof(CoordinateSystem_t));
	}
}

void CPU_frequency(void)
{
	if (Serial)
	{
		Serial.print("CPU frequency : ");
		Serial.println(F_CPU);
	}
}

void LED13_CPU_frequency(void)
{
	// led 13 as OUTPUT
	DDRB = 0xff;

	// LOW
	PORTB = 0x00;
	for(;;)
	{
		// on inverse l'état
		PORTB = ~PORTB;
	}
}
