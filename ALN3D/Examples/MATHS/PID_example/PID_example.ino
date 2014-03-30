#include <SPI.h>
#include <ALN3D.h>

#define FREQ 10

void setup()
{
  Serial.begin(115200);
  
  SetOutputLimits(0, 255);
  SetTunings(0.5, 0.5, 0.005);
  SetSampleTime(FREQ);
  SetMode(AUTOMATIC);
  
  Setpoint = 150;
  
  Initialize();
}

void loop()
{
  Input = analogRead(0) >> 2;
  
  Compute();
  
  Serial.print("input : ");
  Serial.print(Input);
  Serial.print("\t output : ");
  Serial.println(Output);
  
  
  delay(1.0/FREQ * 1000);
}