/// \file InvNorm.h
/// \brief Inverse of normal distribution 
#ifndef INVNORM_H
#define INVNORM_H
#include <ParametricCurve.h>

namespace cxxadt{
  ///\addtogroup RINVNORM
  /// @{
  ///\brief Inverse of cumulative PDF of normal distribution.
  ///
  ///Inverse of cumulative PDF of normal N(0,1) distribution.
  ///
  ///The function is realized as a tabulated one (step size = 0.01) and linear
  ///interpolation between. Values are tabulated between [-5.2, 5.2].
  ///Inverse(1) = -Inverse(0) = 5.2. Cumulative PDF(-5.2) =
  ///1 - Cumulative PDF(5.2) = 1.0e-7
  ///
  ///\pre x in range [0,1] (if x<0, x=0, if x>1, x=1)
  ///\post Inverse in range [-5.2,5.2]
  class InvNorm{
  public:
  InvNorm() {
    int dummy = 0;///< End of function for cxxadt::ParametricCurve
    ///Tabulated function for Inverse of cumulative PDF
    inv_norm = ParametricCurve("0.5  0.0 0.51  0.02506891 0.52  0.05015358 0.53  0.07526986"
			       "0.54  0.10043372 0.55  0.12566135 0.56  0.15096922 0.57  0.17637416 0.58  0.20189348"
			       "0.59  0.22754498 0.6  0.2533471 0.61  0.27931903 0.62  0.30548079 0.63  0.33185335"
			       "0.64  0.35845879 0.65  0.38532047 0.66  0.41246313 0.67  0.43991317 0.68  0.4676988"
			       "0.69  0.49585035 0.7  0.52440051 0.71  0.55338472 0.72  0.58284151 0.73  0.61281299"
			       "0.74  0.64334541 0.75  0.67448975 0.76  0.70630256 0.77  0.73884685 0.78  0.77219321"
			       "0.79  0.80642125 0.8  0.84162123 0.81  0.8778963 0.82  0.91536509 0.83  0.95416525"
			       "0.84  0.99445788 0.85  1.03643339 0.86  1.08031934 0.87  1.12639113 0.88  1.17498679"
			       "0.89  1.22652812 0.9  1.28155157 0.91  1.34075503 0.92  1.40507156 0.93  1.47579103"
			       "0.94  1.55477359 0.95  1.64485363 0.96  1.75068607 0.97  1.88079361 0.98  2.05374891"
			       "0.99  2.32634787 0.999 3.090232 0.9999 3.719016 1.0 5.2 1.5 5.2", dummy);
  }
  ///\brief Inverse of cumulative probability density function
  ///\param m Input from normal distribution
  ///\return Inverse in range \f$ [-5.2,5.2] \f$
  ///\pre \f$ \mathrm{m} \in [0,1], \mathrm{m} \sim N(0,1) \f$
  double operator()(const double m)const;
  private:
    ParametricCurve inv_norm;///< Tabulated inverse function
  };
  /// @}
}//closing namespace

#endif
