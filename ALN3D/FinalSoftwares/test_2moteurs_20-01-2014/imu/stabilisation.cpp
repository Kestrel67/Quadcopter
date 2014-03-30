#if defined(ALN3D_h)

unsigned long c;

// stabilisation
void stabilisation(void)
{
  MPU6000_Read();
  Euler_Angles();
  Serial.print(".");
  
  AP_write(1, c++ % 256);
}

#endif
