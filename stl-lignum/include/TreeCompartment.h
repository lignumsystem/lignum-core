#ifndef TREECOMPARTMENT_H
#define TREECOMPARTMENT_H

#include <stream.h>
#include <LGMdecl.h>
#include <LGMUnits.h>
#include <Point.h>
#include <PositionVector.h>


template <class TS,class BUD> 
class TreeCompartment{
  friend Point<METER> GetPoint(const TreeCompartment<TS,BUD>& tc);
  friend PositionVector GetDirection(const TreeCompartment<TS,BUD>& tc);
public:
  TreeCompartment();
  TreeCompartment(const Point<METER>& p, const PositionVector& d, Tree<TS,BUD>* t);
  virtual ~TreeCompartment();
protected:
  Point<METER> point;
  PositionVector direction;
  Tree<TS,BUD>* tree;
};

#include <TreeCompartmentI.h>

#endif
