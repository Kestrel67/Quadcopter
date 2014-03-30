/*
 * MPU6000.cpp
 *
 *  Created on: 31 déc. 2013
 *      Author: Lucas
 */


MPU6000::MPU6000(SPIMaster *master)
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
    // attachInterrupt(0, MPU6000_data_int, RISING);
}

AccelerometerRow *MPU6000::getAccelerometerRow(void)
{
	AccelerometerRow accel_row;

	byte byte_H;
	byte byte_L;

	// Read AccelX
    byte_H = MPU6000_SPI_read(MPUREG_ACCEL_XOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_ACCEL_XOUT_L);

    accel_row.Xaxis = (byte_H<<8) | byte_L;

    // Read AccelY
    byte_H = MPU6000_SPI_read(MPUREG_ACCEL_YOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_ACCEL_YOUT_L);

    accel_row.Yaxis = (byte_H<<8) | byte_L;

    // Read AccelZ
    byte_H = MPU6000_SPI_read(MPUREG_ACCEL_ZOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_ACCEL_ZOUT_L);

    accel_row.Zaxis = (byte_H<<8) | byte_L;

    return &accel_row;
}

AccelerometerScaled *MPU6000::getAccelerometerScaled(void)
{
	AccelerometerRow *accel_row = getAccelerometerRow();

	AccelerometerScaled accel_scaled;

	accel_scaled.Xaxis = 2.0 * (accelX - G_ACCEL_X_MIN) / (G_ACCEL_X_MAX - G_ACCEL_X_MIN) - 1;

	accel_scaled.Yaxis = 2.0 * (accelY - G_ACCEL_Y_MIN) / (G_ACCEL_Y_MAX - G_ACCEL_Y_MIN) - 1;

	accel_scaled.Zaxis = 2.0 * (accelZ - G_ACCEL_Z_MIN) / (G_ACCEL_Z_MAX - G_ACCEL_Z_MIN) - 1;

	return &accel_scaled;
}

GyroscopeRow *MPU6000::getGyroscopeRow(void)
{
	GyroscopeRow gyro_row;

	byte byte_H;
	byte byte_L;

    // Read GyroX
    byte_H = MPU6000_SPI_read(MPUREG_GYRO_XOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_GYRO_XOUT_L);
    gyro_row.Xaxis = (byte_H<<8) | byte_L;

    // Read GyroY
    byte_H = MPU6000_SPI_read(MPUREG_GYRO_YOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_GYRO_YOUT_L);
    gyro_row.Yaxis = (byte_H<<8) | byte_L;

    // Read GyroZ
    byte_H = MPU6000_SPI_read(MPUREG_GYRO_ZOUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_GYRO_ZOUT_L);
    gyro_row.Zaxis = (byte_H<<8) | byte_L;

    return &gyro_row;
}

GyroscopeScaled *MPU6000::getGyroscopeScaled(void)
{
	GyroscopeRow *gyro_row = getGyroscopeRow();

	return GyroscopeScaled(gyro_row);
}

int MPU6000::getTemperatureRow(void)
{
	byte byte_H;
	byte byte_L;

    // Read Temp
    byte_H = MPU6000_SPI_read(MPUREG_TEMP_OUT_H);
    byte_L = MPU6000_SPI_read(MPUREG_TEMP_OUT_L);
    return (byte_H<<8) | byte_L;
}

int MPU6000::getTemperatureScaled(void)
{
	int temperature = getRemperatureRow();

	// calculating temperation in °Celcius
	return (temperature + 12412) / 340.0;
}

char *MPU6000::format(char *buffer)
{

}
