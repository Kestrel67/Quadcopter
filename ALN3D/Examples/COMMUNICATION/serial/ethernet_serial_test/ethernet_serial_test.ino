#include <ALN3D.h>

void setup()
{
  Serial.begin(115200);
  pinMode(9, OUTPUT);
}

boolean state = LOW;

void reverse()
{
  state = !state;
  digitalWrite(9, state);
}

void loop()
{
  
}

void serialEvent(void)
{
  int r = Serial.read();
  
  if (r == 0x6f)
  {
    reverse();
  }
  Serial.write(r);
  
}
