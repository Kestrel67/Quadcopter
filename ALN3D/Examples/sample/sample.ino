#include <Wire.h>
#include <HMC5883L.h>
#include <SPI.h>
#include <ALN3D.h>

void setup()
{
  
}

void loop()
{
  for(;;)
  {
    dequeue_loop();
   
    loop_counter++; 
  }
}
