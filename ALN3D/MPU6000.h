/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef MPU_h
#define MPU_h

/**
 * Configuration
 */
#define ACCELEROMETER_CIRCLE_SCALE 0

/**
 * accelerometers vector access constants
 */
#define ACCEL_X 0
#define ACCEL_Y 1
#define ACCEL_Z 2

/**
 * gyroscopes vector access constants
 */
#define GYRO_X 0
#define GYRO_Y 1
#define GYRO_Z 2

/**
 * période entre chaque intégration
 */
#define GYRO_INTEG_FREQ FREQUENCY_50Hz

/**
 * Corrections à apporter aux gyroscopes
 */
extern Vector_t Omega_Gap;

/**
 *	Température en degrée Celcius °C
 */
extern float temperature;

// convert the accelerometer value (Full scale = FS = 4g) to gravity vector m.s^-2
#define ACCEL_4G_TO_SCALE_G 0.00121
// example : ACCEL_X * ACCEL_4G_TO_SCALE_G = m.s^-2


// convert the gyrocope value (Full scale = FS = 2000DPS) to 1 degree per second 1°/s
// example : GYRO_X * GYRO_2000DPS_TO_SCALE_D = °/s
//
// 2000 dps <-> 32768
// x <-> 1
//
// <=> x = 2000/32768 = 0.06103515625 (degree)
// <=> x = 2000/32768 / 180 * pi (rad)
#define GYRO_250DPS_TO_SCALE_DEG 0.00762939453
#define GYRO_250DPS_TO_SCALE_RAD 0.00013315805 // 45039619

#define GYRO_500DPS_TO_SCALE_DEG 0.01525878906
#define GYRO_500DPS_TO_SCALE_RAD 0.00026631610 // 0079238

#define GYRO_1000DPS_TO_SCALE_DEG 0.03051757812
#define GYRO_1000DPS_TO_SCALE_RAD 0.00053263221 // 80158476

#define GYRO_2000DPS_TO_SCALE_DEG 0.06103515625
#define GYRO_2000DPS_TO_SCALE_RAD 0.00106526443 // 60316951

// sclae utilisé
#define GYRO_SCALED_USED GYRO_2000DPS_TO_SCALE_RAD


// MPU6000 CHIP SELECT (sur l'IMU)
#define MPU6000_CHIP_SELECT_PIN 4

// MPU 6000 registers
#define MPUREG_WHOAMI 0x75
#define	MPUREG_SMPLRT_DIV 0x19
#define MPUREG_CONFIG 0x1A

#define MPUREG_GYRO_CONFIG 0x1B
#define MPUREG_ACCEL_CONFIG 0x1C

#define MPUREG_INT_PIN_CFG 0x37
#define	MPUREG_INT_ENABLE 0x38 

#define MPUREG_ACCEL_XOUT_H 0x3B
#define MPUREG_ACCEL_XOUT_L 0x3C
#define MPUREG_ACCEL_YOUT_H 0x3D
#define MPUREG_ACCEL_YOUT_L 0x3E
#define MPUREG_ACCEL_ZOUT_H 0x3F
#define MPUREG_ACCEL_ZOUT_L 0x40

#define MPUREG_TEMP_OUT_H 0x41
#define MPUREG_TEMP_OUT_L 0x42

#define MPUREG_GYRO_XOUT_H 0x43
#define	MPUREG_GYRO_XOUT_L 0x44
#define MPUREG_GYRO_YOUT_H 0x45
#define	MPUREG_GYRO_YOUT_L 0x46
#define MPUREG_GYRO_ZOUT_H 0x47
#define	MPUREG_GYRO_ZOUT_L 0x48

#define MPUREG_USER_CTRL 0x6A

#define	MPUREG_PWR_MGMT_1 0x6B
#define	MPUREG_PWR_MGMT_2 0x6C



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
#define	BIT_RAW_RDY_EN		    	0x01
#define	BIT_I2C_IF_DIS              0x10

/**
 * Nouvelle données (interruption, pin 10)
 */
extern volatile uint8_t MPU6000_newdata;

/**
 *	Lit une donnée SPI
 *	@param byte reg : registre
 *	@return byte return_value
 */
byte MPU6000_SPI_read(byte reg);

/**
 *	Ecrit une donnée de configuration
 *	@param byte reg : registre
 *	@param byte data : donnée
 */
void MPU6000_SPI_write(byte reg, byte data);

/**
 *	Nouvelles valeurs disponible, interruption
 */
void MPU6000_data_int(void);

/**
 *	Lis les valeurs des accéléromètres, des gyroscopes et de la température
 *	@var dans MPU6000.h
 */
void MPU6000_Read(void);

/**
 *	Initialise le MPU6000, liaison SPI et configuration composant
 */
void MPU6000_Init(SPIMaster *Master);

/**
 *	Corrige et met à l'echelle les valeurs des gysocopes et accéléromètres
 */
void MPU6000_Corrections_Scale(void);

/**
 * On calibre les valeurs des gyroscopes
 */
void MPU6000_Gyro_Calibration(void);

/**
 * Intégrateur des gyroscopes
 */
void MPU6000_Integrator(void);

/**
 *	Formate les données pour affichage
 */
void MPU6000_Format(char *buffer);

#endif
