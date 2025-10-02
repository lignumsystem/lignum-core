/// \file Gauss.h
/// \brief Normal distrubutiom
#ifndef GAUSS_H
#define GAUSS_H

#include <Uniform.h>
namespace cxxadt{
  ///\brief Normal distribution
  ///
  ///Normally distributed random number with mean 'm' and 
  ///standard deviate 's".
  ///\sa cxxadt::Uniform
  class Gauss{
  public:
    Gauss(int seed = -1):uniform(seed){}
    double init(int seed = -1){return uniform.init(seed);}
    double operator()(double m, double s, int seed = 1);
  private:
    Uniform uniform;
  };

}//closing namespace

#endif
