#ifndef VOXELBOXI_H
#define VOXELBOXI_H




#include <Tree.h>
#include <VoxelSpace.h>

namespace Lignum {


template <class TS,class BUD>
void dumpSegment(VoxelBox &b, const HwTreeSegment<TS,BUD>& ts, int num_parts)
{

}
	


//
//	Dumps a conifer segment to the VoxelBox given as a parameter.
//	Updates also the star value 
//
template <class TS,class BUD>
void dumpSegment(VoxelBox &b, const CfTreeSegment<TS,BUD>& ts, int num_parts)
{	
	LGMdouble r_f = GetValue(ts, Rf);
	LGMdouble lenght = GetValue(ts, L) / num_parts;
	LGMdouble S_f = GetValue(ts, sf);
	LGMdouble fmass = GetValue(ts, Wf) / num_parts;

	if (GetValue(ts, sf) == 0)
		S_f = 28;

	LGMdouble farea = S_f * fmass;	
	b.addNeedleArea(farea);
	b.addNeedleMass(fmass);

	
	
	LGMdouble needle_rad = GetValue(ts, Rf);

	
	//Tarkistettu että for-looppi ajetaan tasan 8 kertaa (mika).
	for (double phi=0; phi<PI_VALUE/2.0; phi+=PI_VALUE/16)
	{		
		b.starSum += b.S(phi, S_f, fmass, needle_rad, lenght)/8.0;
	}

	b.number_of_segments++;
	b.needleMass += fmass;
}



//
//	Calculates the Qabs value to the CfTreeSegment
//
template <class TS,class BUD>
void setSegmentQabs(VoxelBox &b, CfTreeSegment<TS,BUD>& ts, int num_parts)
{
	//LGMdouble r_f = GetValue(ts, Rf);
	//LGMdouble lenght = GetValue(ts, L);
	
	LGMdouble S_f = GetValue(ts, sf);
	if (S_f == 0)
		S_f = 28;
	LGMdouble farea = S_f * GetValue(ts, Wf) / num_parts;
	LGMdouble qabs = 0.0;

	if (farea>0 && b.needleArea>0 && b.star>0)
	{
		qabs = b.Q_abs * (farea / b.needleArea);
		//qabs = b.interceptedRadiation * (farea / b.needleArea);
		//qabs = b.Q_abs * (farea/b.needleArea) * (b.star*b.needleArea) / (b.star*b.needleArea+b.k_b*b.leafArea);
	}
	LGMdouble lqabs = GetValue(ts, Qabs);
	SetValue(ts, Qabs, qabs+lqabs);

	LGMdouble lqin = GetValue(ts, Qin);
	SetValue(ts, Qin, b.Q_in/num_parts+lqin);  
}





} //namespace Lignum


#endif