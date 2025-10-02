/// \file TreeSegmentI.h
/// \brief Tree segment implementation
#ifndef TREESEGMENTI_H
#define TREESEGMENTI_H

#include <Tree.h>

namespace Lignum{
  //Please orginize headers or rewrite "<<" operator
  //to remove this declation; 
template <class TS,class BUD> class CfTreeSegment;

template <class TS,class BUD>
ofstream &operator << (ofstream& os, TreeSegment<TS,BUD>& ts)
{	
  PositionVector pv = GetDirection(ts); 
  Point p = GetPoint(ts);

  os << "DIRECTION " << pv.getX() << " " << pv.getY() << " " << pv.getZ()
     << "  POSITION " << p.getX() << " " << p.getY() << " " << p.getZ() 
     << "  RADIUS " << GetValue(ts,LGAR) << " " 
     << "  LENGTH " << GetValue(ts,LGAL) << "  AGE " << GetValue(ts,LGAage) << flush;
  
  os << " END" << endl;
  
  return os;
}

template <class TS,class BUD>
ofstream &operator << (ofstream& os, Bud<TS,BUD>& bud)
{	
  PositionVector pv = GetDirection(bud); 
  Point p = GetPoint(bud);
  os << "DIRECTION " << pv.getX() << " " << pv.getY() << " " << pv.getZ() 
     << "  POSITION " << p.getX() << " " << p.getY() << " " << p.getZ()   << flush;
  
  os << " END" << endl;
  
  return os;
}

template <class TS,class BUD>
ofstream &operator << (ofstream& os, BranchingPoint<TS,BUD>& bp)
{	
  PositionVector pv = GetDirection(bp); 
  Point p = GetPoint(bp);
  os << "DIRECTION " << pv.getX() << " " << pv.getY() << " " << pv.getZ() 
     << "  POSITION " << p.getX() << " " << p.getY() << " " << p.getZ()   << " END" << endl;
  
  return os;
}

// Reading a tree segment from a file is implemented in LignumWBDocI.h: LoadTreeSegment
template <class TS,class BUD>
istream &operator >> (istream& os, TreeSegment<TS,BUD>& ts)
{	
  return os;
}



template <class TS,class BUD>
TreeSegment<TS,BUD>::TreeSegment(const Point& p, const PositionVector& d, const LGMdouble go,
			     const METER l, const METER r, const METER rh, Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t)
{	
  SetValue(*this,LGAomega,go);
  SetValue(*this,LGAL,l);
  SetValue(*this,LGAR,r);
  SetValue(*this,LGARh,rh);
  SetValue(*this,LGARTop,0.0);
  
  //the first annual ring
  tsa.annual_rings.push_back(r);
}

template <class TS,class BUD>
void TreeSegment<TS,BUD>::SetYearCircles()
{
  int ts_age = GetValue(*this,LGAage);
  float r = GetValue(*this,LGAR);
  float delta_r = r / (ts_age);
  for (int i=0; i<ts_age-1; i++)
  {
    r = r - delta_r;
	//tsa.annual_rings.push_back(r);
  }
}


template <class TS,class BUD>
std::vector<METER> GetAnnualRings(const TreeSegment<TS,BUD>& ts)
{
  return ts.tsa.annual_rings;
}



template <class TS,class BUD>
Point GetEndPoint(const TreeSegment<TS,BUD>& ts)
{
  return GetPoint(ts)+GetValue(ts,LGAL)*(Point)GetDirection(ts);
}

template <class TS,class BUD>
Point GetMidPoint(const TreeSegment<TS,BUD>& ts)
{
  return GetPoint(ts)+0.5*GetValue(ts,LGAL)*(Point)GetDirection(ts);
}

//Return point in the segment at the 'fraction' distance. For example
//GetMidPoint(ts) == GetPoint(ts,0.5). The fraction must be in [0,1]
template <class TS,class BUD>
Point GetPoint(const TreeSegment<TS,BUD>& ts, double fraction)
{
  return GetPoint(ts)+fraction*GetValue(ts,LGAL)*(Point)GetDirection(ts);
}

template <class TS,class BUD>
void TreeSegment<TS,BUD>::SetAnnualRings(std::vector<METER> rings)
{
	int size = rings.size();
	for(int i=0; i<size; i++)
	{
		float r = rings[i];
		tsa.annual_rings.push_back(r);
	}
}

template <class TS,class BUD>
void TreeSegment<TS,BUD>::SetAnnualGrowth(LGMdouble growth)
{
	int size = tsa.annual_rings.size();
	LGMdouble new_rad = 0;
	
	if (size > 0)
		new_rad = tsa.annual_rings[size-1] + growth;
	else new_rad = growth;

	tsa.annual_rings.push_back(new_rad);
//	tsa.R = new_rad;
}

template <class TS,class BUD>
METER TreeSegment<TS,BUD>::AdjustAnnualGrowth(LGMdouble growth)
{
	int size = tsa.annual_rings.size();
	LGMdouble new_rad = 0.0;
	if (size == 1)
	{
		tsa.annual_rings[0] = growth;
		return growth;
	}
	if (size > 1)
	{
		new_rad = tsa.annual_rings[size-2] + growth;
		tsa.annual_rings[size-1] = new_rad;
	}
	return new_rad;
}


// SetRadius. 
template <class TS,class BUD>
METER SetRadius(TreeSegment<TS,BUD>& ts)
{
	int size = ts.tsa.annual_rings.size();
	ts.tsa.R = ts.tsa.annual_rings[size-1];
	ts.tsa.Rtop = ts.tsa.R;
	return ts.tsa.R;
}


// SetLastRing sets the radii of last ring to R. 
template <class TS,class BUD>
METER SetLastRing(TreeSegment<TS,BUD>& ts)
{
	int size = ts.tsa.annual_rings.size();
	ts.tsa.annual_rings[size-1] = ts.tsa.R;
	

	return ts.tsa.R;
}



template <class TS,class BUD>
KGC GetSapwoodMass(const TreeSegment<TS,BUD>& ts)
{
  //volume up to R
  LGMdouble V1 = (PI_VALUE * pow((double)ts.tsa.R,2.0)) * ts.tsa.L;
  //heartwood volume
  LGMdouble V2 = (PI_VALUE * pow((double)ts.tsa.Rh,2.0)) * ts.tsa.L;
  //sapwood volume
  LGMdouble V3 = V1 - V2;

  //mass is density * volume
  return GetValue(*(ts.tree),LGPrhoW) * V3;
}


template <class TS,class BUD>
M2 GetSapwoodArea(const TreeSegment<TS,BUD>& ts)
{
  //area up to R, wood radius up to foliage
  LGMdouble A1 = PI_VALUE*pow(GetValue(ts,LGAR),2.0);
  //heartwood area
  LGMdouble A2 = PI_VALUE*pow(GetValue(ts,LGARh),2.0);
  //sapwood area
  LGMdouble A3 = A1 - A2;

  return A3;
}

template <class TS,class BUD>
M2 GetHeartwoodArea(const TreeSegment<TS,BUD>& ts)
{
  return PI_VALUE*pow(GetValue(ts,LGARh),2.0);
}

template <class TS,class BUD>
METER GetInitialSapwoodArea(const TreeSegment<TS,BUD>& ts)
{
	Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(ts));
	std::vector<METER> rings = GetAnnualRings(ts);

	LGMdouble rd = rings[0];
	LGMdouble A1 = PI_VALUE * pow( rd, 2.0);

	return A1 * GetValue(tt,LGPxi);
}

template <class TS,class BUD>
void AddNewRadiusToAnnualRings(TreeSegment<TS,BUD>& ts, LGMdouble radius)
{
  ts.tsa.annual_rings.push_back(radius);
}

template <class TS,class BUD>
METER GetLastAnnualIncrement(const TreeSegment<TS,BUD>& ts)
{
	std::vector<METER> rings = GetAnnualRings(ts);

	LGMdouble ret=0;

	int s = rings.size();
	if (s>1)
		ret = rings[s-1] - rings[s-2];
	if (s==1)
		ret = rings[s-1];

	
	return ret;
}

template <class TS,class BUD>
LGMdouble GetValue(const TreeSegment<TS,BUD>& ts, const LGMAD name)
{
  if (name == LGAA)
    return PI_VALUE*pow(GetValue(ts,LGAR), 2.0);
  
  else if (name == LGAAh)
    return PI_VALUE*pow(GetValue(ts,LGARh), 2.0);

  else if (name == LGAAs)
    return GetValue(ts,LGAA) - GetValue(ts,LGAAh);

  else if (name == LGAAs0)
    return ts.tsa.As0;

  if (name == LGAage)
    return ts.tc_age; 

  else if (name == LGAH)
    return ts.point.getZ();

  else if (name == LGAHTop)
    return ts.point.getZ() + ts.direction.getZ() * GetValue(ts,LGAL);

  else if (name == LGAL)
    return ts.tsa.L;

  else if (name == LGAM)
    return ts.tsa.M;

  else if (name == LGAomega)
    return ts.tsa.omega;

  else if (name == LGAR)
    return ts.tsa.R;

  else if (name == LGARh)
    return ts.tsa.Rh;

  else if (name == LGARTop)
    return ts.tsa.Rtop;
  
  else if (name == LGAtype)
    return ts.tsa.type;

  else if(name == LGAvi)
    return ts.tsa.vigour;

  else if (name == LGAV){          //Now claculates as frustum volume if Rtop present
    double rb = GetValue(ts,LGAR);
    double rt = GetValue(ts,LGARTop);
    if (rt == 0.0)//LGARTop is not set (default value present)
      return  PI_VALUE*rb*rb *GetValue(ts,LGAL);
    else
      return (PI_VALUE*GetValue(ts,LGAL)*(rb*rb+rb*rt+rt*rt))/3.0;    
  }
  
  else if (name == LGAVfrustum){
    double rb = GetValue(ts,LGAR);
    double rt = GetValue(ts,LGARTop);
    if (rt == 0.0)//LGARTop is not set (default value present)
      return GetValue(ts,LGAV);//Return segment cylinder volume
    else
      //LGARTop set, return the frustum volume
      return (PI_VALUE*GetValue(ts,LGAL)*(rb*rb+rb*rt+rt*rt))/3.0;
  }

  else if (name == LGAVh) {           //Calculated assuming same taper as the whole segment
    double rt = GetValue(ts,LGARTop); //if Rtop present 
    if(rt == 0)
      return  PI_VALUE*pow(GetValue(ts,LGARh),2.0) * GetValue(ts,LGAL);
    else {
      double rh = GetValue(ts,LGARh);
      double rh_t = (rh/GetValue(ts,LGAR))*rt;
      return (PI_VALUE*GetValue(ts,LGAL)*(rh*rh+rh*rh_t+rh_t*rh_t))/3.0; 
    }
    
  }

  else if (name == LGAVs)
    return GetValue(ts,LGAV) - GetValue(ts,LGAVh);
 
  //Personally  I prefer minimum  set of  variables or  attributes and
  //compute others  like Ws  or Wh (we  have to do  these computations
  //anyway). These 3 lines should not be a computational cost.
  else if (name == LGAWs){
    LGMdouble v1 = GetValue(ts,LGAVs);   
    //mass is density * volume
    return GetValue(GetTree(ts),LGPrhoW) * v1;
  }
  //Perhaps we need own 'rho' for Wh?
  else if (name == LGAWh){
    LGMdouble v1 = GetValue(ts,LGAVh);
    return GetValue(GetTree(ts),LGPrhoW) * v1;
  }
  else if (name == LGAWood) {
    LGMdouble v1 = GetValue(ts, LGAVfrustum);
    return GetValue(GetTree(ts), LGPrhoW) * v1;
  }
  else
    return GetValue(dynamic_cast<const TreeCompartment<TS,BUD>&>(ts), name);
}


template <class TS,class BUD>
LGMdouble SetValue(TreeSegment<TS,BUD>& ts, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(ts,name);

  if (name == LGAage)
    ts.tc_age = value;

  else if(name == LGAAs0)
    ts.tsa.As0 = value;

  else if (name == LGAL)
    ts.tsa.L = value; //segment can be 0
  
  else if (name == LGAdR)
  {
    int size = ts.tsa.annual_rings.size();
    if (size>1)
      {
	LGMdouble rad = ts.tsa.annual_rings[size-2];
	ts.tsa.annual_rings[size-1] = value+rad;
      }
  }
 
  else if (name == LGAM)
    ts.tsa.M = value;

  else if (name == LGAomega)
    ts.tsa.omega = value;

  else if (name == LGAR)
	 ts.tsa.R = value;
  
  else if (name == LGARh)
    ts.tsa.Rh = value;

  else if (name == LGARTop)
    ts.tsa.Rtop = value;

  else if (name == LGAtype){
    ts.tsa.type = value;
  }
  else if(name == LGAvi)
	ts.tsa.vigour = value;

  else if (name == LGAWs)
    ts.tsa.Ws = value;

  else if (name == LGAWh)
    ts.tsa.Wh = value;

  else
    old_value = SetValue(dynamic_cast<TreeCompartment<TS,BUD>&>(ts), name,value);

  return old_value;
}



}

#endif
