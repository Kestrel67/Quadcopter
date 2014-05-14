/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef MANAGER_H_
#define MANAGER_H_

/**
 * mise en place de la fonction de management
 */
void set_CPU_Manager(MilliSec_t period = FREQUENCY_MANAGER);

/**
 * fonction de management
 */
void CPU_Manager(void);

/**
 * Debug
 */
void Manager_Debug(void);


#endif
