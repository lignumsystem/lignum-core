#ifndef OPENGLUNIX_H
#define OPENGLUNIX_H
#include <OpenGLHFiles.h>
#include <Lignum.h>
#include "OpenGLinterface.h"



#include <VoxelSpace.h>

//#include <VoxelMatrix.h>


struct SmallCube
{
  float x_coord;
  float y_coord;
  float z_coord;
  float dist; 
  bool ready;
  float areaden;
  float edge;
     

};


void init_window (); //int argc, char** argv);

void InitGraphics();
void ForestNeedlesBegin();
void ForestStemsBegin();
void ForestEnd();

void UseBmpTexture(char *filename);
void UseTgaTexture(char *filename);

void StartVisualization();

void AddVoxelSpaceToVisualization(VoxelSpace *vs);

namespace Lignum{
  
  
  template <class TS,class BUD>
    int VisualizeLGMTreesWithVoxelSpace(vector<Tree<TS,BUD> *> trees, 
					vector<SmallCube> cubes);

  template <class TS,class BUD>
    int VisualizeLGMTree(Tree<TS,BUD> &tree);
  

  template <class TS,class BUD, class S>
    int VisualizeHwTree(Tree<TS,BUD> &tree);

  template <class TS,class BUD>
    int VisualizeCfTree(Tree<TS,BUD> &tree);

  template <class TS, class BUD>
    void drawBud(Bud<TS,BUD> *bud, DRAW_TYPE mode);

  
  template <class TS,class BUD>
    int VisualizeTreesAndVoxelSpace(vector<Tree<TS,BUD> *> trees, 
      VoxelSpace &vs);
 

  

  template <class TS,class BUD>
  void AddScotsPine(Tree<TS,BUD> &tree, int mode);

}

#include <OpenGLUnixI.h>

#endif


