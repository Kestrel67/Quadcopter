/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef ROTATIONMATRIX_H_
#define ROTATIONMATRIX_H_

/**
 * Matrice de rotation global : phi * theta * psi
 */
extern fMatrix_t RotMat;

/**
 * Met à jour la matrice de rotation avec les 3 angles de rotations issues des gyroscopes
 * pitch > roll > yaw
 */
void update_rotation_matrix(float phi, float theta, float psi);

/**
 * On applique la matrice de rotation à V et on retourne le nouveau vecteur
 */
void apply_rotation_matrix(fVector_t V, fVector_t out);

/**
 * On applique la matrice de rotation à V et on retourne dans V
 */
void apply_rotation_matrix(fVector_t V);

/**
 * On applique la matrice de rotation au repère
 */
void apply_rotation_matrix(CoordinateSystem_t rep);

#endif /* ROTATIONMATRIX_H_ */
