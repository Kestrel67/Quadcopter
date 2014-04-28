/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/* Arduino pro (& mini)
#define SS_PIN 10
#define MOSI_PIN 11
#define MISO_PIN 12
#define SCK_PIN 13
*/


#ifndef SPISLAVE_H_
#define SPISLAVE_H_

class SPISlave
{
public:
	/**
	 *	Initialisation
	 */
	SPISlave(void);

	/**
	 * Get de SPI value
	 */
	byte get(void);

	/**
	 * Reply a byte value
	 */
	void reply(byte v);

	/**
	 * Callback
	 */
	/*
	ISR (SPI_STC_vect)
	{
		// ... SPDR ... //
	}
	*/
};


#endif /* SPISLAVE_H_ */
