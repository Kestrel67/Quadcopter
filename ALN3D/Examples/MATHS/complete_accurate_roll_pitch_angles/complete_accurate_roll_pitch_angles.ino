#include <SPI.h>
#include <ALN3D.h>

#define CALCUL_FREQ INTEG_FREQ

void angles(void)
{
  MPU6000_Read();
  MPU6000_Corrections_Scale(); 
  Gyroscopes_Integration();
  Normalize();
}

void display_r(void)
{
  
  Serial.print(millis() / 1000.0);
  Serial.print(";");
  Serial.print(phi * RAD_TO_DEG);
  Serial.print(";");
  Serial.println(theta * RAD_TO_DEG);
  
}

void setup()
{
  Serial.begin(115200);
  
  SPIMaster master;
  
  MPU6000_Init(&master);
  
  register_event(0, angles);
  register_event(1, display_r);
  add_timer(0, FREQUENCY_GYRO_INTEGRATION);
  add_timer(1, FREQUENCY_10Hz);
  
  MPU6000_Gyro_Calibration();
  Apply_Accelerometers_Angles();
  
  pinMode(8, OUTPUT);
  
  initialize_timers();
}

void loop()
{
  for(;;)
  {
    
    dequeue_loop();
    digitalWrite(8, !digitalRead(8));
  }
}
