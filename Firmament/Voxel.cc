#include <stdafx.h>
#include <Voxel.h>

// Default constructor




Voxel::Voxel()
{
  sumvector = Point(0, 0, 0);
  meansegment = Point(0, 0, 0);
  meanlength = 0;
  sumwoodradius = 0;
  meanwoodradius = 0;
  sumtotalradius = 0;
  meantotalradius = 0;
  partsum = 0;
  sumlength = 0;
  totalfoliagemass = 0;
  foliagearea = 0;
  areadensity = 0;
  STAR = 0.0;
  incomingradiation = 0;
  radiationsum = 0;
}
