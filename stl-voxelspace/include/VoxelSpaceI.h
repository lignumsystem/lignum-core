#ifndef VOXELSPACEI_H
#define VOXELSPACEI_H




#include <Tree.h>


namespace Lignum {


template <class TS, class BUD>
TreeCompartment<TS,BUD>* DumpCfTreeFunctor<TS,BUD>::operator ()(TreeCompartment<TS,BUD>* tc)const
{
	if (CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(tc))
	{
		dumpCfTreeSegment(*space, *cfts);
	}
	return tc;
}




template <class TS,class BUD>
void setCfTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree)
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
		LGMdouble fmass = GetValue(*cfts, Wf);

		if (fmass > 0)
		{
			SetValue(*cfts, Qabs, 0.0);
			SetValue(*cfts, Qin, 0.0);


			Point p = GetPoint(*cfts);
			PositionVector pv = GetDirection(*cfts);
			LGMdouble length = GetValue(*cfts, L);
			int num_parts = 1;

			for (float i=0; i<num_parts; i++)
			{
				Point p1 = p + length * (i/num_parts) * pv;
				VoxelBox box = space->getVoxelBox(p1);
				setSegmentQabs(box, *cfts, num_parts);
			}		
		}
	}
	return tc;
}



template <class TS,class BUD>
void dumpCfTree(VoxelSpace &s, Tree<TS, BUD> &tree)
{
	
	DumpCfTreeFunctor<TS,BUD> f;
	f.space = &s;
	ForEach(tree, f);
	
}






template <class TS,class BUD>
void dumpCfTreeSegment(VoxelSpace &s, CfTreeSegment<TS, BUD> &ts)
{
	Point p = GetPoint(ts);
	PositionVector pv = GetDirection(ts);
	LGMdouble length = GetValue(ts, L);
	int num_parts = 1;

	for (float i=0; i<num_parts; i++)
	{
		Point p1 = p + length * (i/num_parts) * pv;
		dumpSegment(s.getVoxelBox(p1), ts, num_parts);
	}
	
}


}

#endif

