
#ifndef HWTREESEGMENTI_H
#define HWTREESEGMENTI_H

namespace Lignum{

  /********************************************************************
   *createLeaves is intented to  be used with L-systems for broadleved*
   *trees. L-system  can easily define the  positions and orientations*
   *of segments and  buds, but leaves are a  bit more complicated. For*
   *LIGNUM we can assume that  the leaf petiole takes the direction of*
   *the bud. Leaf blade is an  ellipse but the orientation of the leaf*
   *normal  is must  be  defined. createLeaves  sets  the leaf  normal*
   *upward random.                                                    *
   ********************************************************************/
  template <class TS, class BUD, class S>
    //The   bud  directions   are  collected   into  vetor   pd  using
    //AccumulateDown(tree,vector<PositionVector>(),AppendLeaves(),CreateLeaves())
    void HwTreeSegment<TS,BUD,S>::createLeaves(vector<PositionVector>& pd,
					       METER pl, METER a, METER b)
    {
      Point origo(0,0,0);
      Point point = GetEndPoint(*this);
      PositionVector up(0,0,1);
      Ellipsis shape(a,b); //initial shape of a leaf
      static Uniform u; //uniform random number [0,1] for setting leaf
			//normals;  static makes it  common throughout
			//the  program and  not reinitialized  in each
			//call.
      int seed = 3267;
      for (int i = 0; i < pd.size(); i++){
	PositionVector pdir = pd[i];
	//Leaves are  created at the end  of the segment  where the buds
	//are, second argument is the intial length of the petiole
	Petiole petiole(point,point + pl*(Point)pdir);
	//Randomize  the leaf blade  normal by  rotating in  around axis
	//that lies in the horizontal plane defined by cross product of
	//petiole direction and up-vector
	PositionVector plane = Cross(pdir,up);
	//limit the rotation  of the leaf normal to  [-90,90] degrees so
	//that the leaf normal does not point downwards
	double ran = (-90.0 +180.0*u(seed))*2.0*PI_VALUE/360; //(radians)
	PositionVector leaf_normal(0,0,1);
	leaf_normal.rotate(origo,plane,ran);
	BroadLeaf<S>* leaf = new BroadLeaf<S>(shape,petiole,leaf_normal);
	leaf_ls.push_back(leaf);
      }
      //clear the vector; don't create leaves twice
      pd.clear();
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
      list<BroadLeaf<S>*>& ll = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
      for(list<BroadLeaf<S>*>::iterator i = ll.begin();
	  i != ll.end(); i++) {
	SetValue(*i, Qabs, 0.0);
	SetValue(*i, Qin, 0.0);
	SetRadiationVector(*i, one);
      }

    }


  template<class TS, class BUD, class S>
    int GetNumberOfLeaves(const HwTreeSegment<TS,BUD,S>& ts)
    {
      std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
      if(leaf_list.empty()) {
	return 0;
      }
      else
	return (int)leaf_list.size();

    }


  template<class TS, class BUD, class S>
    void DropLeaves(HwTreeSegment<TS,BUD,S>& ts)
    {
      std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
      leaf_list.clear();
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
      std::list<BroadLeaf<S>*>::iterator I;
      LGMdouble LA = value / (double)no_leaves;
      for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
	old_area += GetValue(**I, A);   //BroadLeaf returns true area of the leaf
	SetValue(**I, A, LA);
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

      if (name == Wf) {
	std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
	std::list<BroadLeaf<S>*>::iterator I;
	for(I = leaf_list.begin(); I != leaf_list.end(); I++)
	  value += GetValue(**I, Wf);
    
	return value;
      }
      else if (name == P) 
	{
	  std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
	  std::list<BroadLeaf<S>*>::iterator I;
	  for(I = leaf_list.begin(); I != leaf_list.end(); I++)
	    value += GetValue(**I, P);
    
	  return value;
	}
      else if (name == Qin) {
	std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
	std::list<BroadLeaf<S>*>::iterator I;
	for(I = leaf_list.begin(); I != leaf_list.end(); I++)
	  value += GetValue(**I, Qin);
    
	return value;
      }
      else if (name == Qabs) {
	std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&>(ts));
	std::list<BroadLeaf<S>*>::iterator I;
	for(I = leaf_list.begin(); I != leaf_list.end(); I++)
	  value += GetValue(**I, Qabs);
    
	return value;
      }
      else if(name == Af)
	{
	  LGMdouble area = 0.0;
	  std::list<BroadLeaf<S>*>& leaf_list =
	    GetLeafList(const_cast<HwTreeSegment<TS,BUD,S>&(ts));
	  std::list<BroadLeaf<S>*>::iterator I;
	  for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
	    area += GetValue(**I, A);   //BroadLeaf returns true area of the leaf
	  }

	  return area;
	}
      else
	return GetValue(dynamic_cast<const TreeSegment<TS,BUD>&>(ts), name);

    }


}//closing namespace Lignum
#endif
