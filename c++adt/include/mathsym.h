#ifndef MATHSYM_H
#define MATHSYM_H
#include <math.h>
namespace cxxadt{

#define PI_VALUE 3.14159265358979323846
#define PI_DIV_2 1.57079632679489661923
#define PI_DIV_4 0.78539816339744830962


#define EPS       3.0e-8
#define R_EPSILON 1.0e-20
#define R_HUGE 1.0e+20

template <class T>
inline T maximum(T A, T B)
{
  return (A > B) ? A : B;
}

template <class T>
inline T minimum(T A, T B)
{
  return (A < B) ? A : B;
}

typedef double RADIAN;

//constant functions used in RMatrix and in HRMatrix
//for the rotations in 3D space.
inline RADIAN fn_1(RADIAN angle){return 1.0;}
inline RADIAN fn_0(RADIAN angle){return 0.0;}
inline RADIAN neg_sin(RADIAN angle){return (RADIAN) -sin(angle);}
inline RADIAN neg_cos(RADIAN angle){return (RADIAN) -cos(angle);}


//useful mathematical random function implemented
//returns uniformally distributed random number [0.0,1.0]
extern double ran3(int *seed);   

}//closing namespace cxxadt

#endif
