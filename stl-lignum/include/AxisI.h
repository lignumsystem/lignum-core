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
	std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
	while(I != ls.end())
	{
		if (TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS, BUD>*>(*I))
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
        TreeSegment<TS, BUD> *ret = NULL;
        
        std::list<TreeCompartment<TS, BUD>*>& ls = axis.tc_ls;
        std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
        while(I != ls.end())
        {
                if (TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS, BUD>*>(*I))
                {
                        return myts;
                }
                I++;
        }
        return ret;
}

template <class TS,class BUD>
Axis<TS,BUD>::~Axis()  //***
{	
  std::list<TreeCompartment<TS,BUD>*>::iterator first = tc_ls.begin();
  std::list<TreeCompartment<TS,BUD>*>::iterator last = tc_ls.end();

  while (first != last)
    delete *first++;
}

//default constructor
template <class TS,class BUD>
Axis<TS,BUD>::Axis()
{
  tree = NULL;
}

//Constructor, define position and direction in 3D space
//Also to access tree level parameters etc., set pointer
//to the tree this axis is part of
template <class TS,class BUD>
Axis<TS,BUD>::Axis(const Point& p, const PositionVector& d, Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t)
{
}


//insert a tree compartment to the last position of the list
template <class TS,class BUD>
void InsertTreeCompartment(Axis<TS,BUD>& axis, TreeCompartment<TS,BUD>* tc)
{
	  axis.tc_ls.push_back(tc);
}

template <class TS,class BUD>
void InsertTreeCompartmentSecondLast(Axis<TS,BUD>& axis, TreeCompartment<TS,BUD>* ts)
{
	std::list<TreeCompartment<TS,BUD>*>& ls = axis.tc_ls;
	std::list<TreeCompartment<TS,BUD>*>::iterator I = ls.end(); 
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
std::list<TreeCompartment<TS,BUD>*>&  GetTreeCompartmentList(Axis<TS,BUD>& axis)
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
        std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
        while(I != ls.end())
        {
              
	  if (HwTreeSegment<TS,BUD,S>* hwts = dynamic_cast<HwTreeSegment<TS,BUD,S>*>(*I))
                {
                        if (GetValue(*hwts, age) == Age || Age == -1)
                                sum += GetValue(*hwts, name);   
                }
	  /*
                else if (CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(*I))
                {
                        if (GetValue(*cfts, age) == Age || Age == -1)
                                sum += GetValue(*cfts, name);
                }
	  */
                I++;
        }
        return sum;
}


template<class TS, class BUD>
void Delete2ndLastTreeCompartment(Axis<TS,BUD>& axis)
{
  std::list<TreeCompartment<TS, BUD>*>& ls = axis.tc_ls;
  std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.end();

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
  //  LGMdouble unknown_value = 0.0;
  if (name == L) {
    std::list<TreeCompartment<TS, BUD>*>& ls = ax.tc_ls;
    std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
    LGMdouble len = 0.0;
    while(I != ls.end()) {
      if (TS* ts = dynamic_cast<TS*>(*I))
	len += GetValue(*ts, L);
      I++;
    }
    return len;
  }
  else if (name == Wf) {
    std::list<TreeCompartment<TS, BUD>*>& ls = ax.tc_ls;
    std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
    LGMdouble w_f = 0.0;
    while(I != ls.end()) {
      if (TS* ts = dynamic_cast<TS*>(*I))
	w_f += GetValue(*ts, Wf);
      I++;
    }
    return w_f;
  }
  else
    cout << "Axis: Unknown attribute: " << name  << endl;
 
  return 0.0;
}                                                                               


template <class TS,class BUD>
LGMdouble GetBranchFoliage(Axis<TS,BUD>& ax) {
  
  LGMdouble w_fol = 0.0;
  
  std::list<TreeCompartment<TS, BUD>*>& ls = ax.tc_ls;
  std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
  while(I != ls.end()) {
    if (TS* ts = dynamic_cast<TS*>(*I)) {
      w_fol += GetValue(*ts, Wf);
    }


    if(BranchingPoint<TS, BUD>* bp = dynamic_cast<BranchingPoint<TS, BUD>*>(*I)) { 
      std::list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*bp);          
      std::list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();
	  
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




