#ifndef MATHSYM_H
#define MATHSYM_H

#define PI_VALUE 3.14159265358979323846
#define PI_DIV_2 1.57079632679489661923
#define PI_DIV_4 0.78539816339744830962


#define EPS       3.0e-8
#define R_EPSILON 1.0e-20

template <class T>
inline T maximum(T a,T b)
{
  (A > B) ? A : B;
}

template <class T>
inline T minimum(T a,T b)
{
  (A < B) ? A : B;
}

typedef double RADIAN;

//useful mathematical functions implemented
extern float ran3(int *seed);   //returns uniformally distributed random number [0.0,1.0]
#endif
