/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

// global variables
volatile uint8_t MPU6000_newdata;

// corrections à apporter aux gyroscopes
Vector_t Omega_Gap = {GYRO_X_GAP, GYRO_Y_GAP, GYRO_Z_GAP};

// temperature
float temperature;

// MPU6000 support for ArduIMU V3
#include <SPI.h>

/**
 *	Lit une valeur SPI (MPU6000)
 *	@param byte reg
 *	@param byte return_value
 */
byte MPU6000_SPI_read(byte reg)
{
  byte return_value;
	
  digitalWrite(MPU6000_CHIP_SELECT_PIN, LOW);
	
  SPI.transfer(reg | 0x80); // Set most significant bit as address
  return_value = SPI.transfer(0);
	
  digitalWrite(MPU6000_CHIP_SELECT_PIN, HIGH);
	
  return(return_value);
}

/**
 *	Ecrit une donnée SPI (MPU6000)
 *	@param byte reg
 *	@param byte data
 */
void MPU6000_SPI_write(byte reg, byte data)
{
  digitalWrite(MPU6000_CHIP_SELECT_PIN, LOW);
	
  SPI.transfer(reg);
  SPI.transfer(data);
	
  digitalWrite(MPU6000_CHIP_SELECT_PIN, HIGH);
}

/**
 *	Incrémente le compteur de nouvelles datas, lors d'une interruption sur int0
 */
void MPU6000_data_int()
{
  MPU6000_newdata++;
}

/**
 *	Initilisation et configuration du MPU6000
 */
void MPU6000_Init(SPIMaster *Master)
{
    // déclaration du nouveau slave
    Master->addSlave(MPU6000_CHIP_SELECT_PIN);
		
	// configuration
	delay(10);
    
    // Chip reset
    MPU6000_SPI_write(MPUREG_PWR_MGMT_1, BIT_H_RESET);
    delay(100);
	
    // Wake up device and select GyroZ clock (better performance)
    MPU6000_SPI_write(MPUREG_PWR_MGMT_1, MPU_CLK_SEL_PLLGYROZ);
    delay(1);

    // Disable I2C bus (recommended on datasheet)
    MPU6000_SPI_write(MPUREG_USER_CTRL, BIT_I2C_IF_DIS);
    delay(1);
	
    // SAMPLE RATE
    //MPU6000_SPI_write(MPUREG_SMPLRT_DIV,0x04);     // Sample rate = 200Hz    Fsample= 1Khz/(4+1) = 200Hz     
    MPU6000_SPI_write(MPUREG_SMPLRT_DIV,  19);     // Sample rate = 50Hz    Fsample= 1Khz/(19+1) = 50Hz
    delay(1);
	
    // DLPF   DLPF = 20Hz (low pass filter)
    MPU6000_SPI_write(MPUREG_CONFIG, BITS_DLPF_CFG_20HZ);
    delay(1);
	
    // FS FS=2000º/s,
    MPU6000_SPI_write(MPUREG_GYRO_CONFIG, BITS_FS_2000DPS);  // Gyro scale 2000º/s
    delay(1);
	
    MPU6000_SPI_write(MPUREG_ACCEL_CONFIG, BITS_FS_4G);            // Accel scale 4g
    delay(1);   
    // INT CFG => Interrupt on Data Ready
    MPU6000_SPI_write(MPUREG_INT_ENABLE, BIT_RAW_RDY_EN);         // INT: Raw data ready
    delay(1);
	
    MPU6000_SPI_write(MPUREG_INT_PIN_CFG, BIT_INT_ANYRD_2CLEAR);  // INT: Clear on any read
    delay(1);
    // Oscillator set
    // MPU6000_SPI_write(MPUREG_PWR_MGMT_1, MPU_CLK_SEL_PLLGYROZ);
    delay(1);
  
    // MPU_INT is connected to INT 0. Enable interrupt on INT0
    attachInterrupt(0, MPU6000_data_int, RISING);
}

// Read gyros and accel sensors on MPU6000
void MPU6000_Read()
{
  int byte_H;
  int byte_L;
  
	// Read AccelX
    byte_H = MPU6000_SPI_read(MPUREG_ACCEL_XOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_ACCEL_XOUT_L);
    Accel[ACCEL_X] = +( (byte_H<<8) | byte_L );
	
    // Read AccelY
    byte_H = MPU6000_SPI_read(MPUREG_ACCEL_YOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_ACCEL_YOUT_L);
    Accel[ACCEL_Y] = -( (byte_H<<8) | byte_L );
	
    // Read AccelZ
    byte_H = MPU6000_SPI_read(MPUREG_ACCEL_ZOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_ACCEL_ZOUT_L);
    Accel[ACCEL_Z] = -( (byte_H<<8) | byte_L );
    
    // Read Temp
    byte_H = MPU6000_SPI_read(MPUREG_TEMP_OUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_TEMP_OUT_L);
    temperature = (byte_H<<8) | byte_L; 
	
	// calculating temperation in °Celcius
	temperature = (temperature + 12412) / 340.0;
	
	/*********** DEFAULT *************/
	// The temperature sensor is -40 to +85 degrees Celsius.
	// It is a signed integer.
	// According to the datasheet: 
	//   340 per degrees Celsius, -512 at 35 degrees.
	// At 0 degrees: -512 - (340 * 35) = -12412

	/*
	  Serial.print(F("temperature: "));
	  dT = ( (double) temperature + 12412.0) / 340.0;
	  Serial.print(dT, 3);
	  Serial.print(F(" degrees Celsius"));
	  Serial.println(F(""));
	*/
     
    // Read GyroX
    byte_H = MPU6000_SPI_read(MPUREG_GYRO_XOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_GYRO_XOUT_L);
    Omega[GYRO_X] = (byte_H<<8) | byte_L;
	
    // Read GyroY
    byte_H = MPU6000_SPI_read(MPUREG_GYRO_YOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_GYRO_YOUT_L);
    Omega[GYRO_Y] = (byte_H<<8) | byte_L;
	
    // Read GyroZ
    byte_H = MPU6000_SPI_read(MPUREG_GYRO_ZOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_GYRO_ZOUT_L);
    Omega[GYRO_Z] = (byte_H<<8) | byte_L;
}

void MPU6000_Corrections_Scale(void)
{
	// gyroscopes
	Omega[GYRO_X] = (Omega[GYRO_X] + Omega_Gap[X]) * GYRO_2000DPS_TO_SCALE_RAD;
	Omega[GYRO_Y] = (Omega[GYRO_Y] + Omega_Gap[Y]) * GYRO_2000DPS_TO_SCALE_RAD;
	Omega[GYRO_Z] = (Omega[GYRO_Z] + Omega_Gap[Z]) * GYRO_2000DPS_TO_SCALE_RAD;

	// accéléromètres
#if ACCELEROMETER_CIRCLE_SCALE == 0
	// valeur en G
	const int fscale = pow(2, 13);
	Accel[X] = map(Accel[X], G_ACCEL_X_MIN, G_ACCEL_X_MAX, -fscale, fscale) * ACCEL_4G_TO_SCALE_G;
	Accel[Y] = map(Accel[Y], G_ACCEL_Y_MIN, G_ACCEL_Y_MAX, -fscale, fscale) * ACCEL_4G_TO_SCALE_G;
	Accel[Z] = map(Accel[Z], G_ACCEL_Z_MIN, G_ACCEL_Z_MAX, -fscale, fscale) * ACCEL_4G_TO_SCALE_G;
#else

	// valeur de -1 à 1 (normal);
	Accel[X] = toCircleScale(Accel[X], G_ACCEL_X_MIN, G_ACCEL_X_MAX);
	Accel[Y] = toCircleScale(Accel[Y], G_ACCEL_Y_MIN, G_ACCEL_Y_MAX);
	Accel[Z] = toCircleScale(Accel[Z], G_ACCEL_Z_MIN, G_ACCEL_Z_MAX);
#endif
}

void MPU6000_Gyro_Calibration(void)
{
	delay(MPU6000_CALIBRATION_START_DELAY);

	Omega_Gap[X] = Omega_Gap[Y] = Omega_Gap[Z] = 0;

	int sum_x = 0, sum_y = 0, sum_z = 0;

	average_gravity_magnitude = 0;

	for(uint8_t i = 0; i < MPU6000_CALIBRATION_ITERATIONS; i++)
	{
		MPU6000_Read();

		sum_x += Omega[X];
		sum_y += Omega[Y];
		sum_z += Omega[Z];

		MPU6000_Corrections_Scale();

		average_gravity_magnitude += Vector_Magnitude(Accel);

		delay(MPU6000_CALIBRATION_DELAY);
	}

	average_gravity_magnitude /= MPU6000_CALIBRATION_ITERATIONS;

	Omega_Gap[X] = - round(float(sum_x) / MPU6000_CALIBRATION_ITERATIONS);
	Omega_Gap[Y] = - round(float(sum_y) / MPU6000_CALIBRATION_ITERATIONS);
	Omega_Gap[Z] = - round(float(sum_z) / MPU6000_CALIBRATION_ITERATIONS);
}

void MPU6000_Format(char *buffer)
{	
	sprintf(buffer, "accel:\tX:%f\tY:%f\tZ:%f\t\tgyro\tX:%f\tY:%f\tZ:%f\t\tT:%f", Accel[ACCEL_X], Accel[ACCEL_Y], Accel[ACCEL_Z], Omega[GYRO_X], Omega[GYRO_Y], Omega[GYRO_Z], temperature);
}
