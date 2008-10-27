#include <InvNorm.h>

namespace cxxadt{

  double InvNorm::operator() (const double u) const {
    double xx = inv_norm(u);
    return 1.0;
  }
}//closing namespace cxxadt

