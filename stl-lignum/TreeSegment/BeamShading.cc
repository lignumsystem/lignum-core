#include "stdafx.h"
#include <Ellipse.h>
#include <Shading.h>
using namespace Lignum;

#define HIT_THE_FOLIAGE 1
#define NO_HIT 0
#define HIT_THE_WOOD -1
  

///////////////////////////////////////////////////////////////
//     Ellipsis beamshading for hardwoods
///////////////////////////////////////////////////////////////

//If the beam (starting from Point p0 with direction v) hits
//the ellipsis?
//It has its center at Point ps
//other properties are defined by BroadLeaf leaf, PosVector petiole

//If hits, EllipseBeamShading returns 1,
//otherwise EllipseBeamShading returns 0
// 
//
//

int EllipseBeamShading(Point& p0,
			PositionVector& v, BroadLeaf<Ellipse>& leaf)
{

  Point pc =  GetCenterPoint(leaf);

  //	1.	Rough testing, if point p0 is higher (z-axis=height) than
  //      pc + max width of the ellipsis, the beam
  //      cannot hit the ellipsis
  double a;
  a = (double)GetShape(leaf).getSemimajorAxis();
  if( p0.getZ() > pc.getZ() + 2.0*a) {
   return NO_HIT;
  }

  PositionVector n  = GetShape(leaf).getNormal();

  //    2. Where does line starting at p0 and having direction b intersect the plane
  //       that contains the ellipsis leaf

  LGMdouble vn = Dot(v, n);


  if( maximum(vn, -vn) < R_EPSILON ) {
    return NO_HIT;
  }           // if v * n = 0 beam parallel with the plane; cannot
              // we forget here the possibility that the beam is in the plane

  
  // 3. Calculate the point where beam hits the plane (=vector pointing to this point)

  // 3.2 Calculate the hit point

  double u;
  u = (Dot(n, PositionVector( pc  - p0 )) ) / vn;

  //If u < 0 the hit point is in the opposite dirction to that where the sky
  //sector is (it is pointed by v)

  if(u <= 0.0)
    return NO_HIT;

  PositionVector hit(3);
  hit = PositionVector(p0) + u * v;


  // 4. Test if the hit point is inside the ellipse

  double coord_a, coord_b;
  PositionVector diff(3);


  // Since the semiminor axis of the ellipsis is determined by the direction of
  // leaf petiole, and the vector pointing from pc to hit point is in the plane,
  // the distance of the point along the semiminor axis (=coordinate) is obtained
  // with the aid of dot product (hit - ps) * (petiole.end - ps)

  double b = (double)GetShape(leaf).getSemiminorAxis();
  diff = hit - PositionVector(pc);
  Point pend = GetEndPoint(GetPetiole(leaf));
  coord_b = Dot(PositionVector(pend - pc), diff);
  coord_b /= b;
  if(maximum(coord_b, -coord_b) > b) {
    return NO_HIT;
  }

  coord_a = sqrt( Dot(diff, diff) - coord_b * coord_b );

  if(maximum(coord_a, -coord_a) > a) {
  return NO_HIT;
  }

   if(pow(coord_a/a, 2.0) +
	  pow(coord_b/b, 2.0) > 1.0)
     return NO_HIT;
   else
     return HIT_THE_FOLIAGE;
}




///\brief Cylinder light beam shading for conifers
///
///If the beam (starting from `r0` with direction `b`) hits the shoot
///(with radius including foliage `Rs`, length `L`, position `rs` and direction `a`), 
///but not the woody part (radius `Rw`), 
///beamShading returns +1 (HIT_THE_FOLIAGE) and the distance (m) of the beam traversed
///in the shoot in the variable distance. <br>
///If the beam hits the woody part of the shoot beamShading returns -1.<br>
///In the case of no hit beamShading returns 0.<br
//If the beam (starting from `r0` with direction `b`) hits cylinder
///(radius 'Rs', length 'L', position 'rs' and direction 'a'), 
//If the beam hits cylinder, returns HIT_THE_FOLIAGE (= 1)
//and returns the `distanc`e beam travelled in cylinder.
//In the case of no hit returns NO_HIT (= 0).
///\param r0_1 Start point of the light beam
///\param b Direction of the light beam
///\param rs_1 Start point of the shading segment
///\param a Direction of the  shading segment
///\param Rs Radius including foliage of the shading segment
///\param L Length of the shading segment
///\param [out] distance Length of the shading segment
///\pre Direction vector lengths are  |a| = 1 and |b| = 1 !!
///\return 0 (NO_HIT), -1 (HIT_THE_WOOD) or +1 (HIT_THE_FOLIAGE)
int CylinderBeamShading(const Point& r0_1, const PositionVector& b, 
			const Point& rs_1, const PositionVector& a,
			double Rs, double L, double& distance )
{
  distance = 0.0; //No suprises!!

  PositionVector rs = PositionVector(rs_1.getX(),rs_1.getY(),rs_1.getZ());
  PositionVector r0 = PositionVector(r0_1.getX(),r0_1.getY(),r0_1.getZ());
  ///\section lbcintersect Calculation of light beam intersection
  ///\subsection roughtest 1.Rough testing
  ///Shaded segment higher than shading  
  if(rs.getZ() <= r0.getZ() - L){
    return NO_HIT;	//Subject (shaded)shoot is higher
  }

  double apu1, apu2, apu3;
  apu1 = fabs(rs.getX() - r0.getX());
  apu2 = fabs(rs.getY() - r0.getY());
  apu3 = fabs(rs.getZ() - r0.getZ());
 
  if(maximum(apu1, maximum(apu2, apu3)) > L )
    if( Dot(b,(rs - r0)) < 0.0 ) return NO_HIT;
  ///Shading shoot not in direction of light beam pointed by b
 
  //	Intermediate dot products and calculations
  PositionVector rdiff;
  double ab = 0.0, rdiffa = 0.0, rdiffb = 0.0;
  double rdiff2 = 0.0;
  double p1, p2;
  PositionVector rHit;
  PositionVector rd;
  PositionVector rd1;
  PositionVector rd2;
  PositionVector rs1;
  double any;

  rdiff = rs - r0;

  ab = Dot(a, b);
  rdiffa = Dot(rdiff, a);
  rdiffb = Dot(rdiff, b);
  rdiff2 = Dot(rdiff, rdiff);

  ///\subsection specialcase 2. Test for a special case
  ///If \f$ a || b\f$ , then the only possibility
  ///that the beam hits the shoot is that the hit occurs on the end disk.
  ///If the hit occurs in one disc, then it occurs in the other also.
  ///The beam hits the plane containing the end disk at `rHit` with
  ///parameter value `p1` 

  if(ab > 1.0 - R_EPSILON || -ab > 1.0 - R_EPSILON) {
    p1 = rdiffa / ab;
    if(p1 < 0.0) 
      return NO_HIT;	// Not possible that shading shoot is behind (p1<0)
    rHit = r0 + p1 * b;
    rd = rHit - rs;
    if( (any = Dot(rd,rd)) > pow(Rs, 2) )
      return NO_HIT;		// Not inside the end disk
    else {
      distance = L;		//Through needles all the length
      return HIT_THE_FOLIAGE;
    }
  }

  ///\subsection beamhit 3.Test the beam hit the the cylinder with radius Rs
  ///Test no hit <br>
  double c2Over2, c1, c3, discriminantOver4;
  PositionVector r1;
  PositionVector r2;
  bool firstHits = false, secondHits = false;
	
  c2Over2 = rdiffa * ab - rdiffb;
  c1 = 1.0 - pow(ab, 2);
  c3 = rdiff2 - pow(rdiffa, 2) - pow(Rs, 2);
  discriminantOver4 = pow(c2Over2, 2) - c1 * c3;

  if(discriminantOver4 < 0.0) {	
    return NO_HIT;			// Does not hit
  }

  ///Test beam hits the cylinder extending to infinity<br>
  p1 = ( rdiffa * ab - rdiffb + sqrt(discriminantOver4) ) /
    (pow(ab, 2) - 1.0);
 
  p2 = ( rdiffa * ab - rdiffb - sqrt(discriminantOver4) ) /
    (pow(ab, 2) - 1.0);
 
  if( p1 < 0.0 && p2 < 0.0) {
    return NO_HIT;	// In this case p0 outside the cylinder, cannot hit
  }                     // the shoot cylinder in positive direction of b

  r1 = r0 + p1 * b;
  r2 = r0 + p2 * b;

  ///Test  beam hits the shoot cylinder<br>
  /// 0 < (ri-rs)*a < L (and |a| = 1 !)

  rd = r1 - rs;
  any = Dot(a, rd);
  if(any > 0.0 && any < L) firstHits = true;

  rd = r2 - rs;
  any = Dot(a, rd);
  if(any > 0.0 && any < L) secondHits = true;


  ///Test One member of Cartesian product {mantle, end disk} x {mantle, end disk} or no hit possible <br>
  PositionVector rHit1;
  PositionVector rHit2;

  if(firstHits) {	
    if(secondHits)	{
      rd = r1 - r2;
      distance = sqrt( Dot(rd, rd) );
      return HIT_THE_FOLIAGE;
    }
    else	{		// Must be either of end disks
      p1 = rdiffa / ab;
      // N.B. Cannot come into this branch if a perpen-
      // dicular to b (a*b = 0), since in that case both
      // firstHits and secondHits must be true
      rHit = r0 + p1 * b;
      rd = rHit - rs;
      if( (any = Dot(rd, rd)) <  pow(Rs, 2) )  {
	rd1 = r1 - rHit;
	distance = sqrt( Dot(rd1, rd1) );
	return HIT_THE_FOLIAGE;
      }
      // Was not the first one
      rs1 = rs + L * a;
      rd1 = rs1 - r0;
      p1 = Dot(a, rd1) / ab;
      rHit = r0 + p1 * b;
      rd = rHit - rs1;
      if( (any = Dot(rd,rd)) <  pow(Rs, 2) ) {	
	rd1 = r1 - rHit;
	distance = sqrt( Dot(rd1, rd1) );
	return HIT_THE_FOLIAGE;
      }
      else {	//Error condition; this should not happen;
	return  HIT_THE_WOOD;
      }
    }
  } //if (firstHits) ...
  else				//firstHits not true 
    if(secondHits)	{	//Must be either of end disks
      p1 = rdiffa / ab;
      // N.B. Cannot come into this branch if a perpen-
      // dicular to b (a*b = 0), since in that case both
      // firstHits and secondHits must be true
      rHit = r0 + p1 * b;
      rd = rHit - rs;
      if( (any = Dot(rd, rd)) <  pow(Rs, 2) ) {	
	rd1 = r2 - rHit;
	distance = sqrt( Dot(rd1, rd1) );
	return HIT_THE_FOLIAGE;
      }
      // Was not the first one
      rs1 = rs + L * a;
      rd1 = rs1 - r0;
      p1 = Dot(a, rd1) / ab;
      rHit = r0 + p1 * b;
      rd = rHit - rs1;
      if( (any = Dot(rd, rd)) <  pow(Rs, 2) )	{
	rd1 = r2 - rHit;
	distance = sqrt( Dot(rd1, rd1) );
	return HIT_THE_FOLIAGE;
      }
      else {		//Error condition; this should not happen; return 3
	return  HIT_THE_WOOD;
      }
    }
    else   {		// Only end disk-in end disk-out possible
      p1 = rdiffa / ab;
      if(p1 < 0.0)
	return NO_HIT;		// Don't look back!
      rHit1 = r0 + p1 * b;
      rd = rHit1 - rs;
      if( (any = Dot(rd, rd))  >  pow(Rs, 2))  {
	return NO_HIT;
      }

      // The first one yes, now the second one
      rs1 = rs + L * a;
      rd1 = rs1 - r0;
      p1 = Dot(a, rd1) / ab;
      if(p1 < 0.0)
	return NO_HIT;
      rHit2 = r0 + p1 * b;
      rd = rHit2 - rs1;
      if( (any = Dot(rd, rd)) <  pow(Rs, 2) ) {	
	  rd = rHit2 - rHit1;
	  distance = sqrt( Dot(rd, rd) );
	  return HIT_THE_FOLIAGE;
      }
      else  {
      return NO_HIT;
      }
    }
}


//=======================================================================================================================
/////////////////////////////////////////////////////////
//     Cylinder beamshading for conifers
////////////////////////////////////////////////////////

//If the beam (starting from 'r0' with direction 'b') hits cylinder
//(radius 'Rs', length 'L', position 'rs' and direction 'a'), 
//
//If the beam hits cylinder, returns HIT_THE_WOOD (= -1).
//In the case of no hit returns NO_HIT (= 0).
//
//	NOTE:  It is assumed that |a| = 1 & |b| = 1 !!

int CylinderBeamShading(const Point& r0_1, const PositionVector& b, 
			const Point& rs_1, const PositionVector& a,
			double Rs, double L)
{
  PositionVector rs = PositionVector(rs_1.getX(),rs_1.getY(),rs_1.getZ());
  PositionVector r0 = PositionVector(r0_1.getX(),r0_1.getY(),r0_1.getZ());
  
  //	1.	Rough testing

  if(rs.getZ() <= r0.getZ() - L){
    return NO_HIT;	//Subject shoot is higher
  }


  double apu1, apu2, apu3;
  apu1 = fabs(rs.getX() - r0.getX());
  apu2 = fabs(rs.getY() - r0.getY());
  apu3 = fabs(rs.getZ() - r0.getZ());
 
  if(maximum(apu1, maximum(apu2, apu3)) > L )
    if( Dot(b,(rs - r0)) < 0.0 ) return NO_HIT;
  // Shading shoot not in direction pointed by b

  //	Intermediate dot products and calculations
  PositionVector rdiff;
  double ab = 0.0, rdiffa = 0.0, rdiffb = 0.0;
  double rdiff2 = 0.0;
  double p1, p2;
  PositionVector rHit;
  PositionVector rd;
  PositionVector rd1;
  PositionVector rd2;
  PositionVector rs1;
  double any;

  rdiff = rs - r0;

  ab = Dot(a, b);
  rdiffa = Dot(rdiff, a);
  rdiffb = Dot(rdiff, b);
  rdiff2 = Dot(rdiff, rdiff);

  //	2. Test for a special case: if a || b, then the only possibility
  // that the beam hits the shoot is that the hit occurs on the end disk.
  // If the hit occurs in one disc, then it occurs in the other also.
  // The beam hits the plane containing the end disk at rHit with
  // parameter value p1 

  if(ab > 1.0 - R_EPSILON || -ab > 1.0 - R_EPSILON) {
    p1 = rdiffa / ab;
    if(p1 < 0.0) 
      return NO_HIT;	// Not possible that shading shoot is behind (p1<0)
    rHit = r0 + p1 * b;
    rd = rHit - rs;
    if( (any = Dot(rd,rd)) > pow(Rs, 2) ) {
      return NO_HIT;	// Not inside the end disk
    }
    else {
      return  HIT_THE_WOOD;
    }
  }

  // 3. Does the beam hit the the cylinder with radius Rs?

  double c2Over2, c1, c3, discriminantOver4;
  PositionVector r1;
  PositionVector r2;
  bool firstHits = false, secondHits = false;
	
  c2Over2 = rdiffa * ab - rdiffb;
  c1 = 1.0 - pow(ab, 2);
  c3 = rdiff2 - pow(rdiffa, 2) - pow(Rs, 2);
  discriminantOver4 = pow(c2Over2, 2) - c1 * c3;

  if(discriminantOver4 < 0.0) {
    return NO_HIT;			// Does not hit
  }

  // Beam hits the cylinder extending to infinity
  //	6. One member of Cartesian product 
  //	{mantle, end disk} x {mantle, end disk} or no hit possible 
  //

  p1 = ( rdiffa * ab - rdiffb + sqrt(discriminantOver4) ) /
    (pow(ab, 2) - 1.0);
 
  p2 = ( rdiffa * ab - rdiffb - sqrt(discriminantOver4) ) /
    (pow(ab, 2) - 1.0);
 
  if( p1 < 0.0 && p2 < 0.0) { 
    return NO_HIT;	// In this case p0 outside the cylinder, cannot hit
    // the shoot cylinder in positive direction of b
  }
  r1 = r0 + p1 * b;
  r2 = r0 + p2 * b;

  // Does beam hit the shoot cylinder?
  // that is 0 < (ri-rs)*a < L
  // (|a| = 1 !)

  rd = r1 - rs;
  any = Dot(a, rd);
  if(any > 0.0 && any < L) {
    return HIT_THE_WOOD;
  }
  rd = r2 - rs;
  any = Dot(a, rd);
  if(any > 0.0 && any < L) {
    return HIT_THE_WOOD;
  }

  // Only hit to end disk possible
  PositionVector rHit1;
  PositionVector rHit2;

  p1 = rdiffa / ab;
  if(p1 < 0.0) {
    return NO_HIT;		// Don't look back!
  }
  rHit1 = r0 + p1 * b;
  rd = rHit1 - rs;
  if( (any = Dot(rd, rd))  >  pow(Rs, 2))  {
    return NO_HIT;
  }
  else {
    return  HIT_THE_WOOD;
  }

  // Execution should never come here: if the beam does not hit the cylinder,
  // and hits one end disk it must hit also the other. But it was already tested.
  rs1 = rs + L * a;
  rd1 = rs1 - r0;
  p1 = Dot(a, rd1) / ab;
  if(p1 < 0.0)
    return NO_HIT;
  rHit2 = r0 + p1 * b;
  rd = rHit2 - rs1;
  if( (any = Dot(rd, rd)) >  pow(Rs, 2) ) {	
    return  NO_HIT;
  } else	{
    return HIT_THE_WOOD;
  }
}

#undef HIT_THE_FOLIAGE
#undef NO_HIT
#undef HIT_THE_WOOD

