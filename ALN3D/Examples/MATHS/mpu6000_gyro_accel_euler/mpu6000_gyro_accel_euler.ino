#include <Wire.h>
#include <SPI.h>
#include <HMC5883L.h>
#include <ALN3D.h>

SPIMaster Master;

unsigned long last;

void setup()
{
  Master = SPIMaster();
  Serial.begin(115200);
  
  HMC5883L_Init();
  MPU6000_Init(&Master);
}

void loop()
{
  if (millis() - last > 100)
  {
    last = millis();
    
    MPU6000_Read();
    MPU6000_Corrections();
    
    Euler_Angles();
    
    char euler[80];
    Euler_Angles_Format(euler);
    Serial.print(euler);
    
    Serial.print("\t\t");
    
    char row[80];
    MPU6000_Format(row);
    Serial.println(row);
  }  
}
