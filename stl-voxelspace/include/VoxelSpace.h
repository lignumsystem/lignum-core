#ifndef VOXELSPACE_H
#define VOXELSPACE_H


#include <vector>
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
    public:
      LGMdouble Xbox, Ybox, Zbox;
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
      int GetNumBoxes() { return Xn*Yn*Zn; }
      int getNumTreeSegments();
      LGMdouble getQabs();
      LGMdouble getQin();


      VoxelBox& getVoxelBox(Point p);
      LGMdouble calculateLight();

      std::vector<VoxelMovement>& getRoute(std::vector<VoxelMovement> &vec, int startx, int starty, int startz, PositionVector dir);

      void fillVoxelBoxes(LGMdouble inivalue);
      void fillVoxelBoxes(LGMdouble inivalue, int beginZ, int endZ);
      //First four arguments are for box.S() STAR sum
      void fillVoxelBoxesWithNeedles(LGMdouble Sf, LGMdouble Wf, LGMdouble Rf, LGMdouble L, 
				     int beginZ, int endZ);
      
      void AddScotspine(Tree<ScotsPineVisual, ScotsBud> &tree);

      template <class TS,class BUD>
	friend void dumpCfTreeSegment(VoxelSpace &s, CfTreeSegment<TS, BUD> &ts);

      template <class TS,class BUD>
	friend void dumpCfTree(VoxelSpace &s, Tree<TS, BUD> &ts);

      template <class TS,class BUD>
	friend void setCfTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree);
	
      BoundingBox& searchDimensions(BoundingBox &bbox, bool boolDimensionsWithNumBoxes);

      void searchDimensions(bool boolDimensionsWithNumBoxes=true) { searchDimensions(bbox, boolDimensionsWithNumBoxes); };
      
      void updateStar();
      void resetQinQabs();
      void dumpTrees();

      void setLightValues();

      void setLight();

      void draw();
      void draw(bool blackBG);
      //Funktio palauttaa globaalissa koordinaatistossa olevan pisteen
      //VoxelSpacen koordinaatistossa
      Point getLocalPoint(Point p);
      //Write voxel  boxes to file. If  'all' is true  write all boxes
      //else write only  boxes with foliage. By default  'all' is true
      //(old behaviour).
      void writeVoxBoxesToFile(const string& filename, bool all = true);
      //Write voxel  boxes to file up to Z index
      void writeVoxBoxesToFile(const string& filename, int z);
      void writeVoxBoxesToFile2(ofstream &file);

      int getNumVoxBoxes();
      int Xn, Yn, Zn;
    private:

      vector<Tree<ScotsPineVisual,ScotsBud> *> vecScotspines;

      TMatrix3D<VoxelBox> voxboxes;
      BoundingBox bbox;

      Point corner1;  //origo
      Point corner2;
	
      LGMdouble Xspan, Yspan, Zspan;
	
      int getXindex(LGMdouble xcoord);
      int getYindex(LGMdouble ycoord);
      int getZindex(LGMdouble zcoord);

      Firmament* sky;

	
    public:

      // returns the total foliage mass of the tree segments dumped into the VoxelSpace
      LGMdouble getFoliageMass(void);
	
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





} // namespace Lignum

#include "VoxelSpaceI.h"

#endif


