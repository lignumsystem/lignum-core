#include <stdafx.h>
#include <cmath>
#include <interlen.h>

/*****************************************************************************
 * Line/voxel intersectio length                                             *
 *****************************************************************************/

using namespace cxxadt;

/* Returns first voxel coordinate in some direction. a is start coordinate and
   b is end coordinate. Different algorithm is used depending on whether
   a <= b or not. */


int startvoxel(double a, double b)
{
  if(a <= b)
    return static_cast<int>(floor(a));
  else
    return static_cast<int>(ceil(a)) - 1;
}

