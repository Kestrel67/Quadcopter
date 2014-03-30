#include <SPI.h>
#include "ArduinoProLibrary.h"

SPISlave slave;
void setup(){
  
  Serial.begin(115200);
  
  slave = SPISlave();
  
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop(){
  for(;;)
  {
    if (reg_update(0))
    {
      analogWrite(6, reg_read(0));
      Serial.print("modif 0 : ");
      Serial.println(reg_read(0));
    }
    
    if (reg_update(1))
    {
      analogWrite(9, reg_read(1));
      Serial.print("modif 1 : ");
      Serial.println(reg_read(1));
    }
    
  }
}

