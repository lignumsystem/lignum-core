#ifndef VISUAL_FUNCTORI_H
#define VISUAL_FUNCTORI_H

namespace Lignum{




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
  double odd = 0.000001;

  if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
    PositionVector pv = GetDirection(*myts);
    vector<double> v = pv.getVector();
    LGMdouble l = GetValue(*myts, L);
    Point p(v[0], v[1], v[2]);
    
    if ((GetPoint(*(gls.current)) || (GetPoint(*myts) + l * p)) < odd)
      {	
	gls.segment = myts;
      }   
  }
  return gls;
}

template <class TS,class BUD>
METER& SampleDiameterGrowth<TS,BUD>::operator()(METER& r,TreeCompartment<TS,BUD>* tc)const
{
  TreeSegment<TS,BUD>* myts = NULL;
  if (myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
    SetValue(*myts,R,GetValue(*myts,R)+r*0.10);
    r = GetValue(*myts,R);
  }
  return r;
}


}

#endif
