#ifndef LGMDECL_H
#define LGMDECL_H

#include <assert.h>

#include <LGMSymbols.h>
#include <LGMUnits.h>

namespace Lignum{

  template <class TS,class BUD> class Tree;
  template <class TS,class BUD> class TreeCompartment;
  template <class TS,class BUD> class Axis;
  template <class TS,class BUD> class Bud;
  template <class TS,class BUD> class BranchingPoint;
  template <class TS,class BUD> class Bud;
  template <class TS,class BUD> class TreeSegment;
  template <class TS,class BUD> class CfTreeSegment;
  template <class TS,class BUD, class SHAPE> class HwTreeSegment;
  template <class SHAPE> class BroadLeaf;
  template <class TS> class DefaultBud;

  template <class TREE> class RootCompartment;
  template <class TREE> class RootSegment;
  template <class TREE> class RootAxis;
  template <class TREE> class RootBranchingPoint;
  template <class TREE> class RootTip;
 

#ifdef _MSC_VER
  //Windows assert for GUI 
#define LGMassert(expr) ASSERT(expr)
#else
  //Standard C-library assert
#define LGMassert(expr) assert(expr)
#endif

}//closing namepace Lignum

#endif
