#ifndef TREECOMPARTMENT_H
#define TREECOMPARTMENT_H

#include <LGMdecl.h>
#include <LGMUnits.h>
#include <Point.h>
#include <PositionVector.h>


template <class TS> 
class TreeCompartment{
  friend Point<METER> GetPoint(const TreeCompartment<TS>& tc);
  friend PositionVector GetDirection(const TreeCompartment<TS>& tc);
public:
  TreeCompartment();
  TreeCompartment(const Point<METER>& p, const PositionVector& d, Tree<TS>* t);
  virtual ~TreeCompartment();
protected:
  Point<METER> point;
  PositionVector direction;
  Tree<TS>* tree;
};

#endif
