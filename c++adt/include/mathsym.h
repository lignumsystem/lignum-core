#ifndef MATHSYM_H
#define MATHSYM_H
#include <cmath>
using namespace std;
namespace cxxadt{

#define PI_VALUE 3.14159265358979323846
#define PI_DIV_2 1.57079632679489661923
#define PI_DIV_4 0.78539816339744830962

//Standard  gravity,  conventional  standard value  for  gravitational
//acceleration on earth
#define G0_VALUE  9.80665
//The density of ice kg/m3
#define Rho_ICE   916.7
  //Small numbers
#define EPS8      1.0e-8
#define EPS6      1.0e-6 
#define R_EPSILON 1.0e-20
#define EPS1      1.0e-10
#define EPS10     1.0e-10
#define EPS15     1.0e-15
#define EPS18     1.0e-18
#define R_HUGE 1.0e+20

//Light year is about this many meters
#define LIGHT_YEAR 9.461e+15 
//Distance to Alpha Centauri in meters
#define ALPHA_CENTAURI 4.11554e+16

//Try to use standard STL max function if possible, Max is a functor
//that   can  be   used   with  algorithms   designed  for   Lignum,
//e.g. AccumulateDown.
template <class T>
class Max{
public:
  const T& operator()(const T& a, const T& b)const
  {
    return (a > b) ? a : b;
  }
};

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
  typedef unsigned long int long_size;

//constant functions used in RMatrix and in HRMatrix
//for the rotations in 3D space.
inline RADIAN fn_1(RADIAN angle){angle=1.0; return angle;}  //angle used to avoid warning
inline RADIAN fn_0(RADIAN angle){angle=0.0; return angle;}
inline RADIAN neg_sin(RADIAN angle){return (RADIAN) -sin(angle);}
inline RADIAN neg_cos(RADIAN angle){return (RADIAN) -cos(angle);}


//Useful mathematical random function implemented
//returns uniformally distributed random number [0.0,1.0]
//Before use initialize with any negative number. 
extern double ran3(int *seed);   

//Gauss returns normal distribution random number N(m,s) using seed 'seed'. 
//Algorithm implements Box-Muller method and uses ran3 to generate 
//uniformly distributed random numbers [-1,1]. 
//Thus before the  calls to gauss, ran3 must be initialized with seed < 0.
//See Numerical Recipes for details.
extern double gauss(double m, double s, int *seed);

//Change degrees to radian
inline double LGMRadian(double degrees)
{
  return (degrees*PI_VALUE)/180.0;
}

//Change radian to degrees
inline double LGMDegrees(double radian)
{
  return (radian*180.0)/PI_VALUE;
}

}//closing namespace cxxadt

#endif
