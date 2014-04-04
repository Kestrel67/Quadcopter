/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef Matrix_h
#define Matrix_h

/**
 * Matrice identité
 */
extern Matrix_t IdentityMatrix;

/**
 *	on multiplie de matrices carrés d'ordre 3
 *	résultat dans M
 */
void Matrix_Multiply(fMatrix_t A, fMatrix_t B, fMatrix_t M);

/**
 * on multiplie une matrice de rotation par un vecteur et on le retourne dans Vprime
 */
void Vector_Apply_Matrix(fMatrix_t M, fVector_t V, fVector_t Vprime);

/**
 * On calcule la transposé de la matrice M
 */
void Matrix_Transpose(fMatrix_t M, fMatrix_t Out);

/**
 * On calcule la trace de la matrice de rotation
 */
float Matrix_Trace(fMatrix_t M);

/**
 * On multiplie une matrice de rotation par un vecteur et on le retourne dans ce même vecteur
 */
void Vector_Apply_Matrix(fMatrix_t M, fVector_t V);

/**
 * On multiplie une matrice de rotation par un vecteur et on modifie le vecteur, pointeur
 */
void Vector_Apply_Matrix(fMatrix_t M, fVector_t *V);

/**
 * on multiplie une matrice par une scalaire
 */
void Matrix_Scale(fMatrix_t M, float scalar);

/**
 * on affiche une matrice (float ou int)
 */
void Matrix_Display(fMatrix_t M);
void Matrix_Display(Matrix_t);


#endif
