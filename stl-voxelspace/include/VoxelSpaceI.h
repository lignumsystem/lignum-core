#ifndef VOXELSPACEI_H
#define VOXELSPACEI_H


namespace Lignum {

  //First CfTree & CfTreeSegment==========================

  template <class TS,class BUD>
    void DumpCfTree(VoxelSpace &s, Tree<TS, BUD> &tree)
    {
      
      DumpCfTreeFunctor<TS,BUD> f;
      f.space = &s;
      ForEach(tree, f);
	
    }

  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* DumpCfTreeFunctor<TS,BUD>::
    operator ()(TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* cfts = dynamic_cast<TS*>(tc))
	{
	  DumpCfTreeSegment(*space, *cfts);
	} 
      return tc;
    }

  template <class TS,class BUD>
    void DumpCfTreeSegment(VoxelSpace &s, CfTreeSegment<TS, BUD> &ts)
    {
      Point p = GetPoint(ts);
      PositionVector pv = GetDirection(ts);
      LGMdouble length = GetValue(ts, LGAL);
      int num_parts = 1;

      for (float i=0; i<num_parts; i++)
	{
	  Point p1 = p + (Point)(length * (i/num_parts) * pv);
	  DumpSegment(s.getVoxelBox(p1), ts, num_parts);
	}
    }

  template <class TS,class BUD>
    void SetCfTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree)
    {
      SetCfTreeQabsFunctor<TS,BUD> f;
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
	  //Reset values here
	  SetValue(*cfts, LGAQabs, 0.0);
	  SetValue(*cfts, LGAQin, 0.0);
	  if (fmass > R_EPSILON)
	    {
	      Point p = GetPoint(*cfts);
	      PositionVector pv = GetDirection(*cfts);
	      LGMdouble length = GetValue(*cfts, LGAL);
	      int num_parts = 1;

	      for (float i=0; i<num_parts; i++)
		{
		  Point p1 = p + (Point)(length * (i/num_parts) * pv);
		  VoxelBox box = space->getVoxelBox(p1);
		  SetSegmentQabs(box, *cfts, num_parts);
		}		
	    }
	}
      return tc;
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


  template <class TS, class BUD, class SH>
    void SetHwTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree)
    {
      SetHwTreeQabsFunctor<TS,BUD,SH> f;
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

  template <class TS, class BUD, class SH>
    TreeCompartment<TS,BUD>* SetHwTreeQabsFunctor<TS,BUD,SH>::
    operator ()(TreeCompartment<TS,BUD>* tc)const
    {
      if (HwTreeSegment<TS,BUD,SH>* hwts =
	  dynamic_cast<HwTreeSegment<TS,BUD,SH>*>(tc))
	{
	  Point p;
	  LGMdouble la, bQin, lQabs;
	  VoxelBox box;
	  std::list<BroadLeaf<SH>*>& leaf_list = 
	    GetLeafList(const_cast<HwTreeSegment<TS,BUD,SH>&>(ts));
	  typename std::list<BroadLeaf<SH>*>::iterator I;
	  for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
	    p = GetCenterPoint(**I);
	    box = space->getVoxelBox(p);
	    bQin = box.getQin();
	    la = GetValue(**I,  LGAA);
	    lQabs = 0.5 * bQin * la;
	    SetValue(**I, LGAQabs, lQabs);
	    SetValue(**I, LGAQin, bQin);
	  }
	}
      return tc;
    }
}
#endif
