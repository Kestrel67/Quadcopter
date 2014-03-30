/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/** SPI LIBRARY **/

#ifndef SPIClasses_h
#define SPIClasses_h

#include <SPI.h>

// si Master MEGA 2560
#if defined(__AVR_ATmega2560__)

#define SS_PIN 53
#define MOSI_PIN 51
#define MISO_PIN 50
#define SCK_PIN 52

#endif

// ATmega328 (arduino pro (& mini)) || Ethernet || IMU
#if defined(__AVR_ATmega328P__)
#define SS_PIN 10
#define MOSI_PIN 11
#define MISO_PIN 12
#define SCK_PIN 13
#endif

/**
 *	This header require to include the library "SPI.h"
 *	#include <SPI.h> in the Arduino sketch
 */

#define MAX_SPI_SLAVES 4

/**
 *	@param byte CLOCK_DIVIDER, diviseur d'horloge
 *	SPI_CLOCK_DIV2 > SPI_CLOCK_DIV32 <=> ~16Mhz / CLOCK_DIVIDER = 500kHz
 *
 * SPI CLOCK DIVIDER AVAILABLE :
 * 	SPI_CLOCK_DIV2, SPI_CLOCK_DIV4, SPI_CLOCK_DIV8, SPI_CLOCK_DIV16, SPI_CLOCK_DIV32, SPI_CLOCK_DIV64, SPI_CLOCK_DIV128
 */
#define SPI_CLOCK_DIVIDER SPI_CLOCK_DIV4 // maximum

/**
 *	SPI Class
 *	crée un maître pour la communication SPI (singleton)
 */
class SPIMaster
{
	public:

		/**
		 *	contructor du SPIMaster
		 *
		 *	utilises des constantes globales et variables : SS, MOSI, MISO, SCK, SPI, CLOCK_DIVIDER
		 */
		SPIMaster(void);

		/**
		 * Ajoute un esclave au maître
		 * @param Pin_t SS : pin de l'esclave
		 */
		void addSlave(Pin_t SS_pin);

		/**
		 *	envoie un octet et récupère celui de l'esclave
		 *	@param Pin_t SS : slave pin
		 *	@param byte cmd : command to slave (max 255 (base 10))
		 *	@return byte : return value
		 */
		byte send(Pin_t SS_pin, byte cmd);
};

/**
 *	SPISlave
 */
class SPISlave
{
	public:
		/**
		 *	constructeur
		 */
		SPISlave(void);

		/**
		 *	récupère l'octet envoyé par le maître
		 *	@param return byte
		 */
		byte get(void);

		/**
		 *	prépare l'octet pour la prochaîne transaction
		 *	@param byte msg
		 *	@param return byte
		 */
		void reply(byte msg);

	/**
	 *	ISP Callback
	 *
	 *	Ne pas faire dans cette fonction un traitement trop long pour éviter d'etre coupé
	 *	par une autre interruption, ainsi ne rien faire a part de l'assignement de variable
	 *
	 *	Example: SPI\spi_slave, dans la fonction callback, le traitement et l'affichage des données via le port serial est long
	 *	la fonction est donc coupé et empeche l'affichage compelt du message, et plante une partie du programme
	 *
	 *
	ISR (SPI_STC_vect)
	{
		// ... //
	}
	*/
};




#endif
