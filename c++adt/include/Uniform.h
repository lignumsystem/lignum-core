#ifndef UNIFORM_H
#define UNIFORM_H

namespace cxxadt{
  //Return uniform random number in range [0.0,1.0]
  class Uniform{
  public:
    Uniform(int seed = -1):iff(0){init(seed);}
    double init(int seed = -1){return uran(&seed);}
    double operator () (int seed = 1){return uran(&seed);}
  private:
    double uran(int* idum);
    int inext,inextp;
    long ma[56];
    int iff;
  };

}//close namespace 

#endif
