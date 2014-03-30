#include <SPI.h>
#include <ALN3D.h>

fMatrix_t A = {{0, 1, 0}, {0.1, 1, 0}, {0, 1, 1}};

void setup()
{
  Serial.begin(115200);
  
}

void loop()
{
  Matrix_Multiply(A, A, A);
  Matrix_Display(A);
  delay(1000);
}
