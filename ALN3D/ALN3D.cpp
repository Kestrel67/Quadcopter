/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include <ALN3D.h>

/**
 * informations
 */
void ALN3D_Author(HardwareSerial *ser)
{
	if (ser)
	{
		char buffer[200];
		sprintf(buffer, "*********** ALN 3D Project ***********\n** author:Dietrich Lucas (Kestrel)  **\n** email:kestrel.3rd@gmail.com      **\n** website:http://www.kestrel.fr/   **\n**************************************");
		ser->println(buffer);
	}
}
