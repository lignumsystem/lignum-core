#ifndef OPENGLUNIX_H
#define OPENGLUNIX_H

#include <Lignum.h>
#include "OpenGLinterface.h"
//#include <VoxelMatrix.h>

void init_window (); //int argc, char** argv);

namespace Lignum{
  template <class TREE>
    int Initialize3DForest(Forest &f);

  
  
  template <class TS,class BUD>
    int VisualizeLGMTreesWithVoxelSpace(vector<Tree<TS,BUD> *> trees, 
					vector<SmallCube> cubes);

  template <class TS,class BUD>
    int VisualizeLGMTree(Tree<TS,BUD> &tree);
  

  template <class TS,class BUD, class S>
    int VisualizeHwTree(Tree<TS,BUD> &tree);


  template <class TS, class BUD>
    void drawBud(Bud<TS,BUD> *bud, DRAW_TYPE mode);
  
}

#include <OpenGLUnixI.h>

#endif


