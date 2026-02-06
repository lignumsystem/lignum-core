/// \file Gauss.h
/// \brief Normal distrubutiom
#ifndef GAUSS_H
#define GAUSS_H

#include <Uniform.h>
namespace cxxadt{
  /// \addtogroup RNORMAL
  ///@{
  ///\brief Normal distribution
  ///
  ///Normally distributed pseudo-random numbers with mean 'm' and 
  ///standard deviate 's".
  ///Use Box-Muller transformation to map uniformally
  ///distributed pseudo-random numbers to normally distributed
  ///samples.
  ///\sa cxxadt::Uniform
  class Gauss{
  public:
    ///\brief Constructor
    ///\param seed Seed for the pseudo-random number sequence
    ///\pre \p seed < 0
    Gauss(int seed = -1):uniform(seed){}
    double init(int seed = -1){return uniform.init(seed);}
    ///\brief Normally distributed pseudo-random number
    ///\param m Mean of the nomal distribution
    ///\param s Standard deviation of the normal deviation
    ///\param seed Positive integer to denote request for next random number 
    ///\return Next pseudo-random number from the sequence
    ///\pre seed > 0
    double operator()(double m, double s, int seed = 1);
  private:
    Uniform uniform;///< Uniform distribution
  };
  ///@}
}//closing namespace

#endif
