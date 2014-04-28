/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include <ALN3D.h>
/**
 * Niveau d'erreur
 */
Tiny_t warning_level = 0;

unsigned int warning_errors = 0;

void new_error(void)
{
	warning_errors++;

	warning_level = (int) log(warning_errors + 1);
}
