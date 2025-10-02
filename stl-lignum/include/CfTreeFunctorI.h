/// \file CfTreeFunctorI.h
/// \brief Set HwTreeSegment vigour
#ifndef CFTREEFUNCTORI_H
#define CFTREEFUNCTORI_H


namespace Lignum{

///\brief Set vigour value for tree segments
///
///Vigour value \f$ \nu \f$ is defined as \f$ \nu = \nu \times \frac{A_{\mathrm{ts}}}{A_{\mathrm{max}}} \f$
///\param axis Tree axis
///\param vig_val Vigour value 
///\param max_area Maximum cross sectional area in tree segments
///\retval vig_val Modified vigour value
///\pre TS must be able to type cast to HwTreeSegment
///\pre The \p max_area value must be known
///\note Starting from the main axis SetVigours() travels the tree and sets vigours
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
	      SetValue(*hwts, LGAvi, vig_val);
	      lastbp = NULL;
	    }
	  else
	    {
	      SetValue(*hwts, LGAvi, vig_val);
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
