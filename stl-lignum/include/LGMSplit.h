/// \file LGMSplit.h
/// \brief Divide tree segments into smaller parts 
#ifndef LGMSPLIT_H
#define LGMSPLIT_H

#include <fstream>
#include <Lignum.h>
#include <LGMGeometry.h>
#include <VoxelSpace.h>
#include <FindForestBoundingBox.h>
#include <XMLTree.h>

namespace Lignum{

  ///\brief Default functor to cut segments 
  template <class TS,class BUD>
  class CutSegment{
  public:
    bool operator()(list<TreeCompartment<TS,BUD>*>& tc_ls,
		    typename list<TreeCompartment<TS,BUD>*>::iterator iter,
		    METER l_new, METER l_min);
  };

  ///\brief Functor to divide the segments in a tree into smaller segments.
  ///
  ///Makes cuts at the interval l, starting at the base of a segment and continuing until
  /// the end segment's length is <= l + l_min.  The presence of l_min ensures
  /// that no segments of extremely short length will be created, which can cause
  /// runtime errors.  If splitting does cause a runtime error, you can try
  /// providing an increased value of l_min as a second argument to the functor.
  /// call with ForEach to split all segments in a tree:<br>
  ///
  ///        treels = ReadTrees(treels,directory,file_name);
  ///        for (unsigned int i=0; i < treels.size(); i++){
  ///            HBTree *myt = treels[i];
  ///            ForEach(*myt, LGMSplit<HBSegment,HBBud>(0.1));
  ///        }
  template <class TS, class BUD, class F=CutSegment<TS,BUD> >
  class LGMSplit {
  public:
    LGMSplit(METER len, METER l_minimum=0.0001) : l(len), l_min(l_minimum){ }
    void operator ()(TreeCompartment<TS,BUD>* tc)const;
    void split_axis(Axis<TS,BUD>& axis, METER l, METER l_min)const;
  private:
    METER l;     ///< Distance between cuts
    METER l_min; ///< Minimum segment length. defaults to 0.1mm
    mutable F f; ///<The functor that actually splits the segment \sa CutSegment
  };
}

#include "LGMSplitI.h"

#endif
