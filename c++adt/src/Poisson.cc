#include <cmath>
#include <iostream>

//algorithm poisson random number (Knuth):
//    init:
//         Let L=exp(-lambda), k = 0 and p = 1.
//    do:
//         k = k + 1.
//         Generate uniform random number u in [0,1] and let p = p * u.
//    while p > L.
//    return k - 1.

//NOTE: ran3 should be initilized before using Poisson

using namespace std;


namespace cxxadt{

double ran3( int* idum);


  int Poisson(const double lambda, int& ran3_seed){
    if(lambda > 500.0) {
      cout << "Lambda " << lambda << " too big ( > 500) for Poisson deviates algortihm, exit."
	   << endl;
      exit(0);
    }
  
    double L = exp(-lambda);
    int k = 0;
    double p = 1.0;
    do {
      k = k + 1;
      double u = ran3(&ran3_seed);
      p = p * u;
    } while(p > L);

    return k - 1;
  }

}//closing namespace cxxadt
