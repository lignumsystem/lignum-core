#ifndef VOXELSPACERADIATION_H
#define VOXELSPACERADIATION_H
#include <CompareLeaves.h>
//The    multiplicative     extinction    coeffiecients.    Used    in
//DiffuseVoxelSpaceRadiation.
class AccumulateExtinction{
public:
  AccumulateExtinction(VoxelSpace& vspace):vs(vspace){}
  double operator()(double tau,VoxelMovement& vm){
    double tau_box = vs.voxboxes[vm.x][vm.y][vm.z].extinction(vm.l); 
    tau = tau*tau_box;
    return tau;
  }
  VoxelSpace& vs;
};

class AccumulatePairwiseExtinction{
public:
  double operator()(double t,VoxelMovement& vm){
    t = t*vm.tau;
    return t;
  }
};

/* class AccumulateAfTimesL{ */
/*  public: */
/*   double operator()(double al,VoxelMovement& vm){ */
/*     al += vm.af * vm.l; */
/*     return al; */
/*   } */
/* }; */



template <class TS,class BUD>
class AbsorbedRadiation{
public:
  double calculateAbsorbedCfRadiation(const CfTreeSegment<TS,BUD>& ts, const Firmament& f,
				      vector<double>&s, const ParametricCurve& K)const
  {
    vector<double> d(3,0.0);//the direction of the i'th sector
    LGMdouble Lk, inclination, Rfk, Ack, extinction, sfk, Ask, Wfk;
    Lk = Rfk = Ack =  extinction = sfk = Ask = Wfk = 0.0;
    Lk = GetValue(ts, LGAL);   //length is > 0.0, otherwise we would not bee here
    Rfk = GetValue(ts, LGARf); //Radius to foliage limit 
    Wfk = GetValue(ts, LGAWf); //Foliage mass
    //The specific leaf area, m2/kg, is now function of relative light
    sfk = GetValue(ts,LGAsf);
    //This is for Risto 3.11.2007
    //double Qi = accumulate(s.begin(),s.end(),0.0);
    //Loop the sectors
    for (int i = 0; i < f.numberOfRegions(); i++){
      f.diffuseRegionRadiationSum(i,d);//get the direction 'd' of the i'th sector
      double a_dot_b = Dot(GetDirection(ts), PositionVector(d));
      //The angle for the projection: if the segment and the ray are
      //the  same,  the  end  disk  of the  segment  faces  the  ray
      //(i.e. cos(90d-0d) = 0,  sin(90d-0d)=1); if the angle between
      //the ray  and the segment is  90, the surface  of the segment
      //faces the ray (i.e. cos(90d-90d) = 1, sin(90d-90d) = 0). You
      //may want to  plot the Ack for various  angles. Note that dot
      //product is [-1:1] and as  such may be a pitfall: we get  the 
      //same projection  area e.g. with acos(1) and acos(-1)  angles
      //(the ray and  the  segment  have  the same and  the opposite 
      //directions). But taking the absolute value of inclination we
      //create the necessary symmetry. 
      inclination = PI_DIV_2 - acos(a_dot_b);
      Ack = 2.0*Lk*Rfk*cos(fabs(inclination)) + PI_VALUE*pow(Rfk,2.0)*sin(fabs(inclination));
      //The domain of "K" is [0:pi/2], so if the a_dot_b is negative (angle > 90d), 
      //we must take the acute angle
      double phi = 0.0;
      if (a_dot_b < 0.0)//obtuse angle -> take the acute angle
	phi = PI_VALUE - acos(a_dot_b);
      else
	phi = acos(a_dot_b);
      extinction = K(phi);
      if (Ack <= R_EPSILON){
	cout << "ERROR EvaluateRadiationForCfTreeSegment: Ack == 0 (division by 0) "
	     << Ack << endl;
      }
      //implement I(k)p = Ip*Ask, Note  Ack must be greater than 0 (it
      //should if there is any foliage)
      Ask = (1.0 - exp(-extinction*((sfk*Wfk)/Ack)))*Ack;
      //Qabs from one sector
      s[i] = s[i]*Ask;
    }
    //Qabs from all sectors
    MJ Qabs = accumulate(s.begin(),s.end(),0.0);
    if (Qabs < 0.0)
      cerr << "Qabs < 0.0 " << Qabs << endl; 
    return Qabs;
  }
};


//Use     Firmament::diffuseForestRegionRadiationSum    to    describe
//surrounding  plants.   The  documentation  is  in  Firmament.cc  but
//REMEMBER to  create file 'fdensity.fun' (exact this  name). The file
//has the stand  density as a function of stand  age.  Usage is simply
//ForEach(t,DiffuseForestRadiation<TS,BUD>(Hc,La,K)), where  Hc is the
//height  of the crown  base, La  is leaf  area (sf*Wf)  and K  is the
//extinction from Kelllomaki (K(0.2) is somewhat good approximate).
template <class TS,class BUD>
class DiffuseForestRadiation:public AbsorbedRadiation<TS,BUD>{
public:
  DiffuseForestRadiation(VoxelSpace& voxel_space,double Hc,double La, 
			 const ParametricCurve& k,double dens,double start_point)
    :vs(voxel_space),hc(Hc),la(La),K(k),density(dens),sp(start_point){}
  void operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      SetValue(*ts, LGAQin, 0.0);
      SetValue(*ts, LGAQabs, 0.0);
      //Radiation  conditions are not  evaluated if  the segment  has no
      //foliage (in practice  there would be division by  0 in computing
      //absorbed radiation, see below)
      if (GetValue(*ts, LGAWf) < R_EPSILON || GetValue(*ts, LGAL) < R_EPSILON){
	return;
      }

      //1. calculate Qin incoming radiation
      Firmament& f = GetFirmament(GetTree(*ts));
      vector<double> d(3,0.0);//the direction of the i'th sector
      vector<double> s(f.numberOfRegions(),0.0);//number of sectors
      Point p1 = GetPoint(*ts,sp);//start point of the light beam
      Point p2 = GetPoint(GetTree(*ts)); //the position of the tree
      Point p3(p2.getX(),p2.getY(),p1.getZ()); //the point in the main
					       //axis   at   the  same
					       //height     as     the
					       //start point of the light beam 
      double dist = p3 || p1; //distance of the midpoint from the tree stem
      double h = GetValue(GetTree(*ts),LGAH);//tree height
      double z = p1.getZ();//height of the segment midpoint.
      double starmean = GetValue(*ts,LGAstarm); //star mean,extinction
						//coefficient
      //cout << "STARM "  << starmean << " DENS " << density << endl;
      //the Qin sector by sector
      for (int i = 0; i < f.numberOfRegions(); i++){
	vector<VoxelMovement> vm;
	s[i] = f.diffuseForestRegionRadiationSum(i,z,dist,la,starmean,
						 h,hc,d,density);
	PositionVector d1(d[0],d[1],d[2]);
	//Reset the vector of voxel object tags to denote the beam has
	//not hit any segment.
	vs.getBookKeeper().resetVector();
	//Extinction into one direction
	vs.getRoute(vm,p1,d1,K,true,true);
	//calculate the extinction coeffient
	double tau = accumulate(vm.begin(),vm.end(),1.0,
				AccumulatePairwiseExtinction());
	s[i] = s[i]*tau;//the Qin from one sector
	//cout << "TAU " << tau << " s[i] " << s[i] <<endl;
      }
      MJ Q_in = accumulate(s.begin(),s.end(),0.0);
      //Set Qin, it is now needed in calculateAbsorbedRadiation
      SetValue(*ts, LGAQin, Q_in);
      //2. calculate Qabs absorbed radiation
      MJ Q_abs = calculateAbsorbedCfRadiation(*ts,f,s,K);
      SetValue(*ts, LGAQabs, Q_abs);
    }//end if TS
    return;
  }//end operator
private:
  VoxelSpace& vs;
  //Compute hc and la once before calculating forest light
  double hc;//crown limit
  double la;//foliage area of the tree: sf*Wf
  const ParametricCurve& K;//extinction as a function of inclination (from Kellomaki) 
  double density;//Forest density trees/ha
  double sp;//start point of the light beam
};

//PairwiseVoxelSpaceRadiation calculates  the extinction of  the light
//rays  through  the voxel  space  beginning  from  the segment  point
//'sp'=[0:1]  (e.g. 0.5  is the  midpoint  of the  segment) using  the
//methods  in Eco  Mod  98  to calculate  absorbed  radiation for  the
//segment.   It  tries  to  minimize  the  number  of  comparisons  by
//comparing only to the shading objects on path of the light ray.  For
//hardwood the leaf shape is  by default is Ellipse. For conifers this
//is not used  but this same class can be used  for both. The incoming
//light part is the same for both, but the Qabs part is different.
template <class TS,class BUD, class S=Ellipse>
class PairwiseVoxelSpaceRadiation: public AbsorbedRadiation<TS,BUD>{
public:
  //Constructor for hardwoods, K not needed, beam_start center of the leaf
  PairwiseVoxelSpaceRadiation(VoxelSpace& voxel_space):vs(voxel_space),K(0.14),sp(0.5){}
  //Constructor for conifers (K extinction, beam start_point [0:1] on the segment
  PairwiseVoxelSpaceRadiation(VoxelSpace& voxel_space,const ParametricCurve& kfun,
			      double start_point)
    :vs(voxel_space),K(kfun),sp(start_point){}
  PairwiseVoxelSpaceRadiation(const PairwiseVoxelSpaceRadiation& r)
    :vs(r.vs),K(r.K),sp(r.sp){}
  //f: the sky
  //sp: start point of the beam
  //s: vector to contain Qin sector by sector
  void calculatePairwiseQin(const Firmament& f,const Point& sp,vector<double>& s)const{
    vector<double> d(3,0.0);//drection of the i'th sector
    for (int i = 0; i < f.numberOfRegions(); i++){
      vector<VoxelMovement> vm;
      //The potential Qin (brightness of the sky sector)
      s[i] = f.diffuseRegionRadiationSum(i,d);

      PositionVector d1(d[0],d[1],d[2]);
      //Reset the vector of voxel object tags to denote the beam has
      //not hit any segment.
      vs.getBookKeeper().resetVector();
      //Lengths  of  the  light  beam  in different  boxes  and  the
      //extinction coeffient. First, the border stand extinction
      double tau = vs.getBorderStandExtinction(sp,d1);
      tau = 1.0;         //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      if (tau > R_EPSILON){
	//Do not bother  to traverse the voxels for  each sky sector
	//if no light
	vs.getRoute(vm,sp,d1,K,true,true);
	//calculate the extinction coeffient
	tau = tau*accumulate(vm.begin(),vm.end(),1.0,
			     AccumulatePairwiseExtinction());
      }
      s[i] = s[i]*tau;//the Qin from one sector
    }
  }
  //For each segment compute the Qabs  
  void operator()(TreeCompartment<TS,BUD>* tc)const
  {
    Firmament& f = GetFirmament(GetTree(*tc));
    if (CfTreeSegment<TS,BUD>* ts = dynamic_cast<CfTreeSegment<TS,BUD>*>(tc)){
      //Radiation  conditions are not  evaluated if  the segment  has no
      //foliage (in practice  there would be division by  0 in computing
      //absorbed radiation, see below)
      if (GetValue(*ts, LGAWf) < R_EPSILON || GetValue(*ts, LGAL) < R_EPSILON){
	return;
      }
      //s contains Qin sector by sector
      vector<double> s(f.numberOfRegions(),0.0);
      Point p1 = GetPoint(*ts,sp);//start point of the beam on the segment
      //1. the Qin sector by sector
      calculatePairwiseQin(f,p1,s);
      MJ Qin = accumulate(s.begin(),s.end(),0.0);
      //Qin is needed in calculateAbsorbedRadiation
      SetValue(*ts, LGAQin, Qin);
      //2. Calculate now how much segment absorbs from incoming radation.
      MJ Qabs = calculateAbsorbedCfRadiation(*ts,f,s,K);
      SetValue(*ts, LGAQabs, Qabs);
    }//end if (CfTreeSegment<TS,BUD>...
    //For hardwood species compute Qabs for each leaf
    else if (HwTreeSegment<TS,BUD,S>* ts = dynamic_cast<HwTreeSegment<TS,BUD,S>*>(tc)){
      list<BroadLeaf<S>*>& ls = GetLeafList(*ts);
      LeafQabs<S> lqabs;//From CompareLeaves.h
      typename list<BroadLeaf<S>*>::iterator it=ls.begin();
       for (it = ls.begin(); it != ls.end(); it++){
	//s contains Qin sector by sector
	vector<double> s(f.numberOfRegions(),0.0);
	BroadLeaf<S>* l = *it;
	Point p1 = GetCenterPoint(*l);//start point of the beam on the leaf
	//the Qin sector by sector
	calculatePairwiseQin(f,p1,s);
	MJ Qin = accumulate(s.begin(),s.end(),0.0);
	SetValue(*l,LGAQin,Qin);
	lqabs.calculateLeafQabs(f,s,*l);
      }
     }//end if ((HwTreeSegment<TS,BUD,S>*
  }//end operator
private:
  VoxelSpace& vs;
  const ParametricCurve K;//extinction as function of inclination (from Kellomaki) 
  double sp;//The start point [0:1] of the light beam on the segment 
};

//DiffuseVoxelSpaceRadiation  calculates the  extinction of  the light
//rays through  the voxel space  beginning from the  segment midpoint.
//The functor  also calculates the border stand  extinction. See voxel
//space for details.
//The computational  cost is  r*s*O(n), where the  n is the  number of
//segments and  s is the number of  sectors.  Also a cost  is a linear
//route finding  'r' in the voxel  space. 'r' is done  for each sector
//and at worst it is propotional to the size of the voxel space. After
//that  the algorithm  falls back  to older  methods (Eco  Mod  98) to
//calculate absorbed radiation  for the segment. So now  we have three
//related  methods with  decreasing  level of  detail  to compute  the
//light: 1)  pairwise comparison, 2)  this DiffuseVoxelSpaceRasdiation
//approach   and  3)   the   diffuseForestRegionRadiationSum  assuming
//homogenous layer  of foliage  in canopy (implemented  in Firmament).
//Usage: ForEach(tree,DiffuseVoxelSpaceRadiation(voxel_space,K));
template <class TS,class BUD>
class DiffuseVoxelSpaceRadiation: public AbsorbedRadiation<TS,BUD>{
public:
  //Update 'star' and 'val_c' and 'val_b' for extinction in voxel boxes 
  DiffuseVoxelSpaceRadiation(VoxelSpace& voxel_space,const ParametricCurve& kfun,
			     double start)
    :vs(voxel_space),K(kfun),sp(start){}
  void operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      SetValue(*ts, LGAQin, 0.0);
      SetValue(*ts, LGAQabs, 0.0);
      //Radiation  conditions are not  evaluated if  the segment  has no
      //foliage (in practice  there would be division by  0 in computing
      //absorbed radiation, see below)
      if (GetValue(*ts, LGAWf) < R_EPSILON || GetValue(*ts, LGAL) < R_EPSILON){
	return;
      }
      //1) Calculate Qin, incoming radiation
      Firmament& f = GetFirmament(GetTree(*ts));
      vector<double> d(3,0.0);//the direction of the i'th sector
      //s contains Qin sector by sector
      vector<double> s(f.numberOfRegions(),0.0);
      Point p1 = GetPoint(*ts,sp);//start point of the beam on the segment
      //the Qin sector by sector
      for (int i = 0; i < f.numberOfRegions(); i++){
	vector<VoxelMovement> vm;
	s[i] = f.diffuseRegionRadiationSum(i,d);
	PositionVector d1(d[0],d[1],d[2]);
	//Border stand extinction
	double tau = vs.getBorderStandExtinction(p1,d1);
	tau = 1.0;         //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 	//Check if radiation
	if (tau > R_EPSILON){
	  //Lengths of the light beam in boxes
	  vs.getRoute(vm,p1,d1,K,false,true);
	  //calculate the extinction coeffient
	  tau = tau*accumulate(vm.begin(),vm.end(),1.0,
			       AccumulateExtinction(vs));
	}
	s[i] = s[i]*tau;//the Qin from one sector
      }
      MJ Q_in = accumulate(s.begin(),s.end(),0.0);
      //QIn is needed in calculateAbsorbedRadiation
      SetValue(*ts, LGAQin, Q_in);
      //2. Calculate now how much segment absorbs from incoming radation.
      MJ Q_abs = calculateAbsorbedCfRadiation(*ts,f,s,K);
      SetValue(*ts, LGAQabs, Q_abs);

    }//end if TS
    return;
  }//end operator
private:
  VoxelSpace& vs;
  const ParametricCurve& K;//extinction as function of inclination (from Kellomaki) 
  double sp;//Start point [0:1] of the light beam on the segment
};

template <class TS,class BUD>
class InsertCfVoxelObjects{
public:
  InsertCfVoxelObjects(const InsertCfVoxelObjects& ivo):
    vs(ivo.vs),d(ivo.d),dist(ivo.dist),sp(ivo.sp),parts(ivo.parts){}			    
  InsertCfVoxelObjects(VoxelSpace& space, const PositionVector& dir, double distance, 
		     double beam_start, int num_parts)
    :vs(space),d(dir),dist(distance),sp(beam_start),parts(num_parts){}
  void operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
	if (GetValue(*ts,LGAWf) > R_EPSILON) 
	  InsertCfVoxelObject(vs,*ts,d,dist,sp,parts);
    }
    return;
  }
private:
  VoxelSpace& vs;
  const PositionVector d;
  double dist;
  double sp;//start  point [0:1]  of  the light  beam  on the  segment
	    //(e.g. 0.5 is the midpoint)
  int parts;//number of segment parts
};

template <class TS,class BUD,class S>
class InsertHwVoxelObjects{
public:
  InsertHwVoxelObjects(const InsertHwVoxelObjects& ivo):
    vs(ivo.vs),d(ivo.d),dist(ivo.dist),parts(ivo.parts),leaf(ivo.leaf){}			    
  InsertHwVoxelObjects(VoxelSpace& space, const PositionVector& dir, double distance, 
		       int num_parts, bool l)
    :vs(space),d(dir),dist(distance),parts(num_parts),leaf(l){}
  void operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (HwTreeSegment<TS,BUD,S>* ts = dynamic_cast<HwTreeSegment<TS,BUD,S>*>(tc)){
      InsertHwVoxelObject(vs,*ts,d,dist,parts,leaf);
    }
    return;
  }
private:
  VoxelSpace& vs;
  const PositionVector d;//direction to insert
  double dist;//distance where to insert
  int parts;//number of points on the ellipse
  bool leaf;//insert also the leaf itself or not
};

template <class TS, class BUD, class S=Ellipse> 
class InsertVoxelObjects{
public:
  InsertVoxelObjects(VoxelSpace& vs1, const PositionVector& d1,
		     double t1,double sp1,int parts1)
    :vs(vs1),d(d1),t(t1),sp(sp1),parts(parts1),leaf(false){}
  InsertVoxelObjects(VoxelSpace& vs1, const PositionVector& d1,
		     double t1,double sp1,int parts1,bool leaf1)
    :vs(vs1),d(d1),t(t1),sp(sp1),parts(parts1),leaf(leaf1){}
  InsertVoxelObjects(const InsertVoxelObjects& ivo)
    :vs(ivo.vs),d(ivo.d),t(ivo.t),sp(ivo.sp),parts(ivo.parts),leaf(ivo.leaf){}
  void operator()(TreeCompartment<TS,BUD>* tc)const{
    if (HwTreeSegment<TS,BUD,S>* ts = dynamic_cast<HwTreeSegment<TS,BUD,S>*>(tc)){
      InsertHwVoxelObject(vs,*ts,d,t,parts,leaf);
    }//conifer part
    else if (TS* ts = dynamic_cast<TS*>(tc)){
      InsertCfVoxelObject(vs,*ts,d,t,sp,parts);
    }
  }
private:
  VoxelSpace& vs;
  const PositionVector& d;//direction where to insert
  double t;//distance from the original object where to insert
  double sp;//start point  of the light  beam on the  segment (conifer
	    //only)
  int parts;//number of parts to consider
  bool leaf;//Insert  the  leaf  itself   too  into  the  voxel  box
	      //(hartwood only)
};
  
#endif
