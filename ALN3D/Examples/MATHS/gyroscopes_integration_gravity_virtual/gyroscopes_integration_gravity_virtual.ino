#include <SPI.h>
#include <ALN3D.h>

void angles(void)
{
  MPU6000_Read();
  MPU6000_Corrections_Scale(); 
  Gyroscopes_Integration();
  
  // on met à jour la matrice de rotation
  update_rotation_matrix(IOmega[Y], IOmega[X], IOmega[Z]);
  
  // on applique la matrice de rotation à Gravity
  apply_rotation_matrix(Gravity);
  
  // variables d'integrations à 0
  IOmega[X] = IOmega[Y] = IOmega[Z] = 0;
}

void display_r(void)
{
  Vector_Display(Gravity);
}

void setup()
{
  Serial.begin(115200);
  
  SPIMaster master;
  
  MPU6000_Init(&master);
  
  register_event(0, angles);
  register_event(1, display_r);
  add_timer(0, FREQUENCY_50Hz);
  add_timer(1, FREQUENCY_10Hz);
  
  IMU_Init();
  
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
