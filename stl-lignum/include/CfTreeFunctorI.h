
#ifndef CFTREEFUNCTORI_H
#define CFTREEFUNCTORI_H


namespace Lignum{
  //Please orginize headers or rewrite "<<" operator
  //to remove this declation; 
  template <class TS,class BUD> class HwTreeSegment;
template <class TS, class BUD>
TreeCompartment<TS,BUD>* DropAllLeaves<TS,BUD>::operator ()(TreeCompartment<TS,BUD>* tc)const
{

        if (HwTreeSegment<TS,BUD>* hwts = dynamic_cast<HwTreeSegment<TS,BUD>*>(tc))
        {
	  DropLeaves(*hwts);
        }
        return tc;
}




template <class TS, class BUD>
LGMdouble SetVigours(Axis<TS,BUD>& axis, LGMdouble vig_val, LGMdouble max_area)
{
  bool calculate_new_value = false;
  if (max_area>0)
    calculate_new_value = true;
  
  BranchingPoint<TS,BUD> *lastbp = NULL;


  std::list<TreeCompartment<TS, BUD>*>& ls =
    GetTreeCompartmentList(axis);
  std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();

  
  while(I != ls.end())
    { 
      if (HwTreeSegment<TS,BUD>* hwts =
	  dynamic_cast<HwTreeSegment<TS,BUD>*>(*I))
	{
	  if (calculate_new_value)
	    {
	      LGMdouble rad = GetValue(*hwts, R);
	      LGMdouble area = pow(rad, 2) * PI_VALUE;
	      
	      assert(area/max_area <= 1);
	      vig_val = vig_val * (area/max_area);
	      calculate_new_value = false;
	    }
			
			
	  if (lastbp)
	    {
	      LGMdouble max_rad = GetMaxRadius(*lastbp);
	      LGMdouble rad = GetValue(*hwts, R);
	      LGMdouble marea = pow(max_rad, 2) * PI_VALUE;
	      LGMdouble area = pow(rad, 2) * PI_VALUE;
	      
	      if (area > marea)
		marea = area;
	      
	      std::list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*lastbp);  	  
	      std::list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();
			
	      while(II != axis_ls.end())
		{
		  Axis<TS,BUD> *ax = *II;	
		  SetVigours(*ax, vig_val, marea); 
		  II++;	
		}
	      
	      vig_val = vig_val * (area/max_area);
	      SetValue(*hwts, vi, vig_val);
	      lastbp = NULL;
	    }
	  else
	    {
	      SetValue(*hwts, vi, vig_val);
	    }
	  
	}
      if (BranchingPoint<TS,BUD>* bp =
	  dynamic_cast<BranchingPoint<TS,BUD>*>(*I))
	{
	  lastbp = bp;	
	}
      I++;
    }

  return vig_val;
}


}//closing namespace Lignum

#endif
