#ifndef ROOTSYSTEM_H
#define ROOTSYSTEM_H

/*********************************************************************
 *Implementing root system for  LIGNUM. The idea of the implementation
 *is as above ground part of the tree. Root system is represented with
 *a class hierarchy of  RootCompartment (the base class), RootSegment,
 *RootTip,  RootAxis and  RootBranchingPoint. RootSegment  and RootTip
 *will be the main  functioning units, RootBranchingPoint will capture
 *the branching structure of the  root system and RootAxis is the list
 *of  RootCompartments. As  for above  ground part  generic algorithms
 *will be provided  to traverse the root system  and apply functors to
 *root compartments.  Also an  L-system implementation will follow for
 *modeling  the  dynamics of  architectural  development  of the  root
 *system.  Finally, I propose "cleaning" GetValue and SetValue for the
 *tree segment  as I've done  for root segment. Instead  of memorizing
 *functions  for  compound  attributes  all access  to  attributes  is
 *through  GetValue and  SetValue.  Note  also  that the  use of  same
 *symbols is quite possible. See RootSystemI.h for implementation.
 *********************************************************************/

#include <LGMSymbols.h>
#include <LGMUnits.h>
#include <Point.h>
#include <PositionVector.h>
#include <list>
#include <algorithm>
using namespace cxxadt;
using namespace std;

namespace Lignum {
 
  template <class TREE>
    class RootCompartment{
    friend Point GetPoint(const RootCompartment<TREE>& rc){return rc.p;}
    friend PositionVector GetDirection(const RootCompartment<TREE>& rc){
      return rc.d;
    }
    friend void SetPoint(RootCompartment<TREE>& rc,const Point& pos){
      rc.p = pos;
    }
    friend void SetDirection(RootCompartment<TREE>& rc,
			     const PositionVector& dir){rc.d = dir;}
    friend const TREE& GetTree(const RootCompartment<TREE>& rc){return rc.t;}
  public:
    RootCompartment(const Point& point, const PositionVector& dir, 
		    const TREE& tree):p(point),d(dir),t(tree) {}
    virtual ~RootCompartment(){}
  protected:
    Point p;
    PositionVector d;
    const TREE& t;
  };

  template <class TREE>
    class RootAxis: public RootCompartment<TREE>{
    template <class TREE1>
    friend list<RootCompartment<TREE1>*>& GetRootCompartmentList(RootAxis<TREE1>& ra);
    template <class TREE1>
    friend void InsertRootCompartment(RootAxis<TREE1>& ra,
				      const RootCompartment<TREE1>* rpb);
  public:
    RootAxis(const Point& p, const PositionVector& d, const TREE& t):
    RootCompartment<TREE>(p,d,t) {}
    virtual ~RootAxis(){}
  private:
    list<RootCompartment<TREE>*> rc_ls;
  };

  template <class TREE>
    class RootBranchingPoint:public RootCompartment<TREE>{
    template <class TREE1>
    friend list<RootAxis<TREE1>*>& GetAxisList(RootBranchingPoint<TREE1>& rbp);
    template <class TREE1>
    friend void InsertAxis(RootBranchingPoint<TREE1>& rbp,const RootAxis<TREE1>* ra);
  public:
    RootBranchingPoint(const Point& pos, const PositionVector& dir,
		       const TREE& t):
    RootCompartment<TREE>(pos,dir,t){}
    virtual ~RootBranchingPoint(){}
  private:
    list<RootAxis<TREE>*> ra_ls; //list of root axes
  };

  class RootSegmentAttributes{
  public:
    RootSegmentAttributes(METER Length,METER Radius,METER RTopRadius,
			  METER Rheartwood, METER RhairRadius,LGMdouble go):
    L(Length),R(Radius),RTop(RTopRadius),Rh(Rheartwood),Rhair(RhairRadius),
      omega(go){}
  public:
    METER L;      //Length
    METER R;      //Radius including bark
    METER RTop;   //Radius at top
    METER Rh;     //Heartwood radius
    METER Rhair;  //Radius including root hair
    LGMdouble omega; //Gravelius order
  };

  //RootSegment  is the  main functioning  unit.  As  tree  segment it
  //consists of cylindrical layers  of heartwood and sapwood. The root
  //hair, i.e. fine roots, is  aggregated as the third third cyndrical
  //layer (c.f foliage for CfTreeSegment)
  template <class TREE>
    class RootSegment:public RootCompartment<TREE>{
    template <class TR>
      friend LGMdouble GetValue(const RootSegment<TR>& rs, LGMAD name);
    template <class TR>
      friend LGMdouble SetValue(RootSegment<TR>& rs, LGMAD name,
				LGMdouble value);
    template <class TR>
      friend Point GetEndPoint(RootSegment<TR>& rs);
  public:
    RootSegment(const Point& pos, const PositionVector& dir,
		METER Length,METER Radius,METER RTopRadius,
		METER RheartwoodRadius, METER RhairRadius, LGMdouble go,
		const TREE& t):
    RootCompartment<TREE>(pos,dir,t),rsa(Length,Radius,RTopRadius,
					 RheartwoodRadius,RhairRadius,go){}
    virtual ~RootSegment(){}
  private:
    RootSegmentAttributes rsa;
  };

  class RootTipAttributes{
  public:
    RootTipAttributes(LGMdouble coll, LGMdouble st, STATUS s, LGMdouble go):
    collision(coll),status(st),state(s),omega(go){}
    RootTipAttributes():collision(0),status(0),state(ALIVE),omega(0){}
  public:
    LGMdouble collision; //collision with another root compartment
    LGMdouble status;    //user defined counter
    STATUS state;        //DEAD  or ALIVE (c.f.   Bud), note  the type
			 //STATUS is confusing!
    LGMdouble omega;     //Gravelius order
  };

  template <class TREE>
    class RootTip:public RootCompartment<TREE>{
    template <class TR>
      friend LGMdouble GetValue(const RootTip<TR>& rt, LGMAD name);
    template <class TR>
      friend LGMdouble SetValue(RootTip<TR>& rt, LGMAD name, LGMdouble value);
    template <class TR>
      friend STATUS GetValue(const RootTip<TR>& rt, LGMAS name);
    template <class TR>
      friend STATUS SetValue(RootTip<TR>& rt, LGMAS name, STATUS value);
  public:
    RootTip(const Point& pos, const PositionVector& dir,
	    LGMdouble coll, LGMdouble status, STATUS state, LGMdouble go,
	    const TREE& t):
    RootCompartment<TREE>(pos,dir,t),rta(coll,status,state,go){}
    RootTip(const Point& pos, const PositionVector& dir, LGMdouble go,
	    const TREE& t):
    RootCompartment<TREE>(pos,dir,t),rta(0,0,ALIVE,go){}
    virtual ~RootTip(){}
  private:
    RootTipAttributes rta;
  };

  //Generic algorithms for root system (c.f. generic algorithms for Tree).
  template <class TREE, class Function>
    void ForEach(RootAxis<TREE>& ra, const Function f);
  template <class TREE, class T, class BinOp>
    T& Accumulate(RootAxis<TREE>& ra, T& init, const BinOp op);
  template <class TREE, class T, class BinOp>
    T& AccumulateDown(RootAxis<TREE>& ra, T& init, const BinOp op);
  template <class TREE, class T, class BinOp1, class BinOp2>
    T& AccumulateDown(RootAxis<TREE>& ra, T& init, const BinOp1 op1, 
		      const BinOp2 op2);
  template <class TREE, class T, class BinOp>
    void PropagateUp(RootAxis<TREE>& ra, T& init, const BinOp op);

}//close namespace Lignum


#endif

//Implementation of root system and algorithms
#include <RootSystemI.h>

