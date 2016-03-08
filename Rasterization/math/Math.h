#ifndef _GMAE_MATH_H_
#define _GMAE_MATH_H_


#define PI ((float)3.14159265359f)
#define PI2 ((float)6.283185307f)
#define PI_DIV_2 ((float)1.570796327f)
#define PI_DIV_4 ((float)0.785398163f)
#define PI_INV ((float)0.318309886f)

#define DEG_TO_RAD(ang) ((ang)*PI/180.0f)
#define RAD_TO_DEG(rads) ((rads)*180.0f/PI)

#define EPSLION_E3 (float)(1e-3)
#define EPSLION_E5 (float)(1e-5)
#define EPSLION_E6 (float)(1e-6)

#define RAND_RANGE(x, y) ((x) + (rand() % ((y) - (x) + 1))) 
#define FCMP(a, b) ((std::abs(a - b) < EPSLION_E3) ? true : false)

#endif //_GMAE_MATH_H_
