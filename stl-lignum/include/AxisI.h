#ifndef AXISI_H
#define AXISI_H


namespace Lignum{

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



}


#endif