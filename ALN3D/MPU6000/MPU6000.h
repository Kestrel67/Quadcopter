/*
 * MPU6000.h
 *
 *  Created on: 31 déc. 2013
 *      Author: Lucas
 *
 * Static Configuration
 * - accel : 4g
 * - gyro : 2000dps
 */

#ifndef MPU6000_H_
#define MPU6000_H_

/** SETTINGS **/

// corrections for IMU (1)

// static analysing :

// gyroscopes drift correction
#define GYRO_X_GAP 94
#define GYRO_Y_GAP 10
#define GYRO_Z_GAP -9

// temperature
#define TEMPERATURE_GAP -6

// gravity - IMU 1
#define G_ACCEL_X_MIN -8000
#define G_ACCEL_X_MAX 8560
#define G_ACCEL_Y_MIN -8230
#define G_ACCEL_Y_MAX 8100
#define G_ACCEL_Z_MIN -8600
#define G_ACCEL_Z_MAX 8200

// gravity - IMU 2

#define GRAVITY 8192

/**
 * To scale
 */
#define ACCEL_4G_TO_SCALE_G 1.21 // convert the accelerometer value (Full scale = FS = 4g) to gravity vector m.s^-2
// example : ACCEL_X * ACCEL_4G_TO_SCALE_G = m.s^-2

#define GYRO_2000DPS_TO_SCALE_D 0.0152 // convert the gyrocope value (Fule scale = FS = 2000DPS) to 1 degree per second 1°/s
// example : GYRO_X * GYRO_2000DPS_TO_SCALE_D = °/s

/** END SETTINGS **/






/** CONSTANTS **/

// MPU6000 CHIP SELECT
#define MPU6000_CHIP_SELECT_PIN 4

// MPU 6000 registers
#define MPUREG_WHOAMI 0x75 //
#define	MPUREG_SMPLRT_DIV 0x19 //
#define MPUREG_CONFIG 0x1A //

#define MPUREG_GYRO_CONFIG 0x1B
#define MPUREG_ACCEL_CONFIG 0x1C

#define MPUREG_INT_PIN_CFG 0x37
#define	MPUREG_INT_ENABLE 0x38

#define MPUREG_ACCEL_XOUT_H 0x3B //
#define MPUREG_ACCEL_XOUT_L 0x3C //
#define MPUREG_ACCEL_YOUT_H 0x3D //
#define MPUREG_ACCEL_YOUT_L 0x3E //
#define MPUREG_ACCEL_ZOUT_H 0x3F //
#define MPUREG_ACCEL_ZOUT_L 0x40 //

#define MPUREG_TEMP_OUT_H 0x41//
#define MPUREG_TEMP_OUT_L 0x42//

#define MPUREG_GYRO_XOUT_H 0x43 //
#define	MPUREG_GYRO_XOUT_L 0x44 //
#define MPUREG_GYRO_YOUT_H 0x45 //
#define	MPUREG_GYRO_YOUT_L 0x46 //
#define MPUREG_GYRO_ZOUT_H 0x47 //
#define	MPUREG_GYRO_ZOUT_L 0x48 //

#define MPUREG_USER_CTRL 0x6A //

#define	MPUREG_PWR_MGMT_1 0x6B //
#define	MPUREG_PWR_MGMT_2 0x6C //

// Configuration bits  MPU 6000
#define BIT_SLEEP 0x40
#define BIT_H_RESET 0x80
#define BITS_CLKSEL 0x07

#define MPU_CLK_SEL_PLLGYROX 0x01
#define MPU_CLK_SEL_PLLGYROZ 0x03
#define MPU_EXT_SYNC_GYROX 0x02

#define BITS_FS_250DPS              0x00
#define BITS_FS_500DPS              0x08
#define BITS_FS_1000DPS             0x10
#define BITS_FS_2000DPS             0x18

#define BITS_FS_2G					0
#define BITS_FS_4G					B1000
#define BITS_FS_8G					B00010000
#define BITS_FS_16G					B00011000

#define BITS_FS_MASK                0x18
#define BITS_DLPF_CFG_256HZ_NOLPF2  0x00
#define BITS_DLPF_CFG_188HZ         0x01
#define BITS_DLPF_CFG_98HZ          0x02
#define BITS_DLPF_CFG_42HZ          0x03
#define BITS_DLPF_CFG_20HZ          0x04
#define BITS_DLPF_CFG_10HZ          0x05
#define BITS_DLPF_CFG_5HZ           0x06
#define BITS_DLPF_CFG_2100HZ_NOLPF  0x07
#define BITS_DLPF_CFG_MASK          0x07

#define	BIT_INT_ANYRD_2CLEAR	    0x10
#define	BIT_RAW_RDY_EN		    0x01
#define	BIT_I2C_IF_DIS              0x10


/** END CONSTANTS **/

struct AccelerometerRow
{
	int Xaxis;
	int Yaxis;
	int Zaxis;
};

struct AccelerometerScaled
{
	int Xaxis;
	int Yaxis;
	int Zaxis;
};

struct GyroscopeRow
{
	int Xaxis;
	int Yaxis;
	int Zaxis;
};

struct GyroscopeScaled
{
	int Xaxis;
	int Yaxis;
	int Zaxis;
};


class MPU6000
{
public:
	MPU6000(SPIMaster *master);

	AccelerometerRow *getAccelerometerRow(void);

	AccelerometerScaled *getAccelerometerScaled(void);

	GyroscopeRow *getGyroscopeRow(void);

	GyroscopeScaled *getGyroscopeScaled(void);

	int getTemperatureRow(void);

	int getTemperatureScaled(void);

protected:
	void Write(byte reg, byte data);
	byte Read(byte reg);

};


#endif /* MPU6000_H_ */
