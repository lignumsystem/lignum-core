#ifndef OPENGLFUNCTOR_H
#define OPENGLFUNCTOR_H

#include <vector>
#include <Point.h>
#include <LGMUnits.h>


namespace Lignum
{

template <class TS,class BUD=DefaultBud<TS> > class TreeCompartment;

template <class TS,class BUD=DefaultBud<TS> > class TreeSegment;




template <class TS,class BUD>
class DrawStemFunctor
{
public:
	TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const; 
	LGMdouble max_rad;
	LGMdouble min_rad;
};



template <class TS,class BUD>
class DrawLeavesFunctor
{
public:
	DrawLeavesFunctor(LGMdouble x, LGMdouble y) { leave_size_x = x; leave_size_y = y; }
	TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const; 
	LGMdouble leave_size_x;
	LGMdouble leave_size_y;
};

}

#include "OpenGLFunctorI.h"



#endif