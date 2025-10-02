/// \file LGMSplitI.h
/// \brief Divide tree segments implementation
#ifndef SPLITI_H
#define SPLITI_H

namespace Lignum{
  /// Divides the segment specified by tc_ls and iter into two segments.  this is
  /// accomplished by shortening the old segment and inserting a new segment
  /// before the old. the length of the new segment is l_new.  will not split if
  /// it results in a segment shorter than l_min.
  /// returns true if the segment was successfully divided in two,
  /// false otherwise.
  template <class TS, class BUD>
  bool CutSegment<TS,BUD>::operator()(list<TreeCompartment<TS,BUD>*>& tc_ls,
				      typename list<TreeCompartment<TS,BUD>*>::iterator iter,
				      METER l_new, METER l_min)
  {
    if(!dynamic_cast<TS*>(*iter)) {
      return false;
    }
    TS *ts = (TS*)*iter;
    const METER l = GetValue(*ts, LGAL);
    if(l < l_new + l_min) return false;
    const METER r = GetValue(*ts, LGAR);
    const METER rtop = GetValue(*ts, LGARTop);
	
    TS *ts_new = new TS(GetPoint(*ts), GetDirection(*ts),
			GetValue(*ts,LGAomega), l_new, r,
			GetValue(*ts, LGARh), &GetTree(*ts));
    const METER rtop_new = ((r - rtop) / l) * (l - l_new) + rtop;
    SetValue(*ts_new, LGARTop, rtop_new);

    SetValue(*ts, LGAL, l - l_new);
    SetValue(*ts, LGAR, rtop_new);
    const Point& p = GetPoint(*ts) + l_new*(Point)GetDirection(*ts);
    // GetDirection(*ts) above assumed to be unit vector
    SetPoint(*ts, p);

    BranchingPoint<TS,BUD>* bp = new BranchingPoint<TS,BUD>(p,GetDirection(*ts),
							    &GetTree(*ts));

    tc_ls.insert(iter, ts_new);
    tc_ls.insert(iter, bp);

    return true;
  }

  /// Split repeatedly until the segment is divided into segments of length l,
  /// with the exception of the last segment with l_min <= length < l + l_min
  template <class TS, class BUD, class F>
  void LGMSplit<TS,BUD,F>::split_axis(Axis<TS,BUD>& axis, METER l, METER l_min)const
  {
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(axis);
    typename list<TreeCompartment<TS,BUD>*>::iterator it = tc_ls.begin();
    for(it = tc_ls.begin(); it != tc_ls.end(); ++it) {
      while(f(tc_ls, it, l, l_min)){/*empty block*/};
    }
  }

  template <class TS, class BUD,class F>
  void LGMSplit<TS,BUD,F>::operator()(TreeCompartment<TS,BUD>* tc) const
  {
    if(Axis<TS,BUD>* myaxis = dynamic_cast<Axis<TS,BUD>*>(tc))
      split_axis(*myaxis, l, l_min);
  }
}
#endif
