#include <BroadLeaf.h>

namespace Lignum{

void BroadLeaf::photosynthesis(const LGMdouble& p0)
{

  bla.P = p0 * bla.Qabs;
}

}//closing namespace Lignum
