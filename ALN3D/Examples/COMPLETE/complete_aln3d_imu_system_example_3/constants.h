#define EV_INTEGRATE              0
#define EV_CALCULATE_ANGLES       1
#define EV_MAGNETOMETERS          2
#define EV_UPDATE_LED_POSITION    3
#define EV_SERIAL_INPUT_LISTENER  4
#define EV_DISPLAY_DATA           5

#define EV_STABILISATION          6

void gyro_accel_process(void);
void update_led_position(void);
void serial_display(void);
