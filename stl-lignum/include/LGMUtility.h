#ifndef LGMUTILITY_H
#define LGMUTILITY_H

/* #include <iostream> */

/* #include <LGMdecl.h> */
/* #include <LGMSymbols.h> */
/* #include <TreeCompartment.h> */
/* #include <BroadLeaf.h> */
/* #include <Algorithms.h> */

//Declarations (interface) of a number useful functions for
//STL-LIGNUM. Please keep the list of available utilities up to date.

// 1. CountLeaves        Count the number of leaves in a tree


namespace Lignum{

  //Count the number of leaves in a tree

  template <class TS,class BUD,class SHAPE>
    class CountLeaves{
    public:
    int& operator ()(int& n, TreeCompartment<TS,BUD>* tc)const;
  };


}//closing namespace Lignum
#include <LGMUtilityI.h>

#endif

















