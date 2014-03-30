#include <SPI.h>
#include <ALN3D.h>

SPIMaster master;

void setup()
{
  Serial.begin(115200);
  
  master = SPIMaster();
  
  AP_init(&master, SS);
  
  AP_write(1, 1);
}

byte c;

void loop()
{
  for(int i = 0; i<255;i++)
  {
    AP_write(0, i);
    delay(5);
  }
  
    AP_write(1, !AP_read(1));
  delay(50);
}
