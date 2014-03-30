#include <MsTimer2.h>

unsigned long s;

volatile unsigned long c;

volatile float i;

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
    for(int r = 0; r <=8000; r++)
    {
      i = sin(c);
    }
    c++;
  }
}

void display_frequency(void)
{
  Serial.println((c * 1000) / (millis() - s));
}
