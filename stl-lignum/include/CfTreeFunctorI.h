
#ifndef CFTREEFUNCTORI_H
#define CFTREEFUNCTORI_H


namespace Lignum{


template <class TS, class BUD,class S>
LGMdouble SetVigours(Axis<TS,BUD>& axis, LGMdouble vig_val, LGMdouble max_area)
{
  bool calculate_new_value = false;
  if (max_area>0)
    calculate_new_value = true;
  
  BranchingPoint<TS,BUD> *lastbp = NULL;


  list<TreeCompartment<TS, BUD>*>& ls =
    GetTreeCompartmentList(axis);
  typename list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();

  
  while(I != ls.end())
    { 
      if (HwTreeSegment<TS,BUD,S>* hwts =
	  dynamic_cast<HwTreeSegment<TS,BUD,S>*>(*I))
	{
	  if (calculate_new_value)
	    {
	      LGMdouble rad = GetValue(*hwts, LGAR);
	      LGMdouble area = pow(rad, 2) * PI_VALUE;
	      
	      assert(area/max_area <= 1);
	      vig_val = vig_val * (area/max_area);
	      calculate_new_value = false;
	    }
			
			
	  if (lastbp)
	    {
	      LGMdouble max_rad = GetMaxRadius(*lastbp);
	      LGMdouble rad = GetValue(*hwts, LGAR);
	      LGMdouble marea = pow(max_rad, 2) * PI_VALUE;
	      LGMdouble area = pow(rad, 2) * PI_VALUE;
	      
	      if (area > marea)
		marea = area;
	      
	      list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*lastbp);  	  
	      typename list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();
			
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
