#include <MsTimer2.h>

unsigned long s;

volatile unsigned long c;

void setup()
{
  Serial.begin(115200);
  
  MsTimer2::set(1000, display_frequency);
  MsTimer2::start();
}

void loop()
{
  s = millis();
  for(;;)
  {
    c++;
  }
}

void display_frequency(void)
{
  Serial.println((c * 1000) / (millis() - s));
}
