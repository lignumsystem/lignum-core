#ifndef BERNOULLI_H
#define BERNOULLI_H

#include <Uniform.h>
#include <cmath>
using namespace std;
namespace cxxadt{
  //Implement Bernoulli distribution: Pr(X=1) = 1 - Pr(X=0) = 1 - q = p
  class Bernoulli{
  public:
    Bernoulli(int seed = -1):uniform(-fabs(seed)){}
    double init(int seed = -1){return uniform.init(-fabs(seed));}
    double operator()(double p, int seed=1);
  private:
    Uniform uniform;
  };

}//closing namespace

#endif
