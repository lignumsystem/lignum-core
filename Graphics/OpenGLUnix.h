#ifndef OPENGLUNIX_H
#define OPENGLUNIX_H

#include <Tree.h>
#include "OpenGLinterface.h"

void init_window (); //int argc, char** argv);

namespace Lignum{


  template <class TS,class BUD>
  int VisualizeLGMTree(Tree<TS,BUD> &tree);

  template <class TS, class BUD>
  void drawBud(Bud<TS,BUD> *bud, DRAW_TYPE mode);

}

#include <OpenGLUnixI.h>

#endif
