#include <SPI.h>
#include <ALN3D.h>

void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  initialize_timers(1);
  
  Serial.println("type something through the serial port and see the led blinking");
}

void loop()
{
  dequeue_loop();
}

void serialEvent(void)
{
  Serial.read();
    
  Serial.println(generate_pulse(13, 150));
}
