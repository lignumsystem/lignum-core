#ifndef AXIS_H
#define AXIS_H

#include <algorithm>
#include <numeric>
#include <list>
#include <Point.h>
#include <PositionVector.h>
#include <TreeFunctor.h>
#include <TreeCompartment.h>

template <class TS,class BUD = DefaultBud<TS> >
class Axis: public TreeCompartment<TS,BUD>{
  friend Bud<TS,BUD>* GetTerminatingBud(const Axis<TS,BUD>& axis);
  friend list<TreeCompartment<TS,BUD>*>& GetTreeCompartmentList(Axis<TS,BUD>& axis);
  friend void InsertTreeCompartment(Axis<TS,BUD>& axis, TreeCompartment<TS,BUD>* ts);
public:
  virtual ~Axis();
  Axis();
  Axis(const Point<METER>& p, const PositionVector& d, Tree<TS,BUD>* t);
private:
  list<TreeCompartment<TS,BUD>*> tc_ls;
};

//The implementations of methods and functions Axis
#include <AxisI.h>

#endif
