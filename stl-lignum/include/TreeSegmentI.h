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
     << "  RADIUS " << GetValue(ts,R) << " " 
     << "  LENGTH " << GetValue(ts,L) << "  AGE " << GetValue(ts,age) << flush;
  
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
TreeSegment<TS,BUD>::TreeSegment()
{
  tree = NULL;
}



template <class TS,class BUD>
TreeSegment<TS,BUD>::TreeSegment(const Point& p, const PositionVector& d, const LGMdouble go,
			     const METER l, const METER r, const METER rh, Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t)
{	
  SetValue(*this,omega,go);
  SetValue(*this,L,l);
  SetValue(*this,R,r);
  SetValue(*this,Rh,rh);
  SetValue(*this,RTop,r);
  
  //the first annual ring
  tsa.annual_rings.push_back(r);
}




//This method returns the amount[kg] of transpired water. 
//Time interval[s] is given as parameter
template <class TS,class BUD>
LGMdouble TreeSegment<TS,BUD>::GetTranspiration(LGMdouble time)
{
  return 0.12e-9;
}


template <class TS,class BUD>
void TreeSegment<TS,BUD>::SetYearCircles()
{
  int ts_age = GetValue(*this,age);
  float r = GetValue(*this,R);
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
  return GetPoint(ts)+GetValue(ts,L)*(Point)GetDirection(ts);
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

	/*
	Tree<TS,BUD> &tree = GetTree(ts);
	LGMdouble A_s = (1.0 - GetValue(tree, xi)) * GetValue(ts, Wf)/(2.0*GetValue(tree, af)*GetValue(tree, lr));
	LGMdouble r_h = sqrt((PI_VALUE*ts.tsa.R*ts.tsa.R - A_s)/PI_VALUE);
	SetValue(ts, Rh, r_h);
*/
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
  return GetValue(*(ts.tree),rho) * V3;
}


template <class TS,class BUD>
M2 GetSapwoodArea(const TreeSegment<TS,BUD>& ts)
{
  //area up to R, wood radius up to foliage
  LGMdouble A1 = PI_VALUE*pow(GetValue(ts,R),2.0);
  //heartwood area
  LGMdouble A2 = PI_VALUE*pow(GetValue(ts,Rh),2.0);
  //sapwood area
  LGMdouble A3 = A1 - A2;

  return A3;
}

template <class TS,class BUD>
M2 GetHeartwoodArea(const TreeSegment<TS,BUD>& ts)
{
  return PI_VALUE*pow(GetValue(ts,Rh),2.0);
}

template <class TS,class BUD>
METER GetInitialSapwoodArea(const TreeSegment<TS,BUD>& ts)
{
	Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(ts));
	std::vector<METER> rings = GetAnnualRings(ts);

	LGMdouble rd = rings[0];
	LGMdouble A1 = PI_VALUE * pow( rd, 2.0);

	return A1 * GetValue(tt,xi);
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
    return PI_VALUE*pow(GetValue(ts,R), 2.0);
  
  else if (name == LGAAh)
    return PI_VALUE*pow(GetValue(ts,Rh), 2.0);

  else if (name == LGAAs)
    return GetValue(ts,LGAA) - GetValue(ts,LGAAh);
    
  if (name == age)
    return ts.tc_age; 

  else if (name == H)
    return ts.point.getZ();

  else if (name == Hm)
    return ts.point.getZ() + ts.direction.getVector()[2] * GetValue(ts,L);

  else if (name == L)
    return ts.tsa.L;

  else if (name == M)
    return ts.tsa.M;

  else if (name == omega)
    return ts.tsa.omega;

  else if (name == R)
    return ts.tsa.R;

  else if (name == Rh)
    return ts.tsa.Rh;

  else if (name == RTop)
    return ts.tsa.Rtop;
  
  else if(name == vi)
	  return ts.tsa.vigour;

  //Personally  I prefer minimum  set of  variables or  attributes and
  //compute others  like Ws  or Wh (we  have to do  these computations
  //anyway). These 3 lines should not be a computational cost.
  else if (name == LGAWs){
     //volume up to R
    LGMdouble v1 = PI_VALUE*pow(GetValue(ts,R),2.0) * GetValue(ts,L);
    //heartwood volume
    LGMdouble v2 = PI_VALUE*pow(GetValue(ts,Rh),2.0) * GetValue(ts,L);
    //sapwood volume
    LGMdouble v3 = v1 - v2;   
    //mass is density * volume
    return GetValue(GetTree(ts),rho) * v3;
  }
  //Perhaps we need own 'rho' for Wh?
  else if (name == LGAWh){
    LGMdouble v1 = PI_VALUE*pow(GetValue(ts,Rh),2.0) * GetValue(ts,L);
    return GetValue(GetTree(ts),rho) * v1;
  }
  else
    return GetValue(dynamic_cast<const TreeCompartment<TS,BUD>&>(ts), name);
}


template <class TS,class BUD>
LGMdouble SetValue(TreeSegment<TS,BUD>& ts, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(ts,name);
  
  if (name == age)
    ts.tc_age = value;

  else if (name == L)
    ts.tsa.L = value; //segment can be 0
  
  else if (name == dR)
  {
    int size = ts.tsa.annual_rings.size();
    if (size>1)
      {
	LGMdouble rad = ts.tsa.annual_rings[size-2];
	ts.tsa.annual_rings[size-1] = value+rad;
      }
  }
 
  else if (name == M)
    ts.tsa.M = value;

  else if (name == omega)
    ts.tsa.omega = value;

  else if (name == R)
	 ts.tsa.R = value;
  
  else if (name == Rh)
    ts.tsa.Rh = value;

  else if (name == RTop)
    ts.tsa.Rtop = value;

  else if(name == vi)
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
