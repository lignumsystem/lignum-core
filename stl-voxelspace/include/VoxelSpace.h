#ifndef VOXELSPACE_H
#define VOXELSPACE_H


#include <vector>
#include <utility>
#include <Lignum.h>
#include <TMatrix3D.h>
#include <VoxelBox.h>
#include <Firmament.h>

#include <ScotsBud.h>
#include <ScotsPineVisual.h>

  
namespace Lignum {

  struct VoxelMovement
  {
    int x;
    int y;
    int z;
    LGMdouble l;
  };


  class VoxelSpace
  {
    //VoxelBox::update Value  accesses private data  members--> friend
    //declaration needed due to lack of access methods/functions

    friend class VoxelBox;

    template <class TS,class BUD>
    friend void DumpCfTree(VoxelSpace &s, Tree<TS, BUD> &ts);

    template <class TS,class BUD>
    friend void DumpCfTreeSegment(VoxelSpace &s, CfTreeSegment<TS, BUD> &ts);

    template <class TS,class BUD>
    friend void SetCfTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree);
     
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


  public:

    VoxelSpace(); 
    VoxelSpace(Point corner1, Point corner2, 
	       int xn, int yn, int zn,
	       Firmament& f);
    //constructor defining corner points, voxel box size,
    //number of boxes (size of the matrix) and the sky.
    VoxelSpace(Point corner1, Point corner2, 
	       double xsize, double ysize, double zsize,
	       int xn, int yn, int zn,
	       Firmament& f);
    void reset();
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

    void move(const Point corner1); //Move Voxelspace so that its
				    //lower left corner is set at
				    //corner1

    int getNumberOfBoxes()const{ return Xn*Yn*Zn; }
    int getNumberOfFilledBoxes()const;
    int getNumberOfTreeSegments()const;
    LGMdouble getQabs()const;
    LGMdouble getQin()const;
    pair<double,double> getMinMaxNeedleMass()const;
    // returns the total foliage mass of the tree segments dumped into
    // the VoxelSpace
    LGMdouble getFoliageMass(void);
    VoxelBox& getVoxelBox(Point p);
    vector<VoxelMovement>& getRoute(vector<VoxelMovement> &vec, int startx, 
				    int starty, int startz, PositionVector dir)const;
    //Given a point 'p' in global coordinate system, return a point in
    //VoxelSpace coordinate system
    Point getLocalPoint(const Point& p)const;
    void updateStar();
    LGMdouble calculateTurbidLight();
    LGMdouble calculatePoplarLight();
    void setLightValues();
    void setLight();
 
    void fillVoxelBoxes(M2 needleA, M2 leafA);
    void fillVoxelBoxes(LGMdouble inivalue, int beginZ, int endZ);
    //First four arguments are for box.S() STAR sum
    void fillVoxelBoxesWithNeedles(LGMdouble Sf, LGMdouble Wf, LGMdouble Rf, 
				   LGMdouble L, int beginZ, int endZ);
    //Remove this, no concrete tree species here (Jari)
    void AddScotspine(Tree<ScotsPineVisual, ScotsBud> &tree);

    BoundingBox& searchDimensions(BoundingBox &bbox,
				  bool boolDimensionsWithNumBoxes);

    void searchDimensions(bool boolDimensionsWithNumBoxes=true){ 
      searchDimensions(bbox, boolDimensionsWithNumBoxes); 
    }
 
    void dumpTrees();
    //Move drawing (visualization) to Grapichs
    // void draw();
    //void draw(bool blackBG);
 
    //Write voxel  boxes to file. If  'all' is true  write all boxes
    //else write only  boxes with foliage. By default  'all' is true
    //(old behaviour).
    void writeVoxBoxesToFile(const string& filename, bool all = true);
    //Write voxel  boxes to file up to Z index
    void writeVoxBoxesToFile(const string& filename, int z);
    void writeVoxBoxesToFile2(const string& filename);
    void writeVoxelSpaceContents();
    LGMdouble Xbox, Ybox, Zbox;
    int Xn, Yn, Zn;
TMatrix3D<VoxelBox> voxboxes;
  private:
  
    vector<Tree<ScotsPineVisual,ScotsBud> *> vecScotspines;

    BoundingBox bbox;

    Point corner1;  //origo
    Point corner2;  //diagonallly opposite corner(??)
	
    int getXindex(LGMdouble xcoord);
    int getYindex(LGMdouble ycoord);
    int getZindex(LGMdouble zcoord);

    Firmament* sky;

  };


  template <class TS,class BUD>
  class DumpCfTreeFunctor
  {
  public:
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;
  };

  template <class TS,class BUD>
  class SetCfTreeQabsFunctor
  {
  public:
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;
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
  
/*   template <class TS, class BUD, class SHAPE> */
/*     class SetHwTreeSegmentQabs */
/*     { */
/*     public: */
/*       void operator ()(VoxelSpace &space, */
/* 		       HwTreeSegment<TS,BUD,SHAPE>* ts); */
/*     }; */
  
  
} // namespace Lignum

#include "VoxelSpaceI.h"

#endif


