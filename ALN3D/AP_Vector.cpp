/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

// V * V
float Vector_Dot_Product(fVector_t vector1, fVector_t vector2)
{
  float op = 0;

  for(uint8_t c = 0; c < 3; c++)
  {
	  op += vector1[c] * vector2[c];
  }

  return op;
}

// V _|_ V (cross product)
void Vector_Cross_Product(fVector_t vectorOut, fVector_t v1, fVector_t v2)
{
  vectorOut[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
  vectorOut[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
  vectorOut[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
}

// V * scalar
void Vector_Scale(fVector_t vectorOut, fVector_t vectorIn, float scale2)
{
  for(uint8_t c = 0; c < 3; c++)
  {
	  vectorOut[c] = vectorIn[c] * scale2;
  }
}

// V * scalar
void Vector_Scale(Vector_t vectorOut, Vector_t vectorIn, float scale2)
{
  for(uint8_t c = 0; c < 3; c++)
  {
	  vectorOut[c] = vectorIn[c] * scale2;
  }
}

// V + V
void Vector_Add(fVector_t vectorOut, fVector_t vectorIn1, fVector_t vectorIn2)
{
  for(uint8_t c = 0; c < 3; c++)
  {
     vectorOut[c] = vectorIn1[c] + vectorIn2[c];
  }
}

// || V || (float)
float Vector_Magnitude(fVector_t V)
{
	return sqrt(V[X] * V[X] + V[Y] * V[Y] + V[Z] * V[Z]);
}

// || V || (int)
float Vector_Magnitude(Vector_t V)
{
	return sqrt(V[X] * V[X] + V[Y] + V[Y] + V[Z] * V[Z]);
}

// V' = V / magnitude(V) => magnitude(V1) = 1
void Vector_Normalize(fVector_t V)
{
	float magn = Vector_Magnitude(V);
	Vector_Scale(V, V, 1.0 / magn);
}

void Vector_Normalize(Vector_t V)
{
	float magn = Vector_Magnitude(V);
	Vector_Scale(V, V, 1.0 / magn);
}

void Vector_Normalize(fVector_t V, fVector_t Vout)
{
	float magn = Vector_Magnitude(V);
	Vector_Scale(Vout, V, 1.0 / magn);
}

// Serial.print(V) (float)
void Vector_Display(fVector_t vector)
{
	Serial.println("Vector (3, 1) : ");
	for(uint8_t i = 0; i < 3; i++)
	{
		Serial.print("\t");
		Serial.println(vector[i], 4);
	}
}

// Serial.print(V) (int)
void Vector_Display(Vector_t vector)
{
	Serial.println("Vector (3, 1) : ");
	for(uint8_t i = 0; i < 3; i++)
	{
		Serial.print("\t");
		Serial.println(vector[i]);
	}
}

// angle entre U et V
float Vectors_Angle(fVector_t U, fVector_t V)
{
	return acos(constrain((U[X] * V[X] + U[Y] * V[Y] + U[Z] * V[Z]) / (Vector_Magnitude(U) * Vector_Magnitude(V)), -1.0, 1.0));
}

float Vectors_Angle(Vector_t U, Vector_t V)
{
	return acos(constrain((U[X] * V[X] + U[Y] * V[Y] + U[Z] * V[Z]) / (Vector_Magnitude(U) * Vector_Magnitude(V)), -1.0, 1.0));
}

// angle entre U et V
float Vectors1_Angle(fVector_t U, fVector_t V)
{
	return acos(constrain(U[X] * V[X] + U[Y] * V[Y] + U[Z] * V[Z], -1.0, 1.0));
}

// V = U
void Vector_Copy(fVector_t U, fVector_t V)
{
	for(uint8_t i = 0; i <3; i++)
		V[i] = U[i];
}

float Vector_Error_Sum(fVector_t U, fVector_t V)
{
	float s = 0.0;

	for(uint8_t i = 0; i < 3; i++)
		s += abs(V[i] - U[i]);

	return s;
}
