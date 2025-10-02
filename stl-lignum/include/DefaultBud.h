/// \file DefaultBud.h
/// \brief Example for the minimum bud
#ifndef DEFAULTBUD_H
#define DEFAULTBUD_H

#include <LGMdecl.h>
#include <Tree.h>

namespace Lignum{

///\brief Example for the minimum bud 
template <class TS>
class DefaultBud:public Bud<TS,DefaultBud<TS> >{
 public:
  DefaultBud(const Point& p, const PositionVector& d, 
	     const LGMdouble omega, Tree<TS,DefaultBud<TS> >* tree)
    :Bud<TS,DefaultBud<TS> >(p,d,omega,tree){}
};

}//closing namespace Lignum
#endif
