// 300 éxécution de la boucle loop par seconde en moyenne

#include <Wire.h>
#include <SPI.h>
#include <HMC5883L.h>
#include <ALN3D.h>

int c = 0;

SPIMaster Master;

void setup()
{
  Master = SPIMaster();
	
  Serial.begin(115200);
  
  HMC5883L_Init();
  MPU6000_Init(&Master);
}

void loop()
{  
  MPU6000_Read();
  HMC5883L_Read();
	
  Euler_Angles();
  Heading();
  
  c++;
  Serial.println(c / (millis() / 1000.0));
}