
#ifndef ZBRENT_H
#define ZBRENT_H

using namespace Lignum;

template <class TS,class BUD>
LGMdouble BracketFunction(LGMdouble& a, LGMdouble& b, LGMdouble& fa, LGMdouble& fb, Tree<TS,BUD>& tree);

template <class TS,class BUD>
LGMdouble HwBracketFunction(LGMdouble& a, LGMdouble& b, LGMdouble& fa, LGMdouble& fb, Tree<TS,BUD>& tree);

template <class TS,class BUD>
LGMdouble Zbrent(LGMdouble x1,LGMdouble x2,LGMdouble fa, LGMdouble fb, LGMdouble tol, Tree<TS,BUD>& tree);

template <class TS,class BUD>
LGMdouble HwZbrent(LGMdouble x1,LGMdouble x2,LGMdouble fa, LGMdouble fb, LGMdouble tol, Tree<TS,BUD>& tree);

template <class TS,class BUD>
bool AdjustIncrementZbrent(Tree<TS,BUD>& tree);

template <class TS,class BUD>
void AdjustNewLambda(Tree<TS,BUD> &tree);

//Adjust the length of the size of the new segments. First bracket the function P-R-F(L)
//and then find the root using the Van Wijngaarden, Dekker and Brent method.
template <class TS,class BUD>
bool AdjustIncrementHwZbrent(Tree<TS,BUD>& tree);

#include "ZBrentI.h"

#endif