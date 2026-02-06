/// \file Uniform.h
/// \brief Random number from uniform distribution 
#ifndef UNIFORM_H
#define UNIFORM_H
/// \defgroup PSEUDORANDOM Pseudo-random numbers
/// \brief Pseudo-random number generators
///
/// \note The Standard C++ Library (C++11 onwards) has a [random number
/// library](https://en.cppreference.com/w/cpp/numeric/random.html)
/// to generate random and pseudo-random numbers from diverse statistical distributions.
/// @{
/// \defgroup RUNIFORM Uniform distribution
/// \brief Generate pseudo-random numbers from uniform distribution
/// \defgroup RNORMAL Normal distribution
/// \brief Generate pseudo-random numbers from normal distribution
/// @{
/// \defgroup RINVNORM Inverse of normal distribution
/// \brief Inverse of cumulative probability density function (PDF) of normal distribution.
/// @}
/// \defgroup RBERNOULLI Bernoulli distribution
/// \brief Generate pseudo-random numbers from Bernoulli distribution
/// @}


namespace cxxadt{
  /// \addtogroup RUNIFORM
  ///@{ 
  ///\brief Uniform random number in range [0.0,1.0)
  class Uniform{
  public:
    ///\brief Constructor with -1
    ///
    ///Any negative number initializes the sequence
    Uniform(int seed = -1):iff(0){init(seed);}
    ///\brief Initialize the sequence with a negative number
    ///
    ///Different negative seed values initialize  different sequences.
    ///\param seed Negative integer
    ///\pre \p seed < 0
    double init(int seed = -1){return uran(&seed);}
    ///\brief Produce next random number from the sequence.
    ///
    ///Any positive \p seed value produces the next value form the sequence
    ///\param seed Positive integer
    ///\return Randon number in range [0.0,1.0)
    ///\pre \p seed > 0 
    double operator () (int seed = 1){return uran(&seed);}
  private:
    ///\brief Uniform random number generator
    ///\return Uniformally distributed random number [0.0,1.0]
    ///\sa Knuth, D.E. 1981, Seminumerical Algorithms, 2nd ed., vol. 2 of The Art of Computer Programming.
    ///\sa Numerical Recipes in C. Second Edition.
    double uran(int* idum);
    int inext,inextp;
    long ma[56];
    int iff;
  };
  /// @}
}//close namespace 

#endif
