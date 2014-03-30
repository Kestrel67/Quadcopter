#include <SPI.h>
#include "ArduinoProLibrary.h"

SPISlave slave;
void setup(){
  
  Serial.begin(115200);
  
  slave = SPISlave();
  
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop(){
  for(;;)
  {
    if (reg_update(0))
    {
      analogWrite(6, reg_read(0));
    }
    
    if (reg_update(1))
    {
      digitalWrite(8, reg_read(1));
    }
  }
}

