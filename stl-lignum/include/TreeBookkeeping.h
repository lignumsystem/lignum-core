#ifndef TREEBOOKKEEPING_H
#define TREEBOOKKEEPING_H


namespace Lignum{

//Age TreeCompartment by delta_age
template <class TS, class BUD=DefaultBud<TS> >
class Age: public AdaptableTCFunction<TS,BUD>{
public:
   Age(LGMdouble delta_a) { delta_age = delta_a; }
   TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
private:
  LGMdouble delta_age;
};


}

#include <TreeBookkeepingI.h>
#endif
