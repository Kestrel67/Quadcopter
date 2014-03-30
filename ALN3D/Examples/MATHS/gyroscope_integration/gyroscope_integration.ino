#include <SPI.h>
#include <ALN3D.h>

#define CALIB_FREQ FREQUENCY_50Hz
#define DISPLAY_FREQ FREQUENCY_20Hz

#define DELTA_ERR 0.05

SPIMaster Master;

void setup()
{
  Serial.begin(115200);
  
  Master = SPIMaster();
  
  MPU6000_Init(&Master);
  
  register_event(0, integration);
  register_event(1, serial);
  
  add_timer(0, CALIB_FREQ);
  add_timer(1, DISPLAY_FREQ);
  
  initialize_timers(1);
}

void loop()
{
  dequeue_loop();
}

double integ_roll;

double integ_pitch;

double integ_yaw;

unsigned long timeout;

unsigned long last_update;

void integration(void)
{
  MPU6000_Read();
  MPU6000_Corrections();
  Euler_Angles();
  
  if (abs(Omega[GYRO_X]) > 5)
  {
   integ_roll += (CALIB_FREQ / 1000.0) * Omega[GYRO_X] * GYRO_2000DPS_TO_SCALE_RAD;
  }
  
  if (abs(Omega[GYRO_Y]) > 5)
  {
    integ_pitch += (CALIB_FREQ / 1000.0) * - Omega[GYRO_Y] * GYRO_2000DPS_TO_SCALE_RAD;
  }
  
  integ_yaw += (CALIB_FREQ / 1000.0) * Omega[GYRO_Z] * GYRO_2000DPS_TO_SCALE_RAD;
  
  stabilisation();
}

void serial(void)
{
  Serial.print("accel : ");
  Serial.print(phi * RAD_TO_DEG);
  Serial.print("\t");
  Serial.print(theta * RAD_TO_DEG);
  Serial.print("\t\t gyro : ");
  Serial.print("roll : ");
  Serial.print(integ_roll * RAD_TO_DEG);
  Serial.print("\tpitch : ");
  Serial.print(integ_pitch * RAD_TO_DEG);
  Serial.print("\tyaw : ");
  Serial.println(integ_yaw * RAD_TO_DEG);
  /*
  Serial.print("euler : ");
  Serial.print(theta * RAD_TO_DEG);
  Serial.print("\t atan2 : ");
  Serial.print(atan2(accelY, accelZ) * RAD_TO_DEG);
  Serial.print("\t integ : ");
  Serial.println(integ);
  */
}

void serialEvent()
{
  integ_roll = 0;
  integ_pitch = 0;
  integ_yaw = 0;
  Serial.read();
}

void stabilisation(void)
{
  if (millis() - timeout > 5000000)
  {
    if (abs(Accel_Magnitude - 1) < DELTA_ERR)
    {
      
      float roll_error = (theta - integ_roll);
      float pitch_error = (phi - integ_pitch);
      
      float last_stab = (millis() - last_update) / 1000.0;
      
      integ_roll = theta;
      integ_pitch = phi;
      
      Serial.print("update : ");
      Serial.print("error : ");
      Serial.print(roll_error * RAD_TO_DEG);
      Serial.print("\t");
      Serial.print(pitch_error * RAD_TO_DEG);
      Serial.print("\t relative : ");
      Serial.print(roll_error / last_stab * RAD_TO_DEG);
      Serial.print("\t");
      Serial.println(pitch_error / last_stab * RAD_TO_DEG);
      
      last_update = millis();
    }
    timeout = millis();
  }
}