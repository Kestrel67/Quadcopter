// disconnect the USB2SERIAL board !!!!

#include <SPI.h>
#include <ALN3D.h>

void setup()
{
  Serial.begin(9600);
  set_serial_observer(FREQUENCY_20Hz);
  initialize_timers(1);
}

void loop()
{
  for(;;)
  {
    dequeue_loop();
  }
}
