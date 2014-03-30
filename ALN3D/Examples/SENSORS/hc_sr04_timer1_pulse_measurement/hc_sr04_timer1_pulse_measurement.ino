#include <SPI.h>
#include <ALN3D.h>

void display_altitude(void)
{
  Serial.print("altitude : ");
  Serial.print(distance / 10.0, 1);
  Serial.println(" cm");
}

void setup()
{
   Serial.begin(115200);
   
   register_event(1, display_altitude);
   add_timer(1, FREQUENCY_2Hz);
   
   initialize_hc_sr04(PWM0);
   
   initialize_timers(1);
}

void loop()
{
  dequeue_loop();
}
