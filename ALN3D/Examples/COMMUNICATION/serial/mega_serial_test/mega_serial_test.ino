#include <ALN3D.h>

#define RATE 115200

// test des ports séries, quand on envoie unm msg depuis le PC on envoie la donnée depuis Serial1 to Serial2 quand serial 2 detecte une donnée on la retransmet à Serial au PC

int c = 0;

boolean led1 = HIGH;

// fonctions callback d'évènements
void func(void)
{
  led1 = !led1;
  digitalWrite(22, led1);
}


void setup()
{
  Serial.begin(RATE);
  Serial1.begin(RATE);
  
  pinMode(22, OUTPUT);
  
  // on enregistre les évènement et leur callback
  register_event(1, func);
  
  func();
  
  initialize_timers(100);
  
  add_timer(1, 1000);
}

void loop()
{
  dequeue_loop();
}

void serialEvent()
{
  Serial1.write(Serial.read());
}

void serialEvent1()
{
  c++;
  Serial.print(Serial1.read(), HEX);
  Serial.println(" - " + String (c));
}
