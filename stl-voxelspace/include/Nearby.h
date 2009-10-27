#ifndef NEARBY_H
#define NEARBY_H

#include <cmath>
using namespace std;
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>
using namespace cxxadt;
#include <LGMSymbols.h>
using namespace Lignum;
//Input  out = point where the beam leaves the voxelspace
//       direction = direction of the beam
//       Htop z-coordinate of top of canopy m
//       Hbot z-coordinate of bottom of canopy , m
//       LAIc LAI of conifers (total needle area)
//       LAIb LAI of broadleaves (one-sided leaf area)
//       k_conifer Extinction coefficient of conifer foliage area (total)
//       k_decidious Extinction coefficient of deciduous foliage area (one-sided)


double NearbyShading(const Point& out, const PositionVector& direction, double Htop,
		     double Hbot, double LAIc, double LAIb, double k_conifer, double k_deciduous);


//This is for some applications that that call NearbyShading withoout values for
//extincion coefficients.

double NearbyShading(const Point& out, const PositionVector& direction, double Htop,
		     double Hbot, double LAIc, double LAIb);
#endif
