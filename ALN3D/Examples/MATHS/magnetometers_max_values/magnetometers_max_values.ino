#include <Wire.h>
#include <SPI.h>
#include <HMC5883L.h>
#include <ALN3D.h>

int c = 0;

int Xmin;
int Xmax;
int Ymin;
int Ymax;
int Zmin;
int Zmax;

void setup()
{
  Serial.begin(115200);
  
  HMC5883L_Init();
}

void loop()
{
  HMC5883L_Read_notScaled();

  char buf[120];
  
  if (magnXns < Xmin)
  {
    Xmin = magnXns;
  }
  
  if (magnXns > Xmax)
  {
    Xmax = magnXns;
  }
  
  if (magnYns < Ymin)
  {
    Ymin = magnYns;
  }
  
  if (magnYns > Ymax)
  {
    Ymax = magnYns;
  }
  
  if (magnZns < Zmin)
  {
    Zmin = magnZns;
  }
  
  if (magnZns > Zmax)
  {
    Zmax = magnZns;
  }
	
  snprintf(buf, sizeof(buf), "xmin:%d\txmax:%d\tymin:%d\tymax:%d\tzmin:%d\tzmax:%d", int(Xmin), int(Xmax), int(Ymin), int(Ymax), int(Zmin), int(Zmax));
  
  
  Serial.println(buf);
  delay(100);
}
