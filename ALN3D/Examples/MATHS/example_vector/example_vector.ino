#include <SPI.h>
#include <ALN3D.h>

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  fVector_t a = {1/2, sqrt(3) / 2, 0};
  Display_Vector(a);
  Matrix_Display(IdentityMatrix);
  delay(1000);
}
