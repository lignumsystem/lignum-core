#ifndef SHADINGI_H
#define SHADINGI_H

#include <mathsym.h>
#include <time.h>
#include <Tree.h>
#include <Ellipse.h>
#include <algorithm>
using namespace Lignum;
using namespace sky;

#define HIT_THE_FOLIAGE 1
#define NO_HIT 0
#define HIT_THE_WOOD -1

int EllipseBeamShading(Point& p0, PositionVector& v,
			BroadLeaf<cxxadt::Ellipse>& leaf);
int cylinderBeamShading(const Point& r0, const PositionVector& b, 
			const Point& rs, const PositionVector& a,
			double Rs, double Rw, double L, 
			double& distance );



//==============================================================
//THE HARDWOOD PART
//===============================================================

//This functor EvaluateRadiationForHwTreeSegment evaluates shading
//caused by all other leaves to all leaves of this hardwood
//segment. This functor uses functor ShadingEffectOfLeaf<TS,BUD> to
//go through all leaves and to check the shading.

//This method is not necessary for hardwoods. Having this this 'do
//nothing' method defined makes sure that programs compiles even if
//constructor of SGetFIWrapRadiationEvaluations<F,TS,BUD> is invoked with
//string argumend for hardwoods.
template <class TS,class BUD,class S>
void EvaluateRadiationForHwTreeSegment<TS,BUD,S>::setExtinction(ParametricCurve& K_in)
{
  ;
}



template <class TS,class BUD,class S>
void EvaluateRadiationForHwTreeSegment<TS,BUD,S>::operator()
  (TS* hwts)const
{

  // Radiation conditions are not evaluated if the segment has no leaves
  list<BroadLeaf<S>*> leaves = GetLeafList(*hwts);
  if (leaves.empty()) return;

  Tree<TS,BUD>& tt = GetTree(*hwts);
  FirmamentWithMask& firmament = GetFirmament(tt);
  int number_of_sectors = firmament.numberOfRegions();
  double tmp_adotb = 0, a_dot_b = 0.0;
  double help;
  MJ radiation = 0.0;
  vector<double> radiation_direction(3);
  
  vector<LGMdouble> result(number_of_sectors);
  vector<LGMdouble> init(number_of_sectors);
  typename list<BroadLeaf<S>*>::iterator Il = leaves.begin();

  ShadingEffectOfLeaf<TS,BUD,S>  s_e(hwts, *Il);

  //Go through of all leaves of this segment
  int i = 0;
  for (Il = leaves.begin(); Il != leaves.end(); Il++) {
    for(i = 0; i < number_of_sectors; i++)
      init[i] = 1.0;
    s_e.shaded_l = *Il;
    result = Accumulate(tt, init, s_e);
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
      help *= GetValue(**Il, LGAdof)*(GetShape(**Il).getArea())*a_dot_b;
      SetValue(**Il, Qabs, help+GetValue(**Il, Qabs));
    }
  }
}


//This functor ShadingEffectOfLeaf<TS,BUD> evaluates shading caused
//by all leaves of a hardwood segment on a leaf (shaded_l) of a
//hardwood segment (shaded_s). 


template <class TS, class BUD,class S> 
ShadingEffectOfLeaf<TS,BUD,S>::
  ShadingEffectOfLeaf(HwTreeSegment<TS,BUD,S>* ts, BroadLeaf<S>* lf)
{
  shaded_s = ts;
  shaded_l = lf;
}


template <class TS,class BUD,class S>
vector<LGMdouble>& ShadingEffectOfLeaf<TS,BUD,S>::operator()(vector<LGMdouble>& v,
		       TreeCompartment<TS,BUD>* tc)const
{
  //  int beamShading(Point& p0, PositionVector& v,
  //	BroadLeaf& leaf);

  if (TS* ts = dynamic_cast<TS*>(tc)) {
    if (ts == shaded_s)
      return v;

    Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD> &>(GetTree(*ts));
    FirmamentWithMask& firmament = GetFirmament(tt);
    Point mp;
    int i = 0, number_of_sectors = 0, result = 0;
    LGMdouble Vp = 0.0;
    vector<double> radiation_direction(3);
    number_of_sectors = firmament.numberOfRegions();
  
    //XXXthis loop will contain the actual comparisons of tree segments and leaves
    //compare each leaf in shaded tree segment to each leaf in shading tree segment
    //to each sector

    list<BroadLeaf<S>*>& llshding = GetLeafList(*ts);
    typename list<BroadLeaf<S>*>::iterator Ishding;
    PositionVector tmp;
    mp = GetCenterPoint(*shaded_l);

    for (Ishding = llshding.begin(); Ishding != llshding.end(); Ishding++){
      for (i = 0; i < number_of_sectors; i++){
	//the radiation from the sector i and direction of sector i
	firmament.diffuseRegionRadiationSum(i,radiation_direction);
	tmp = PositionVector(radiation_direction[0],
			     radiation_direction[1],
			     radiation_direction[2]);
	result = EllipseBeamShading(mp, tmp, **Ishding);
	if (result == HIT_THE_FOLIAGE){
	  Vp = 1.0-GetValue(**Ishding,LGAdof)+GetValue(**Ishding,LGAdof)*
	    GetValue(**Ishding,tauL);
	  v[i] *= Vp;
	}
      }
    }    //End of checking all leaves
  }
  return v;

} 



//=========================================================================
//THE CONIFER PART
//=========================================================================


//This functor EvaluateRadiationForCfTreeSegment evaluates shading
//caused by all other segments on this conifer segment. This functor
//uses functor ShadingEffectOfCfTreeSegment<TS,BUD> to go through all
//segments to check the shading.


template <class TS, class BUD>
TreeCompartment<TS,BUD>* EvaluateRadiationForCfTreeSegment<TS,BUD>::operator() (TreeCompartment<TS, BUD>* tc)const
{
  if (TS* ts = dynamic_cast<TS*>(tc)){
    SetValue(*ts, Qin, 0.0);
    SetValue(*ts, Qabs, 0.0);
    //Radiation  conditions are not  evaluated if  the segment  has no
    //foliage (in practice  there would be division by  0 in computing
    //absorbed radiation)
    if (GetValue(*ts, Wf) < R_EPSILON){
	return tc;
    }

    Tree<TS,BUD>& tt = GetTree(*ts);
    FirmamentWithMask& firmament = GetFirmament(tt);
    int number_of_sectors = firmament.numberOfRegions();
    double a_dot_b = 0.0;
    vector<double> radiation_direction(3);

    vector<double> v(number_of_sectors,0.0); 
    ShadingEffectOfCfTreeSegment<TS,BUD> s_e(ts,K,v);
    //This  goes  through  the  tree  and computes  shading  based  on
    //1)distance  light beam traverses  in foliage,  2)foliage density
    //and 3) inclination light beam hits the segment.
    ForEach(tt,s_e);
    
    //implement  "Ip  =  Iope^(-Vp)",  s[i] =  radiation  coming  from
    //direction i after this
    vector<double>& s = s_e.getS();
    for (int i = 0; i < number_of_sectors; i++){
      if (s[i] == HIT_THE_WOOD){
	s[i] = 0.0;
      }
      else {
	MJ Iop = firmament.diffuseRegionRadiationSum(i,radiation_direction);
	s[i] = Iop*exp(-s[i]);
      }
    }

    //Total incoming radiation  
    MJ Q_in = accumulate(s.begin(),s.end(),0.0);

    //s contains now incoming radiation from each sector. Evaluate how
    //much segment absorbs from incoming radation.
    LGMdouble Lk, inclination, Rfk, Ack, extinction, sfk, Ask, Wfk;
    Lk = Rfk = Ack =  extinction = sfk = Ask = Wfk = 0.0;
    Lk = GetValue(*ts, L);   //length is > 0.0, otherwise we would not bee here
    Rfk = GetValue(*ts, Rf);  //Radius to foliage limit 
    Wfk = GetValue(*ts, Wf); //Foliage mass
    sfk  = GetValue(tt, sf); //Foliage m2/kg from tree

    for (int i = 0; i < number_of_sectors; i++){
      firmament.diffuseRegionRadiationSum(i,radiation_direction);
      a_dot_b = Dot(GetDirection(*ts), PositionVector(radiation_direction));
      inclination = PI_DIV_2 - acos(fabs(a_dot_b));

      Ack = 2.0*Lk*Rfk*cos(inclination) + PI_VALUE*pow(Rfk,2.0)*sin(inclination);
      extinction = (double)K(inclination);

      if (Ack == 0.0){
	cout << "ERROR EvaluateRadiationForCfTreeSegment: Ack == 0 (division by 0)"
	     << endl;
      }

      //implement I(k)p = Ip*Ask, Note  Ack must be greater than 0 (it
      //should if there is any foliage)
      Ask = (1.0 - exp(-extinction*((sfk*Wfk)/Ack)))*Ack;
      s[i] *= Ask;
    }
    MJ Q_abs = accumulate(s.begin(),s.end(),0.0);
    SetValue(*ts, Qabs, Q_abs);
    SetValue(*ts, Qin, Q_in);
  }
  return tc;
}




//This functor ShadingEffectOfCfTreeSegment<TS,BUD> evaluates shading caused
//by a conifer segment on this conifer segment (shaded_s)

template <class TS,class BUD>
TreeCompartment<TS,BUD>* ShadingEffectOfCfTreeSegment<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const {

  //  int beamShading(Point& p0, PositionVector& v,

  if (CfTreeSegment<TS,BUD>* ts = dynamic_cast<CfTreeSegment<TS,BUD>*>(tc)) {
    //Don't compare to yourself
    if (ts == shaded_s)
      return tc;

    //Don't compare to lower segment
    if (GetPoint(*ts).getZ() < GetPoint(*shaded_s).getZ())
      return tc;

    //Now go on computing shading
    int i = 0, number_of_sectors = 0, result = NO_HIT;
    double distance = 0.0;
    vector<double> radiation_direction(3);

    Tree<TS,BUD>& tt = GetTree(*ts);
    
    FirmamentWithMask& firmament = GetFirmament(tt);
    
    number_of_sectors = firmament.numberOfRegions();

    //Foliage density: Mass divided by  volume. Perhaps a good idea to
    //implement it as GetValue?
    LGMdouble fol_dens = GetValue(*ts,Wf)/
      (PI_VALUE*(pow(GetValue(*ts,Rf),2.0)-pow(GetValue(*ts,R),2.0))
       *GetValue(*ts,L));

    for (i = 0; i < number_of_sectors; i++) {
      //If the sector is blocked by another shoot
      //do not make computations, check the next sector instead
      if (S[i] == HIT_THE_WOOD) { 
	continue;
      }
      //The radiation and its direction of sector i. We need the direction
      firmament.diffuseRegionRadiationSum(i,radiation_direction);

      Point r_0 =  GetPoint(*shaded_s)+0.5*GetValue(*shaded_s,L)*
	(Point)GetDirection(*shaded_s);        //Midpoint of shaded seg

      result = cylinderBeamShading(r_0,
				   radiation_direction,
				   GetPoint(*ts),
				   GetDirection(*ts),
				   GetValue(*ts, Rf),
				   GetValue(*ts, R),
				   GetValue(*ts, L),
				   distance);


      if (result == HIT_THE_WOOD){
	//mark the sector blocked 
	S[i] = HIT_THE_WOOD;
      }
      else if (result == HIT_THE_FOLIAGE){
	//otherwise compute Vp (the shadiness):
	//1. compute the inclination of light beam and the segment
	//1a. angle between segment and light beam 
	double a_dot_b = Dot(GetDirection(*ts),
			     PositionVector(radiation_direction));
	//1b.  inclination: Perpendicular  (PI_DIV_2) to segment minus
	//angle between segment and light beam
	double inclination = PI_DIV_2 - acos(fabs(a_dot_b));
	//2.the light extinction coefficient according to inclination
	double extinction = K(inclination);
	//3.Vp = extinction*distance*foliage_density
	double Vp = extinction *distance*fol_dens;
	S[i] += Vp;
      }
  
    }
  }
  return tc;
}
#undef HIT_THE_FOLIAGE
#undef NO_HIT
#undef HIT_THE_WOOD

#endif

