/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

const char PYTHON_SEPERATOR = ';';

// float
void Python_Matrix_Display(fMatrix_t M)
{
	Serial.print("Matrix(");
	Serial.print("[");
	for(uint8_t i = 0; i < 3; i++)
	{
		Serial.print("[");
		for(uint8_t j = 0; j < 3; j++)
		{
			Serial.print(M[i][j], 4);

			if (j<2)
				Serial.print(",");
		}
		Serial.print("]");

		if (i < 2);
			Serial.print(",");
	}
	Serial.println("])");
}

// int
void Python_Matrix_Display(Matrix_t M)
{
	Serial.print("Matrix(");
	Serial.print("[");

	for(uint8_t i = 0; i < 3; i++)
	{
		Serial.print("[");
		for(uint8_t j = 0; j < 3; j++)
		{
			Serial.print(M[i][j], 4);

			if (j<2)
				Serial.print(",");
		}
		Serial.print("]");

		if (i<2)
			Serial.print(",");

	}
	Serial.println("])");
}
// float
void Python_Vector_Display(fVector_t V)
{
	Serial.print("Matrix([[");
	Serial.print(V[X]);
	Serial.print("],[");
	Serial.print(V[Y]);
	Serial.print("],[");
	Serial.print(V[Z]);
	Serial.println("]])");
}

// int
void Python_Vector_Display(Vector_t V)
{
	Serial.print("Matrix([[");
	Serial.print(V[X]);
	Serial.print("],[");
	Serial.print(V[Y]);
	Serial.print("],[");
	Serial.print(V[Z]);
	Serial.println("]])");
}

// programme matplotlib
void Python_MatPlotLib_Angles(void)
{
	Serial.print(millis() / 1000.0);
	Serial.print(";");
	Serial.print(phi * RAD_TO_DEG);
	Serial.print(";");
	Serial.println(theta * RAD_TO_DEG);
}
