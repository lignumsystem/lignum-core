//<<<<<<< bernoulli.cc
/***********************************************************************
                     bernoulli.cc
 bernoulli is a member function of StochasticLib Class, and can create a
integer 0 or 1 with probability p.
***********************************************************************/

//=======
#include <iostream>
//>>>>>>> 1.3
#include "berncreator.h"
#include <cmath>
#include "randomc.h"
using namespace std;
/***********************************************************************
                      Constructor
***********************************************************************/
StochasticLib::StochasticLib (int seed)
  : RANDOM_GENERATOR(seed) {

  if (!(fac_table[2])) {
    // make table of ln(n!)
    double sum = 0;
    fac_table[0] = 0;
    for (int i=1; i<FAK_LEN; i++) {
      //<<<<<<< bernoulli.cc
      sum += log(static_cast<double>(i)); 
      //=======
      sum += log(static_cast<double>(i));
      //>>>>>>> 1.3
      fac_table[i] = sum;}}}

/***********************************************************************
                   Table used by several functions
***********************************************************************/

double StochasticLib::fac_table[FAK_LEN] = {0,0,0}; // table of ln(n!):


void TRandomMersenne::RandomInit(long int seed) {
  // re-seed generator
  unsigned long s = (unsigned long)seed;
  for (mti=0; mti<N; mti++) {
    s = s * 29943829 - 1;
    mt[mti] = s;}}


unsigned long TRandomMersenne::BRandom() {
  // generate 32 random bits
  unsigned long y;

  if (mti >= N) {
    // generate N words at one time
    const unsigned long LOWER_MASK = (1u << R) - 1; // lower R bits
    const unsigned long UPPER_MASK = -1 << R;       // upper 32-R bits
    int kk, km;
    for (kk=0, km=M; kk < N-1; kk++) {
      y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
      mt[kk] = mt[km] ^ (y >> 1) ^ (-(signed long)(y & 1) & MATRIX_A);
      if (++km >= N) km = 0;}

    y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
    mt[N-1] = mt[M-1] ^ (y >> 1) ^ (-(signed long)(y & 1) & MATRIX_A);
    mti = 0;}

  y = mt[mti++];

  // Tempering (May be omitted):
  y ^=  y >> TEMU;
  y ^= (y << TEMS) & TEMB;
  y ^= (y << TEMT) & TEMC;
  y ^=  y >> TEML;

  return y;}

  
double TRandomMersenne::Random() {
  // output random float number in the interval 0 <= x < 1
  union {
    double f;
    unsigned long i[2];}
  convert;
  // get 32 random bits and convert to float
  unsigned long r = BRandom();
  convert.i[0] =  r << 20;
  convert.i[1] = (r >> 12) | 0x3FF00000;
  return convert.f - 1.0;}

  
long TRandomMersenne::IRandom(long min, long max) {
  // output random integer in the interval min <= x <= max
  long r;
  r = long((max - min + 1) * Random()) + min; // multiply interval with random and truncate
  if (r > max) r = max;
  if (max < min) return 0x80000000;
  return r;}



/***********************************************************************
                      Bernoulli distribution
***********************************************************************/
int StochasticLib::Bernoulli(double p) {
  // Bernoulli distribution with parameter p. This function returns 
  // 0 or 1 with probability (1-p) and p, respectively.
  // if (p < 0 || p > 1) FatalError("Parameter out of range in bernoulli function");
  if (p<0 || p> 1) cout<<"Parameter out of range in bernoulli function"<<endl;
  return Random() < p;
}


#ifndef __BORLANDC__	
// If your system doesn't have a rotate function for 32 bits integers,
// then define it thus:
unsigned long _lrotl (unsigned long x, int r) {
  return (x << r) | (x >> (sizeof(x)*8-r));}
#endif  






