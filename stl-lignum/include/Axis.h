#ifndef AXIS_H
#define AXIS_H

#include <list>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>


namespace Lignum{

using namespace cxxadt;
template <class TS,class BUD=DefaultBud<TS> >
class Axis: public TreeCompartment<TS,BUD>{
  template <class TS1,class BUD1>
  friend Bud<TS1,BUD1>* GetTerminatingBud(const Axis<TS1,BUD1>& axis);
  template <class TS1,class BUD1>
  friend list<TreeCompartment<TS1,BUD1>*>& GetTreeCompartmentList(Axis<TS1,BUD1>& axis);
  template <class TS1,class BUD1>
  friend void InsertTreeCompartment(Axis<TS1,BUD1>& axis, TreeCompartment<TS1,BUD1>* ts);
public:
  virtual ~Axis();
  Axis();
  Axis(const Point<METER>& p, const PositionVector& d, Tree<TS,BUD>* t);
private:
  list<TreeCompartment<TS,BUD>*> tc_ls;
};

}//closing namespace Lignum

//The implementations of methods and functions Axis
#include <AxisI.h>

#endif
