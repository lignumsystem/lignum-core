#ifndef OPENGLUNIX_H
#define OPENGLUNIX_H

#include <Tree.h>

void init_window (); //int argc, char** argv);

namespace Lignum{


  template <class TS,class BUD>
  int Visualize(Tree<TS,BUD> &tree);
}

#include <OpenGLUnixI.h>

#endif
