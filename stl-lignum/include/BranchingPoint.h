/// \file BranchingPoint.h
/// \brief Tree branching point
#ifndef BRANCHINGPOINT_H
#define BRANCHINGPOINT_H

#include <list>
#include <algorithm>
#include <numeric>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>

using namespace cxxadt;

namespace Lignum{

///\brief BranchingPoint is a list of Axes
///\tparam TS Tree segment
///\tparam BUD Bud
template <class TS,class BUD=DefaultBud<TS> >
class BranchingPoint: public TreeCompartment<TS,BUD>{
  ///\brief Append terminating bud
  ///
  ///Create new Axis and append \p bud to it
  ///\param bp Branching point
  ///\param bud Bud 
  template <class TS1,class BUD1>
  friend void InsertTerminatingBud(BranchingPoint<TS1,BUD1>& bp, Bud<TS1,BUD1>* bud);

  ///\brief Insert axis
  ///\param bp Bracnhing point
  ///\param axis Axis 
  template <class TS1,class BUD1>
  friend void InsertAxis(BranchingPoint<TS1,BUD1>& bp, Axis<TS1,BUD1>* axis);

  ///\brief Output operator
  template <class TS1,class BUD1>
  friend ostream &operator << (ostream& os, BranchingPoint<TS1,BUD1>& ts);

  ///\brief Get axis list
  ///\param bp Branching point
  ///\retval axis_ls Axis list
  template <class TS1,class BUD1>
  friend std::list<Axis<TS1,BUD1>*>& GetAxisList(BranchingPoint<TS1,BUD1>& bp);

  ///\brief Get max branch radius
  ///\return Maximum radius of the first tree segments in the axes.
  template <class TS1, class BUD1>
  friend LGMdouble GetMaxRadius(BranchingPoint<TS1,BUD1>& bp);

  ///\brief Get branching point attribute value
  ///\param bp Branching point
  ///\param name Attribute name
  ///\return Attribute value matching name 
  template <class TS1, class BUD1>
  friend LGMdouble GetValue(BranchingPoint<TS1,BUD1>& bp,LGMAD name);

  ///\brief Set branching point attribute value
  ///\param bp Branching point
  ///\param name Attribute name
  ///\param value New attribute alue
  ///\return Previous attribute value matching name 
  template <class TS1, class BUD1>
  friend LGMdouble SetValue(BranchingPoint<TS1,BUD1>& bp,LGMAD name, 
			    LGMdouble value); 
public:
  BranchingPoint();
  ///\brief Initiate \p omega and \p type to 0.0 and -1.0 respectively
  ///\param p Branching point position
  ///\param d Branching point direction
  ///\param t Tree branching point belongs to
  BranchingPoint(const Point& p, const PositionVector& d, Tree<TS,BUD>* t);
  ///\brief Initiate type to -1.0
  ///\param p Branching point position
  ///\param d Branching point direction
  ///\param go Branching point Gravelius order
  ///\param t Tree branching point belongs to
  BranchingPoint(const Point& p, const PositionVector& d, LGMdouble go,Tree<TS,BUD>* t);
  ///\brief Set the tree branching point belongs to
  ///\param t Tree 
  BranchingPoint(Tree<TS,BUD>* t):TreeCompartment<TS,BUD>(t) { }
  ///\brief Delete axes in the axis list
  virtual ~BranchingPoint();
private:
  /// List of Axes
  list<Axis<TS,BUD>*> axis_ls; 
  ///Max diameter of the forking axes, see Lignum::TreePhysiologyVigourIndex
  LGMdouble maxd;
  ///Gravelius  order, set  in Lengine::lstringToLignum,	 
  LGMdouble omega;
  ///Type of  the bud  at the end  of axis
  LGMdouble type;
  ///State of the  bud at the end of  axis.
  LGMdouble state;
		  
};


} //close namespace Lignum


#include <BranchingPointI.h>


#endif

