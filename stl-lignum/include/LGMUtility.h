/// \file LGMUtility.h
/// \brief Utility functions not active
#ifndef LGMUTILITY_H
#define LGMUTILITY_H

/* #include <iostream> */

/* #include <LGMdecl.h> */
/* #include <LGMSymbols.h> */
/* #include <TreeCompartment.h> */
/* #include <BroadLeaf.h> */
/* #include <Algorithms.h> */

#include <TreeGrowthAllocator.h>

//Declarations (interface) of a number useful functions for
//STL-LIGNUM. Please keep the list of available utilities up to date.

// 1. TreeGrowthAllocator Allocate net production so that P-M = G. 
// 2. CountLeaves         Count the number of leaves in a tree.


namespace Lignum{
  //Growth Allocator for Cf and Hw tree.
  //Usage: TreeGrowthAllocator<TS,BUD,F1,F2) G(tree); 
  //       Bisection(0,5,G);
  //Output:  After  the iteration,  the  segment  lengths  in the  new
  //segments allocate  P-M=G (including the induced  diameter and root
  //growth).  F1:  set the segment lengths with  lamda.  F2: calculate
  //the effect of diameter growth  induced by the new segments and the
  //foliage.   Root growth  is assumed  to be  propotional to  the new
  //foliage mass:  Wrnew = LGPar*Wfnew. Instead of  Bisection, one can
  //have any root finding algorithm (to be) implemented in c++adt.
  template<class TS,class BUD,class F1,class F2> 
  class TreeGrowthAllocator;


  //Count the number of leaves in a tree

  template <class TS,class BUD,class SHAPE>
    class CountLeaves{
    public:
    int& operator ()(int& n, TreeCompartment<TS,BUD>* tc)const;
  };


}//closing namespace Lignum
#endif

#include <LGMUtilityI.h>
















