#include <Wire.h>
#include <SPI.h>
#include <HMC5883L.h>
#include <ALN3D.h>

// led pins
#define RED 5
#define BLUE 6

// we define all the events

// getting values from accelerometers and gyroscopes
#define E_GET_MPU 1

// calculating euler angles with MPU datas
#define E_CALCULATING_EULER 2

// getting values from magnetometers
#define E_GET_HMC 3

// calculating heading with magnetic north
#define E_CALCULATING_HEADING 4

// debug function
#define E_DEBUG 5

// update led status, according to IMU position in space
#define E_UPDATE_POSITION 6

// display euler angles 
#define E_DISPLAY_EULER_ANGLES 7

// we instanciate the SPI Master
SPIMaster IMU();

// debug function, display calculated values
void debug()
{
  char buf[30];
  
  sprintf(buf, "temperature:%d\theading:%d\t",temperature + TEMPERATURE_GAP, int(heading * RAD_TO_DEG));
  Serial.println(buf);
}

// show euler angles attached to E_DISPLAY_EULER_ANGLES
void show_angles()
{
  char buf[80];
  
  sprintf(buf, "phi:%d\ttheta:%d\tpsi:%d", int(phi * RAD_TO_DEG), int(theta * RAD_TO_DEG), int(psi * RAD_TO_DEG));
  Serial.println(buf);
}

// function attached to E_UPDATE_POSITION event
void update_position()
{
  digitalWrite(BLUE, psi * RAD_TO_DEG >= 80);
  digitalWrite(RED, psi * RAD_TO_DEG < 75);
}

// init
void setup()
{
  Serial.begin(9600);
  
  // calling the class constructor
  IMU = SPIMaster();
  
  // MPU and HMC init
  HMC5883L_Init();
  MPU6000_Init(&IMU);
  
  // set input outputs pins
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  // we set all the events in the register, with them attached callback
  register_event(E_GET_MPU, MPU6000_Read);
  register_event(E_CALCULATING_EULER, Euler_Angles);
  
  register_event(E_GET_HMC, HMC5883L_Read);
  register_event(E_CALCULATING_HEADING, Heading);
  
  register_event(E_DEBUG, debug);
  
  register_event(E_UPDATE_POSITION, update_position);
  
  register_event(E_DISPLAY_EULER_ANGLES, show_angles);
  
  // we define new timers with the calling frequency
  add_timer(E_GET_MPU, FREQUENCY_10Hz); // period 100ms
  add_timer(E_CALCULATING_EULER, FREQUENCY_10Hz);
  
  add_timer(E_GET_HMC, FREQUENCY_1Hz); // period 1s
  add_timer(E_CALCULATING_HEADING, FREQUENCY_1Hz);
  
  add_timer(E_DEBUG, FREQUENCY_100mHz); // period 2s
  
  add_timer(E_UPDATE_POSITION, FREQUENCY_20Hz); // period 50ms
  
  add_timer(E_DISPLAY_EULER_ANGLES, FREQUENCY_2Hz);
  
  // initilializing main timer
  initialize_timers(MAIN_TIMER_MIN_PERIOD);
}

void loop()
{
  // processing throwed events
  dequeue_loop();
}