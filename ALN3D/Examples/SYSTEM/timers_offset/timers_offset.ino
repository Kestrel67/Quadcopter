#include <SPI.h>
#include <ALN3D.h>

void a(void)
{
  digitalWrite(EMBEDED_LED_RED, !digitalRead(EMBEDED_LED_RED));
  Serial.println(TIMERS[1].remains);
}

void b(void)
{
  digitalWrite(EMBEDED_LED_BLUE, !digitalRead(EMBEDED_LED_BLUE));
  Serial.println(TIMERS[0].remains);
}


void setup()
{
  Serial.begin(115200);
  pinMode(EMBEDED_LED_RED, OUTPUT);
  pinMode(EMBEDED_LED_BLUE, OUTPUT);
  
  register_event(0, a);
  register_event(1, b);
  
  add_timer(0, 1000);
  Tiny_t i = add_timer(1, 1000);
  
  timer_offset(i, 500);
  
  initialize_timers(1);
}

void loop()
{
  dequeue_loop();
}
