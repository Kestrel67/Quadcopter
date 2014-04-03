#include <ALN3D.h>

// debug
void ser_display_angles_pid_motors(HardwareSerial *ser)
{
	  ser->print("phi : ");
	  ser->print(phi * RAD_TO_DEG, 3);
	  ser->print("\t theta : ");
	  ser->print(theta * RAD_TO_DEG, 3);
	  ser->print("\t");
	  ser->print("altitude : ");
	  ser->print(distance);
	  ser->print("\t");
	  ser->print("freq : ");
	  ser->print(system_frequency);
	  ser->print("\t");

	  DisplayMotorsThrottle(ser);
}
