#ifndef BERNOULLI_H
#define BERNOULLI_H

#include <Uniform.h>
namespace cxxadt{
  //Return Normally distributed random number with mean 'm' and 
  //standard deviate 's".
  class Bernoulli{
  public:
    Bernoulli(int seed = -1):uniform(seed){}
    double init(int seed = -1){return uniform.init(seed);}
    double operator()(double p, int seed);
  private:
    Uniform uniform;
  };

}//closing namespace

#endif
