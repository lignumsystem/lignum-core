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
      LGMdouble lenght = GetValue(ts, LGAL) / num_parts;
      LGMdouble S_f = GetValue(GetTree(ts), sf);
      LGMdouble fmass = GetValue(ts, LGAWf) / num_parts;

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


   //dumpSegment for poplar
   template <class TS,class BUD, class S>
    void dumpSegment(VoxelBox &b, HwTreeSegment<TS, BUD, S> &ts, int num_parts)
    {	
      LGMdouble r_f = GetValue(ts, Rf);
      LGMdouble lenghth = GetValue(ts, LGAL) / num_parts;
      LGMdouble S_f = GetValue(GetTree(ts), sf);
      LGMdouble fmass = GetValue(ts, LGAWf) / num_parts;

      if (GetValue(GetTree(ts), sf) == 0)
	S_f = 28;

      LGMdouble farea = S_f * fmass;	
      b.addNeedleArea(farea);
      b.addNeedleMass(fmass);

      // LGMdouble needle_rad = GetValue(ts, Rf); //get Rf= 0 for HwTree?
     LGMdouble needle_rad = GetValue(ts, R);
     //  cout<<S_f<<" "<<fmass<<" "<<needle_rad<<" Radius "<<lenghth<<"test>>>>>>>>>>>>>>>>>>"<<endl;
      //Tarkistettu että for-looppi ajetaan tasan 8 kertaa (mika).
      for (double phi=0; phi<PI_VALUE/2.0; phi+=PI_VALUE/16)
	{		
	  //  b.starSum += b.S(phi, S_f, fmass, needle_rad, lenght)/8.0;
	    b.addStarSum(b.S(phi, S_f, fmass, needle_rad, lenghth)/8.0);
	      
       	}
    
      //  cout<<b.getNumSegments()<<"   numofsegment______"<<endl;
       b.increaseNumberOfSegments();
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
      LGMdouble farea = S_f * GetValue(ts, LGAWf) / num_parts;
      LGMdouble qabs = 0.0;

      //Qabs computetd based on Qin, mean star and foliage area.
      qabs = b.getQin()*0.14*(GetValue(GetTree(ts), sf)*GetValue(ts, LGAWf));

      SetValue(ts, Qabs, GetValue(ts, Qabs)+qabs);

      SetValue(ts, Qin, GetValue(ts, Qin)+b.getQin()/num_parts);

     /*  cout <<  "Segment Z: " << GetPoint(ts).getZ() << " Box: "  */
/* 	   <<  b.corner1.getX() << " " <<  b.corner1.getY() << " " << b.corner1.getZ()  */
/* 	   << " Qin: " << b.getQin() << endl;  */
    }



} //namespace Lignum


#endif




