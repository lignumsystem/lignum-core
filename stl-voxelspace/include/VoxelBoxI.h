#ifndef VOXELBOXI_H
#define VOXELBOXI_H




#include <Tree.h>
#include <VoxelSpace.h>

namespace Lignum {


template <class TS,class BUD>
void dumpSegment(VoxelBox &b, const HwTreeSegment<TS,BUD>& ts)
{

}
	


//
//	Dumps a conifer segment to the VoxelBox given as a parameter.
//	Updates also the star value 
//
template <class TS,class BUD>
void dumpSegment(VoxelBox &b, const CfTreeSegment<TS,BUD>& ts)
{	
	LGMdouble r_f = GetValue(ts, Rf);
	LGMdouble lenght = GetValue(ts, L);
	LGMdouble farea = lenght * r_f * 2 * PI_VALUE;
	b.addNeedleArea(farea);

	LGMdouble s_f = GetValue(ts, sf);
	LGMdouble fmass = GetValue(ts, Wf);
	LGMdouble needle_rad = GetValue(ts, Rf);

	for (double phi=0; phi<PI_VALUE/2.0; phi+=PI_VALUE/16)
	{		
		b.star += b.S(phi, s_f, fmass, needle_rad, lenght)/8.0;
	}
}



//
//	Calculates the Qabs value to the CfTreeSegment
//
template <class TS,class BUD>
void setSegmentQabs(VoxelBox &b, CfTreeSegment<TS,BUD>& ts)
{
	LGMdouble r_f = GetValue(ts, Rf);
	LGMdouble lenght = GetValue(ts, L);
	LGMdouble farea = lenght * r_f * 2 * PI_VALUE;

	LGMdouble qabs = b.Q_abs * (farea/b.needleArea) * (b.star*b.needleArea) / (b.star*b.needleArea+b.k_b*b.leafArea);

	//SetValue(ts, Qabs, qabs);
}





} //namespace Lignum


#endif
