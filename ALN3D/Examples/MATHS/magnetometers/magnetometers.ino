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

  char buf[30];
  
  sprintf(buf, "x:%d\ty:%d\tz:%d", int(Magn[X]), int(Magn[Y]), int(Magn[Z]));
  
  Serial.println(buf);
  
  delay(100);
}