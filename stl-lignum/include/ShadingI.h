#ifndef SHADINGI_H
#define SHADINGI_H

#include <mathsym.h>
#include <time.h>

#include <Shading.h>
using namespace Lignum;

#define HIT_THE_FOLIAGE 1
#define NO_HIT 0

//Method to compute radiation interception by the leaves of the segment
template <class TS, class BUD>
TreeCompartment<TS,BUD>* EvaluateRadiation<TS,BUD>::operator()
  (TreeCompartment<TS, BUD>* tc)const
{
  if (HwTreeSegment<TS,BUD>* ts = dynamic_cast<HwTreeSegment<TS,BUD>*> (tc)){
   
    Tree<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >& tt =
      dynamic_cast<Tree<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >&>
      (GetTree(*ts));
    
    int i = 0;
  
    Firmament& firmament = GetFirmament(tt);
    int number_of_sectors = firmament.numberOfRegions();
    double tmp_adotb = 0, a_dot_b = 0.0;
    double help;
    MJ radiation = 0.0;
    vector<double> radiation_direction(3);
    
    list<BroadLeaf*> leaves = GetLeafList(*ts);
    if (leaves.empty()){
      return tc;
    }

    vector<LGMdouble> result(number_of_sectors);
    vector<LGMdouble> init(number_of_sectors);
    list<BroadLeaf*>::iterator Il = leaves.begin();
    EvaluateRadiationForLeaf  er(ts, *Il);
    for (Il = leaves.begin(); Il != leaves.end(); Il++) {
      for(i = 0; i < number_of_sectors; i++)
	init[i] = 1.0;
      er.shaded_s = ts;
      er.shaded_l = *Il;
      result = Accumulate(tt, init, er);
      SetRadiationVector(**Il, result);
    }


    //compute the total absorbed radiation 
    number_of_sectors = firmament.numberOfRegions();
    for (Il = leaves.begin(); Il != leaves.end(); Il++) {
      result = GetRadiationVector(**Il);
      SetValue(**Il, Qin, 0.0);
      SetValue(**Il, Qabs, 0.0);
      for(i = 0; i < number_of_sectors; i++) {
	radiation = firmament.diffuseRegionRadiationSum(i,radiation_direction);
	//cos of the angle between the leaf normal and the light beam
	tmp_adotb = Dot(GetLeafNormal(**Il),
			PositionVector(radiation_direction[0],
				       radiation_direction[1], radiation_direction[2]) );
	a_dot_b = fabs(tmp_adotb);  
	help = radiation*result[i];
	SetValue(**Il, Qin, help+GetValue(**Il, Qin));
	help *= GetValue(**Il, dof)*(GetEllipsis(**Il).getArea())*a_dot_b;
	SetValue(**Il, Qabs, help+GetValue(**Il, Qabs));
      }
    }
  }   //end of first if
  else if (CfTreeSegment<TS,BUD>* ts = dynamic_cast<CfTreeSegment<TS,BUD>*> (tc)){
    //The same for the cylinder (copy paste from ...)
  }
  return tc;
}


template <class TS,class BUD> 
EvaluateRadiationForLeaf<class TS, class BUD>::EvaluateRadiationForLeaf(TreeCompartment<TS,BUD>* ts,
									BroadLeaf* lf)
{
  shaded_s = dynamic_cast<BetulaWithFlow*>(ts);
  shaded_l = lf;
}

template <class TS,class BUD>
vector<LGMdouble>& EvaluateRadiationForLeaf::operator()(vector<LGMdouble>& v, TreeCompartment<TS,BUD>* tc)const
{
  int beamShading(Point& p0, PositionVector& v,
		BroadLeaf& leaf);

  if (Lignum::BetulaWithFlow* ts = dynamic_cast<Lignum::BetulaWithFlow*>(tc)) {
    if (ts == shaded_s)
      return v;

    Tree<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >& tt =
      dynamic_cast<Tree<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> > &>
      (GetTree(*ts));
    Firmament& firm = GetFirmament(tt);

  Point mp;
  int i = 0, number_of_sectors = 0, result = 0;
  LGMdouble Vp = 0.0;
  vector<double> radiation_direction(3);
  number_of_sectors = firm.numberOfRegions();
  
  //XXXthis loop will contain the actual comparisons of tree segments and leaves
  //compare each leaf in shaded tree segment to each leaf in shading tree segment
  //to each sector

  list<BroadLeaf*>& llshding = GetLeafList(*ts);
  list<BroadLeaf*>::iterator Ishding;
  PositionVector tmp;
  mp = GetCenterPoint(*shaded_l);

  for (Ishding = llshding.begin(); Ishding != llshding.end(); Ishding++){
      for (i = 0; i < number_of_sectors; i++){
	//the radiation from the sector i
	firm.diffuseRegionRadiationSum(i,radiation_direction);
	tmp = PositionVector(radiation_direction[0],
					    radiation_direction[1],
					    radiation_direction[2]);
	result = beamShading(mp, tmp, **Ishding);
	if (result == HIT_THE_FOLIAGE){
	  Vp = 1.0-GetValue(**Ishding,dof)+GetValue(**Ishding,dof)*
	    GetValue(**Ishding,tauL);
	  v[i] *= Vp;
	}
      }
  }    //End of checking all leaves
  }
  return v;

} 

//If the beam (starting from Point p0 with direction v) hits
//the ellipsis?
//It has its center at Point ps
//other properties are defined by BroadLeaf leaf, PosVector petiole

//If hits, beamShading returns +1,
//otherwise beamShading returns 0
// 
//
//

int beamShading(Point& p0,
		PositionVector& v, BroadLeaf& leaf)
{

  Point pc =  GetCenterPoint(leaf);

  //	1.	Rough testing, if point p0 is higher (z-axis=height) than
  //      pc + max width of the ellipsis, the beam
  //      cannot hit the ellipsis
  double a;
  a = (double)GetEllipsis(leaf).getSemimajorAxis();
  if( p0.getZ() > pc.getZ() + 2.0*a) {
   return NO_HIT;
  }

  PositionVector n  = GetLeafNormal(leaf);

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

  double b = (double)GetEllipsis(leaf).getSemiminorAxis();
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



/*
---------------------------------------------------------------------
*/
TreeCompartment<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >*
PrintLight::operator()
  (TreeCompartment<Lignum::BetulaWithFlow, DefaultBud<Lignum::BetulaWithFlow> >* tc)const
{
  if (Lignum::BetulaWithFlow* ts = dynamic_cast<Lignum::BetulaWithFlow*>(tc)) {

    Tree<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >& tt =
      dynamic_cast<Tree<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >&>
      (GetTree(*ts));

  Firmament& firmament = GetFirmament(tt);
  
  list<BroadLeaf*> leaves = GetLeafList(*ts);
  if (leaves.empty()){
    return tc;
  }
  double ball = firmament.diffuseBallSensor();
  double plane = firmament.diffusePlaneSensor();
  double kin, kaps;
  double ala; 

  for (list<BroadLeaf*>::iterator Il = leaves.begin(); Il != leaves.end(); Il++) {
    kin = GetValue(**Il, Qin);
    kaps = GetValue(**Il, Qabs);
    ala = (GetEllipsis(**Il).getArea())*GetValue(**Il, dof);
    cout << "Qin:  " << kin/ball <<"  Qabs:  " << kaps/ala/plane << endl;
  }
   
  }

return tc;
}

#undef HIT_THE_FOLIAGE
#undef NO_HIT

#endif
