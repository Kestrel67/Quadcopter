/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/**
 *	Méthodes de communication
 *
 *	Communications Wifi, Serial, SPI, Wire
 *
 *	@need : 1 EVENT, 1 TIMER
 */

#ifndef Communication_h
#define Communication_h


#define MSB(b) (b >> 7) // récupère le Most Significant Bit d'un octet (8bits)
#define LSBS(b) (b & (~(1<<7))) // Récupère le reste de l'octet (les LSBs) (8bits)
#define SERIAL_BUFFER_MAX_SIZE 64 // Taille du buffer de la communication série, 64 octets



/********************/
/*******  SPI  ******/
/********************/

/**
 * Select Slave pin (PWM1 = SS)
 */
extern Pin_t AP_select_pin;

/**
 * Synchronisation SPI avec l'esclave
 */
void AP_synchronization(void);

/**
 * Mise en place de la liaison SPI
 * @param SPIMaster *MASter
 * @param Pin_t pin, select pin
 */
void AP_init(SPIMaster *Master, Pin_t select_pin = SS);

/**
 * Met à jour une valeur de registre de l'AP
 * @param Reg_t reg : id du registre
 * @param byte value : nouvelle valeur
 */
bool AP_write(Reg_t reg, byte value);

/**
 * Lit la valeur d'un registre de l'AP
 * @param Reg_t reg : registre
 * @return bool
 */
byte AP_read(Reg_t reg);

/**
 * On envoie les rapports cycliques de chaque moteur au slave
 */
void AP_ApplyMotorsThrottle(void);


/********************/
/*****  SERIAL  *****/
/********************/

#define SERIAL_CMD_FIRST_BIT 1		// B10000000
#define SERIAL_PARAM_FIRST_BIT 0 	// B00000001
#define SERIAL_CMD_MAX_SIZE 63		// B01111110
#define SERIAL_PARAM_MAX_SIZE 255
#define SERIAL_CMD_OFFSET 1
#define SERIAL_CMD_MASK B01111110
#define SERIAL_PARAM_MSB_MASK B00000001

#define SERIAL_BAUDRATE 9600 // baudrate

/**
 *	ID du timer pour la fonction d'écoute du serial
 */
extern Tiny_t serial_observer_timer;

/**
 *	Période d'appel du serial listener
 */
extern MilliSec_t serial_observer_period;

/**
 *	Commande courante
 */
extern Command_t current_cmd;

/**
 *	Paramètre attaché
 */
extern Parameter_t attached_param;

/**
 * Premier bit du paramètre
 */
extern byte parameter_MSB;

/**
 * Indique si la commande est à jour
 */
extern bool uptodate_param;

/**
 *	Taille du buffer série
 *	(à voir si vraiment nécessaire)
 */
extern SSigned_t serial_buffer_size;

/**
 * Nouvelle donnée
 */
extern unsigned int serial_new_data;

/**
 * Evènement à lancé lorsqu'il y a une nouvelle données
 */
extern Event_t serial_new_data_event;

/**
 *	On met en place la fonction d'écoute du serial et on met en place le timer
 *	une période de serial_observer_period en ms
 */
void set_serial_observer(MilliSec_t serial_observer_period = FREQUENCY_SERIAL_OBSERVER, Event_t ev = EVENT_NULL);

/**
 * On change la période d'observation du serial observer
 */
void alter_serial_obsever_timer(MilliSec_t serial_observer_period = FREQUENCY_SERIAL_OBSERVER);

/**
 *	On envoie un message sur la communication série
 *	@param Command_t cmd : commande à envoyer
 *	@param Parameter_t param : paramètre à envoyer si nécéssaire
 *
 *	Paramètre par défaut : 0
 *	Si la commande ne nécéssite pas l'envoie d'un paramètre. On ne l'envoie pas
 */
void send_serial_command(Command_t cmd, Parameter_t param = 0, HardwareSerial *serial_obj = &Serial);

/**
 *	callback d'écoute du serial
 */
void serial_observer(void);

/**
 * Xbee : Formate et envoies les données par xbee
 *
 *
 * DATASHEET
 */
/* TEMP !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;;;f phi; f theta; f psi; f altitude; frequency; CPU_use; cmd_received; cmd_sended; events; timers; events_overflows; warning; mu; checksum;;
2				2				2				2						3						1					2						2						4					4				2									1			2				1

=30 + 19 (;) = 49

checksum = B11111111 & (phi ^ theta ^ ... ^ mu)

angle = byte / 65535.0 * 360.0 (Achille)
byte = angle / 360.0 * 65535.0 (Lucas)

altitude = byte / 65535.0 * 5.0
byte = altitude / 5.0 * 65535.0
*/
void send_serial_data(void);

#endif
