#ifndef TREEBOOKKEEPING_I_H
#define TREEBOOKKEEPING_I_H

#include <typeinfo>
// Contains functions for evaluating quantities at the level
// of the tree.
// At the moment, photosynthesis realized

namespace Lignum{


//Age TreeCompartments by the given delta_age
template <class TS, class BUD>
TreeCompartment<TS,BUD>*  Age<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
{
        SetValue(*tc, age, GetValue(*tc,age)+delta_age);

        
        return tc;
}


 
} //Closing namespace Lignum

#endif



