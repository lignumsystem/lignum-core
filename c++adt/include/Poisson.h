/// \file Poisson.h
/// \brief Poisson distributed numbers
#ifndef POISSON_H
#define POISSON_H


namespace cxxadt{
  ///\brief Poisson distributed integer numbers.
  ///
  ///Generation of Poisson distributed numbers
  ///with a simple algorithm taken from
  /// <a href="https://en.wikipedia.org/wiki/Poisson_distribution">Wikipedia</a>
  ///that has been proposed originally by Donald Knuth.
  ///
  ///Algorithm poisson random number (Knuth):
  ///\code{.uparsed}
  ///    init:
  ///         Let L=exp(-lambda), k = 0 and p = 1.
  ///    do:
  ///         k = k + 1.
  ///         Generate uniform random number u in [0,1] and let p = p * u.
  ///    while p > L.
  ///    return k - 1.
  ///\endcode
  ///cxxadt::ran3 is used to generate uniform deviates in [0, 1]
  ///\important  cxxadt::ran3 must be initialized first before using Poisson
  ///\sa cxxadt::ran3
  int Poisson(const double lambda, int& ran3_seed);
}//closing namespace

#endif
