#include <SPI.h>
#include <ALN3D.h>

SPIMaster Master = SPIMaster();

byte cmd;

void setup()
{
	Master.addSlave(PWM0);
	
  Serial.begin(115200);
}

void loop()
{
  cmd = cmd ? cmd * 2 : 3;
  
  byte reply = Master.send(PWM0, cmd);
	
	Serial.println(reply);

  delay(100);
}
