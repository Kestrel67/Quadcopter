/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef ABSTRACT_H_
#define ABSTRACT_H_

extern byte system_status; // status du système

/**
 * On change l'état du système
 */
void ChangeSystemStatus(byte status = SYS_EMERGENCY);

/**
 * On valide les angles
 */
void CheckAngles(void);

#endif
