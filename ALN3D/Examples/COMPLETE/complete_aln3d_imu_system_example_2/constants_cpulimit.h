/*****************************/
/* complete aln3D IMU system */
/* SIZE : 15ko               */
/* loop frequency : 20-30KHz */
/* events freq    : 1500ev/s */
/* last test      : 33min		 */
/* ev							:	3110000  */
/* timers	(-110)	:	3110000  */
/* overflow				:	2				 */
/*****************************/

// QUEUE_SIZE : 100


#ifndef ExampleConstants_h
#define ExampleConstants_h

// enable analyser (useless, defined in ALN3D.h)
#define ENABLE_ANALYSER 1

// events
#define EVENT_GET_MPU 0
#define EVENT_GET_HMC 1
#define EVENT_GET_HC 2

#define EVENT_CALCULATING_EULER_ANGLES 3
#define EVENT_CALCULATING_HEADING 4
#define EVENT_UPDATE_LED_POSITION 5

#define EVENT_DISPLAY_EULER_ANGLES 6
#define EVENT_DISPLAY_SENSORS 7
#define EVENT_DISPLAY_SYSTEM_INFORMATION 8

#define EVENT_SERIAL_INPUT_LISTENER 9

#define EVENT_DEBUG 10

#define EVENT_LEDS_MANAGER 11

// fr?quencies
#define FREQUENCY_CPU_ANALYSER FREQUENCY_20Hz

#define FREQUENCY_GETTING_MPU_VALUES FREQUENCY_333Hz
#define FREQUENCY_CALCULATING_EULER_ANGLES FREQUENCY_333Hz

#define FREQUENCY_GETTING_HMC_VALUES FREQUENCY_250Hz
#define FREQUENCY_CALCULATING_HEADING FREQUENCY_250Hz

#define FREQUENCY_UPDATE_LED_POSITION FREQUENCY_500Hz

#define FREQUENCY_SERIAL_INPUT_LISTENER FREQUENCY_100Hz

#define FREQUENCY_DISPLAYING_EULER_ANGLES FREQUENCY_20Hz
#define FREQUENCY_DISPLAYING_SYSTEM_INFORMATION FREQUENCY_20Hz
#define FREQUENCY_DISPLAY_SENSORS_VALUES FREQUENCY_20Hz

// variables
Tiny_t leds_position_timer;
Tiny_t leds_manager_timer;

// functions headers
void display_euler_angles(void);

void display_position(void);

void display_system_information(void);

void update_led_position(void);

void display_MPU_HMC(void);

void serial_input_listener(void);

void debug(void);

void leds_manager(void);

// proc?dure
bool blink_red(unsigned int called);

bool blink_blue(unsigned int called);

bool blink_both(unsigned int called);

bool turnoff_leds(unsigned int called);

bool end_proc(unsigned int called);

// tasks
Task_t task_blink_red = {blink_red, 40};
Task_t task_blink_blue = {blink_blue, 150};
Task_t task_blink_both = {blink_both, 75};
Task_t task_off = {turnoff_leds, 0};
Task_t task_end = {end_proc, 0};

// sequence of tasks
Task_t *PROC_ARRAY[8] = {&task_off, &task_blink_red, &task_blink_both, &task_off, &task_blink_blue, &task_blink_both, &task_off, &task_end};

// new procedure
Procedure blink(PROC_ARRAY, 8);

#endif