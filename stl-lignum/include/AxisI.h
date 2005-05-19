#ifndef AXISI_H
#define AXISI_H


namespace Lignum{
  //Please orginize headers or rewrite "<<" operator
  //to remove this declation; 
  template <class TS,class BUD,class S> class HwTreeSegment;
  
  template <class TS,class BUD>
    TreeSegment<TS, BUD>* GetLastTreeSegment(Axis<TS,BUD>& axis)
    {
      TreeSegment<TS, BUD> *ret = NULL;
      
      std::list<TreeCompartment<TS, BUD>*>& ls = axis.tc_ls;
      typename std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
      while(I != ls.end())
	{
	  if (TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS,
	      BUD>*>(*I))
	    {
	      ret = myts;
	    }
	  I++;
	}
      return ret;
    }
  
  template <class TS,class BUD>
    TreeSegment<TS, BUD>* GetFirstTreeSegment(Axis<TS,BUD>& axis)
    {
      TS *ret = NULL;
      
      list<TreeCompartment<TS, BUD>*>& ls = axis.tc_ls;
      typename list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
      while(I != ls.end())
        {
	  if (TS* myts = dynamic_cast<TS*>(*I))
	    {
	      return myts;
	    }
	  I++;
        }
      return ret;
    }

  template <class TS,class BUD>
    Axis<TS,BUD>::~Axis() 
    {	
      //Delete tree compartments, the list will be destroyed automatically. 
      //See TreeFunctorI.h for  DestroyTreeCompartments.
      for_each(tc_ls.begin(),tc_ls.end(), DestroyTreeCompartments<TS,BUD>());
    }
  
  //default constructor
  template <class TS,class BUD>
    Axis<TS,BUD>::Axis()
    :aa(ALIVE)
    {
      this->tree = NULL;
    }
  
  //Constructor, define position and direction in 3D space
  //Also to access tree level parameters etc., set pointer
  //to the tree this axis is part of
  template <class TS,class BUD>
    Axis<TS,BUD>::Axis(const Point& p, const PositionVector& d,
		       Tree<TS,BUD>* t)
    :TreeCompartment<TS,BUD>(p,d,t),aa(ALIVE)
    {
    }
 

  //insert a tree compartment to the last position of the list
  template <class TS,class BUD>
    void InsertTreeCompartment(Axis<TS,BUD>& axis, TreeCompartment<TS,BUD>* tc)
    {
      axis.tc_ls.push_back(tc);
    }
  
  template <class TS,class BUD>
    void InsertTreeCompartmentSecondLast(Axis<TS,BUD>& axis,
					 TreeCompartment<TS,BUD>* ts)
    {
      std::list<TreeCompartment<TS,BUD>*>& ls = axis.tc_ls;
      typename std::list<TreeCompartment<TS,BUD>*>::iterator I = ls.end(); 
      I--;
      
      axis.tc_ls.insert(I, ts);	
    }
  
  
  
  //Return the terminating bud of the axis
  template <class TS, class BUD>
    Bud<TS,BUD>* GetTerminatingBud(const Axis<TS,BUD>& axis)
    {
      return (Bud<TS,BUD>*) axis.tc_ls.back();
    }
  
  
  
  template <class TS,class BUD>
    std::list<TreeCompartment<TS,BUD>*>&
    GetTreeCompartmentList(Axis<TS,BUD>& axis)
    {
      return  axis.tc_ls;
    }
  
  
  template <class TS,class BUD>
    TreeCompartment<TS,BUD>* GetFirstTreeCompartment(Axis<TS,BUD>& axis)
    {
      return axis.tc_ls.front();
    }
  
  template <class TS,class BUD,class S>
    LGMdouble GetSumValue(Axis<TS,BUD>& axis, LGMAD name, int Age)
    {
      
      LGMdouble sum = 0.0;
      
      std::list<TreeCompartment<TS, BUD>*>& ls = axis.tc_ls;
      typename std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
      while(I != ls.end())
	{
	  if (HwTreeSegment<TS,BUD,S>* hwts = dynamic_cast<HwTreeSegment<TS,
	      BUD,S>*>(*I))
	    {
	      if (GetValue(*hwts, LGAage) == Age || Age == -1)
		sum += GetValue(*hwts, name);   
	    }
	  I++;
	}
      return sum;
    }
  
  
  template<class TS, class BUD>
    void Delete2ndLastTreeCompartment(Axis<TS,BUD>& axis)
    {
      std::list<TreeCompartment<TS, BUD>*>& ls = axis.tc_ls;
      typename std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.end();
      
      if(axis.tc_ls.size() > 1) {
	I--;
	I--;
	delete *I;
	axis.tc_ls.erase(I);
      }
      return;
    }
  
  
  template <class TS,class BUD>
    LGMdouble GetValue(Axis<TS,BUD>& ax, LGMAD name)
    {
      if (name == LGAstate)
	return ax.aa.state;
      
      else if (name == LGAL) {
	std::list<TreeCompartment<TS, BUD>*>& ls = ax.tc_ls;
	typename std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
	LGMdouble len = 0.0;
	while(I != ls.end()) {
	  if (TS* ts = dynamic_cast<TS*>(*I))
	    len += GetValue(*ts, LGAL);
	  I++;
	}
	return len;
      }
      else if (name == LGAWf) {
	std::list<TreeCompartment<TS, BUD>*>& ls = ax.tc_ls;
	typename std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
	LGMdouble w_f = 0.0;
	while(I != ls.end()) {
	  if (TS* ts = dynamic_cast<TS*>(*I))
	    w_f += GetValue(*ts, LGAWf);
	  I++;
	}
	return w_f;
      }
      else
	cout << "Axis: Unknown attribute: " << name  << endl;
      
      return 0.0;
    }                                                                               
  
  template <class TS,class BUD>
    LGMdouble SetValue(Axis<TS,BUD>& axis, LGMAD name, const LGMdouble value)
    {
      
      LGMdouble old_value = GetValue(axis,name);
      
      if (name == LGAstate)
	axis.aa.state = value;
      
      return old_value;
    }
  
  
  template <class TS,class BUD>
    LGMdouble GetBranchFoliage(Axis<TS,BUD>& ax) {
    
    LGMdouble w_fol = 0.0;
    
    std::list<TreeCompartment<TS, BUD>*>& ls = ax.tc_ls;
    typename std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
    while(I != ls.end()) {
      if (TS* ts = dynamic_cast<TS*>(*I)) {
	w_fol += GetValue(*ts, LGAWf);
      }
      
      
      if(BranchingPoint<TS, BUD>* bp = dynamic_cast<BranchingPoint<TS,
	 BUD>*>(*I)) { 
	std::list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*bp);          
	typename std::list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();
	
	while(II != axis_ls.end()) {
	  Axis<TS,BUD> *axis = *II;       
	  w_fol += GetBranchFoliage(*axis);                     
	  II++;   
	}
	
      }
      
      I++;
    }
    
    return w_fol;
  }
  
  
}//closing namesapce


#endif




