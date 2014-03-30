/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

Matrix_t IdentityMatrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

// A * B = M
void Matrix_Multiply(fMatrix_t A, fMatrix_t B, fMatrix_t M)
{
  float op;

  // pour chaque ligne
  for(uint8_t line = 0; line < 3; line++)
  {
	  // pour chaque colonnes
    for(uint8_t column = 0; column < 3; column++)
    {
      op = 0;

      // somme de 3 produits
      for(uint8_t w = 0; w < 3; w++)
      {
    	  op += A[line][w] * B[w][column];
      }

      // output matrix
      M[line][column] = op;
    }
  }
}

// M * scalar
void Matrix_Scale(fMatrix_t M, float scalar)
{
	for(uint8_t line = 0; line < 3; line++)
	{
		for(uint8_t column = 0; column < 3; column++)
		{
			M[line][column] *= scalar;
		}
	}
}

// transposée
void Matrix_Transpose(fMatrix_t M, fMatrix_t Out)
{
	for (uint8_t i = 0; i < 3; i++)
	{
		for (uint8_t j = 0; j < 3; j++)
		{
			Out[j][i] = M[i][j];
		}
	}
}

// Vprime = M * V
void Vector_Apply_Matrix(fMatrix_t M, fVector_t V, fVector_t Vprime)
{
	for(uint8_t line = 0; line < 3; line++)
	{
		float op = 0;

		for(uint8_t w = 0; w < 3; w++)
		{
			op += M[line][w] * V[w];
		}

		Vprime[line] = op;
	}
}

// V = M * V
void Vector_Apply_Matrix(fMatrix_t M, fVector_t V)
{
	fVector_t op;

	Vector_Apply_Matrix(M, V, op);

	V[X] = op[X];
	V[Y] = op[Y];
	V[Z] = op[Z];
}

// Serial.print(M) (float)
void Matrix_Display(fMatrix_t M)
{
	Serial.print("Matrix (3, 3) : ");
	for(uint8_t i = 0; i < 3; i++)
	{
		Serial.print("\n");
		for(uint8_t j = 0; j < 3; j++)
		{
			Serial.print("\t");
			Serial.print(M[i][j], 4);
		}
	}
	Serial.println("");
}

// Serial.print(M) (int)
void Matrix_Display(Matrix_t M)
{
	Serial.print("Matrix (3, 3) : ");
	for(uint8_t i = 0; i < 3; i++)
	{
		Serial.print("\n");
		for(uint8_t j = 0; j < 3; j++)
		{
			Serial.print("\t");
			Serial.print(M[i][j]);
		}
	}
	Serial.println("");
}
