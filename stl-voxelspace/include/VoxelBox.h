/// \file VoxelBox.h
/// \brief Voxel box in voxel space (needs clean-up)
/// \todo Needs clean-up 
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

namespace voxelspace {

class VoxelSpace;

 class VoxelBox
 {
   ///\brief Insert conifer tree segment foliage data into a VoxelBox.
   ///
   ///Updates the STAR sum and the \p weight based on foliage area for the weighted STAR.
   ///Updates number of segments in the VoxelBox. Updates the record of true number of segments
   ///in the VoxelBox based on \p num_parts. Note that this approximate the number of true segments
   ///when the segment is divided into \p num_parts imaginary segments.
   ///\tparam TS Tree segment
   ///\tparam BUD Bud
   ///\param b VoxelBox
   ///\param ts TreeSegment
   ///\param num_parts Number of parts tree segment is divided into
   ///\sa starSum
   ///\sa weight
   template <class TS,class BUD>
     friend void DumpCfSegmentFoliage(VoxelBox &b, const CfTreeSegment<TS,BUD>& ts,
				      int num_parts );
   ///\brief Insert conifer tree segment wooden part into a VoxelBox.
   ///
   ///Updates wood mass and the wooden cylinder surface area values (based on cxxadt::LGAR)
   ///in the VoxelBox.
   ///\tparam TS Tree segment
   ///\tparam BUD Bud
   ///\param b VoxelBox
   ///\param ts Tree segment
   ///\param num_parts Number of parts tree segment is divided into 
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
   ///\brief Update \f$ \mathit{STAR} \f$, \f$ \mathit{val}_c\f$ and \f$ \mathit{val}_b\f$
   ///
   ///Recalculate weighted \f$ \mathit{STAR} \f$:
   ///\f{math}{
   ///   \mathit{STAR}  = \left\{
   ///     \begin{array}{l}
   ///       \mathit{STARSUM}/w \quad w > 0\\
   ///       0 \quad w = 0
   ///     \end{array}
   ///   \right.
   ///\f}
   ///then \f$ \mathit{val}_c\f$ for conifers and \f$ \mathit{val}_b\f$ for broadleaved trees:
   ///\f{math}{
   ///  \begin{array}{l}
   ///   \mathit{val}_c = \mathit{STAR} \times (A_{\mathrm{needle}} / V_{\mathrm{voxel}})\\
   ///   \mathit{val}_b = k_b \times (A_{\mathrm{leaf}} / V_{\mathrm{voxel}})
   ///  \end{array}
   ///\f}
   ///\sa star 				       
   ///\sa val_c
   ///\sa val_b
   ///\sa voxelspace::LGAkb
   ///\sa DumpCfSegmentFoliage
   void updateValues();
   ///\brief Update directional \f$\mathbf{STARDIR}\f$ vector
   ///
   ///Recalculate weighted values in \f$\mathbf{STARDIR}\f$ vector:
   /// \f{math}{
   ///     \mathbf{STARDIR}_i = \left\{
   ///       \begin{array}{l}
   ///         \mathbf{STARDIRSUM}_i \times  1/w \quad  w > 0 \\
   ///         0 \quad  w = 0
   ///       \end{array}
   ///     \right.
   /// \f}
   ///\sa starDir
   ///\sa starDirSum
   ///\sa weight
   void updateValuesDirectionalStar();
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
   LGMdouble getStar()const{return star; }
   ///\brief STAR for conifers
   ///\retval val_c
   LGMdouble getStarConifer()const{return val_c;}
   ///\brief STAR for broadleaved
   ///\retval val_b
   LGMdouble getStarBroadLeaf()const{return val_b;}
   vector<LGMdouble> getDirStar() const{ return starDir;}
   vector<LGMdouble> getDirStarSum()const{  return starDirSum;}
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
   void addDirectionalStarSum(vector<LGMdouble> stardirmean){
     std::transform (starDirSum.begin(),starDirSum.end(),stardirmean.begin(),starDirSum.begin(),plus<LGMdouble>());
   }
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
   void setOccupied(const bool& set_value) {occupied = set_value;}
   bool getOccupied() {return occupied;}
   void setOccupiedTry(const bool& set_value) {occupied_try = set_value;}
   bool getOccupiedTry() {return occupied_try;}
    
   LGMdouble S(LGMdouble phi, LGMdouble sf, LGMdouble Wf,
	       LGMdouble r, LGMdouble l);
   //reset  the  box to  0,  clear  the  vector of  photosynthesising
   //objects (not the objects though!!!) vector<LGMdouble>starDirSum(7,0.0);vector<LGMdouble>starDir(7,0.0); // here i initialise the vectors with 8 of the values to zero.
   void reset();

   //Reset Qin, Qabs and  intercepedRadiation to 0, this is necessary
   //in  short time  steps, where  structural update  is  slower than
   //changing light environment.
   void resetQinQabs(){Q_in = 0.0; Q_abs = 0.0;interceptedRadiation = 0.0;
     Qin_mean = 0.0; Qabs_mean = 0.0;}

 protected:
   void resetCfData(){
     star = 0; starSum = 0.0; needleArea = 0.0;needleMass = 0.0;
     //        vector<LGMdouble>starDirSum(7,0.0);vector<LGMdouble>starDir(7,0.0); // here i initialise the vectors with 8 of the values to zero.
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
   vector<LGMdouble> starDirSum;    // Added for vector calculations
   vector<LGMdouble> starDir;        // Added as a simple Star vector
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

   bool occupied;      // if you need only to know present/not present
   bool occupied_try;  // present not present for iterative adjusting of segment length
   // in growth allocation 
 };

} //namespace Lignum

#include <VoxelBoxI.h>

#endif

