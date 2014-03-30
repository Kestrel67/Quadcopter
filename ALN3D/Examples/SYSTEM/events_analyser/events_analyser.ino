#include <SPI.h>
#include <ALN3D.h>

// fonction d'affichage
void serial_displayer(void)
{
   char buf[80];
   
   sprintf(buf, "c:%d\tt:%d\to:%d", events_count, events_thrown, events_overflow);
   
   Serial.println(buf);
}

// callback
void callback(void)
{
  
}

void setup()
{
  Serial.begin(115200);
  
  // on enregistre les quelques évènements
  register_event(0, serial_displayer);
  register_event(1, callback);
  
  // les timers
  add_timer(0, 1000);
  add_timer(1, 15);
  
  // on initialise les timers
  initialize_timers(1);
}

void loop()
{
  // on traite les évènements
  for(;;) { dequeue_loop(); }
}
