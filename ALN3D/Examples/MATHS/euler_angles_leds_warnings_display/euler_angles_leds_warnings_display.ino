#include <Wire.h>
#include <SPI.h>
#include <HMC5883L.h>
#include <ALN3D.h>

#define RED 5
#define BLUE 6

int c = 0;

SPIMaster Master;

void setup()
{
  Master = SPIMaster();
	
  Serial.begin(115200);
  
  HMC5883L_Init();
  MPU6000_Init(&Master);
  
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{  
  MPU6000_Read();
  
  Euler_Angles();
  
  // la led rouge s'allume si l'angle est supérieur à 15 °
  if (psi * RAD_TO_DEG <= 75)
  {
    digitalWrite(RED, HIGH);
  }
  else
  {
    digitalWrite(RED, LOW);
  }
  
  // led bleu stabilisé
  if (psi * RAD_TO_DEG >= 80)
  {
    digitalWrite(BLUE, HIGH);
  }
  else
  {
    digitalWrite(BLUE, LOW);
  }
  
  char buf[80];
	Euler_Angles_Format(buf);
	Serial.print(buf);
	Serial.print("\tradius:");
	Serial.println(accelVectorLength#include <Wire.h>
#include <SPI.h>
#include <HMC5883L.h>
#include <ALN3D.h>

#define RED 5
#define BLUE 6

int c = 0;

SPIMaster Master;

void setup()
{
  Master = SPIMaster();
	
  Serial.begin(115200);
  
  HMC5883L_Init();
  MPU6000_Init(&Master);
  
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{  
  MPU6000_Read();
  
  Euler_Angles();
  
  // la led rouge s'allume si l'angle est supérieur à 15 °
  if (psi * RAD_TO_DEG <= 75)
  {
    digitalWrite(RED, HIGH);
  }
  else
  {
    digitalWrite(RED, LOW);
  }
  
  // led bleu stabilisé
  if (psi * RAD_TO_DEG >= 80)
  {
    digitalWrite(BLUE, HIGH);
  }
  else
  {
    digitalWrite(BLUE, LOW);
  }
  
  char buf[80];
	Euler_Angles_Format(buf);
	Serial.print(buf);
	Serial.print("\tradius:");
	Serial.println(Accel_Magnitude);
	
	delay(100);
}
