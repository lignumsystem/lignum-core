#ifndef VOXELSPACEI_H
#define VOXELSPACEI_H


namespace Lignum {



  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* DumpPopTreeFunctor<TS,BUD>::operator ()(TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* popts = dynamic_cast<TS*>(tc))
	{
	  DumpPopTreeSegment(*space, *popts);
	} 
      return tc;
    }



  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* DumpCfTreeFunctor<TS,BUD>::operator ()(TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* cfts = dynamic_cast<TS*>(tc))
	{
	  DumpCfTreeSegment(*space, *cfts);
	} 
      return tc;
    }




  template <class TS,class BUD>
    void SetCfTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree)
    {
      SetQabsCfTreeFunctor<TS,BUD> f;
      f.space = &s;
      ForEach(tree, f);
    }


  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* SetQabsCfTreeFunctor<TS,BUD>::operator ()(TreeCompartment<TS,BUD>* tc)const
    {
      if (CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(tc))
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

  template <class TS,class BUD>
    void DumpPopTree(VoxelSpace &s, Tree<TS, BUD> &tree)
    {
      DumpPopTreeFunctor<TS,BUD> f;
      f.space = &s;
      ForEach(tree, f);
    }

  template <class TS,class BUD>
    void DumpCfTree(VoxelSpace &s, Tree<TS, BUD> &tree)
    {
	
      DumpCfTreeFunctor<TS,BUD> f;
      f.space = &s;
      ForEach(tree, f);
	
    }


   template <class TS,class BUD, class S>
   void DumpPopTreeSegment(VoxelSpace &s, HwTreeSegment<TS, BUD, S> &ts)
 
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
 
}
#endif




