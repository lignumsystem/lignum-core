#ifndef PINE_H
#define PINE_H
#include <Lignum.h>
//PineBud and  PineSegment are  meant to be  generic Pine  segment and
//bud.   We  need  to  keep  them  as  templates  in  order  to  allow
//inheritance. Notice we partially decide  the type of the tree in the
//constructor, i.e. the  type is Tree<TS,BUD>. If the  segment and bud
//types     were     not    templates     the     tree    would     be
//Tree<PineSegment,PineBud>.  And if,  for example, some other segment
//would  be   needed  inheriting  Pine,   say  ScotsPineSegment:public
//PineSegment,  then there is  no way  to create  a ScotsPine  tree as
//Tree<ScotsPineSegment,ScotsPineBud>,   because  PineSegment  already
//defines as the tree  type Tree<PineSegment,PineBud>. But now, as the
//actual type  of the tree is  left open, inheritance  is possible and
//all the generic algorithms implemented in stl-lignum will compile.

//PineSegment constructor implements:  segment radius R =lr*L, foliage
//height Hf=nl*sin(na),  radius to foliage  Rf=R+Hf, initial heartwood
//Rh=sqrt(xi*A/PI)  and   initial  foliage  mass   Wf=af*Sa.  See  the
//constructor for details.

//PineBud has  SetValue and  GetValue functions to  update and  to use
//PineBudData in order to pass information to L-system and back. 

template <class TS,class BUD> class PineBud;

template <class TS, class BUD>
class PineSegment: public CfTreeSegment<TS,BUD>{
 public:
  PineSegment(const Point& p,const PositionVector& d,
	      const LGMdouble go,const METER l,
	      const METER r,const METER rh,Tree<TS,BUD>* tree)
    :CfTreeSegment<TS,BUD>(p,d,go,l,r,rh,tree)
    {
      //Set radius according to length radius ratio:
      //As we multiply lr should be [0:1]
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
      //compute the initial mass of the foliage
      //1. compute the surface area (Sa) of the segment cylinder
      //2. initial mass of the foliage is then af*Sa ((kg/m2)*m2)
      LGMdouble wf =  GetValue(*tree,LGPaf)*GetValue(*this,LGASa);
      SetValue(*this,LGAWf,wf);
      //Remember original sapwood area As0
      SetValue(*this,LGAAs0,GetValue(*this,LGAAs));
      //incoming radiation
      SetValue(*this,LGAQin,0.0);
    }    
};

//PineBudData  is  intented  to  be  the data  structure  that  passes
//information  between LIGNUM  model and  L-system. A  simpler example
//than  in  SugarMaple. Currently  PineBudData  has 'state',  'foliage
//mass' (of  the mother segment) and  the direction of  the bud (looks
//like we need the orientation of the bud in world coordinates, at the
//very least it will make  life easier).  See PineBud for SetValue and
//GetValue methods  (used by the  L-system implementation).  Obviously
//this is  not the  final set of  attributes for PineBudData  that are
//required,  needed  or useful,  but  the  implementation  is open  to
//discussion
enum PBNAME {PBDATA};//The name of the data structure
class PineBudData{
  //GetDirection returns  the direction of  the bud (not used  in data
  //exchange but makes life easier)
  friend PositionVector GetDirection(const PineBudData& data){
    return PositionVector(data.x,data.y,data.z);
  }
public:
  //A  couple of  constructors to  initialize members.  Recommended in
  //general (read: required!!).
  PineBudData():state(ALIVE),fm(0.0){}
  PineBudData(double s, double fol):state(s),fm(fol){}
  double state; //ALIVE,DEAD, FLOWER, etc
  double fm;//foliage mass (of the mother segment)
  //Direction   is   PositionVector(x,y,z).    Note  you   can't   use
  //PositionVector  here, because  internally it  has  implemented the
  //(x,y,z)  as an  stl-vector.  During  passing the  information from
  //LIGNUM to L-system and back, L-system uses the sizeof(PineBudData)
  //built-in  function to  access  this PineBudData  structure in  the
  //string.  And the sizeof(vector<double>) is something else than the
  //sizeof three floating point numbers. In general, to be on the safe
  //side,  do not  use  references or  pointers  or structures  within
  //structures to  pass the information, just  fundamental c/c++ types
  //corresponding to basic storage units.
  double x;
  double y;
  double z;
};

template <class TS, class BUD>
class PineBud: public Bud<TS,BUD>{
  template <class TS1,class BUD1>
  friend PineBudData SetValue(PineBud<TS1,BUD1>& b,
			      PBNAME name,const PineBudData& data){
    PineBudData old_data = GetValue(b,name); 
    SetValue(b,LGAstate,data.state);
    b.fm_mother_segment = data.fm;
    //Do not update  the direction, it would override  the work of the
    //turtle in L-system
    return old_data;
  }
  template <class TS1,class BUD1>
  friend PineBudData GetValue(const PineBud<TS1,BUD1>& b,PBNAME name){
    PineBudData pbdata;
    if (name == PBDATA){
      pbdata.state = GetValue(b,LGAstate);
      pbdata.fm = b.fm_mother_segment;
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
  PineBud(const Point& p, const PositionVector& d, 
	  const LGMdouble go, Tree<TS,BUD>* tree)
    :Bud<TS,BUD>(p,d,go,tree),fm_mother_segment(0.0){}
private:
  LGMdouble fm_mother_segment;
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
	       << GetValue(*ts,P) << " " << GetValue(*ts,LGAM) << " "
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
      Firmament& f = GetFirmament(GetTree(*b));
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
    l = sl.lamda;
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
	 //branching         effect        double         Lvi        =
	 //1.0-(GetValue(*ts,omega)-1.0)*GetValue(GetTree(*ts),q);
	 //Vigour index
	 double vi = GetValue(*ts,LGAvi);
	 //In Tree Physiology for side branches fp is for example as follows:
	 //fp = (1-a)f(vi) = (1-0.2)(0.15+0.85vi) = 0.8(0.15+0.85vi)
	 const ParametricCurve& fvi = GetFunction(GetTree(*ts),LGMVI);
	 //Lvi = apical*(0.05+0.95*Lvi);
	 double Lvi = apical*fvi(vi);
	 //experimental   forest   grown  double   Lq   =  pow(1.0   -
	 //GetValue(GetTree(*ts),q),GetValue(*ts,omega)-1);    relative
	 //light, if TreeQinMax  is ball sensor reading, it  is as for
	 //open grown pine
	 double B = GetValue(GetTree(*ts),TreeQinMax);
	 double L_new = l*Lvi*fip(GetValue(*ts,LGAQin)/B);
         //Eero's idea distance from ground
         //double z = GetPoint(*ts).getZ();
	 //Path length
	 double plength = GetValue(*ts,LGAplength);
         L_new = L_new*(sqrt((30.0-plength)/30.0));
	 L_new = max(L_new,0.0);
	 //don't allow segments shorter than 1cm
	 if (L_new <= 0.010)
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
  double l;//Lamda to iterate segment lengths
  mutable double apical; //Apical dominance, 1 or less, e.g. 0.8
};

//This  is must be  the same  as diameterGrowth  method, but  we can't
//change the segment's dimensions.
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
class CollectNewFoliage{
public:
  LGMdouble& operator()(LGMdouble& wf, TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      if (GetValue(*ts,LGAage) == 0.0){
	wf += GetValue(*ts,LGAWf);
      }
    }
    return wf;
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
//the job.
template <class TS,class BUD>
class LPineGrowthFunction{
public:
  LPineGrowthFunction(Tree<TS,BUD>& tree):t(tree),P(-1.0),M(-1.0){}
  double operator()(double l);
  void init();
  double getP()const{return P;}
  double getM()const{return M;}
private:
  Tree<TS,BUD>& t;
  double P;
  double M;
};


//Collect photosynthates and respiration once per growth allocation.
template <class TS,class BUD>
void LPineGrowthFunction<TS,BUD>::init()
{
  P = GetValue(t,TreeP);
  M = GetValue(t,TreeM);
  //if (P <= M)
  //cout << "P: " << P << " M: " << M << " P-M: " << P-M << endl;
} 

template <class TS,class BUD>
double LPineGrowthFunction<TS,BUD>::operator()(double l)
{
  DiameterGrowthData data;
  

  //1.Elongate or shorten segment lengths
  ForEach(t,SetSegmentLength<TS,BUD>(l));

  //2. Simulate  diameter  growth  and  collect  sapwood  and  foliage
  //masses.
  data = AccumulateDown(t,data,TryDiameterGrowth<TS,BUD>());   
  

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


template <class T>
class Max{
public:
  const T& operator()(const T& a, const T& b)const
  {
    return max(a,b);
  }
};

//This  can be  used  to  set foliage  afterwards,  say, for  measured
//architectural  model trees.  ForEach(t,SetFoliage) will  traverse the
//tree and apply the functor to each segment.
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
	      LGMdouble& ShortenSegment<TS,BUD>::operator()(LGMdouble& c, TreeCompartment<TS,BUD>* tc)const
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

#endif
