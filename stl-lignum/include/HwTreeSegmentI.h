#ifndef HWTREESEGMENTI_H
#define HWTREESEGMENTI_H

template<class TS, class BUD >
list<BroadLeaf*>& GetLeafList(HwTreeSegment<TS,BUD>& ts)
{
  return ts.leaf_ls;
}

template<class TS, class BUD >
void InsertLeaf(HwTreeSegment<TS,BUD>& ts, BroadLeaf* l)
{
  ts.leaf_ls.push_back(l);
}

#endif
