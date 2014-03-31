#include <IRremote.h>
#include <ArduinoProLibrary.h>

void setup()
{
  system_setup();
}

void loop()
{
  unsigned long cmd = irrm_get_cmd();
  
  if(cmd)
  {
    Serial.println(cmd, HEX);
  }
}
