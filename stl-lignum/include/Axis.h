#ifndef AXIS_H
#define AXIS_H

#include <list>
#include <Point.h>
#include <PositionVector.h>
#include <TreeCompartment.h>
#include <Bud.h>

class Axis: public TreeCompartment{
  friend Bud* GetTerminatingBud(const Axis& axis);
  friend void InsertTreeCompartment(Axis& axis, TreeCompartment* ts);
public:
  Axis();
  Axis(const Point<METER>& p, const PositionVector& d, Tree* t);
  virtual ~Axis();
private:
  list<TreeCompartment*> tc_ls;
};

#endif
