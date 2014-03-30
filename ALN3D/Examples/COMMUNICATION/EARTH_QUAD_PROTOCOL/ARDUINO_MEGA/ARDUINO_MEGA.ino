#include <SPI.h>
#include <ALN3D.h>

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

unsigned long l;
byte param;

void loop()
{
  if (millis() - l > 100)
  {
    send_serial_command(CMD_CFG_AZIMUT, param++, &Serial1);
    l = millis();
  }
  else if(Serial1.available())
  {
    Serial.println(Serial1.read());
  }
}
