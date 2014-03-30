#include <HCSR04.h>

#define ECHO 22
#define TRIG 24

HCSR04 SRO(ECHO, TRIG);

void setup()
{  
  Serial.begin(115200);
}

void loop()
{
  Serial.print(SRO.getDistanceMM());
  Serial.print(" mm = ");
  Serial.print(SRO.getDistance());
  Serial.println(" m");
  
  delay(100);
}