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
///NearbyShading  calculates shading caused  by forest  surrounding the
///voxelspace.  The  extinction is  exponetial in a  homogeneous turbid
///medium.   It  is assumed  that  the  surrounding  forest extends  to
///infinity.   The  optical  thickness  is  calculated  separately  for
///conifers and broadleved  trees on the basis of  their respective LAI
///values (total  needle surface area for conifers,  one-sided area for
///deciduous).  The  STAR mean values are 0.14 for conifers and  0.5 for
///deciduous(random flat leaf  orientation)
///
/// \pre |direction| = 1
/// \param out Point where the beam leaves the voxelspace
/// \param direction Direction of the beam
/// \param Htop z-coordinate of top of canopy m
/// \param Hbot z-coordinate of bottom of canopy , m
/// \param LAIc LAI of conifers (total needle area)
/// \param LAIb LAI of broadleaves (one-sided leaf area)
/// \param k_conifer Extinction coefficient of conifer foliage area (total)
/// \param k_deciduous Extinction coefficient of deciduous foliage area (one-sided)
/// \retval ext Extinction coeffient
/// \return Proportion  left of radiant intensity  after passing through
///         surrounding forest (that is, no shading = 1)
///
///The light beam's path through the border forest is the hypotenuse:
/// - Check for special cases in advance:
///  - No extinction if the ray comes out from the voxel space ceiling slab.
///  - No extinction if the ray is horizontal.
/// .
///\snippet{lineno} Nearby.cc BorderDist
///The Beer-Lambert law formulates the light extinction:
///\snippet{lineno} Nearby.cc BorderExt
///\todo Maybe  STAR mean values should be  given as  input
///\sa LignumForest::BorderForest::getBorderForestExtinction()
///\sa \ref radiative_properties "Radiative properties"
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
