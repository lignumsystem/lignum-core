#ifndef TREECOMPARTMENTI_H
#define TREECOMPARTMENTI_H

template <class TS,class BUD>
TreeCompartment<TS,BUD>::TreeCompartment()
{
}

template <class TS,class BUD>
TreeCompartment<TS,BUD>::TreeCompartment(const Point<METER>& p, const PositionVector& d, 
				 Tree<TS,BUD>* t)
  :point(p),direction(d)
{
  //normalize the direction vector
  //to avoid domain problems e.g., with visualization
  //using built-in acos etc. functions. 
  direction.normalize();

  tree = t;
}

template <class TS,class BUD>
TreeCompartment<TS,BUD>::~TreeCompartment()
{
}


template <class TS,class BUD>
Point<METER> GetPoint(const TreeCompartment<TS,BUD>& tc)
{
  return tc.point;
}

template <class TS,class BUD>
PositionVector GetDirection(const TreeCompartment<TS,BUD>& tc)
{
  return  tc.direction;
}

#endif
