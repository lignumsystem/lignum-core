#ifndef VOXELBOX_H
#define VOXELBOX_H

#include <fstream>
#include <Lignum.h>
#include <VoxelObject.h>
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
    friend void DumpCfSegmentFoliage(VoxelBox &b, const CfTreeSegment<TS,BUD>& ts, 
			    int num_parts );

    template <class TS,class BUD>
      friend void DumpSegmentWood(VoxelBox &b, const TreeSegment<TS,BUD>& ts,
				  int num_parts);
    template <class OBJ>
    friend void InsertVoxelObject(VoxelBox& b, OBJ* obj);

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
    bool isEmpty()const;
    const vector<VoxelObject*>& getObjects()const{return objects;}
    Point getCenterPoint()const;
    Point getCornerPoint()const;  //= lower left
    Point getUpperRightPoint()const;
    int getNumSegments()const{ return number_of_segments; }
    LGMdouble getNumSegmentsReal()const{ return number_of_segments_real; }
    int getNumLeaves()const{ return number_of_leaves; }
    LGMdouble getAreaDensity();
    LGMdouble getQabs()const{ return Q_abs; }
    LGMdouble getQin()const{ return Q_in; }
    LGMdouble getQabsMean()const{return Qabs_mean;}
    LGMdouble getQinMean()const{return Qin_mean;}
    LGMdouble getStarSum()const{ return starSum; }
    LGMdouble getStar()const{ return star; }
    LGMdouble getNeedleMass()const{return needleMass;}
    LGMdouble getNeedleArea()const{return needleArea;}
    LGMdouble getLeafMass()const{return leafMass;}
    LGMdouble getLeafArea()const{return leafArea;}
    LGMdouble getFoliageMass()const{return needleMass + leafMass;}
    LGMdouble getFoliageArea()const{return needleArea+leafArea;}
    LGMdouble getWoodMass() const{return woodMass; }
    LGMdouble getWoodArea() const{return woodArea; }
    PositionVector getBigLeafNormal(){return big_leaf_normal.normalize();}
    LGMdouble getWeight()const{return weight;}
    LGMdouble getQ_inStdDiff()const{ return Q_inStdDiffuse; }
    //Return the extinction of the objects in the box
    LGMdouble getExtinction(const Point& p1, const PositionVector& d, 
			    const ParametricCurve& K)const;
    PositionVector getMeanDirection()const {return mean_direction;}

    void setArea( M2 needleA, M2 leafA);
    void setVoxelSpace(VoxelSpace *s, Point c);
    void setQ_inStdDiff(LGMdouble val){Q_inStdDiffuse = val;}
    void addRadiation(LGMdouble r);
    void addNeedleArea(M2 narea) { needleArea += narea; }
    void subtractNeedleArea(M2 narea) { needleArea -= narea; }
    void addNeedleMass(M2 nmass) { needleMass += nmass; }
    void subtractNeedleMass(M2 nmass) { needleMass -= nmass; }
    void addLeafArea(M2 larea) { leafArea += larea; }
    void addLeafMass(LGMdouble lmass) {leafMass += lmass; }
    void addQabs(LGMdouble val) { Q_abs += val; }
    void addQin(LGMdouble val){Q_in += val;}
    void setQinMean(LGMdouble val){Qin_mean= val;}
    void setQabsMean(LGMdouble val){Qabs_mean= val;}
    void addInterceptedRadiation(LGMdouble rad) { interceptedRadiation += rad; }
    void addStarSum(LGMdouble starmean){starSum += starmean;}
    void subtractStarSum(LGMdouble starmean){starSum -= starmean;}
    void addWoodMass(LGMdouble mass) {woodMass += mass; }
    void addWoodArea(LGMdouble area) {woodArea += area; }
    void subtractWoodMass(LGMdouble mass) {woodMass -= mass; }
    void subtractWoodArea(LGMdouble area) {woodArea -= area; }
    void addWeight(LGMdouble w){weight += w;}
    void subtractWeight(LGMdouble w){weight -= w;}
    void increaseNumberOfSegments(){number_of_segments++;}
    void decreaseNumberOfSegments(){number_of_segments--;}
    void addNumberOfSegmentsReal(LGMdouble inc){number_of_segments_real += inc;}
    void addOneLeaf() {number_of_leaves++;}
    void addVector(PositionVector v) {mean_direction = PositionVector(mean_direction+v);}
    
    LGMdouble S(LGMdouble phi, LGMdouble sf, LGMdouble Wf,
		LGMdouble r, LGMdouble l);
    //reset  the  box to  0,  clear  the  vector of  photosynthesising
    //objects (not the objects though!!!)
    void reset();
     
    //Reset Qin, Qabs and  intercepedRadiation to 0, this is necessary
    //in  short time  steps, where  structural update  is  slower than
    //changing light environment.
    void resetQinQabs(){Q_in = 0.0; Q_abs = 0.0;interceptedRadiation = 0.0;
      Qin_mean = 0.0; Qabs_mean = 0.0;}
 
  protected:
    void resetCfData(){
      star = 0; starSum = 0.0; needleArea = 0.0;needleMass = 0.0;
      number_of_segments = 0; val_c = 0.0; weight = 0.0;
      number_of_segments_real = 0.0; mean_direction = PositionVector(0.0,0.0,0.0);
    }
    void resetHwData(){
      leafArea = 0.0;leafMass = 0.0;number_of_leaves = 0;
      val_b = 0.0; Q_inStdDiffuse = 0;
      big_leaf_normal = PositionVector(0,0,0);
    }
    LGMdouble SAc(LGMdouble phi, LGMdouble r, LGMdouble l);
    LGMdouble K(LGMdouble phi);

    M2 needleArea;
    M2 leafArea;
    LGMdouble Q_in;
    LGMdouble Q_abs;
    LGMdouble Qin_mean;
    LGMdouble Qabs_mean;
    LGMdouble star;
    LGMdouble starSum;
    LGMdouble weight; //weighted starSum, e.g. foliage area
    
    LGMdouble Q_inStdDiffuse;

    // Q_absbox
    LGMdouble interceptedRadiation;
    LGMdouble needleMass;
    LGMdouble leafMass;
    int number_of_segments;
    int number_of_leaves;
    PositionVector big_leaf_normal;//Weighted  sum  of  directions  of
				   //leaves in a box

  private:
    void init();	
    Point corner1;

    LGMdouble val_c; //val_c * l is coniferous extinction
    LGMdouble val_b; //val_b * l is broadleaf  extinction
    VoxelSpace *space;
    vector<VoxelObject*> objects;//vector     of     photosynthesising
				 //elements in the box

    LGMdouble woodMass;
    LGMdouble woodArea;         //surface area of segments (woody part) in box
    LGMdouble number_of_segments_real;   //this is the correct number of segments
                                    //considering consiering dumping of segs in
                                    // parts (num_parts)
 
    PositionVector mean_direction;
  };

} //namespace Lignum

#include <VoxelBoxI.h>

#endif

