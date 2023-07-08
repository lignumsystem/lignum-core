#ifndef PINE_H
#define PINE_H
#include <Lignum.h>

///\brief Classes for PineSegment and PineBud
namespace PineTree{

///\file Pine.h
///\brief PineBud and  PineSegment are  meant to be  generic Pine  segment and bud.
///
///We  need  to  keep  them  as  templates  in  order  to  allow
///inheritance. Notice we partially decide  the type of the tree in the
///constructor, i.e. the  type is Tree<TS,BUD>. If the  segment and bud
///types     were     not    templates     the     tree    would     be
///Tree<PineSegment,PineBud>.  And if,  for example, some other segment
///would  be   needed  inheriting  Pine,   say  ScotsPineSegment:public
///PineSegment,  then there is  no way  to create  a ScotsPine  tree as
///Tree<ScotsPineSegment,ScotsPineBud>,   because  PineSegment  already
///defines as the tree  type Tree<PineSegment,PineBud>. But now, as the
///actual type  of the tree is  left open, inheritance  is possible and
///all the generic algorithms implemented in stl-lignum will compile.

///Scots Pine Functions
enum SPFN {SPFAF,///<Scots pine Initial foliage m^2/kgC   
	   SPFAD,///<Scots pine  Apical Dominance,
	   SPFGO,///<Scots pine Gravelius Order
	   SPFLR,///<Scots pine length - radius relationship, R = f(relative_light)*R 
	   SPFNA,///<Scots pine Needle Angle
	   SPFSF,///<Scots pine Specific Leaf Area
	   SPSD,///<Scots pine Sapwood Down as a function of Gravelius order
	   SPWD,///<Scots pine density of growth ring as function of tree age
	   SPEBHF,///<Scots pine Extended Borcher-Honda lambda value function
	   SPBVF///<Scots pine Bud View function
};

///Enumeration for SetValue, GetValue in ScotsPine
enum SPAD {SPAAsDown,///<Sapwood down
	   SPCrownRatio,///<Crown ratio: CrownL/TreeH
	   SPHc,///<Height at crown limit
	   SPHwStart,///<Start year of heartwood buld up
	   SPrue ///< Radiation use efficiency
};

///Scots Pine Parameter Double SPPD
///Extended Borchert-Honda (1 = true,  < 1 = false)
enum SPPD {
  SPis_EBH ///< Extended Borchert-Honda ("boolean") 
};


  template <class TS,class BUD> class PineBud;
  enum LGMSPAD {
    LGAplength,///< Path length from base to segment
    LGAphysage ///< Physiological age
  };



template <class TS, class BUD>
class PineSegment: public CfTreeSegment<TS,BUD>{
  ///GetValue for PineSegment
  friend LGMdouble GetValue(const PineSegment& ts,LGMSPAD name){
    if (name == LGAplength)
      return ts.plength;
    else if (name == LGAphysage)
      return ts.phys_age;
    else{
      LGMError("GetValue PineSegment unknown name");
      return 0.0;
    }
  }
  ///SetValue for PineSegment
  friend LGMdouble SetValue(PineSegment& ts,LGMSPAD name,LGMdouble val){
    LGMdouble old_val = GetValue(ts,name);
    if (name == LGAplength)
      ts.plength = val;
    else if (name == LGAphysage)
      ts.phys_age = val;
    else{
      LGMError("SetValue PineSegment unknown name");
    }
    return old_val;
  }

public:
  ///\brief PineSegment constructor sets the initial segment dimensions.
  ///\param p Base point
  ///\param d Direction
  ///\param go Gravelius order
  ///\param l Length
  ///\param r Initial radius
  ///\param rh Intial heartwood radius
  ///\param tree The tree segment belongs to
  ///\post Segment radius == LGPlr*L
  ///\post Foliage height == LGPnl*sin(LGPna)
  ///\post Radius to foliage limit == LGAR+LGAHf
  ///\post Heartwood radius = (LGPxi/(1.0+LGPxi))*LGAR
  ///\post Foliage mass = LGPaf*LGASa
  PineSegment(const Point& p,const PositionVector& d,
	      const LGMdouble go,const METER l,
	      const METER r,const METER rh,Tree<TS,BUD>* tree)
    :CfTreeSegment<TS,BUD>(p,d,go,l,r,rh,tree),plength(0.0),phys_age(0.0)
    {
      //Set radius according to length radius ratio:
      //As we multiply lr should be in [0,1]
      double r_new = GetValue(*tree,LGPlr)*GetValue(*this,LGAL);
      SetValue(*this,LGAR,r_new);
      //compute the radius to foliage limit (Rf)
      //the given parameters are needle length (nl) and the
      //needle angle (na)
      //Rf = hf + tsa.R, where hf is height of the foliage (hf = nl * sin(na))
      SetValue(*this,LGAHf,GetValue(*tree,LGPnl)*sin(GetValue(*tree,LGPna)));
      SetValue(*this,LGARf,GetValue(*this,LGAR)+GetValue(*this,LGAHf));
      //Set the initial heartwood radius 
      SetValue(*this,LGARh,sqrt((GetValue(*tree,LGPxi)*GetValue(*this,LGAA))/PI_VALUE));
      //LGPxi defines the area of heartwood in relation to sapwood, i.e.
      //Ah = LGPxi * As ; this results in the following equation for Rh
      SetValue(*this,LGARh,sqrt(GetValue(*tree,LGPxi)/(1.0+GetValue(*tree,LGPxi)))*GetValue(*this,LGAR));
      //compute the initial mass of the foliage
      //1. compute the surface area (Sa) of the segment cylinder
      //2. initial mass of the foliage is then af*Sa ((kg/m2)*m2)
      LGMdouble wf =  GetValue(*tree,LGPaf)*GetValue(*this,LGASa);
      SetValue(*this,LGAWf,wf);
      //Remember the original foliage
      SetValue(*this,LGAWf0,wf);
      //Remember original sapwood area As0
      SetValue(*this,LGAAs0,GetValue(*this,LGAAs));
      //incoming radiation
      SetValue(*this,LGAQin,0.0);
    } 
private:
  LGMdouble plength; ///< Path length  from the base of the  tree to a segment
  ///Physiological age of the bud. Different from chronological age. Implementation depended.
  ///Can trigger for example growth habit trait in tree crown
  LGMdouble phys_age; 
};




///PineBud has  SetValue and  GetValue functions to  update and  to use
///PineBudData in order to pass information to L-system and back. 
enum PBNAME {PBDATA};
///\brief PineBudData  is  intented  pass data  between LIGNUM  model and  L-system.
///
///A  simpler example than  in  SugarMaple. Currently  PineBudData  has *state*,  *foliage
///mass* (of  the mother segment) and  the direction of  the bud (looks
///like we need the orientation of the bud in world coordinates, at the
///very least it will make  life easier).  See PineBud for SetValue and
///GetValue methods  (used by the  L-system implementation).  Obviously
///this is  not the  final set of  attributes for PineBudData  that are
///required,  needed  or useful,  but  the  implementation  is open  to
///discussion.
class PineBudData{
  ///GetDirection returns  the direction of  the bud (not used  in data
  ///exchange but makes life easier)
  friend PositionVector GetDirection(const PineBudData& data){
    return PositionVector(data.x,data.y,data.z);
  }
public:
  ///A  couple of  constructors to  initialize members.  Recommended in
  ///general.
  PineBudData():state(ALIVE),fm(0.0),ip(1.0),x(0.0),y(0.0),z(0.0),length(0.0),view(0.0),phys_age(0.0){}
  PineBudData(double s, double fol, double rl, double len, double physiol_age=0.0)
    :state(s),fm(fol),ip(rl),x(0.0),y(0.0),z(0.0),length(len), view(0.0),phys_age(physiol_age) {}
  PineBudData(const PineBudData& pbd)
    :state(pbd.state),fm(pbd.fm),ip(pbd.ip),x(pbd.x),y(pbd.y),z(pbd.z),
     length(pbd.length),view(pbd.view),phys_age(pbd.phys_age){}
  double state; //ALIVE,DEAD, FLOWER, etc
  double fm;//foliage mass (of the mother segment)
  double ip;//qin/TreeQinMax, i.e. relative light
  ///Direction   is   PositionVector(x,y,z).    Note  you   can't   use
  ///PositionVector  here, because  internally it  has  implemented the
  ///(x,y,z)  as an  stl-vector.  During  passing the  information from
  ///LIGNUM to L-system and back, L-system uses the sizeof(PineBudData)
  ///built-in  function to  access  this PineBudData  structure in  the
  ///string.  And the sizeof(vector<double>) is something else than the
  ///sizeof three floating point numbers. In general, to be on the safe
  ///side,  do not  use  references or  pointers  or structures  within
  ///structures to  pass the information, just  fundamental c/c++ types
  ///corresponding to basic storage units.
  double x;///< X coordinate
  double y;///< Y coordinate
  double z;///z Z coordinate
  double length; ///<Length of the mother segment
  ///\attention Not documented
  double view;
  ///Physiological age of the bud. Different from chronological age.Implementation depended.
  ///Can trigger for example growth habit trait in tree crown
  double phys_age;
};

///PineBud has additional attributes: \sa fm_mother_segment \sa length_mother_segment \sa phys_age
template <class TS, class BUD>
class PineBud: public Bud<TS,BUD>{
  ///GetValue for PineBud 
  template <class TS1,class BUD1>
  friend double GetValue(PineBud<TS1,BUD1>& b,LGMSPAD name){
    if (name == LGAphysage){
      return b.phys_age;
    }
    else{
      LGMError("GetValue PineBud unknown name");
    }
    return 0.0;
  }
  ///SetValue for PineBud for PineBudData
  template <class TS1,class BUD1>
  friend PineBudData SetValue(PineBud<TS1,BUD1>& b,
			      PBNAME name,const PineBudData& data){
    PineBudData old_data = GetValue(b,name); 
    SetValue(b,LGAstate,data.state);
    SetValue(b,LGAip,data.ip);
    b.fm_mother_segment = data.fm;
    b.length_mother_segment = data.length;
    //Do not update  the direction (x,y,z), it would override  the work of the
    //turtle in L-system
    b.view = data.view;
    b.phys_age = data.phys_age;
    return old_data;
  }
  ///GetValue for  PineBud for PineBudData
  ///Construct PineBudData from its parts/constituents
  template <class TS1,class BUD1>
  friend PineBudData GetValue(const PineBud<TS1,BUD1>& b,PBNAME name){
    PineBudData pbdata;
    if (name == PBDATA){
      pbdata.state = GetValue(b,LGAstate);
      pbdata.fm = b.fm_mother_segment;
      pbdata.ip = GetValue(b,LGAip);
      pbdata.length = b.length_mother_segment;
      pbdata.view = b.view;
      pbdata.phys_age = b.phys_age;
      //Pass the direction to  L-system, user can access the direction
      //easily by calling GetDirection.
      pbdata.x = GetDirection(b).getX();
      pbdata.y = GetDirection(b).getY();
      pbdata.z = GetDirection(b).getZ();
    }
    else
      cout << " PineBudData error, name: " << name << " not known" << endl;
    return pbdata;
  }
public:
  ///\param p Point
  ///\param d Direction
  ///\param go Gravelius order
  ///\param tree Tree bud belongs to
  PineBud(const Point& p, const PositionVector& d, 
	  const LGMdouble go, Tree<TS,BUD>* tree)
    :Bud<TS,BUD>(p,d,go,tree),view(0.0),fm_mother_segment(0.0),length_mother_segment(0.0),phys_age(0.0){}
  LGMdouble view;
private:
  LGMdouble fm_mother_segment; ///< Foliage mass of mother segment
  LGMdouble length_mother_segment; ///< Length of the mother segment
  ///Physiological age of the bud. Different from chronological age. Implementation depended.
  ///Can trigger for example growth habit trait in tree crown
  LGMdouble phys_age;
};

//Prints Qin, Qabs, P, R, Wf, As and LGAAh
template <class TS, class BUD>
class CheckQinQabsPRWsWfAsAh{
 public:
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* ts = dynamic_cast<TS*>(tc)){
	if (GetValue(*ts,LGAQabs) != 0.0){
	  cout << GetValue(*ts,LGAQin) << " " << GetValue(*ts,LGAQabs) << " "
	       << GetValue(*ts,LGAP) << " " << GetValue(*ts,LGAM) << " "
	       << GetValue(*ts,LGAWs) << " "
	       << GetValue(*ts,LGAWf) << " " << GetValue(*ts,LGAAs) << " "
	       << GetValue(*ts,LGAAh) << " " << flush;
	  cout << GetPoint(*ts).getX() << " " << GetPoint(*ts).getY() << " "
	       <<  GetPoint(*ts).getZ() << endl;
	}
      }
      return tc;
    }
};	  

   

 
template <class TS,class BUD>
class KillBuds{
public:
  double operator()(double& qin, TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
	qin = GetValue(*ts,LGAQin);
    }
    else if (BUD* b = dynamic_cast<BUD*>(tc)){
      //absloute light
      //Firmament& f = GetFirmament(GetTree(*b));
      //double B = f.diffuseBallSensor();
      //Best light in the tree
      double B = GetValue(GetTree(*b),TreeQinMax);
      const ParametricCurve& fip = GetFunction(GetTree(*b),LGMIP);
      double irel = fip(qin/B);
      if (irel < R_EPSILON){
	//cout << "Bud Killed" << endl;
	SetValue(*b,LGAstate,DEAD);
      }
    }
    return qin;
  }
};
     


template <class TS,class BUD>
class SetSegmentLength{
public:
  SetSegmentLength(double lamda):l(lamda),apical(1.0){}
  SetSegmentLength& operator=(const SetSegmentLength& sl){
    l = sl.l;
    apical = sl.apical;
    return *this;
  }
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const
  {
     if (TS* ts = dynamic_cast<TS*>(tc)){
       if (GetValue(*ts,LGAage) == 0.0){
	 const ParametricCurve& fip = GetFunction(GetTree(*ts),LGMIP);
	 //TreeQinMax  should  work also  for  open trees:  TreeQinMax
	 //should  then  equal  to  Ball  sensor  reading  Open  grown
	 //branching         effect
	 double GravOrder = GetValue(*ts,LGAomega); ////////////////
	 double Lvi   =1.0-(GravOrder-1.0)*GetValue(GetTree(*ts),LGPq); ////////////////
	 if (Lvi < 0.0)
	   Lvi = 0.0;
	 //Vigour index
	 double vi = GetValue(*ts,LGAvi);
	 //In Tree Physiology for side branches fp is for example as follows:
	 //fp = (1-a)f(vi) = (1-0.2)(0.15+0.85vi) = 0.8(0.15+0.85vi)
	 const ParametricCurve& fvi = GetFunction(GetTree(*ts),LGMVI);
	 //Lvi = apical*(0.05+0.95*Lvi);
	 Lvi = apical*fvi(vi)*Lvi; /////////////////////////
	 //experimental   forest   grown  double   Lq   =  pow(1.0   -
	 //GetValue(GetTree(*ts),q),GetValue(*ts,omega)-1);    relative
	 //light, if TreeQinMax  is ball sensor reading, it  is as for
	 //open grown pine
	 double B = GetValue(GetTree(*ts),TreeQinMax);
	 double L_new = l*Lvi*fip(GetValue(*ts,LGAQin)/B);
         //Eero's idea distance from ground
         //double z = GetPoint(*ts).getZ();
	 //Path length
	 //double plength = GetValue(*ts,LGAplength);
	 //         L_new = L_new*(sqrt((30.0-plength)/30.0)); ///////////////////
	 L_new = max(L_new,0.0);
	 //don't allow segments shorter than LGPmin
	 if (L_new < GetValue(GetTree(*ts),LGPLmin))     //////////////////////////////////////
	   L_new = 0.0;
	 SetValue(*ts,LGAL,L_new);
	 //Initial radius
	 SetValue(*ts,LGAR,GetValue(GetTree(*ts),LGPlr)*L_new);
	 //Reset previous Rh!!!!
	 SetValue(*ts,LGARh,0.0);
	 //Initial heartwood
	 SetValue(*ts,LGARh,sqrt((GetValue(GetTree(*ts),LGPxi)*GetValue(*ts,LGAAs))/PI_VALUE));
	 //Initial foliage
	 SetValue(*ts,LGAWf,GetValue(GetTree(*ts),LGPaf)*GetValue(*ts,LGASa));

	 //Remember initial foliage!!
	 SetValue(*ts,LGAWf0,GetValue(*ts,LGAWf));

 	 //Remember original sapwood area As0
	 SetValue(*ts,LGAAs0,GetValue(*ts,LGAAs));
       }
     }//segment
     else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
	 list<TreeCompartment<TS,BUD>*> & ls = GetTreeCompartmentList(*axis);
	 //new brancing [TS,BP,B]
	 if (ls.size() == 3)
	   apical = GetValue(GetTree(*axis),LGPapical);
	 //old branch
	 else
	   apical = 1.0;
     }
     return tc;
  }
private:
  double l;///<Lamda to iterate segment lengths
  mutable double apical; ///<Apical dominance, 1 or less, e.g. 0.8
};

///This  is must be  the same  as diameterGrowth  method, but  we can't
///change the segment's dimensions.
template <class TS,class BUD>
class TryDiameterGrowth{
public:
  DiameterGrowthData& operator()(DiameterGrowthData& data, TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      if (GetValue(*ts,LGAage) == 0){//New segment
	//Collect the masses
	SetValue(data,DGWfnew,GetValue(*ts,LGAWf));
	SetValue(data,DGWf,GetValue(*ts,LGAWf));
	SetValue(data,DGWs,GetValue(*ts,LGAWs));
	//Sapwood requirement
	SetValue(data,LGAAs,GetValue(*ts,LGAAs));
      }
      else{//old segment
	const ParametricCurve& fm = GetFunction(GetTree(*ts),LGMFM);
	//Sapwood requirement of  remaining foliage, assume fm returns
	//proportion of initial foliage present, declining function of
	//age from 1 to 0.
	LGMdouble Asr = fm(GetValue(*ts,LGAage))*GetValue(*ts,LGAAs0);
	//sapwood area from above
	LGMdouble Asu = GetValue(data,LGAAs); 
	//own heartwood, assume aging has done
	LGMdouble Ahown  = GetValue(*ts,LGAAh);
	//requirement for new radius: sapwood above + own heartwood + own foliage 
	LGMdouble Rnew = sqrt((Asu + Ahown + Asr)/PI_VALUE);
	//compare Rnew to R, choose max
	Rnew = max(Rnew, GetValue(*ts,LGAR));
	//New sapwood requirement, thickness growth
	double Asnew = PI_VALUE*pow(Rnew,2.0) -  GetValue(*ts,LGAA);
	
	//Mass of the new sapwood 
	double Wsnew = GetValue(GetTree(*ts),LGPrhoW)*Asnew*GetValue(*ts,LGAL); 

	//Down goes new plus existing sapwood area 
	SetValue(data,LGAAs,Asnew+GetValue(*ts,LGAAs)); 
	//Mass of sapwood used in diamater growth
	SetValue(data,DGWs,GetValue(data,DGWs)+Wsnew);
	//Total foliage
	SetValue(data,DGWf,GetValue(data,DGWf)+GetValue(*ts,LGAWf));
      }
    }
    return data;
  }
};




template <class TS,class BUD>
class PrintAxis{
public:
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      cout << "Age: " << GetValue(*ts,LGAage)  <<  " L: " << GetValue(*ts,LGAL) 
	   << " Qin: " << GetValue(*ts,LGAQin) << " Qabs: " << GetValue(*ts,LGAQabs)
	   << " Qin/QinMax: " << GetValue(*ts,LGAQin)/ GetValue(GetTree(*ts),
							     TreeQinMax)
	   << " Wf: " << GetValue(*ts,LGAWf) <<  " P: " << GetValue(*ts,LGAP) 
	   << " M: " << GetValue(*ts,LGAM) << endl
	   << " R: " << GetValue(*ts,LGAR)   <<  " A: " << GetValue(*ts,LGAA)   
	   << " As: " << GetValue(*ts,LGAAs) << " Ah: " << GetValue(*ts,LGAAh) << endl;
      cout << " P2: " << GetEndPoint(*ts) << endl;
    }
    return tc;
  }
};
				       
//LPineGrowthFunction  will  implement in  the  function operator  the
//elongation/shortening of  segments, simulation of  diameter and root
//growth.   The it  returns  P-M-G.   Use it  with  some root  finding
//algorithm.  For  example Bisection. See function  operator that does
//the job.  L is  the functor  for elongation and  D for  the diameter
//growth
template <class TS,class BUD, class L, class D>
class LPineGrowthFunction{
public:
  LPineGrowthFunction(Tree<TS,BUD>& tree)
    :t(tree),P(-1.0),M(-1.0){}
  double operator()(double l)const;
  void init();
  double getP()const{return P;}
  double getM()const{return M;}
  double getL()const{return lambda;}
private:
  Tree<TS,BUD>& t;
  double P;
  double M;
  mutable double lambda;//save lambda
};


///Collect photosynthates and respiration once per growth allocation.
template <class TS,class BUD,class L,class D>
void LPineGrowthFunction<TS,BUD,L,D>::init()
{
  P = GetValue(t,TreeP);
  M = GetValue(t,TreeM);
  //if (P <= M)
  //cout << "P: " << P << " M: " << M << " P-M: " << P-M << endl;
} 

template <class TS,class BUD,class L,class D>
double LPineGrowthFunction<TS,BUD,L,D>::operator()(double l)const
{
  DiameterGrowthData data;
  //0.Save current value of lambda
  lambda = l;
  //1.Elongate or shorten segment lengths
  ForEach(t,L(l));

  //2. Simulate  diameter  growth  and  collect  sapwood  and  foliage
  //masses.
  data = AccumulateDown(t,data,D());   
  

  //3. return P-M-G where G = iWs(l) + iWfnew(l) + iWrnew(l)
  //iWs = sapwood mass: new segments + thickening
  //iWfnew = new foliage
  //iWrnew = new roots = ar*iWfnew

  return P - M - GetValue(data,DGWs) - GetValue(data,DGWfnew) - GetValue(t,LGPar)* GetValue(data,DGWfnew);
}

template <class TS, class BUD>
class ForwardWf{
public:
  double& operator()(double& wf, TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      wf = GetValue(*ts,LGAWf);
    }
    else if (BUD* bud = dynamic_cast<BUD*>(tc)){
      PineBudData data = GetValue(*bud,PBDATA);
      data.fm = wf;
      SetValue(*bud,PBDATA,data);
    }
    return wf;
  }
};

template <class TS, class BUD>
class ForwardSegLen{
public:
  double& operator()(double& len, TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      len = GetValue(*ts,LGAL);
    }
    else if (BUD* bud = dynamic_cast<BUD*>(tc)){
      PineBudData data = GetValue(*bud,PBDATA);
      data.length = len;
      SetValue(*bud,PBDATA,data);
    }
    return len;
  }
};

template <class TS, class BUD>
class IncrementAgeDown{
public:
  int& operator()(int& counter,TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      SetValue(*ts,LGAage,counter);
      counter++;
    }
    return counter;
  }
};


///This  can be  used  to  set foliage  afterwards,  say, for  measured
///architectural  model trees.  ForEach(t,SetFoliage) will  traverse the
///tree and apply the functor to each segment.
template <class TS, class BUD>
class SetFoliage{
public:
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      const ParametricCurve& fm = GetFunction(GetTree(*ts),LGMFM);
      //Original foliage
      LGMdouble wf =  GetValue(GetTree(*ts),LGPaf)*GetValue(*ts,LGASa);
      //Annual senescence
      int a = GetValue(*ts,LGAage); 
      wf = fm(a)*wf;
      SetValue(*ts,LGAWf,wf);
    }
    return tc;
  }
};


template <class TS, class BUD>
class PrintSegmentQin{
public:
  void operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      if (GetValue(*ts,LGAage) == 0 && GetValue(*ts,LGAomega) <= 2)
	cout << "Qin: " <<  GetValue(*ts, LGAQin) 
	     << " Point: " << GetPoint(*ts);
     }
  }
};

template <class TS, class BUD>
class GetTopQin{
public:
  LGMdouble operator()(LGMdouble qin,TreeCompartment<TS,BUD>* tc)const{
    if (TS* ts = dynamic_cast<TS*>(tc)){
      if (GetValue(*ts,LGAage) == 0)
	qin = GetValue(*ts,LGAQin);
    }
    return qin;
  }
};


template <class TS, class BUD>
class ShortenSegment{
 public:
  LGMdouble& operator()(LGMdouble& c, TreeCompartment<TS,BUD>* tc)const;
};

//The 'c'  denotes if a  branch or  part of it  is alive (c=1)  or not
//(c=0).  If at the end of an axis  a bud is dead 'c' is set to 0.  In
//a branching point 'c':s are summed and passed down to segment below.
//If some of the buds is alive then sum of 'c':s is not 0.
template <class TS, class BUD>
LGMdouble& ShortenSegment<TS,BUD>::operator()(LGMdouble& c, 
					      TreeCompartment<TS,BUD>* tc)const
{
    if (BUD* b = dynamic_cast<BUD*>(tc)){
      if (GetValue(*b,LGAstate)==DEAD)
	  c = 0.0;
      else{
	//Alive bud
	c = 1.0;
      }
    }
    else if (TS* ts =  dynamic_cast<TS*>(tc)){
      if (c == 0.0){
	//All buds and segments above dead, shorten segment
	//cout << "Shorten segment" << endl;
	SetValue(*ts,LGAL,0.0);
      }
      else{
	//Denote branch alive
	c = 1.0;
      }
    }
    return c;
}

//Using L-systems  we 'blindly' create new  segments. After allocation
//some of  the segments migh be 0  length. We do not  know this before
//hand because there  is a treshold length LGPmin. This  is a clean up
//routine to kill  buds in front of 0 length  segments to prevent them
//grow any further.
template <class TS, class BUD> 
class KillBudsAfterAllocation{
public:
  bool& operator()(bool& kill, TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      METER l = GetValue(*ts,LGAL);
      if (l <= R_EPSILON){
	kill = true;
      }
    }
    else if (BUD* b = dynamic_cast<BUD*>(tc)){
      if (kill == true){
	SetValue(*b,LGAstate,DEAD);
      }
    }
    return kill;
  }
};

///Calculate     path    length     for     each    segment.
///Usage:<br>
///double plength=0.0<br>
///PropagateUp(t,plength,PathLength())
template <class TS,class BUD>
class PathLength{
public:
  LGMdouble operator()(LGMdouble& l, 
		       TreeCompartment<TS,BUD>* tc)const{
    if (TS* ts = dynamic_cast<TS*>(tc)){
      //This works for new segments (age  == 0) too, l is just ignored
      //in buds
      SetValue(*ts,LGAplength,l);
      l = l + GetValue(*ts,LGAL);
    }
    return l;
  }
};

///Pass physiological age of the buds to the newly created segments
///\pre L-system has just created new segments
///\pre Segment age == 0.0
///Usage: <br>
///LGMdouble phys_age=0.0;<br>
///AccumulateDown(tree,phys_age,PassPhysiologicalAge<TS,BUD>())
///\post Segment phys. age == Mother bud phys. age
template <class TS, class BUD>
class PassPhysiologicalAge{
public:
  LGMdouble operator()(LGMdouble& phys_age, 
		       TreeCompartment<TS,BUD>* tc)const{
    if (BUD* b = dynamic_cast<BUD*>(tc)){
      phys_age = GetValue(*b,LGAphysage);
    }
    else if (TS* ts = dynamic_cast<TS*>(tc)){
      if (GetValue(*ts,LGAage) == 0.0){
	SetValue(*ts,LGAphysage,phys_age);
      }
    }
    return phys_age;
  }
};



}
#endif
