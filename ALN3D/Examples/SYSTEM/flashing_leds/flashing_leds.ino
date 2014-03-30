#include <SPI.h>
#include <ALN3D.h>

#define LED1 22
#define LED2 24
#define LED3 26
#define LED4 28
#define LED5 30
#define LED6 32

#define LEDA 13

// status des leds au début
boolean led1 = HIGH;
boolean led2 = HIGH;
boolean led3 = HIGH;
boolean led4 = HIGH;
boolean led5 = HIGH;
boolean led6 = HIGH;
boolean leda = HIGH;

// fonctions callback des leds
void func(void)
{
  led1 = !led1;
  digitalWrite(LED1, led1);
}

void func2(void)
{
  led2 = !led2;
  digitalWrite(LED2, led2);
}

void func3(void)
{
  led3 = !led3;
  digitalWrite(LED3, led3);
}

void func4(void)
{
  led4 = !led4;
  digitalWrite(LED4, led4);
}

void func5(void)
{
  led5 = !led5;
  digitalWrite(LED5, led5);
}

void func6(void)
{
  led6 = !led6;
  digitalWrite(LED6, led6);
}

void funca(void)
{
  leda = !leda;
  digitalWrite(LEDA, leda);
}

void setup()
{
	// outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LEDA, OUTPUT);
  
  // on enregistre les évènement et leur callback
  register_event(1, func);
  register_event(2, func2);
  register_event(3, func3);
  register_event(4, func4);
  register_event(5, func5);
  register_event(6, func6);
  register_event(7, funca);
  
  // appel fonction initilisation des leds
  func();
  func2();
  func3();
  func4();
  func5();
  func6();
  funca();
  
  // initilisation du timer à 1000Hz Max
  initialize_timers(1);
  
  // que des nombres premiers, pour éviter au max que 2 leds 
  // apparaissent en même temps pour montre l'éfficacité des timers
  // 		   MS		FREQUENCY	REAL (/2 car la led s'étaiens et s'allume)
  
  /*
  add_timer(1, 7);	//	142.86 Hz	/2
  add_timer(2, 47); //	21.28 Hz	/2
  add_timer(3, 71);//	14.08 Hz	/2
  add_timer(4, 127);//	7.87 Hz		/2
  add_timer(5, 227);//	4.41 Hz		/2
  add_timer(6, 701);//	1.43 Hz		/2
  */
  
  /* SINON */
  add_timer(1, 5);
  add_timer(2, 10);
  add_timer(3, 20);
  add_timer(4, 40);
  add_timer(5, 80);
  add_timer(6, 160);
  add_timer(7, 320);
  /* */
}

void loop()
{
  dequeue_loop();
}
