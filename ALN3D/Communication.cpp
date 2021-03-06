/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

/********************/
/*****  SPI COM  ****/
/********************/

Pin_t AP_select_pin;

void AP_synchronization(void)
{
	// tant qu'il n'y a aucune réponse de l'esclave
	while(AP_read(APL_REG_STATUS) == SYS_UNDEFINED)
	{
		// led effect
		digitalWrite(EMBEDED_LED_RED, !digitalRead(EMBEDED_LED_RED));
		delay(50);
	}
	AP_write(APL_REG_STATUS, SYS_PAUSE); // pause

	digitalWrite(EMBEDED_LED_RED, LOW);
}

// initialisation
void AP_init(SPIMaster *Master, Pin_t select_pin)
{
	// select pin
	AP_select_pin = select_pin;

	// SPIMaster class
	Master->addSlave(select_pin);
}

bool AP_write(Reg_t reg, byte value)
{
	if (reg >= APL_MAX_REGISTERS_MAX_VALUE)
		return false; // erreur, registre inexistant (non utilisé)

	// trigger on
	digitalWrite(AP_select_pin, LOW);

	// envoie du 1er octet
	// protocole décrit dans la documentation
	byte byte1 = APL_SPI_REG_BYTE_MASK | (reg << APL_SPI_REG_OFFSET) | (APL_SPI_WRITE << APL_SPI_RW_OFFSET) | MSB(value);
	SPI.transfer(byte1);

	// reset trigger
	digitalWrite(AP_select_pin, HIGH);
	digitalWrite(AP_select_pin, LOW);

	// envoie du 2ème octet
	// protocole décrit dans la documentation
	byte byte2 = APL_SPI_VAL_BYTE_MASK | LSBS(value);
	SPI.transfer(byte2);

	// trigger off
	digitalWrite(AP_select_pin, HIGH);

	return true;
}

byte AP_read(Reg_t reg)
{
	if (reg > APL_MAX_REGISTERS_MAX_VALUE)
		return false; // erreur, registre inexistant

	// trigger on
	digitalWrite(AP_select_pin, LOW);

	// protocole décrit dans la documentation
	byte byte1 = APL_SPI_REG_BYTE_MASK | (reg << APL_SPI_REG_OFFSET) | (APL_SPI_READ << APL_SPI_RW_OFFSET);
	SPI.transfer(byte1);

	// reset trigger
	digitalWrite(AP_select_pin, HIGH);
	digitalWrite(AP_select_pin, LOW);

	// CHAINE VIDE (aucune action)
	byte read = SPI.transfer(0);

	digitalWrite(AP_select_pin, HIGH);

	// on retourne le byte lu
	return read;
}


/********************/
/*****  SERIAL  *****/
/********************/

Tiny_t serial_observer_timer;

HardwareSerial *serial_listener_obj = &Serial;

Command_t current_cmd;

Parameter_t attached_param;

byte parameter_MSB = 0;

bool uptodate_param = false;

SSigned_t serial_buffer_size;

unsigned int serial_new_data = 0;

Event_t serial_new_data_event = EVENT_NULL;

byte communication_status;

void set_serial_observer(MilliSec_t serial_observer_period, Event_t ev)
{
	register_event(EVENT_SERIAL_OBSERVER, serial_observer);
	
	serial_observer_timer = add_timer(EVENT_SERIAL_OBSERVER, serial_observer_period, true);

	serial_new_data_event = ev;
}

void alter_serial_obsever_timer(MilliSec_t serial_observer_period)
{
	set_timeout(serial_observer_timer, serial_observer_period, true);
}

// on envoie une commande par le serial
void send_serial_command(Command_t cmd, Parameter_t param, HardwareSerial *serial_obj)
{
	// voir documentation

	// commande [1][CMD:6][MSB(param)]
	byte serial_cmd = SERIAL_CMD_FIRST_BIT << 7 | cmd << SERIAL_CMD_OFFSET | MSB(param);

	// param  	[0][LSBS(param)]
	byte serial_param = SERIAL_PARAM_FIRST_BIT << 7 | LSBS(param) << 0;

	serial_obj->write(serial_cmd);
	serial_obj->write(serial_param);
}

// serial observer/listener
void serial_observer(void)
{
	// on met à jour la taille du buffer
	serial_buffer_size = serial_listener_obj->available();

	// s'il y a une donnée à traiter
	if (serial_buffer_size >= 1)
	{
		// on récupère l'octet
		byte data = serial_listener_obj->read();

		// si c'est une commande
		if (data >> 7)
		{
			// on décode la commande
			current_cmd = (data & SERIAL_CMD_MASK) >> SERIAL_CMD_OFFSET;

			// le premier bit du paramètre
			parameter_MSB = data & SERIAL_PARAM_MSB_MASK;

			uptodate_param = false;
		}
		else if(uptodate_param == false) // si c'est un paramètre et que la commande précédait (cmd + param)
		{
			// on termine de décoder le paramètre
			attached_param = parameter_MSB << 7 | data;

			uptodate_param = true;

			// une nouvelle commande est disponible
			serial_new_data++;

			// on appel une fonction spécial si elle est défini
			if (serial_new_data_event != EVENT_NULL)
				event_queue(serial_new_data_event);
		}
		else
		{
			//Serial.write(CMD_COM_ERROR);
		}

		serial_buffer_size--;
	}
}

// DEBUG pas de formatage
void send_serial_data_debug(HardwareSerial *ser)
{
	char buf[150];
	sprintf(buf, "phi: %d  \ttheta: %d\talt: %d cm\tCPU Hz : %lu\tCPU use : %d \tev_ex: %lu\ttimers_ex: %lu\toverflow: %d", int(phi * RAD_TO_DEG), int(theta * RAD_TO_DEG), int(distance / 10.0), system_frequency, int(CPU_use), events_thrown, timers_expired, analyser_events_overflow);
	ser->println(buf);
}


// XBEE formatage des données de vol (accel, angles, frequency, etc...)
void send_serial_data_xbee(HardwareSerial *ser)
{
	byte buffer[60];

	// angles / décode: (((b1 << 8) | b2) / 65536.0) * (2*PI) - PI) * 180 / PI);
	unsigned int fphi = round((phi + PI) / (2 * PI) * 65536);
	unsigned int ftheta = round((theta + PI) /  (2 * PI) * 65536);
	unsigned int fpsi = round((psi + PI) /  (2 * PI) * 65536);

	// altitude / décode : ((b1 << 8) | b2) * 5.0 / 65536
	unsigned int faltitude = round(Altitude / 5.0 * 65536);

	// cursor
	uint8_t i = 0;

	// phi
	buffer[i++] = fphi >> 8;
	buffer[i++] = fphi;

	// theta
	buffer[i++] = ftheta >> 8;
	buffer[i++] = ftheta;

	// psi
	buffer[i++] = fpsi >> 8;
	buffer[i++] = fpsi;

	// altitude
	buffer[i++] = faltitude >> 8;
	buffer[i++] = faltitude;

	// motors
	buffer[i++] = MotorsThrottle[MA];
	buffer[i++] = MotorsThrottle[MB];
	buffer[i++] = MotorsThrottle[MC];
	buffer[i++] = MotorsThrottle[MD];

	// frequency
	buffer[i++] = system_frequency >> 16;
	buffer[i++] = system_frequency >> 8;
	buffer[i++] = system_frequency;

	// cpu_use
	buffer[i++] = byte(CPU_use);

	// cmd received, sended
	buffer[i++] = received_commands >> 8;
	buffer[i++] = received_commands;

	buffer[i++] = sended_answers >> 8;
	buffer[i++] = sended_answers;

	// events
	buffer[i++] = events_thrown >> 24;
	buffer[i++] = events_thrown >> 16;
	buffer[i++] = events_thrown >> 8;
	buffer[i++] = events_thrown;

	// timers
	buffer[i++] = timers_expired >> 24;
	buffer[i++] = timers_expired >> 16;
	buffer[i++] = timers_expired >> 8;
	buffer[i++] = timers_expired;

	// events_overflows
	buffer[i++] = analyser_events_overflow >> 8;
	buffer[i++] = analyser_events_overflow;

	// communication status
	buffer[i++] = communication_status;

	// end sequence
	buffer[i++] = '\n';
	buffer[i++] = '\n';
	buffer[i++] = '\n';

	// on envoie
	for (uint8_t j = 0; j < i; j++)
	{
		ser->write(buffer[j]);
	}
}
