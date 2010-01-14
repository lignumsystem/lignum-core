#ifndef POISSON_H
#define POISSON_H

//Generation of Poisson distributed numbers with a simple algorithm
//taken from Wikipedia that has been proposed by Knuth.
//algorithm poisson random number (Knuth):
//    init:
//         Let L=exp(-lambda), k = 0 and p = 1.
//    do:
//         k = k + 1.
//         Generate uniform random number u in [0,1] and let p = p * u.
//    while p > L.
//    return k - 1.

//ran3 is used to generate uniform deviates in [0, 1], the seed for that
//is given as argument (preferably a global variable to make sure that the
//uniform sequence of deviates will not be accidentally reinitilized at some
//point (with unfortunate results)).

//NOTE: ran3 should be initilized before using Poisson

namespace cxxadt{
  int Poisson(const double lambda, int& ran3_seed);
}//closing namespace

#endif
