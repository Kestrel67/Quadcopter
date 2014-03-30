/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

/**
 * For communication with python interface
 */

#ifndef PYTHON_H_
#define PYTHON_H_

/**
 * Python seperator
 */
extern const char PYTHON_SEPERATOR;

/**
 * On affiche une matrice au format python (sympy)
 */
void Python_Matrix_Display(fMatrix_t M);
void Python_Matrix_Display(Matrix_t M);

/**
 * On affiche un vecteur au format python (sympy)
 */
void Python_Vector_Display(fVector_t V);
void Python_Vector_Display(Vector_t V);

/**
 * void python matplot_lib_display_angles
 */
void Python_MatPlotLib_Angles(void);

#endif
