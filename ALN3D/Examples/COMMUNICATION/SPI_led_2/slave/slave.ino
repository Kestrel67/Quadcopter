#include <SPI.h>
#include "ALN3D.h"

SPISlave slave = SPISlave();



void setup()
{
  Serial.begin(115200);
  
  pinMode(3, OUTPUT);
}

void loop()
{
  
}

ISR (SPI_STC_vect)
{
  Serial.println(SPDR);
  analogWrite(3, SPDR);
}
