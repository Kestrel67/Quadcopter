#include <SPI.h>
#include <ALN3D.h>

#define FREQ 24


void setup()
{
  Serial.begin(115200);
  
  SPIMaster master;

  MPU6000_Init(&master);  
}

void loop()
{
  MPU6000_Read();
  
  Roll_Pitch();
  
  char buf[50];
  Roll_Pitch_Format(buf);
  Serial.println(buf);
  
  delay(1.0 / FREQ * 1000);
}
