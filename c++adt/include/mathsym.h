/// \file mathsym.h
/// \brief Mathematical symbols and constants
/// \note Some of the constant exists for historic reasons.
/// Prefer The C++ Standard Library. 
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
#define EPS16     1.0e-16
const double EPS17 = 1.0e-17;
const double  EPS18 = 1.0e-18;
const double EPS19  = 1.0e-19;
#define R_HUGE 1.0e+20

///\brief Light year in meters (big number)
#define LIGHT_YEAR 9.461e+15 
///\brief Distance to Alpha Centauri in meters (big number)
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

///\brief Constant functions used in RMatrix and in HRMatrix
///for the rotations in 3D space.
inline RADIAN fn_1(RADIAN angle){angle=1.0; return angle;}  //angle used to avoid warning
inline RADIAN fn_0(RADIAN angle){angle=0.0; return angle;}
inline RADIAN neg_sin(RADIAN angle){return (RADIAN) -sin(angle);}
inline RADIAN neg_cos(RADIAN angle){return (RADIAN) -cos(angle);}


///\brief Uniformly distributed random numbers.
///
///Before use initialize with any negative number.
///negative numbers generate different sequences.
///Generate sequence with repeated calls with a positive number.
///\note Different negative numbers will initialize different sequences.
///The same negative number will always initialize the same sequence. 
///\return Uniformly distributed random number in \f$ U(0.0,1.0) \f$.
extern double ran3(int *seed);   

///\brief Gauss returns normal distribution random number N(m,s).
///
///Algorithm implements Box-Muller method and uses `ran3` to generate 
///uniformly distributed random numbers [-1,1]. 
///Thus before the  calls to `gauss`, `ran3` must be initialized with seed < 0.
///See Numerical Recipes for details.
extern double gauss(double m, double s, int *seed);

///\brief Change degrees to radian
///\param degrees Angle in degrees
///\return Angle in radians
inline double LGMRadian(double degrees)
{
  return (degrees*PI_VALUE)/180.0;
}

///\brief Change radian to degrees
///\param radian Angle in radians
///\return Angle in degrees
inline double LGMDegrees(double radian)
{
  return (radian*180.0)/PI_VALUE;
}

}//closing namespace cxxadt

#endif
