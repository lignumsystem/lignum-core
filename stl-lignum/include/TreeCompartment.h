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
      friend Point<METER> GetPoint(const TreeCompartment<TS,BUD>& tc);
      friend PositionVector GetDirection(const TreeCompartment<TS,BUD>& tc);
      friend Tree<TS,BUD>& GetTree(const TreeCompartment<TS,BUD>& tc);
      friend LGMdouble GetValue(const TreeCompartment<TS,BUD>& tc, const LGMAD name);
      friend LGMdouble SetValue(TreeCompartment<TS,BUD>& tc, const LGMAD name,
				const LGMdouble value);
    public:
      TreeCompartment();
      TreeCompartment(const Point<METER>& p, const PositionVector& d, Tree<TS,BUD>* t);
      virtual ~TreeCompartment();
      virtual void photosynthesis() { /* Default: do nothing */ }
    protected:
      Point<METER> point;
      PositionVector direction;
      LGMdouble age;
      Tree<TS,BUD>* tree;
    };
}//closing namespace Lignum
#include <TreeCompartmentI.h>

#endif
