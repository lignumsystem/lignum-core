#ifndef VOXELBOX_H
#define VOXELBOX_H




#include <Tree.h>
#include <VoxelSpace.h>
#include <fstream>

using namespace cxxadt;



struct VisualCube
{
	LGMdouble x,y,z;
	float dist;
	float areaden;
	bool ready;
};


namespace Lignum {


class VoxelSpace;

class VoxelBox
{
public:
	VoxelBox(VoxelSpace *s); 
	VoxelBox();

	LGMdouble extinction(LGMdouble l);

	void UpdateValues();

	bool isEmpty();

	Point& getCenterPoint(Point &point);
	Point getCornerPoint();

	template <class TS,class BUD>
	friend void dumpSegment(VoxelBox &b, const HwTreeSegment<TS,BUD>& ts);
	
	template <class TS,class BUD>
	friend void dumpSegment(VoxelBox &b, const CfTreeSegment<TS,BUD>& ts);

	template <class TS,class BUD>
	friend void setSegmentQabs(VoxelBox &b, CfTreeSegment<TS,BUD>& ts);

	void setArea(M2 larea, M2 narea);
	void addRadiation(LGMdouble r);
	void setVoxelSpace(VoxelSpace *s, Point c);

	LGMdouble getAreaDen();
	void addNeedleArea(M2 narea) { needleArea += narea; }
	void addLeafArea(M2 larea) { leafArea += larea; }
	void addQabs(LGMdouble val) { Q_abs += val; }

	friend ostream &operator << (ostream& os, VoxelBox &b);

protected:
	LGMdouble star;
	LGMdouble SAc(LGMdouble phi, LGMdouble r, LGMdouble l);
	LGMdouble S(LGMdouble phi, LGMdouble Sf, LGMdouble Wf, LGMdouble r, LGMdouble l);
	LGMdouble K(LGMdouble phi);
	M2 leafArea;
	M2 needleArea;
	LGMdouble Q_in;
	LGMdouble Q_abs;
private:
	
	Point corner1;

	

	LGMdouble val_c;
	LGMdouble val_b;
	LGMdouble k_c;
	LGMdouble k_b;

	

	VoxelSpace *space;
};


} //namespace Lignum

#include <VoxelBoxI.h>

#endif

