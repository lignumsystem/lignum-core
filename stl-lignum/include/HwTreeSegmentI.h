
#ifndef HWTREESEGMENTI_H
#define HWTREESEGMENTI_H

namespace Lignum{

  /********************************************************************
   addLeaf replaces createLeaf.  Because the  shape of the leaf can be
   ellips,  triangle   or  even   polygon,  we  simply   transfer  the
   responsibility   to  the   modeller   to  create   the  leaf.   See
   CreateLeaves.h how to create ellips shape leaves.
   ********************************************************************/
  template <class TS, class BUD, class S>
    //The   bud  directions   are  collected   into  vetor   pd  using
    //AccumulateDown(tree,vector<PositionVector>(),AppendLeaves(),CreateLeaves())
    void HwTreeSegment<TS,BUD,S>::addLeaf(BroadLeaf<S>* leaf)
    {
      leaf_ls.push_back(leaf);
    }

  template<class TS, class BUD, class S>
    list<BroadLeaf<S>*>& GetLeafList(HwTreeSegment<TS,BUD,S>& ts)
    {
      return ts.leaf_ls;
    }

  template<class TS, class BUD,class S>
    void InsertLeaf(HwTreeSegment<TS,BUD,S>& ts, BroadLeaf<S>* l)
    {
      ts.leaf_ls.push_back(l);
    }

  template<class TS, class BUD, class S>
    void InitializeForRadiation(HwTreeSegment<TS,BUD,S>& ts)
    {
      Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*ts));
      Firmament& f = GetFirmament(tt);
      int nr =  f.numberOfRegions();
      vector<LGMdouble> one(nr, 1.0);
      list<BroadLeaf<S>*>& ll = 
	GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
      for(typename list<BroadLeaf<S>*>::iterator i = ll.begin();
	  i != ll.end(); i++) {
	SetValue(*i, LGAQabs, 0.0);
	SetValue(*i, LGAQin, 0.0);
	SetRadiationVector(*i, one);
      }

    }


  template<class TS, class BUD, class S>
    int GetNumberOfLeaves(const HwTreeSegment<TS,BUD,S>& ts)
    {
      std::list<BroadLeaf<S>*>& leaf_list = 
	GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
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
  template<class TS, class BUD, class S>
    LGMdouble SetLeafArea(HwTreeSegment<TS,BUD,S>& ts, const LGMdouble value)
    {
      int no_leaves = GetNumberOfLeaves(ts);
      if(no_leaves == 0)
	return 0.0;

      LGMdouble old_area = 0.0;
      std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(ts);
      typename std::list<BroadLeaf<S>*>::iterator I;
      LGMdouble LA = value / (double)no_leaves;
      for(I = leaf_list.begin(); I != leaf_list.end(); I++){
	old_area += GetValue(**I, A);   //BroadLeaf returns true area of the leaf
	SetValue(**I, LGAA, LA);
      }
      return old_area;
    }



  template<class TS, class BUD, class S>
    LGMdouble SetValue(HwTreeSegment<TS,BUD,S>& ts, const LGMAD name,  
		       const LGMdouble value)
    {
      return SetValue(dynamic_cast<TreeSegment<TS,BUD>&>(ts), name, value);
    }

  template<class TS, class BUD, class S>
    LGMdouble GetValue(const HwTreeSegment<TS,BUD,S>& ts, const LGMAD name)
    {

      LGMdouble value = 0.0;

      if (name == LGAWf){
	std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
	typename std::list<BroadLeaf<S>*>::iterator I;
	for(I = leaf_list.begin(); I != leaf_list.end(); I++)
	  value += GetValue(**I, LGAWf);
	return value;
      }
      else if (name == LGAP){
	std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
	typename std::list<BroadLeaf<S>*>::iterator I;
	for(I = leaf_list.begin(); I != leaf_list.end(); I++)
	  value += GetValue(**I, LGAP);
	return value;
	}
      else if (name == LGAQin){
	std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
	typename std::list<BroadLeaf<S>*>::iterator I;
	for(I = leaf_list.begin(); I != leaf_list.end(); I++)
	  value += GetValue(**I, LGAQin);
	return value;
      }
      else if (name == LGAQabs){
	std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
	typename std::list<BroadLeaf<S>*>::iterator I;
	for(I = leaf_list.begin(); I != leaf_list.end(); I++)
	  value += GetValue(**I, LGAQabs);
	return value;
      }
      else if(name == LGAAf){
	LGMdouble area = 0.0;
	std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
	typename std::list<BroadLeaf<S>*>::iterator I;
	for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
	    area += GetValue(**I,LGAA);   //BroadLeaf returns true area of the leaf
	}
	return area;
      }
      else
	return GetValue(dynamic_cast<const TreeSegment<TS,BUD>&>(ts), name);
    }


}//closing namespace Lignum
#endif
