#include <VisualFunctor.h>

template <class TS,class BUD> GUS<TS,BUD>& 
GetUpperSegment<TS,BUD>::operator()(GUS<TS,BUD>& gus, 
				    TreeCompartment<TS,BUD>* tc)const
{
  if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
    if (gus.v[0] == myts)
      {	
	gus.flag = 1;
      }
    else 
      {       
	if (gus.flag == 2 && gus.point == GetPoint(*myts)){
	  gus.v.insert(gus.v.end(), myts);
	}
    }

  }
  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    if (gus.flag == 1){
      gus.flag = 2;
      gus.point = GetPoint(*bp);
    }
  } 

  return gus;
}



template <class TS,class BUD> GLS<TS,BUD>& 
GetLowerSegment<TS,BUD>::operator()(GLS<TS,BUD>& gls, 
				    TreeCompartment<TS,BUD>* tc)const
{
  if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
    PositionVector pv = GetDirection(*myts);
    vector<double> v = pv.getVector();
    TP l = GetTSAttributeValue(*myts, L);
    Point<METER> p(v[0], v[1], v[2]);
    
    if (0.000001*GetPoint(*(gls.current)) == 0.000001*(GetPoint(*myts) + l * p))
      {	
	gls.segment = myts;
	cout << "equal" << endl;
      }
    else{
      cout << GetPoint(*(gls.current)) << " " 
	   << GetPoint(*myts) + l * p << endl;
      cout << "Not equal" << endl;
    }
  }
  return gls;
}
  

