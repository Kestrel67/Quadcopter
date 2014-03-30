#include <Wire.h>
#include <SPI.h>
#include <HMC5883L.h>
#include <ALN3D.h>

#define E_1 1
#define E_2 2

void func_e1(void)
{
  Serial.println(E_1);
}

void func_e2(void)
{
  Serial.println(E_2);
}

void setup()
{
  Serial.begin(115200);
  
  register_event(E_1, func_e1);
  register_event(E_2, func_e2);
  
  add_timer(E_1, FREQUENCY_1Hz);
  add_timer(E_2, FREQUENCY_2Hz);
  
  initialize_timers(MAIN_TIMER_MIN_PERIOD);
}

void loop()
{
  dequeue_loop();
}
