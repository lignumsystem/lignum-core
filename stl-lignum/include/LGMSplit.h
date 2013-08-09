#ifndef LGMSPLIT_H
#define LGMSPLIT_H

#include <fstream>
#include <Lignum.h>
#include <LGMGeometry.h>
#include <VoxelSpace.h>
#include <FindForestBoundingBox.h>
#include <XMLTree.h>

// Functor to divide the segments in a tree into smaller segments.  Makes cuts
// at the interval l, starting at the base of a segment and continuing until
// the end segment's length is <= l + l_min.  The presence of l_min ensures
// that no segments of extremely short length will be created, which can cause
// runtime errors.  If splitting does cause a runtime error, you can try
// providing an increased value of l_min as a second argument to the functor.
// call with ForEach to split all segments in a tree:
//	treels = ReadTrees(treels,directory,file_name);
//	for (unsigned int i=0; i < treels.size(); i++) {
//		HBTree *myt = treels[i];
//		ForEach(*myt, LGMSplit<HBSegment,HBBud>(0.1));
//	}
template <class TS, class BUD>
class LGMSplit {
	METER l;     // distance between cuts
	METER l_min; // minimum segment length. defaults to 0.1mm
public:
	LGMSplit(METER len) : l(len), l_min(0.0001) { }
	LGMSplit(METER len, METER min) : l(len), l_min(min) { }
	void operator ()(TreeCompartment<TS,BUD>* tc)const;
};

#include "LGMSplitI.h"

#endif
