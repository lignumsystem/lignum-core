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
  ///\addtogroup RBERNOULLI
  /// @{
  ///\brief Bernoulli distribution: \f$ P_r(X=1) = 1 - P_r(X=0) \f$
  ///
  ///A Bernoulli distribution is a discrete probability distribution
  ///that models a random variable with only two possible outcomes.
  ///Use a threshold value to map uniformly distributed random numbers
  ///to Bernoulli distribution.
  class Bernoulli{
  public:
    Bernoulli(int seed = -1):uniform(-abs(seed)){}
    ///\brief Initialize the sequence from Bernoulli distribution
    ///\param seed Negative integer 
    ///\pre \p seed < 0
    double init(int seed = -1){return uniform.init(-abs(seed));}
    ///\brief Return pseudo-random number from Bernoulli distribution
    ///\param p Threshold value for \f$ P_r(X=1) \f$
    ///\param seed Positive integer to denote request for the next random variable
    ///\pre \f$ p \in [0,1] \f$
    ///\pre \p seed > 0
    ///\retval 1 with probabilty \f$ p \f$
    ///\retval 0 with probability \f$ 1-p \f$
    double operator()(double p, int seed=1);
  private:
    Uniform uniform;
  };
  /// @}
}//closing namespace

#endif
