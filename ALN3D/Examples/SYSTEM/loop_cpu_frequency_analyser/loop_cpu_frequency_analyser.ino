#include <ALN3D.h>
#include <SPI.h>

// setup
void setup()
{
  Serial.begin(115200);
  
  register_event(1, display_frequency);
  
  add_timer(1, 100);
  
  set_CPU_analyser();
  
  initialize_timers(1);
  
  Serial.println("CPU_use\tfrequency");
}

void loop()
{
  loop_last_measurement = micros();
  
  for(;;)
  {
    dequeue_loop();
  
    loop_counter++;
  }
}

// lors 
void display_frequency(void)
{  
  // on envoie
  Serial.print(CPU_use);
  Serial.print("\t");
  Serial.println(system_frequency);
}