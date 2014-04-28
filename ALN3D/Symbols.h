/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef SYMBOLS_H_
#define SYMBOLS_H_

/*
Cartesian coordinate : (0, x, y, z)
phi (tanguage, pitch) : about Y, X to Z
theta (roulis, roll): about X, Y to Z
psi (lacet, yaw)   : about Z, Y to X

         z
        /|\
         |	 D
         |
         |
B      O |_ _ _ _ _\ x
        /          / A
       /
      /
    |/_ C
     y
*/




/**
 * Angle Vector access index
 */
#define PHI 	0 // INDEX 0
#define THETA 	1 // INDEX 1
#define PSI		2 // INDEX 2

/**
 * Scalar Vector access index
 */
#define X 0
#define Y 1
#define Z 2

#endif
