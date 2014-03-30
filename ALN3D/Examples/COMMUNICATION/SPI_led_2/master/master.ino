#include <SPI.h>
#include <ALN3D.h>

SPIMaster Master = SPIMaster();



byte cmd = 1;

void setup()
{
  Master.addSlave(PWM0);
}

void loop()
{
  byte ret = Master.send(PWM0, cmd);
  
  cmd = cmd ? cmd * 2 : 3;
  
  delay(100);
  
}