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

template<class TS, class BUD >
void InitializaForRadiation(HwTreeSegment<TS,BUD>& ts)
{
  Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*ts));
  Firmament& f = GetFirmament(tt);
  int nr =  f.numberOfRegions();
  vector<LGMdouble> one(nr, 1.0);
  SetValue(ts, Qin, 0.0);
  SetValue(ts, Qabs, 0.0);
  list<BroadLeaf*> ll = GetLeafList(ts);
  for(list<BroadLeaf*>::iterator i = ll.begin(),
	i != ll.end(), i++) {
    SetValue(*i, Qabs, 0.0);
    SetValue(*i, Qin, 0.0);
    SetRadiationVector(*i, one);
  }

}


template<class TS, class BUD >
bool HasLeaves(HwTreeSegment<TS,BUD>& ts)
{
  list<BroadLeaf*>& leaf_list = GetLeafList(ts);
  if(leaf_list.empty()) {
    return false;
  }
  else
    return true;

}


#endif
