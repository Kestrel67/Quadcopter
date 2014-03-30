#include <Wire.h>
#include <SPI.h>
#include <HMC5883L.h>
#include <ALN3D.h>

int c = 0;

void setup()
{
  Serial.begin(115200);
  
  HMC5883L_Init();
}

void loop()
{
  HMC5883L_Read();
  Heading();

  Serial.print("heading:");
  Serial.println(heading * RAD_TO_DEG);
  //Serial.println(c++ / (millis() / 1000.0));
  
  delay(100);
  
}
