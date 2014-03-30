/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

#ifndef Vector_h
#define Vector_h

/**
 * on calcul le produit sclaire de 2 vecteurs
 */
float Vector_Dot_Product(fVector_t vector1, fVector_t vector2);

/**
 * on calcul le produit croisé de 2 vecteurs
 */
void Vector_Cross_Product(fVector_t vectorOut, fVector_t v1, fVector_t v2);

/**
 * on multiplie un vecteur par une scalaire
 */
void Vector_Scale(fVector_t vectorOut, fVector_t vectorIn, float scale2);
void Vector_Scale(Vector_t vectorOut, Vector_t vectorIn, float scale2);

/**
 * on additionne 2 vecteurs
 */
void Vector_Add(fVector_t vectorOut, fVector_t vectorIn1, fVector_t vectorIn2);

/**
 * On calculate la norme d'un vecteur
 */
float Vector_Magnitude(fVector_t V);
float Vector_Magnitude(Vector_t V);

/**
 * On normalize le vecteur
 */
void Vector_Normalize(fVector_t V);
void Vector_Normalize(Vector_t V);

// out
void Vector_Normalize(fVector_t V, fVector_t Vout);

/**
 * on affiche le vecteur
 */
void Vector_Display(fVector_t vector);
void Vector_Display(Vector_t vector);

/**
 * Angle fait entre les vecteurs U et V
 */
float Vectors_Angle(fVector_t U, fVector_t V);
float Vectors_Angle(Vector_t U, Vector_t V);

/**
 * Magnitude = 1
 * Angle entre U et V
 */
float Vectors1_Angle(fVector_t U, fVector_t V);

/**
 * On copie U dans V
 */
void Vector_Copy(fVector_t U, fVector_t V);

/**
 * On somme les erreurs pour chaque coordonnées
 */
float Vector_Error_Sum(fVector_t U, fVector_t V);


#endif
