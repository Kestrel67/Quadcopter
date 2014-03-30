#include <SPI.h>
#include <ALN3D.h>

// on démarre la capture et on mesure la pulse
void trigger_pulse(void)
{
  // on génère le signal
  generate_pulse(13, 1);
  
  // on démarre la capture
  start_capture();
}

// affiche les résultats
void results(unsigned int counter, byte over)
{
  Serial.println(calculate_duration(counter, over)); // durée de la pulse en µs
}

void setup()
{
  Serial.begin(115200);
  
  pinMode(13, OUTPUT);
  
  // on initialise le timer1
  set_timer1_counter(PRESCALE_8, results);
  
  // on enregistre l'évènement de trigger
  register_event(0, trigger_pulse);
  
  // on active son timer
  add_timer(0, 500);
  
  Serial.println("Precision : ");
  Serial.println(timer1_precision);
  
  Serial.println("Pulse duration");
  
  // on initialise les timers
  initialize_timers(1);
}

void loop()
{
  dequeue_loop();
}
