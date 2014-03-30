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
  
  Euler_Angles();
  
  char buf[80];
	Euler_Angles_Format(buf);
	Serial.print(buf);
	Serial.print("\tradius:");
	Serial.println(Accel_Magnitude);
	
  delay(100);
  
  /*
  c++;
  Serial.println(c / (millis() / 1000.0));
  */
}