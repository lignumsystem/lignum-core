#ifndef TREECOMPARTMENT_H
#define TREECOMPARTMENT_H

#include <LGMUnits.h>
#include <Point.h>
#include <PositionVector.h>

class Tree;

class TreeCompartment{
  friend Point<METER> GetPoint(const TreeCompartment& tc);
  friend PositionVector GetDirection(const TreeCompartment& tc);
public:
  TreeCompartment();
  TreeCompartment(const Point<METER>& p, const PositionVector& d, Tree* t);
  virtual ~TreeCompartment();
protected:
  Point<METER> point;
  PositionVector direction;
  Tree* tree;
};

#endif
