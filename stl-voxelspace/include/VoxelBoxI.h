#ifndef VOXELBOXI_H
#define VOXELBOXI_H

namespace Lignum {


  //
  //	Dumps a conifer segment to the VoxelBox given as a parameter.
  //	Updates also the star value 
  //
  template <class TS,class BUD>
    void dumpSegment(VoxelBox &b, const CfTreeSegment<TS,BUD>& ts, int num_parts)
    {	
      LGMdouble r_f = GetValue(ts, Rf);
      LGMdouble lenght = GetValue(ts, L) / num_parts;
      LGMdouble S_f = GetValue(GetTree(ts), sf);
      LGMdouble fmass = GetValue(ts, Wf) / num_parts;

      if (GetValue(GetTree(ts), sf) == 0)
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
    }



  //
  //	Calculates the Qabs value to the CfTreeSegment
  //
  template <class TS,class BUD>
    void setSegmentQabs(VoxelBox &b, CfTreeSegment<TS,BUD>& ts, int num_parts)
    {
      //LGMdouble r_f = GetValue(ts, Rf);
      //LGMdouble lenght = GetValue(ts, L);
	
      LGMdouble S_f = GetValue(GetTree(ts), sf);
      LGMdouble farea = S_f * GetValue(ts, Wf) / num_parts;
      LGMdouble qabs = 0.0;

      //Qabs computetd based on Qin, mean star and foliage area.
      qabs = b.getQin()*0.14*(GetValue(GetTree(ts), sf)*GetValue(ts, Wf));

      SetValue(ts, Qabs, GetValue(ts, Qabs)+qabs);

      SetValue(ts, Qin, GetValue(ts, Qin)+b.getQin()/num_parts);  
    }







} //namespace Lignum


#endif




