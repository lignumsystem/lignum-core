/// \file HwTreeSegment.h
/// \brief Hardwood tree segment
#ifndef HWTREESEGMENT_HPP
#define HWTREESEGMENT_HPP

#include <list>
#include <BroadLeaf.h>
#include <Uniform.h>
#include <LGMdecl.h>
#include <LGMUnits.h>
#include <LGMSymbols.h>
#include <Firmament.h>
#include <TreeSegment.h>
namespace Lignum{

///\brief Hardwood tree segment
///
///HwTreeSegment has properties of TreeSegment. Leaves are in a list container.
///\tparam TS Tree segment
///\tparam BUD Bud
///\tparam SHAPE Leaf geometric shape
///\sa Lignum::BroadLeaf
template <class TS, class BUD=DefaultBud<TS>, class SHAPE=cxxadt::Ellipse>
class HwTreeSegment:public TreeSegment<TS,BUD>
{
  ///\brief Insert one leaf to the list
  ///\param ts Tree segment
  ///\param l Leaf
  template <class TS1,class BUD1, class S>
  friend void InsertLeaf(HwTreeSegment<TS1,BUD1,S>& ts, BroadLeaf<S>* l);

  ///\brief Reset values used in radiation calculations
  ///\param ts Tree segment
  template <class TS1,class BUD1,class S>
  friend void InitializeForRadiation(HwTreeSegment<TS1,BUD1,S>& ts);

  ///\brief Number of leaves in the leaf list
  ///\return Length of the leaf list
  template <class TS1,class BUD1,class S>
  friend int GetNumberOfLeaves(const HwTreeSegment<TS1,BUD1,S>& ts);

  ///\brief Sum  of leaf areas in the leaf list
  ///\param ts tree segment 
  ///\return Tree segment leaf area
  template <class TS1,class BUD1,class S>
  friend LGMdouble GetLeafArea(const HwTreeSegment<TS1,BUD1,S>& ts);

  ///\brief Distribute leaf area to leaves.
  ///
  ///Sets the area of the all leaves, when the (true) area of the
  ///all leaves is given as input. That is, every leaf gets the same (true) area
  ///that is equal to leaf area / number of leaves.  Area of the ellipse
  ///= leaf area / degree_of_filling. Return old (true) leaf area, return
  ///0.0, and do nothing if no leaves.
  ///\note Lignum::BroadLeaf returns true area of the leaf
  ///\param ts Tree segment
  ///\param value Total leaf area
  template <class TS1,class BUD1,class S>
  friend LGMdouble SetLeafArea(HwTreeSegment<TS1,BUD1,S>& ts, const LGMdouble value);

  ///\brief Set tree segment attribute value
  ///\param ts Tree segment
  ///\param name Attribute name
  ///\param value Attribute value
  ///\sa Lignum::LGMAD names
  template <class TS1,class BUD1,class S>
  friend LGMdouble SetValue(const HwTreeSegment<TS1,BUD1,S>& ts, const LGMAD name, const LGMdouble value);
  ///\brief Get tree segment attribute value
  ///\param ts Tree segment
  ///\param name Attribute name
  ///\sa Lignum::LGMAD names
  template <class TS1,class BUD1,class S>
  friend LGMdouble GetValue(const HwTreeSegment<TS1,BUD1,S>& ts, const LGMAD name);
  ///\brief Get the leaf list
  ///\brief ts Tree segment
  ///\retval leaf_ls The leaf list
  template <class TS1,class BUD1, class S>
  friend std::list<BroadLeaf<S>*>& GetLeafList(HwTreeSegment<TS1,BUD1,S>& ts);

public:
  ///\brief Constructor
  ///\param p Position
  ///\param pv Tree segment direction
  ///\param go Gravelius order
  ///\param l Tree segment length
  ///\param r Tree segment radius
  ///\param rh Tree segment heartwood radius
  ///\param tree Tree the tree segment belongs to 
  HwTreeSegment(const Point& p,const PositionVector& pv,
		const LGMdouble go, const METER l, const METER r,
		const METER rh,Tree<TS,BUD>* tree)
  :TreeSegment<TS,BUD>(p,pv,go,l,r,rh,tree)
  { //Initialize the vigor to -1.0, so  you for sure will see if it is
    //computed vor not.
    SetValue(*this, LGAvi,-1.0); 
  }
  HwTreeSegment(Tree<TS,BUD>* tree):TreeSegment<TS,BUD>(tree) { }
  ///\brief Photosynthesis
  ///\deprecated Use functors to implement photynthesis models
  void photosynthesis();
  ///\brief Respiration
  ///\deprecated Use functors to impelemnt respiration models
  void respiration();
  ///\brief Diameter growth
  ///\deprecated Use functors to implement diameter growth models
  TcData& diameterGrowth(TcData& data);
  ///\brief Aging
  ///\deprecated Use functors to implement aging processes in a tree segment
  void aging();
  ///\brief Add leaf
  ///\deprecated Use InsertLeaf()
  virtual void addLeaf(BroadLeaf<SHAPE>* l);
protected:
  list<BroadLeaf<SHAPE>*> leaf_ls;///< List of leaves
};


}//close namespace Lignum

#include <HwTreeSegmentI.h>
#include <HwTreeSegmentMetabolismI.h>


#endif
