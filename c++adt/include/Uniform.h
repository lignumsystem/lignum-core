/// \file Uniform.h
/// \brief Random number from uniform distribution 
#ifndef UNIFORM_H
#define UNIFORM_H

namespace cxxadt{
  ///\brief Uniform random number in range [0.0,1.0]
  class Uniform{
  public:
    ///\brief Constructor with -1
    Uniform(int seed = -1):iff(0){init(seed);}
    ///\brief Initialize the sequence
    ///
    ///Different negative seeds initialize  different sequences.
    ///\param seed Negative integer
    ///\pre The \p seed must be negative 
    double init(int seed = -1){return uran(&seed);}
    ///\brief Produce next random number from the sequence
    ///\return Randon number in range [0.0,1.0]
    double operator () (int seed = 1){return uran(&seed);}
  private:
    ///\brief Uniform random random number
    ///\return Uniformally distributed random number [0.0,1.0]
    double uran(int* idum);
    int inext,inextp;
    long ma[56];
    int iff;
  };

}//close namespace 

#endif
