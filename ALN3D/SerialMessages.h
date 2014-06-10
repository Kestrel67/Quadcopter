#ifndef SERIALMESSAGES_H_
#define SERIALMESSAGES_H_

// tabulation
void sTab(HardwareSerial *ser = &Serial);

// retour à la ligne
void sLn(HardwareSerial *ser = &Serial);

// on affiche les angles, PID, et PWM
void ser_display_angles_pid_motors(HardwareSerial *ser = &Serial);

// on affiche les données de l'analyseur
void ser_display_analyser_data(HardwareSerial *ser = &Serial);

// affichage de la configuration du quad
void ser_display_IMU_conf(HardwareSerial *ser = &Serial);

// affichage de la conf du quad
void ser_display_IMU_conf_old(HardwareSerial *ser);

// com visual
void PreConfCOMVisual(void);

// python
void PreConfCOMPython(void);

// processing
void PreConfCOMProcessing(void);

// python setpoint PID angle
void PreConfCOMPythonPID(void);

// informations
void ALN3D_Author(HardwareSerial *ser = &Serial);

#endif
