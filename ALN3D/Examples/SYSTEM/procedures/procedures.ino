#include <SPI.h>
#include <ALN3D.h>

#define RED_LED 5
#define BLUE_LED 6

// process function attached to task 1
bool msg1(unsigned int called)
{
  Serial.println("Task 1");
	
  // blinking RED led
  digitalWrite(RED_LED, called % 2);
  return called == 10;
}

// process function attached to task 2
bool msg2(unsigned int called)
{
  Serial.println("Task 2");
	
  // blinking BLUE led
  digitalWrite(BLUE_LED, called % 2);
  return called == 5;
}

bool blk(unsigned int called)
{
  Serial.println("Task 3");
	
  digitalWrite(RED_LED, called % 2);
  digitalWrite(BLUE_LED, (called + 1) % 2);

  return called == 31;
}

bool msg4(unsigned int called)
{
  Serial.println("task 4, ending procedure");
  
  // fin de la procédure
  //return true;
  
  // on reset la tache
  reset_procedure();
  
  return false;
}

bool off(unsigned int called)
{
  Serial.println("turn leds off");
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  return true;
}


// we create 2 tasks
Task_t t1 = {msg1, 250};
Task_t t2 = {msg2, 750};
Task_t tblink = {blk, 75};
Task_t t4 = {msg4, 0};
Task_t toff = {off, 0};

// we store tasks into an array
Task_t *PROC_ARRAY[7] = {&t1, &tblink, &toff, &t2, &tblink, &toff, &t4};

// new procedure
Procedure proc(PROC_ARRAY, 7);


void setup()
{
  Serial.begin(115200);
  
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  
  // on enregistre les procédures  
  register_procedure(&proc);
  
  // on initialise le gestionnaire des procédures
  initialize_procedures();
  
  // on initialise le timer principal
  initialize_timers(1);
  
  // on utilise la seul procédure créé
  use_procedure(&proc);
}

void loop()
{
  // on traite les évènements
  dequeue_loop();
}

// lors d'un appel serial
void serialEvent()
{
  Serial.read();
  
  // on reset la procédure
  reset_procedure();
}