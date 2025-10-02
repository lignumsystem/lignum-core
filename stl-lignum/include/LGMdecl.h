/// \file LGMdecl.h
/// \brief Data type forward declarations 
#ifndef LGMDECL_H
#define LGMDECL_H

#include <cassert>
#include <iostream>
using namespace std;
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
 
  //Assert  and Message as  message boxes  for Windows,  otherwise use
  //standard assert,  cout and cerr respectively.  The argument 'expr'
  //must be a string.
#ifdef _MSC_VER
  //Windows assert for GUI 
#define LGMassert(expr) ASSERT(expr)
#else
  //Standard C-library assert
#define LGMassert(expr) assert(expr)
#endif

#ifdef _MSC_VER
  //Windows message box
#define LGMMessage(expr) MessageBox(NULL,expr, NULL, NULL)
#else
  //Output to cout
#define  LGMMessage(expr) cout << expr << endl
#endif

#ifdef _MSC_VER
  //Windows message box
#define LGMError(expr) MessageBox(NULL,expr, NULL, NULL)
#else
  //Output to cerr
#define  LGMError(expr) cerr << expr << endl
#endif

}//closing namepace Lignum

#endif
