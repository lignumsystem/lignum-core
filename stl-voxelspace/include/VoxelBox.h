#ifndef VOXELBOX_H
#define VOXELBOX_H

#include <fstream>
#include <Lignum.h>
#include <VoxelSpace.h>

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
      friend void DumpSegment(VoxelBox &b, const CfTreeSegment<TS,BUD>& ts, 
			      int num_parts);
    template <class SH>
      friend void DumpLeaf(VoxelBox &b, const BroadLeaf<SH>& leaf);

    template <class TS,class BUD>
      friend void SetSegmentQabs(VoxelBox &b, CfTreeSegment<TS,BUD>& ts, 
				 double num_parts);
    friend ostream &operator << (ostream& os, VoxelBox &b);
  public:
    VoxelBox(VoxelSpace *s); 
    VoxelBox();
    //Recalculate star and val_c,  k_b and val_b
    //currently star and k_b hard-coded!!
    void updateValues();
    LGMdouble extinction(LGMdouble l)const;

    //reset the box to 0
    void reset(){resetQinQabs(); resetCfData();resetHwData();}

    bool isEmpty()const;

    Point getCenterPoint()const;
    Point getCornerPoint()const;
    int getNumSegments()const{ return number_of_segments; }
    int getNumLeaves()const{ return number_of_leaves; }
    LGMdouble getAreaDensity();
    LGMdouble getQabs()const{ return Q_abs; }
    LGMdouble getQin()const{ return Q_in; }
    LGMdouble getStarSum()const{ return starSum; }
    LGMdouble getStar()const{ return star; }
    LGMdouble getNeedleMass()const{return needleMass;}
    LGMdouble getNeedleArea()const{return needleArea;}
    LGMdouble getLeafMass()const{return leafMass;}
    LGMdouble getLeafArea()const{return leafArea;}
    LGMdouble getFoliageMass()const{return needleMass + leafMass;}
    LGMdouble getWeight()const{return weight;}

    void setArea( M2 needleA, M2 leafA);
    void setVoxelSpace(VoxelSpace *s, Point c);

    void addRadiation(LGMdouble r);
    void addNeedleArea(M2 narea) { needleArea += narea; }
    void addNeedleMass(M2 nmass) { needleMass += nmass; }
    void addLeafArea(M2 larea) { leafArea += larea; }
    void addLeafMass(LGMdouble lmass) {leafMass += lmass; }
    void addQabs(LGMdouble val) { Q_abs += val; }
    void addInterceptedRadiation(LGMdouble rad) { interceptedRadiation += rad; }
    void addStarSum(LGMdouble starmean){starSum += starmean;}
    void addWeight(LGMdouble w){weight += w;}
    void increaseNumberOfSegments(){number_of_segments++;}
    void addOneLeaf() {number_of_leaves++;}
    LGMdouble S(LGMdouble phi, LGMdouble sf, LGMdouble Wf,
		LGMdouble r, LGMdouble l);
  protected:
    void resetQinQabs(){Q_in = 0.0; Q_abs = 0.0;interceptedRadiation = 0.0;}
    void resetCfData(){
      star = 0; starSum = 0.0; needleArea = 0.0;needleMass = 0.0;
      number_of_segments = 0; val_c = 0.0; weight = 0.0;
    }
    void resetHwData(){
      leafArea = 0.0;leafMass = 0.0;number_of_leaves = 0;
      val_b = 0.0;
    }
    LGMdouble SAc(LGMdouble phi, LGMdouble r, LGMdouble l);
    LGMdouble K(LGMdouble phi);

    LGMdouble star;
    LGMdouble starSum;
    LGMdouble weight; //weighted starSum, e.g. foliage area
    M2 leafArea;
    M2 needleArea;
    LGMdouble Q_in;
    LGMdouble Q_abs;
    // Q_absbox
    LGMdouble interceptedRadiation;
    LGMdouble needleMass;
    LGMdouble leafMass;
    int number_of_segments;
    int number_of_leaves;
  private:
    void init();	
    Point corner1;

    LGMdouble val_c; //val_c * l is coniferous extinction
    LGMdouble val_b; //val_b * l is broadleaf  extinction
    VoxelSpace *space;
  };

} //namespace Lignum

#include <VoxelBoxI.h>

#endif

