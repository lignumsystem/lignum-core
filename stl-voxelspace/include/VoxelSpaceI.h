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
		Point p = GetPoint(*cfts);
		p = space->getLocalPoint(p);

		VoxelBox box = space->getVoxelBox(p);
		
		setSegmentQabs(box, *cfts);
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
	
	dumpSegment(s.getVoxelBox(p), ts);
}


}

#endif

