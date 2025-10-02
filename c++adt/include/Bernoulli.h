#ifndef BERNOULLI_H
#define BERNOULLI_H
/// \file Bernoulli.h
/// \brief Bernoulli distribution
#include <Uniform.h>
#include <numeric>
#include <cmath>
#include <cstdlib>
using namespace std;
namespace cxxadt{
  ///Bernoulli distribution: \f$ P_r(X=1) = 1 - P_r(X=0) = 1 - q = p\f$
  class Bernoulli{
  public:
    Bernoulli(int seed = -1):uniform(-abs(seed)){}
    double init(int seed = -1){return uniform.init(-abs(seed));}
    double operator()(double p, int seed=1);
  private:
    Uniform uniform;
  };

}//closing namespace

#endif
