#include <SPI.h>
#include <ArduinoProLibrary.h>

void setup()
{
  enable_timer0(TIMER0_PRESCALER8);
}

byte i = 1;

void loop()
{
  i++;
  
  i = i == 0 ? 1 : i;
  
  analogWrite(5, i);
  analogWrite(6, i);
  
  delay(200);
}
