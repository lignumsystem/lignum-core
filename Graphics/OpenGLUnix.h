#ifndef OPENGLUNIX_H
#define OPENGLUNIX_H

#include <Tree.h>
#include "OpenGLinterface.h"


void init_window (); //int argc, char** argv);

namespace Lignum{
  
  
  struct SmallCube
  {
    int x,y,z;
    float dist;
    float areaden;

    float x_coord;
    float y_coord;
    float z_coord;

    bool ready;
  };
  
  template <class TS,class BUD>
    int VisualizeLGMTreesWithVoxelSpace(vector<Tree<TS,BUD> *> trees, 
					vector<SmallCube> cubes);

  template <class TS,class BUD>
    int VisualizeLGMTree(Tree<TS,BUD> &tree);
  
  template <class TS, class BUD>
    void drawBud(Bud<TS,BUD> *bud, DRAW_TYPE mode);
  
}

#include <OpenGLUnixI.h>

#endif
