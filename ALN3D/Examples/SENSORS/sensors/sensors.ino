#include <Wire.h>
#include <SPI.h>
#include <ALN3D.h>
#include <HMC5883L.h>

int c = 0;

SPIMaster Master;

void setup()
{
  Serial.begin(115200);
	
  Master = SPIMaster();
  
  HMC5883L_Init();
  MPU6000_Init(&Master);
}

void loop()
{
  HMC5883L_Read();
  Heading();
  
  MPU6000_Read();
  
  char buf[100];
  
  MPU6000_Format(buf);
  
  // Serial.println(toScale(heading, 0, 2 * M_PI, 0, 360));
  Serial.print("heading:");
  Serial.print(heading * RAD_TO_DEG);
  Serial.print(" ");
  
  
  
  Serial.println(buf);
  //Serial.println(c++ / (millis() / 1000.0));
  
  delay(100);
  
}