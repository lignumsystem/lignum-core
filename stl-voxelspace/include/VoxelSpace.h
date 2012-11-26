#ifndef VOXELSPACE_H
#define VOXELSPACE_H


#include <vector>
#include <utility>
#include <climits>
#include <Lignum.h>
#include <TMatrix3D.h>
#include <VoxelBox.h>
#include <VOBookKeeper.h>
#include <ForestDescriptor.h>
#include <Firmament.h>
#include <Nearby.h>
namespace Lignum {

  struct VoxelMovement
  {
    VoxelMovement():x(0),y(0),z(0),l(0.0),af(0.0),tau(0.0),
      STAR_mean(0.0),n_segs_real(0.0),mean_direction(PositionVector(0,0,1)),
      wood_area(0.0){}
    int x;//box indices
    int y;
    int z;
    LGMdouble l;//Path length in the box
    LGMdouble af;//Foliage area in the box
    LGMdouble tau;//the  extinction  caused  by  objects  in  the  box
		  //(pairwise comparison)
    LGMdouble STAR_mean;
    LGMdouble n_segs_real;
    PositionVector  mean_direction;
    LGMdouble wood_area; //Surface area of segments
                         //Area of those that do not have needles in conifers
  };

  //The value for 'kb'  (angle of incidence, c.f.star mean for coniferous)
  //for broadleaf
  enum VAD {LGAkb}; 

  //Exception thrown  (instead of assert) in getVoxelBox  if the point
  //is not in the VoxelSpace
  class OutOfVoxelSpaceException{
  public:
    OutOfVoxelSpaceException(const Point& p1, const Point p2)
      :box(p1),p(p2){}
    Point getPoint()const{return p;}
    Point getBox()const{return box;}
  private:
    Point box;//The voxel box indices where the segment would belong to 
    Point p;//The global point of the segment causing the excepetion
  };

  class VoxelSpace
  {
    //VoxelBox::update Value  accesses private data  members--> friend 
    //declaration needed due to lack of access methods/functions
    friend class VoxelBox;
    friend class InsertHwEllipse;

    template <class TS,class BUD>
    friend void DumpCfTree(VoxelSpace &s, Tree<TS, BUD> &tree,int num_parts);

    template <class TS,class BUD>
    friend void DumpCfTree(VoxelSpace &s, Tree<TS, BUD> &tree,int num_parts, bool wood);

    //Conifers
    template <class TS>
    friend void InsertCfVoxelObject(VoxelSpace& s, const TS& ts, 
				    const PositionVector& dir, 
				    double t,double beam_start,
				    int segment_parts);
    //Broadleaved trees with ellipse leaf model
    template <class TS, class BUD,class S>
    friend void InsertHwVoxelObject(VoxelSpace& s, HwTreeSegment<TS,BUD,S>& ts, 
				    const PositionVector& d, 
				    double t,int parts);

    template <class TS,class BUD>
    friend void SetCfTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree,int num_parts);
     
    template <class TS,class BUD>
    friend void DumpHwTree(VoxelSpace &s, Tree<TS, BUD> &ts);

    template <class TS, class BUD, class S>
    friend void DumpHwTreeSegment(VoxelSpace &s,
				  HwTreeSegment<TS, BUD, S> &ts);

    template <class TS,class BUD>
    friend void SetHwTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree);

    template <class TS, class BUD, class SHAPE>
    friend void SetHwTreeSegmentQabs(VoxelSpace &space,
		     HwTreeSegment<TS,BUD,SHAPE>& ts);

    friend LGMdouble GetValue(const VoxelSpace& s,VAD LGAkb);
    friend void PrintVoxelObjectLocations(const VoxelSpace& s,const 
					  string& fname);

    friend void PrintBoxCfData(const VoxelSpace& s,const 
			       string& fname, bool empty);

    
  public:

    VoxelSpace(); 
    VoxelSpace(Point corner1, Point corner2, 
	       int xn, int yn, int zn,
	       Firmament& f);
    //constructor defining  corner points,  voxel box size,  number of
    //boxes (size of the matrix), the sky.and the k_b for broad leaf
    VoxelSpace(Point corner1, Point corner2, 
	       double xsize, double ysize, double zsize,
	       int xn, int yn, int zn,
	       Firmament& f, LGMdouble k_b=0.50);
    
    void reset();
    void resetQinQabs();
    void resize(int nX, int nY, int nZ); //change number of VoxelBoxes
					 //in x, y, and
					 //z-directions. The extent
					 //of VoxelSpace does not
					 //change.Contents are lost.
    void resize(LGMdouble lX, LGMdouble lY,
		LGMdouble lZ);           //Change sizes of VoxelBoxes
					 //in x, y, and
					 //z-directions. The extent of
					 //VoxelSpace does not change
					 //(only by size of the
					 //VoxelBox). Contents are lost.

    void resize(LGMdouble lX, LGMdouble lY, LGMdouble lZ,int nX, int nY,
		int nZ );           //Change both number and size of
				    //VoxelBoxes. The extent of
				    //VoxelSpace changes. Contents are
				    //lost.

    void resize(const Point lower_left, const Point upper_right); 
                                    //Change physical dimensions of
                                    // voxelspace (i.e. extent, i.e. opposite corners)
				    // The number of VoxelBoxes may change
				    //Contents are lost (because TMatrix3D resize
                                    //destroys contents)

    void move(const Point corner1); //Move Voxelspace so that its
				    //lower left corner is set at
				    //corner1
    VOBookKeeper& getBookKeeper(){return book_keeper;}
    ForestDescriptor& getForestDescriptor(){return forest_descriptor;}
    double getArea()const{return (Xn*Xbox)*(Yn*Ybox);}
    Point getLowerLeftCorner()const{return corner1;}
    Point getUpperRightCorner()const{return corner2;}
    int getNumberOfBoxes()const{ return Xn*Yn*Zn; }
    int getNumberOfFilledBoxes()const;
    int getNumberOfTreeSegments()const;
    LGMdouble getBoxVolume()const{ return Xbox*Ybox*Zbox; }
    LGMdouble getXSideLength(){ return Xbox; }
    LGMdouble getYSideLength(){ return Ybox; }
    LGMdouble getZSideLength(){ return Zbox; }
    int getNoBoxX() {return Xn;}
    int getNoBoxY() {return Yn;}
    int getNoBoxZ() {return Zn;}
    LGMdouble getQabs()const;
    LGMdouble getQin()const;
    pair<double,double> getMinMaxNeedleMass()const;
    // returns the total foliage mass of the tree segments dumped into
    // the VoxelSpace
    LGMdouble getFoliageMass(void);
    VoxelBox& getVoxelBox(const Point& p);
    //Given a point 'p' in global coordinate system, return a point in
    //VoxelSpace coordinate system (=indexes)
    //returns the indexes in a vector: v[0] = Xindex, v[1] = Yindex, v[2] = Zindex
    vector<int> getBoxIndexes(const Point& p);
    //Returns indexes of boxes that are within distance dist from point p.
    //(May work even if p is outside VoxelSpace but be careful).
    //Within distance = if any point of box may be closer than dist.
    //Indexes in a vector: v[0] = Xindex, v[1] = Yindex, v[2] = Zindex
    //If permissive = true  returns the VoxelBoxes in the big box, that is
    // p +- dist along all coordinate axes. If permissive = false,
    //it is checked whether any corner of the VoxelBox
    //is within distance dist, and if not, box is not included. This
    //may discard some boxes in the corners of the "big" box but may fail
    //to notice that part of the ball with radius dist around p intersect the
    //VoxelBox.
    list<vector<int> > getBoxesAroundPoint(const Point& p, const double& dist,
					   const bool permissive = true);

    vector<VoxelMovement>& getRoute(vector<VoxelMovement> &vec, int startx, 
				    int starty, int startz, PositionVector dir)const;
    //The method  calculates the route through the  voxel space from
    //start point to the direction given. 
    //Input/Output: vec   the route, includes extincion in each voxel
    //Input:        p0  start point (global)
    //              dir direction, |dir| == 1 (!!!)
    //              K   extinction
    //              pairwise if true use the voxel objects in voxels to 
    //                       calculate extinction, if false calculate only the 
    //                       path lengths in voxels 
    vector<VoxelMovement>& getRoute(vector<VoxelMovement> &vec,
				    const Point& p0,
				    const PositionVector& dir, 
				    const ParametricCurve& K,
				    bool pairwise)const;
    //Return the extinction caused by the border stand
    //Input: p0   start point of the light beam
    //       dir  direction of the light beam, |dir| == 1 (!!!)
    double getBorderStandExtinction(const Point& p0, const PositionVector& dir)const;
    void updateBoxValues();  //Runs updateValues() of voxelboxes (whatever it does)
    LGMdouble calculateTurbidLight(bool self_shading = true);
    //diffuse is to calcluate the real diffuse from standard 1200, structureFlag is used to indicate if it is the first time light calculation after structure update
    LGMdouble calculatePoplarLight(LGMdouble diffuse, LGMdouble structureFlag);
    void setLightValues();
    void setLight();
 
    void fillVoxelBoxes(M2 needleA, M2 leafA);
    void fillVoxelBoxes(LGMdouble inivalue, int beginZ, int endZ);
    //First four arguments are for box.S() STAR sum
    void fillVoxelBoxesWithNeedles(LGMdouble Sf, LGMdouble Wf, LGMdouble Rf, 
				   LGMdouble L, int beginZ, int endZ);

    BoundingBox& searchDimensions(BoundingBox &bbox,
				  bool boolDimensionsWithNumBoxes);

    void searchDimensions(bool boolDimensionsWithNumBoxes=true){ 
      searchDimensions(bbox, boolDimensionsWithNumBoxes); 
    }
 
    void dumpTrees();
 
    //Write voxel  boxes to file. If  'all' is true  write all boxes
    //else write only  boxes with foliage. By default  'all' is true
    //(old behaviour).
    void writeVoxBoxesToFile(const string& filename, bool all = true);
    //Write voxel  boxes to file up to Z index
    void writeVoxBoxesToFile(const string& filename, int z);
    void writeVoxBoxesToFile2(const string& filename);
    void writeVoxelBoxesToGnuPlotFile(const string& filename, 
				      const string& sep=" ");
    void writeVoxelSpaceContents();
    void writeStarMean();
    void writeMeanDirection();

    double getMeanFoliageAreaDensity();     
    void calculateMeanQabsQin();
    LGMdouble getNeedleArea();      //Returns sum of needle area in voxelboxes
    LGMdouble getLeafArea();        //Returns sum of leaf area in voxelboxes
    LGMdouble getFoliageArea();     //Returns sum of needle + leaf area in voxelboxes

    void evaluateVerticalNeedleAreaDensity(LGMdouble& Hmax, LGMdouble& Hmin, int& n,
					   vector<pair<LGMdouble,LGMdouble> >& NAD);
    LGMdouble evaluateLacunarityNeedles();


    //==========================================================

    LGMdouble Xbox, Ybox, Zbox;
    int Xn, Yn, Zn;
    TMatrix3D<VoxelBox> voxboxes;
    //debug
    int sgmnt;//segments inserted (to compare with)
    int hitw;//wood hits;
    int hitfol;//foliage hits
    int nohit;//no hits
    int hitself; //Self comparison
  private:
  

    BoundingBox bbox;

    Point corner1;  //origo
    Point corner2;  //diagonallly opposite corner(??)
	
    int getXindex(LGMdouble xcoord)const;
    int getYindex(LGMdouble ycoord)const;
    int getZindex(LGMdouble zcoord)const;

    Firmament* sky;

    LGMdouble k_b; //impact angle of a broad  leaf (c.f. star mean for
		   //coniferous)
    VOBookKeeper book_keeper; //maintains   information  if   a  voxel
			      //object has been hit by a light beam
    ForestDescriptor forest_descriptor;//maintains         descripitive
				       //statistics and indices of the
				       //forest in the voxel space
  };


  template <class TS,class BUD>
  class DumpCfTreeFunctor
  {
  public:
    DumpCfTreeFunctor(int n, bool wood):num_parts(n), dumpWood(wood) {}
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;
    double num_parts;
    bool dumpWood;
  };

  template <class TS,class BUD>
  class SetCfTreeQabsFunctor
  {
  public:
    SetCfTreeQabsFunctor(int n):num_parts(n){}
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;
    double num_parts;
  };

  //For deciduous trees, that is, hardwoods
  template <class TS,class BUD>
  class DumpHwTreeFunctor
  {
  public:
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;
  };


  template <class TS,class BUD>
    class SetHwTreeQabsFunctor
    {
    public:
      TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
      mutable VoxelSpace *space;
    };
  
} // namespace Lignum

#endif
#include "VoxelSpaceI.h"
#include "VoxelSpaceRadiationI.h"
