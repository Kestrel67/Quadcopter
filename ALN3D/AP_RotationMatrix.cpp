/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

fMatrix_t RotMat;

void update_rotation_matrix(float phi, float theta, float psi)
{
	// voir doc (...)

	// phi
	float cos_phi = cos(phi); // optimisations
	float sin_phi = sin(phi);

	// les matrices des rotations sont dans l'autre sens cas plus que de déplacer le
	// repère de l'angle alpha global il faut déplacer le repère terrestre de -alpha
	fMatrix_t Mphi = {
			{cos_phi, 0, sin_phi},
			{0, 1, 0},
			{-sin_phi, 0, cos_phi}
	};

	// theta
	float cos_theta = cos(theta);
	float sin_theta = sin(theta);

	fMatrix_t Mtheta = {
			{1, 0, 0},
			{0, cos_theta, sin_theta},
			{0, -sin_theta, cos_theta}
	};

	// psi
	float cos_psi = cos(psi);
	float sin_psi = sin(psi);

	fMatrix_t Mpsi = {
			{cos_psi, -sin_psi, 0},
			{sin_psi, cos_psi, 0},
			{0, 0, 1}
	};

	// matrice temporraire
	fMatrix_t Mtemp;

	// ordre de multiplication tranposé : (Mphi * Mtheta * Mpsi)T = (Mpsi T * Mtheta T) * Mphi T
	Matrix_Multiply(Mpsi, Mtheta, Mtemp);
	Matrix_Multiply(Mtemp, Mphi, RotMat);
}

void apply_rotation_matrix(fVector_t V, fVector_t out)
{
	Vector_Apply_Matrix(RotMat, V, out);
}

void apply_rotation_matrix(fVector_t V)
{
	Vector_Apply_Matrix(RotMat, V);
}

void apply_rotation_matrix(CoordinateSystem_t rep)
{
	apply_rotation_matrix(rep.x);
	apply_rotation_matrix(rep.y);
	apply_rotation_matrix(rep.z);
}
