#include <stdafx.h>
#include <math.h>
#include <interlen.h>

/*****************************************************************************
 * Line/voxel intersectio length                                             *
 *****************************************************************************/

using namespace cxxadt;

/* Returns first voxel coordinate in some direction. a is start coordinate and
   b is end coordinate. Different algorithm is used depending on whether
   a <= b or not. */


int startvoxel(float a, float b)
{
  if(a <= b)
    return (int)floorf(a);
  else
    return (int)ceilf(a) - 1;
}

