#ifndef VOXELSPACEI_H
#define VOXELSPACEI_H

namespace Lignum {
    inline 
    LGMdouble GetValue(const VoxelSpace& s,VAD LGAkb){
      return s.k_b;
    }
  //First CfTree & CfTreeSegment==========================

  template <class TS,class BUD>
    void DumpCfTree(VoxelSpace &s, Tree<TS, BUD> &tree,int num_parts)
    {
      DumpCfTreeFunctor<TS,BUD> f(num_parts);
      f.space = &s;
      ForEach(tree, f);
    }

  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* DumpCfTreeFunctor<TS,BUD>::
    operator ()(TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* cfts = dynamic_cast<TS*>(tc))
	{
	  DumpCfTreeSegment(*space,*cfts,num_parts);
	} 
      return tc;
    }

  template <class TS,class BUD>
  void DumpCfTreeSegment(VoxelSpace &s, CfTreeSegment<TS, BUD> &ts,double num_parts)
  {
    Point p = GetPoint(ts);
    PositionVector pv = GetDirection(ts);
    LGMdouble length = GetValue(ts, LGAL);

    for (int i=1; i<(num_parts+1.0); i++)
      {
	Point p1 = p + (Point)(length * (i/(num_parts+1.0)) * pv);
	DumpSegment(s.getVoxelBox(p1), ts, num_parts);
      }
  }
  
  template <class TS,class BUD>
    void SetCfTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree, int num_parts)
    {
      SetCfTreeQabsFunctor<TS,BUD> f(num_parts);
      f.space = &s;
      ForEach(tree, f);
    }


  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* SetCfTreeQabsFunctor<TS,BUD>::
    operator ()(TreeCompartment<TS,BUD>* tc)const
    {
      if (CfTreeSegment<TS,BUD>* cfts = 
	  dynamic_cast<CfTreeSegment<TS,BUD>*>(tc))
	{
	  LGMdouble fmass = GetValue(*cfts, LGAWf);
	  //Reset Qabs Qin  here
	  SetValue(*cfts, LGAQabs, 0.0);
	  SetValue(*cfts, LGAQin, 0.0);
	  if (fmass > R_EPSILON)
	    {
	      Point p = GetPoint(*cfts);
	      PositionVector pv = GetDirection(*cfts);
	      LGMdouble length = GetValue(*cfts, LGAL);
	      //if the user wants 1 part (whole segment), the loop is executed
	      //once  and the midpoint  of the  segment is  used; if  the user
	      //wants 2 parts,  the loop is executed twice  and the points 1/3
	      //and 2/3 of the segment length are used, and so on
	      for (int i=1; i<(num_parts+1.0); i++)
		{
		  Point p1 = p + (Point)(length * (i/(num_parts+1.0)) * pv);
		  VoxelBox box = space->getVoxelBox(p1);
		  SetSegmentQabs(box, *cfts, num_parts);
		}		
	    }
	}
      return tc;    
    }

  //Insert Segment to  boxes it belongs to based on  base, mid and end
  //points
  template <class TS>
  void InsertSegment(VoxelSpace& s, const TS& ts)
  {
    Point p1 = GetPoint(ts);
    Point p2 = GetPoint(ts,0.5);
    Point p3 = GetPoint(ts,1.0);
    int x1=s.getXindex(p1.getX());
    int y1=s.getYindex(p1.getY());
    int z1=s.getZindex(p1.getZ());

    int x2=s.getXindex(p2.getX());
    int y2=s.getYindex(p2.getY());
    int z2=s.getZindex(p2.getZ());

    int x3=s.getXindex(p3.getX());
    int y3=s.getYindex(p3.getY());
    int z3=s.getZindex(p3.getZ());
    //start from the base
    InsertSegment(s.voxboxes[x1][y1][z1],ts);
     //check that the box has changed
    if (x1!=x2 || y1!=y2 || z1!=z2){
       InsertSegment(s.voxboxes[x2][y2][z2],ts);
    }
    //check again that the box has changed
    if (x2!=x3 || y2!=y3 || z2!=z3){
       InsertSegment(s.voxboxes[x3][y3][z3],ts);
    }
    s.sgmntfol = s.sgmntfol + 1;
  }
  //Then HwTree & HwTreeSegment ==========================

  template <class TS,class BUD>
    void DumpHwTree(VoxelSpace &s, Tree<TS, BUD> &tree)
  {
      DumpHwTreeFunctor<TS,BUD> f;
      f.space = &s;
      ForEach(tree, f);
    }

  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* DumpHwTreeFunctor<TS,BUD>::
    operator ()(TreeCompartment<TS,BUD>* tc)const
    { 
      if (TS* hwts = dynamic_cast<TS*>(tc))
	{ 
	  DumpHwTreeSegment(*space, *hwts);
	} 
      return tc;
    }

  //Deciduous TreeSegments are dumped to VoxelBoxes differently than
  //coniferous TreeSegments: all leaves of the segment are considered
  //one by one.

   template <class TS,class BUD, class SH>
   void DumpHwTreeSegment(VoxelSpace &s, HwTreeSegment<TS, BUD, SH> &ts)
    {
      Point p;
      std::list<BroadLeaf<SH>*>& leaf_list = 
	GetLeafList(const_cast<HwTreeSegment<TS,BUD,SH>&>(ts));
      typename std::list<BroadLeaf<SH>*>::iterator I;
      for(I = leaf_list.begin(); I != leaf_list.end(); I++) {  
	p = GetCenterPoint(**I);
	DumpLeaf(s.getVoxelBox(p), **I);
      }
    }


  template <class TS, class BUD>
    void SetHwTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree)
    {
      SetHwTreeQabsFunctor<TS,BUD> f;
      f.space = &s;
      ForEach(tree, f);
    }

  //HwTreeSegment does not store Qin or Qabs, it is done by its
  //leaves. Hence, the leaves are gone through one by one and their
  //Qabs, Qin values are set. Since the angle between leaf normal
  //(impact angle) and incoming radiation is not known (radiation can
  //come anywhere fron the upper hemisphere), it is assumed that the
  //impact angle is random. Therefore cos(impact angle) = 0.5 in
  //calculation of absorbed radiation. The radiation coming to the
  //voxelbox (Qin) is recorded also as Qin for the leaf.

  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* SetHwTreeQabsFunctor<TS,BUD>::
    operator ()(TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* hwts =  dynamic_cast<TS*>(tc))
	{
	  SetHwTreeSegmentQabs(*space, *hwts);
	} 
      return tc;
    }


  template <class TS, class BUD, class SHAPE>
    void SetHwTreeSegmentQabs(VoxelSpace &space,
			      HwTreeSegment<TS,BUD,SHAPE>& ts)
    {
      Point p;
      LGMdouble la, bQin, lQabs;
      VoxelBox box;
      list<BroadLeaf<SHAPE>*>& leaf_list = GetLeafList(ts);
      typename list<BroadLeaf<SHAPE>*>::iterator I;
      for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
	p = GetCenterPoint(**I);
	box = space.getVoxelBox(p);
	bQin = box.getQin();
	la = GetValue(**I,  LGAA);
	lQabs = GetValue(space,LGAkb) * bQin * la;
	//	cout<<"Qin: "<<bQin<<" Qabs: "<<lQabs<<endl;
	SetValue(**I, LGAQabs, lQabs);
	SetValue(**I, LGAQin, bQin);
      }
    }

} //End of namespace Lignum

#endif
