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
  SetValue(ts, Qin, 0.0);
  SetValue(ts, Qabs, 0.0);
  list<BroadLeaf*> ll = GetLeafList(ts);
  for(list<BroadLeaf*>::iterator i = ll.begin(),
	i != ll.end(), i++) {
    SetValue(*i, Qabs, 0.0);
    SetValue(*i, Qin, 0.0);
  }
  for(int j = 0; j < f.numberOfRegions(); j++) {
    ts.bla.sv[j] = 0.0;
  }
}

#endif
