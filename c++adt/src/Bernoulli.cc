#include <Bernoulli.h>

#include <numeric>
#include <vector>
#include <mathsym.h>
#include <math.h>

namespace cxxadt{

  //Before any calls initialize ran3 with seed < 0. 
  double Bernoulli::operator()(double p, int seed){
       return init(seed)<p;
 }
}//closing namespace cxxadt

#ifdef BERNOULLI

#include <iostream>
using namespace cxxadt;
using namespace std;

template <class T> 
class Square{
public:
  T operator() (T x){return x*x;}
};


#endif
