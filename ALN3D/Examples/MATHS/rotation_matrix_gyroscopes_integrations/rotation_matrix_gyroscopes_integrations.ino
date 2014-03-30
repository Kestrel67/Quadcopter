#include <SPI.h>
#include <ALN3D.h>

#define INTEG_FREQ FREQUENCY_100Hz
#define CALCUL_FREQ FREQUENCY_100Hz

fVector_t IOmega = {0.0, 0.0, 0.0};
fVector_t g = {0.0, 0.0, -1.0};
fMatrix_t Mtemp, R;

void integ(void)
{
  MPU6000_Read();
  MPU6000_Corrections();
  MPU6000_Scale();
  
  IOmega[X] += Omega[X] * INTEG_FREQ / 1000.0;
  IOmega[Y] += Omega[Y] * INTEG_FREQ / 1000.0;
  IOmega[Z] += Omega[Z] * INTEG_FREQ / 1000.0;
}

void calculate(void){
  
  float phi = IOmega[Y], psi = IOmega[Z], theta = IOmega[X];
  
  // phi
  fMatrix_t Mphi = {
    {cos(phi), 0, -sin(phi)},
    {0, 1, 0},
    {sin(phi), 0, cos(phi)}
  };
  
  // psi
  fMatrix_t Mpsi = {
    {cos(psi), -sin(psi), 0},
    {sin(psi), cos(psi), 0},
    {0, 0, 1}
  };
  
  // theta
  fMatrix_t Mtheta = {
    {1, 0, 0},
    {0, cos(theta), -sin(theta)},
    {0, sin(theta), cos(theta)}
  };
  
  Matrix_Multiply(Mphi, Mpsi, Mtemp);
  Matrix_Multiply(Mtemp, Mtheta, R);
  
  fVector_t Out;
  Vector_Apply_Matrix(R, g, Out);
  
  g[X] = Out[X];
  g[Y] = Out[Y];
  g[Z] = Out[Z];
  
  IOmega[X] = IOmega[Y] = IOmega[Z] = 0;
}

void display_r(void)
{
  
  //Python_Matrix_Display(R);
  //Vector_Display(IOmega);
  Vector_Display(g);
}

void setup()
{
  Serial.begin(115200);
  
  SPIMaster master;
  
  MPU6000_Init(&master);
  
  MPU6000_Gyro_Calibration();
  
  register_event(0, integ);
  register_event(1, display_r);
  register_event(2, calculate);
  add_timer(0, INTEG_FREQ);
  add_timer(1, FREQUENCY_1Hz);
  add_timer(2, CALCUL_FREQ);
  
  initialize_timers();
}

void loop()
{
  for(;;)
  {
    dequeue_loop();
  }
}