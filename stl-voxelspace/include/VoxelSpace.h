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
    //declaration needed du to lack of access methods/functions
    friend class VoxelBox;
    template <class TS,class BUD>
    friend void DumpCfTreeSegment(VoxelSpace &s, CfTreeSegment<TS, BUD> &ts);

    template <class TS,class BUD>
    friend void DumpCfTree(VoxelSpace &s, Tree<TS, BUD> &ts);

    template <class TS,class BUD>
    friend void SetCfTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree);
    //define for  poplar (Fine, but we should  consider general names
    //for the "dumping" of hw segments, Jari)
    template <class TS,class BUD, class S>
    friend void DumpPopTreeSegment(VoxelSpace &s, HwTreeSegment<TS,BUD, S> &ts);
     
    template <class TS,class BUD>
    friend void DumpPopTree(VoxelSpace &s, Tree<TS, BUD> &ts);

    template <class TS,class BUD>
    friend void SetPopTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree);
    //define for poplar done

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
    LGMdouble calculateLight();
    LGMdouble calculatePopLight();
    void setLightValues();
    void setLight();
 
    void fillVoxelBoxes(LGMdouble inivalue);
    void fillVoxelBoxes(LGMdouble inivalue, int beginZ, int endZ);
    //First four arguments are for box.S() STAR sum
    void fillVoxelBoxesWithNeedles(LGMdouble Sf, LGMdouble Wf, LGMdouble Rf, 
				   LGMdouble L, int beginZ, int endZ);
    //Remove this, no concrete tree species here (Jari)
    void AddScotspine(Tree<ScotsPineVisual, ScotsBud> &tree);

    BoundingBox& searchDimensions(BoundingBox &bbox, bool boolDimensionsWithNumBoxes);

    void searchDimensions(bool boolDimensionsWithNumBoxes=true){ 
      searchDimensions(bbox, boolDimensionsWithNumBoxes); 
    }
 
    void dumpTrees();
    //Move drawing (visualization) to Grapichs
    void draw();
    void draw(bool blackBG);
 
    //Write voxel  boxes to file. If  'all' is true  write all boxes
    //else write only  boxes with foliage. By default  'all' is true
    //(old behaviour).
    void writeVoxBoxesToFile(const string& filename, bool all = true);
    //Write voxel  boxes to file up to Z index
    void writeVoxBoxesToFile(const string& filename, int z);
    void writeVoxBoxesToFile2(ofstream &file);
  private:
    LGMdouble Xbox, Ybox, Zbox;
    int Xn, Yn, Zn;
    vector<Tree<ScotsPineVisual,ScotsBud> *> vecScotspines;

    TMatrix3D<VoxelBox> voxboxes;
    BoundingBox bbox;

    Point corner1;  //origo
    Point corner2;  //diagonallly opposite corner(??)
	
    LGMdouble Xspan, Yspan, Zspan;
	
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
  class SetQabsCfTreeFunctor
  {
  public:
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;
  };

  //for poplar
  template <class TS,class BUD>
  class DumpPopTreeFunctor
  {
  public:
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;
  };


  template <class TS,class BUD>
  class SetQabsPopTreeFunctor
  {
  public:
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;
  };
  //for poplar done



} // namespace Lignum

#include "VoxelSpaceI.h"

#endif


