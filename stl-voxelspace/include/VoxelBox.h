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
	template <class TS,class BUD>
	friend void dumpSegment(VoxelBox &b, const HwTreeSegment<TS,BUD>& ts, int num_parts);
	
	template <class TS,class BUD>
	friend void dumpSegment(VoxelBox &b, const CfTreeSegment<TS,BUD>& ts, int num_parts);

	template <class TS,class BUD>
	friend void setSegmentQabs(VoxelBox &b, CfTreeSegment<TS,BUD>& ts, int num_parts);

public:
	VoxelBox(VoxelSpace *s); 
	VoxelBox();

	LGMdouble extinction(LGMdouble l);

	void UpdateValues();

	bool isEmpty();

	Point& getCenterPoint(Point &point);
	Point getCornerPoint();

	int getNumSegments() { return number_of_segments; }

	void setArea(M2 larea, M2 narea);
	void addRadiation(LGMdouble r);
	void setVoxelSpace(VoxelSpace *s, Point c);

	// Q_absbox
	LGMdouble interceptedRadiation;
	LGMdouble getAreaDen();
	void addNeedleArea(M2 narea) { needleArea += narea; }
	void addNeedleMass(M2 nmass) { needleMass += nmass; }
	void addLeafArea(M2 larea) { leafArea += larea; }
	void addQabs(LGMdouble val) { Q_abs += val; }
	void addInterceptedRadiation(LGMdouble rad) { interceptedRadiation += rad; }

	friend ostream &operator << (ostream& os, VoxelBox &b);
	LGMdouble getQabs() { return Q_abs; }
protected:
	LGMdouble star;
	LGMdouble starSum;
	LGMdouble SAc(LGMdouble phi, LGMdouble r, LGMdouble l);
	LGMdouble S(LGMdouble phi, LGMdouble Sf, LGMdouble Wf, LGMdouble r, LGMdouble l);
	LGMdouble K(LGMdouble phi);
	M2 leafArea;
	M2 needleArea;
	LGMdouble Q_in;
	LGMdouble Q_abs;

	LGMdouble needleMass;
	int number_of_segments;
private:
	void init();	
	Point corner1;

	

	LGMdouble val_c;
	LGMdouble val_b;
	LGMdouble k_c;
	LGMdouble k_b;

	

	VoxelSpace *space;
public:

	// returns the foliage mass of the voxel box
	LGMdouble getFoliageMass(void)
	{
		return needleMass;
	}
};


} //namespace Lignum

#include <VoxelBoxI.h>

#endif

