/// \file Nearby.h
/// \brief Border forest extinction
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
namespace voxelspace{

/// \brief Border forest shading
///
///Border forest shading with extinction coefficients
/// \param out Point where the beam leaves the voxelspace
/// \param direction Direction of the beam
/// \param Htop z-coordinate of top of canopy m
/// \param Hbot z-coordinate of bottom of canopy , m
/// \param LAIc LAI of conifers (total needle area)
/// \param LAIb LAI of broadleaves (one-sided leaf area)
/// \param k_conifer Extinction coefficient of conifer foliage area (total)
/// \param k_deciduous Extinction coefficient of deciduous foliage area (one-sided)
/// \return Proportion  left of radiant intensity  after passing through
///         surrounding forest (i.e. no shading = 1)
double NearbyShading(const Point& out, const PositionVector& direction, double Htop,
		     double Hbot, double LAIc, double LAIb, double k_conifer, double k_deciduous);


/// \brief Border forest shading
///
///This is for some applications that that call NearbyShading without values for
///extincion coefficients.
/// \param out Point where the beam leaves the voxelspace
/// \param direction Direction of the beam
/// \param Htop z-coordinate of top of canopy m
/// \param Hbot z-coordinate of bottom of canopy , m
/// \param LAIc LAI of conifers (total needle area)
/// \param LAIb LAI of broadleaves (one-sided leaf area)
/// \return Proportion  left of radiant intensity  after after passing through
///         surrounding forest (i.e. no shading = 1)
double NearbyShading(const Point& out, const PositionVector& direction, double Htop,
		     double Hbot, double LAIc, double LAIb);
}//end namespace voxelspace
#endif
