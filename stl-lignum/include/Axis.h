#ifndef AXIS_H
#define AXIS_H

#include <list>
#include <Point.h>
#include <PositionVector.h>
#include <TreeCompartment.h>
#include <Bud.h>

template <class TS>
class Axis: public TreeCompartment<TS>{
  friend Bud<TS>* GetTerminatingBud(const Axis<TS>& axis);
  friend void InsertTreeCompartment(Axis<TS>& axis, TreeCompartment<TS>* ts);
public:
  virtual ~Axis();
  Axis();
  Axis(const Point<METER>& p, const PositionVector& d, Tree<TS>* t);
private:
  list<TreeCompartment<TS>*> tc_ls;
};

#endif
