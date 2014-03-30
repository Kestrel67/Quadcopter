#include <SPI.h>
#include <ALN3D.h>

// on affiche, la commande courante, le paramètre et la taille du buffer
void show_commands(void)
{
  char buf[80];
  
  sprintf(buf, "command:%d;parameter:%d;buffer:%d", current_cmd, attached_param, serial_buffer_size);
  
  Serial.println(buf);
}

void setup()
{
  Serial.begin(115200);
  
  // on enregistre l'évènement
  register_event(0, show_commands);
  
  // on met en place l'observer
  set_serial_observer(FREQUENCY_5Hz);
  
  // le timer d'affichage
  add_timer(0, FREQUENCY_5Hz);
  
  // on initialise les timers
  initialize_timers(1);
}

void loop()
{
  for(;;)
  {  // on traite les évènements
     dequeue_loop();
  } 
}
