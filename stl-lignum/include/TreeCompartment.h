#ifndef TREECOMPARTMENT_H
#define TREECOMPARTMENT_H

#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>

namespace Lignum{

  using namespace cxxadt;
  using cxxadt::Point;
  template <class TS,class BUD=DefaultBud<TS> > 
    class TreeCompartment{
      template <class TS1,class BUD1> 
      friend Point GetPoint(const TreeCompartment<TS1,BUD1>& tc);

      template <class TS1,class BUD1> 
      friend PositionVector GetDirection(const TreeCompartment<TS1,BUD1>& tc);

      template <class TS1,class BUD1> 
      friend Tree<TS1,BUD1>& GetTree(const TreeCompartment<TS1,BUD1>& tc);

      template <class TS1,class BUD1>
      friend LGMdouble GetValue(const TreeCompartment<TS1,BUD1>& tc, const LGMAD name);

      template <class TS1,class BUD1>
      friend LGMdouble SetValue(TreeCompartment<TS1,BUD1>& tc, const LGMAD name,
				const LGMdouble value);

      template <class TS1,class BUD1>
      friend void SetDirection(TreeCompartment<TS1,BUD1>& tc, const PositionVector& d);

      template <class TS1,class BUD1>
      friend void SetPoint(TreeCompartment<TS1,BUD1>& tc, const Point& p);
    public:
      TreeCompartment();
      TreeCompartment(const Point& p, const PositionVector& d, Tree<TS,BUD>* t);
      virtual ~TreeCompartment();
      virtual void photosynthesis() { /* Default: do nothing */ }
      virtual void respiration() { /* Default: do nothing */ }
    protected:
      Point point;
      PositionVector direction;
      LGMdouble tc_age;
      Tree<TS,BUD>* tree;
    };
}//closing namespace Lignum
#include <TreeCompartmentI.h>

#endif




