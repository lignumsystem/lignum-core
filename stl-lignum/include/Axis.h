/// \file Axis.h
/// \brief Tree axis
///
/// Tree axis as a list of tree compartments
#ifndef AXIS_H
#define AXIS_H

#include <list>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
#include <TreeCompartment.h>
#include <TreeFunctor.h>




using namespace cxxadt;

namespace Lignum{
  ///\brief Axis attributes
  class AxisAttributes{
  public:
    AxisAttributes(AxisAttributes& aa) : state(aa.state) {}
    AxisAttributes(LGMdouble s):state(s){ }
      LGMdouble state; ///<< Axis state ALIVE or DEAD 
  };

///\brief Tree axis is a list of tree compartments
///\tparam TS Tree segment
///\tparam BUD Bud 
template <class TS,class BUD=DefaultBud<TS> >
class Axis: public TreeCompartment<TS,BUD>{
  ///\brief Query terminating bud
  ///\return Terminating bud
  template <class TS1,class BUD1>
  friend Bud<TS1,BUD1>* GetTerminatingBud(const Axis<TS1,BUD1>& axis);
  template <class TS1,class BUD1>
  ///\brief Query the list of tree compartments
  ///\retval axis The list of tree compartments
  friend list<TreeCompartment<TS1,BUD1>*>& GetTreeCompartmentList(Axis<TS1,BUD1>& axis);
  ///\brief Append tree compartment
  ///\param axis Tree axis 
  ///\param ts Tree compartment
  ///\post Tree compartment \p ts is the last element in \p axis
  template <class TS1,class BUD1>
  friend void InsertTreeCompartment(Axis<TS1,BUD1>& axis, TreeCompartment<TS1,BUD1>* ts);
  template <class TS1,class BUD1>
  ///\brief Insert tree compartment
  ///\param axis Tree axis
  ///\param ts Tree compartment
  ///\post Tree compartment \p ts second last element in \p axis behind terminating bud.
  friend void InsertTreeCompartmentSecondLast(Axis<TS1,BUD1>& axis, 
					      TreeCompartment<TS1,BUD1>* ts);
  ///\brief Get first tree compartment.
  ///
  ///The first tree compartment can be a bud or a tree segment.
  ///\param axis Tree axis
  ///\return Tree compartment
  ///\retval NULL if tree compartment list is empty
  ///\note Query type with *dynamic_cast* for Bud or TreeSegment
  template <class TS1,class BUD1>
  friend TreeCompartment<TS1,BUD1>* GetFirstTreeCompartment(Axis<TS1,BUD1>& axis);
  template <class TS1,class BUD1>
  ///\brief Get the last tree segment
  ///\param axis tree axis
  ///\return Last tree segment
  ///\retval NULL if no segments
  friend TreeSegment<TS1, BUD1>* GetLastTreeSegment(Axis<TS1,BUD1>& axis);
  ///\brief Get the first tree segment
  ///\param axis tree axis
  ///\return First tree segment
  ///\retval NULL if no segments
  template <class TS1,class BUD1>
  friend TreeSegment<TS1, BUD1>* GetFirstTreeSegment(Axis<TS1,BUD1>& axis);
  ///\brief Sum of values for \p name in HwTreeSegments of \p Age
  ///\param axis Tree axis
  ///\param name Attribute name
  ///\param Age HwTreeSegment age
  ///\return Sum of values for \p name in HwTreeSegments of \p Age 
  template <class TS1,class BUD1>
  friend LGMdouble GetSumValue(Axis<TS1,BUD1>& axis, LGMAD name, int Age);
  ///\brief Delete element before the terminating bud
  ///\param  axis Tree axis
  ///\pre Axis size > 1
  template <class TS1,class BUD1>
  friend void Delete2ndLastTreeCompartment(Axis<TS1,BUD1>& axis);
  ///\brief Get axis property value.
  ///
  ///The property name can be a meaningful name in cxxadt::LGMAD.
  ///For example LGAL returns \p axis length
  ///\param axis Tree axis
  ///\param name Attribute name
  ///\return 
  template <class TS1,class BUD1>
  friend LGMdouble GetValue(Axis<TS1,BUD1>& axis, LGMAD name);
  ///\brief Se axis attribute value
  ///
  ///The attribute \p name can be cxxadt::LGAstate
  ///\param axis Tree axis
  ///\param name Attribute name 
  ///\param value Attribute value
  ///\return Previous attribute value 
  template <class TS1,class BUD1>
  friend LGMdouble SetValue(Axis<TS1,BUD1>& axis, LGMAD name, const LGMdouble value);
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchFoliage(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend int GetNumberOfCompartments(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchSapwoodMass(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchHeartwoodMass(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchWoodMass(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchPhotosynthesis(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchRespiration(Axis<TS1,BUD1>& axis);
  ///\brief Get current axis number
  ///\return Axis number
  template <class TS1,class BUD1>  
  friend int GetAxisNumber(Axis<TS1,BUD1>& axis);
  ///\brief Set a new axis number
  ///\return Previous axis number
  template <class TS1,class BUD1>  
  friend int SetAxisNumber(Axis<TS1,BUD1>& axis, int number); 
public:
  ///\brief Delete the tree compartments in \p tc_ls, the list of tree compartments
  virtual ~Axis();
  Axis();
  ///\brief Constructor
  ///\param p Position
  ///\param d Direction
  ///\param t Tree axis belongs to
  ///\post The tree compartment list \p tc_ls is empty 
  Axis(const Point& p, const PositionVector& d, Tree<TS,BUD>* t);
  Axis(Tree<TS,BUD>* t):TreeCompartment<TS,BUD>(t),aa(ALIVE), axis_number(0){ }
  //Copy constructor (for making a Tree out of an Axis - see comments in Tree.h)
  Axis(Axis<TS,BUD>& ax) : aa(ax.aa), tc_ls(ax.tc_ls), axis_number(ax.axis_number) {}
protected: 
  AxisAttributes aa;///< Axis attributes
  list<TreeCompartment<TS,BUD>*> tc_ls; ///< Tree compartment list
  int axis_number;///Identification number
};




}//closing namespace Lignum

//The implementations of methods and functions Axis
#include <AxisI.h>

#endif
