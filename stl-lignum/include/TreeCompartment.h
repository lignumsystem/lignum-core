#ifndef TREECOMPARTMENT_H
#define TREECOMPARTMENT_H

#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
#include <LGMUnits.h>
#include <LGMSymbols.h>

//#include "BendingInfo.h"


//class Point;

using namespace cxxadt;

//class PositionVector;



namespace Lignum{

template <class TS,class BUD = DefaultBud<TS> > class Tree;

template <class TS,class BUD=DefaultBud<TS> > 
class TreeCompartment
{
#ifdef _MSC_VER

	  friend Point GetPoint(const TreeCompartment<TS,BUD>& tc);
      friend PositionVector GetDirection(const TreeCompartment<TS,BUD>& tc);
	  friend void SetPoint(TreeCompartment<TS,BUD>& tc, Point& p);
	  friend void SetDirection(TreeCompartment<TS,BUD>& tc, PositionVector& pv);
      friend Tree<TS,BUD>& GetTree(const TreeCompartment<TS,BUD>& tc);
      friend LGMdouble GetValue(const TreeCompartment<TS,BUD>& tc, const LGMAD name);
      friend LGMdouble SetValue(TreeCompartment<TS,BUD>& tc, const LGMAD name, const LGMdouble value);

#else
	  template <class TS1,class BUD1> 
      friend Point GetPoint(const TreeCompartment<TS1,BUD1>& tc);

      template <class TS1,class BUD1> 
      friend PositionVector GetDirection(const TreeCompartment<TS1,BUD1>& tc);

	  template <class TS1,class BUD1> 
	  friend void SetPoint(TreeCompartment<TS,BUD>& tc, Point& p);
	  
	  template <class TS1,class BUD1> 
	  friend void SetDirection(TreeCompartment<TS,BUD>& tc, PositionVector& pv);

      template <class TS1,class BUD1> 
      friend Tree<TS1,BUD1>& GetTree(const TreeCompartment<TS1,BUD1>& tc);

      template <class TS1,class BUD1>
      friend LGMdouble GetValue(const TreeCompartment<TS1,BUD1>& tc, const LGMAD name);

      template <class TS1,class BUD1>
      friend LGMdouble SetValue(TreeCompartment<TS1,BUD1>& tc, const LGMAD name, const LGMdouble value);
#endif // _MSC_VER
    
public:
      TreeCompartment();
      TreeCompartment(const Point& p, const PositionVector& d, Tree<TS,BUD>* t);
      virtual ~TreeCompartment();
      virtual void photosynthesis() { /* Default: do nothing */ }
	  virtual void respiration() {  }
protected:
      Point point;
      PositionVector direction;
      LGMdouble age;
      Tree<TS,BUD>* tree;
};




}  // closing namespace Lignum

#include <TreeCompartmentI.h>

#endif

