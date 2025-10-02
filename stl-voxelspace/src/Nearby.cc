#include <Nearby.h>

//NearbyShading  calculates shading caused  by forest  surrounding the
//voxelspace.  The  extinction is  exponetial in a  homogeneous turbid
//medium.   It  is assumed  that  the  surrounding  forest extends  to
//infinity.   The  optical  thickness  is  calculated  separately  for
//conifers and broadleved  trees on the basis of  their respective LAI
//values (total  needle surface area for conifers,  one-sided area for
//deciduous).  The  extinction coefficients  are 0.14 and  0.5 (random
//leaf  orientation) [maybe  should be  given as  input?]. If  the ray
//(from a point in voxel space to  a sector in the sky) comes out from
//ceiling  (i.e.   z-component  of  out  >  Htop  -  R_EPSILON)  =  no
//extinction.

//Input  out = point where the beam leaves the voxelspace
//       direction = direction of the beam
//       Htop z-coordinate of top of voxel space, m
//       Hbot z-coordinate of bottom of voxel space, m
//       LAIc LAI of conifers (total needle area)
//       LAIb LAI of broadleaves (one-sided leaf area)
//       k_conifer Extinction coefficient of conifer foliage area (total)
//       k_decidious Extinction coefficient of deciduous foliage area (one-sided)

//NOTE: It is assumed that direction is normalized, i.e. ||direction|| = 1

//Output: proportion  left of radiant intensity  after passing through
//surrounding forest (i.e. no shading = 1)

namespace voxelspace{
extern int lage;


//This is for some applications that that call NearbyShading withoout values for
//extincion coefficients (and assume these values for them)
double NearbyShading(const Point& out, const PositionVector& direction, double Htop,
		     double Hbot, double LAIc, double LAIb) {

  double k_conifer = 0.14;
  double k_deciduous = 0.5;

  double r_turn = NearbyShading(out, direction, Htop, Hbot, LAIc, LAIb, k_conifer, k_deciduous);
  return r_turn;
}


double NearbyShading(const Point& out, const PositionVector& direction, double Htop,
		     double Hbot, double LAIc, double LAIb, double k_conifer, double k_deciduous) {

  if(out.getZ() >= Htop - R_EPSILON)
    return 1.0;    //no shading if out from ceiling

  // Inclination angle of the direction (from horizon),
  // length of direction = 1, hence z coordinate = sin(alpha)
  double sin_alpha = direction.getZ();
  if(maximum(1.0-sin_alpha,sin_alpha-1.0) < R_EPSILON)
    return 1.0;   // vertical beam, cannot travel in surrounding 
                  // (this check may be unnecessary)

  if(maximum(sin_alpha, -sin_alpha) < R_EPSILON)
    return 0.0;       //horizontal ray
 
  double Hpoint = out.getZ();
  if(Hpoint < Hbot)  Hpoint = Hbot;  //Allows for possibility that the ray
                   //comes out lower than bottom of surrounding canopy


  double distance = (Htop - Hpoint) / sin_alpha;

  double dens_c  = LAIc/(Htop-Hbot);
  double dens_b  = LAIb/(Htop-Hbot);

  double optTh = (k_conifer*dens_c + k_deciduous*dens_b)*distance;
  double ext;
  if(optTh < R_HUGE)
    ext = exp(-optTh);
  else
    ext = 0.0;

  // if(lage > 18)
  // return 1.0;
  //else 
      return ext;
}
}//end namespace voxelspace
