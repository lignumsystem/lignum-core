#ifndef OPENGLFUNCTOR_H
#define OPENGLFUNCTOR_H

#include <vector>
#include <Point.h>
#include <LGMUnits.h>
#include <Lignum.h>

namespace Lignum
{

  //template <class TS,class BUD=DefaultBud<TS> > class TreeCompartment;

  //template <class TS,class BUD=DefaultBud<TS> > class TreeSegment;



template <class TS,class BUD>
class DrawBudFunctor
{
public:
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const; 
  DRAW_TYPE mode;
};


template <class TS,class BUD>
class DrawStemFunctor
{
public:
	TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const; 
	LGMdouble max_rad;
	LGMdouble min_rad;
};


template <class TREE>
class DrawRootFunctor
{
public:
	RootCompartment<TREE>* operator()(RootCompartment<TREE>* tc)const; 
       
};


template <class TS,class BUD>
class DrawNeedlesFunctor
{
public:
        TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const; 
};



template <class TS,class BUD,class S = Ellipsis>
class DrawLeavesFunctor
{
public:
	DrawLeavesFunctor(LGMdouble x, LGMdouble y) { leave_size_x = x; leave_size_y = y; }
	TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const; 
	LGMdouble leave_size_x;
	LGMdouble leave_size_y;
};




template <class TS,class BUD,class S = Ellipse>
class DrawLignumLeavesFunctor
{
public:
   DrawLignumLeavesFunctor() {};
   TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const; 
};




}

#include "OpenGLFunctorI.h"



#endif
