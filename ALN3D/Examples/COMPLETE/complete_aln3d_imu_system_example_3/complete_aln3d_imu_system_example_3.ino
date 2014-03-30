// inclusions
#include <Wire.h>
#include <SPI.h>
#include <HMC5883L.h>
#include <ALN3D.h>

#include "constants.h"

#define MAX 0
#if MAX == 0
#include "freq.h"
#else
#include "freqm.h"
#endif

void gyro_accel_process(void);
void update_led_position(void);
void serial_display(void);

void setup()
{
        digitalWrite(EMBEDED_LED_RED, HIGH);
        setup_start();

	IO_init();

	SPIMaster Master = SPIMaster();

	Serial.begin(115200);

	MPU6000_Init(&Master);

	AP_init(&Master);

	HMC5883L_Init();

	initialize_hc_sr04(PWM1);

        set_serial_observer(SERIAL_OBSERVER_PERIOD);

	register_event(EV_INTEGRATE, gyro_accel_process);

        gyro_integration_period = EV_INTEGRATE_FREQUENCY;

	register_event(EV_CALCULATE_ANGLES, Normalize);
	register_event(EV_MAGNETOMETERS, HMC5883L_Read);
	register_event(EV_UPDATE_LED_POSITION, update_led_position);
        register_event(EV_DISPLAY_DATA, serial_display);
        
        set_CPU_analyser(CPU_ANALYSER_FREQUENCY);

        add_timer(EV_INTEGRATE, EV_INTEGRATE_FREQUENCY);
        add_timer(EV_CALCULATE_ANGLES, EV_CALCULATE_ANGLES_FREQUENCY);
        add_timer(EV_MAGNETOMETERS, EV_MAGNETOMETERS_FREQUENCY);
        add_timer(EV_UPDATE_LED_POSITION, EV_UPDATE_LED_POSITION_FREQUENCY);
        add_timer(EV_DISPLAY_DATA, EV_DISPLAY_DATA_FREQUENCY);
        
        // calibration
        MPU6000_Gyro_Calibration();
        Apply_Accelerometers_Angles();

	initialize_timers(MAIN_TIMER_MIN_PERIOD);

        ALN3D_Author();
        
	setup_stop();
        digitalWrite(EMBEDED_LED_RED, LOW);
}

void loop()
{
  loop_start();

	for(;;)
	{
		dequeue_loop();

		loop_counter++;
	};
}

void gyro_accel_process(void)
{
  MPU6000_Read();  
  MPU6000_Corrections_Scale();
  Gyroscopes_Integration();
}

void update_led_position(void)
{
  digitalWrite(EMBEDED_LED_BLUE, abs(phi * RAD_TO_DEG) < 10 && abs(theta * RAD_TO_DEG) < 10);
  digitalWrite(EMBEDED_LED_RED, abs(phi * RAD_TO_DEG) > 15 || abs(theta * RAD_TO_DEG) > 15);
}

void serial_display(void)
{
  char buf[150];
  sprintf(buf, "phi: %d  \ttheta: %d\talt: %d cm\tCPU : %lu\tCPU_use : %d\tev_ex: %lu\ttimers_ex: %lu\toverflow: %d", int(phi * RAD_TO_DEG), int(theta * RAD_TO_DEG), int(distance / 10.0), system_frequency, int(CPU_use), events_thrown, timers_expired, analyser_events_overflow);
  Serial.println(buf);
}