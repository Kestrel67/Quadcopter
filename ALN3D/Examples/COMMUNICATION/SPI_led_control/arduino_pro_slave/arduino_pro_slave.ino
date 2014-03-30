#include <SPI.h>
#include <ALN3D.h>

SPISlave Slave = SPISlave();

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  
}

ISR (SPI_STC_vect)
{
  analogWrite(3, SPDR);
}
