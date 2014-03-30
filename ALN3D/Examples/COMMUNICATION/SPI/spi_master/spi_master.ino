#include <SPI.h>
#include <ALN3D.h>

// Master Ethernet

SPIMaster master;

void setup()
{  
  Serial.begin(115200);
  
  master = SPIMaster();
  
  Serial.println("Master initiliazed");
  Serial.print("SS : ");
  Serial.println(SS);
  Serial.print("MISO : ");
  Serial.println(MISO);
  Serial.print("MOSI : ");
  Serial.println(MOSI);
  Serial.print("SCK : ");
  Serial.println(SCK);
  
  master.addSlave(SS);
}

void loop()
{
  // listen to the serial port
  if (Serial.available())
  {
    // read the incoming byte
    byte data = Serial.read();
  
    // send the byte
    byte reply = master.send(SS, data);
    
    Serial.print("sended : ");
    Serial.print(data, BIN);
    Serial.print(" received : ");
    Serial.println(reply, BIN);
  }
}
