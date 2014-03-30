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

Vector_t MaxAccel = {0.0, 0.0, 0.0};
Vector_t MinAccel = {0.0, 0.0, 0.0};

void loop()
{
  if (millis() - last > 100)
  {
    last = millis();    
    Vector_Display(MinAccel);
    Vector_Display(MaxAccel);  
  }  
  
    MPU6000_Read();
    
    if (Accel[X] > MaxAccel[X])
      MaxAccel[X] = Accel[X];
      
    if (Accel[Y] > MaxAccel[Y])
      MaxAccel[Y] = Accel[Y];
      
    if (Accel[Z] > MaxAccel[Z])
      MaxAccel[Z] = Accel[Z];
      
    if (Accel[X] < MinAccel[X])
      MinAccel[X] = Accel[X];
      
    if (Accel[Y] < MinAccel[Y])
      MinAccel[Y] = Accel[Y];
      
    if (Accel[Z] < MinAccel[Z])
      MinAccel[Z] = Accel[Z];
}
