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
void InitializeForRadiation(HwTreeSegment<TS,BUD>& ts)
{
  Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*ts));
  Firmament& f = GetFirmament(tt);
  int nr =  f.numberOfRegions();
  vector<LGMdouble> one(nr, 1.0);
  list<BroadLeaf*>& ll = GetLeafList(const_cast<HwTreeSegment<TS,BUD>&>(ts));
  for(list<BroadLeaf*>::iterator i = ll.begin();
	i != ll.end(); i++) {
    SetValue(*i, Qabs, 0.0);
    SetValue(*i, Qin, 0.0);
    SetRadiationVector(*i, one);
  }

}


template<class TS, class BUD >
int GetNumberOfLeaves(const HwTreeSegment<TS,BUD>& ts)
{
  list<BroadLeaf*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD>&>(ts));
  if(leaf_list.empty()) {
    return 0;
  }
  else
    return (int)leaf_list.size();

}

//Sets the area of the all leaf ellipses, when the (true) area of the
//all leaves is given as input. That is, every leaf gets the same (true) area
//that is equal to input/# of leaves.  Area of the ellipse
//= leaf area / degree_of_filling. Return old (true) leaf area, return
//0.0, and do nothing if no leaves
template<class TS, class BUD >
LGMdouble SetLeafArea(HwTreeSegment<TS,BUD>& ts, const LGMdouble value)
{
  int no_leaves = GetNumberOfLeaves(ts);
  if(no_leaves == 0)
    return 0.0;

  LGMdouble old_area = 0.0;
  list<BroadLeaf*>& leaf_list = GetLeafList(ts);
  list<BroadLeaf*>::iterator I;
  LGMdouble LA = value / (double)no_leaves;
  for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
    old_area += GetValue(**I, A);   //BroadLeaf returns true area of the leaf
    SetValue(**I, A, LA);
  }
  return old_area;
}

//Returns total leaf area of the segment, return 0.0 if no leaves.
template<class TS, class BUD >
LGMdouble GetLeafArea(const HwTreeSegment<TS,BUD>& ts)
{

  LGMdouble area = 0.0;
  list<BroadLeaf*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD>&>(ts));
  list<BroadLeaf*>::iterator I;
  for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
    area += GetValue(**I, A);   //BroadLeaf returns true area of the leaf
  }

  return area;
}

template<class TS, class BUD >
LGMdouble GetValue(const HwTreeSegment<TS,BUD>& ts, const LGMAD name)
{

  LGMdouble value = 0.0;

  if (name == Wf) {
    list<BroadLeaf*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD>&>(ts));
    list<BroadLeaf*>::iterator I;
    for(I = leaf_list.begin(); I != leaf_list.end(); I++)
      value += GetValue(**I, Wf);
    
    return value;
  }
  elseif (name == P) {
    list<BroadLeaf*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD>&>(ts));
    list<BroadLeaf*>::iterator I;
    for(I = leaf_list.begin(); I != leaf_list.end(); I++)
      value += GetValue(**I, P);
    
    return value;
  }
  elseif (name == Qin) {
    list<BroadLeaf*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD>&>(ts));
    list<BroadLeaf*>::iterator I;
    for(I = leaf_list.begin(); I != leaf_list.end(); I++)
      value += GetValue(**I, Qin);
    
    return value;
  }
  elseif (name == Qabs) {
    list<BroadLeaf*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD>&>(ts));
    list<BroadLeaf*>::iterator I;
    for(I = leaf_list.begin(); I != leaf_list.end(); I++)
      value += GetValue(**I, Qabs);
    
    return value;
  }
  else
    return GetValue(dynamic_cast<const TreeSegment<TS,BUD>&>(ts), name);

}


#endif

