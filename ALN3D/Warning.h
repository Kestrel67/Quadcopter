/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/**
 * Gestionnaire des erreurs et avertissements
 *
 * Implementer une fonction pour le nombre d'erreur
 */

#ifndef Warning_h
#define Warning_h

/**
 * Niveau d'avertissement (aucun, faible, moyen, élevé, critique, etc...)
 */
extern Tiny_t warning_level;

/**
 * Number of errors logged
 */
extern unsigned int warning_errors;

/**
 * Une nouvelle erreur à eu lieu
 */
void new_error(void);

#endif /* Warning_h */
