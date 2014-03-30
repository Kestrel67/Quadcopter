#include <SPI.h>
#include <ALN3D.h>

void setup()
{
  SPIMaster Master;
  Serial.begin(115200);
  
  MPU6000_Init(&Master);
  
  MPU6000_Gyro_Calibration();
  
  Vector_Display(Omega_Gap);
}

void loop()
{
  MPU6000_Read();
  MPU6000_Corrections();
  char buffer[80];
  MPU6000_Format(buffer);
  Serial.println(buffer);
  delay(100); 
}
