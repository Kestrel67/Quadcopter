#include <SPI.h>
#include <ALN3D.h>

// Slave Mega

#define LEDA 22
#define LEDB 24

SPISlave slave;

byte message;
byte reply;

void setup()
{
  Serial.begin(115200);
  
  slave = SPISlave();
  
  Serial.println("Slave Initiliazed");
  Serial.print("SS : ");
  Serial.println(SS);
  Serial.print("MISO : ");
  Serial.println(MISO);
  Serial.print("MOSI : ");
  Serial.println(MOSI);
  Serial.print("SCK : ");
  Serial.println(SCK);
  
  pinMode(LEDA, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void loop()
{
  
}

// SPI callback
ISR (SPI_STC_vect)
{
  // get de SPI message
  message = slave.get();
  
  // reply the message for the next request
  slave.reply(message);
  
  Serial.print("getted : ");
  Serial.print(message, BIN);
  
  // reverse LED A if LSB on
  if (message & 1)
  {
    digitalWrite(LEDA, !digitalRead(LEDA));
    Serial.print(" reverse LEDA");
  }
  
  // reverse LED A if second bit on
  if (message & 0b10)
  {
    digitalWrite(LEDB, !digitalRead(LEDB));
    Serial.print(" reverse LEDB");
  }
  
  Serial.println();
}
