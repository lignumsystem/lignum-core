#ifndef LGMVOXELVISUALIZATION_H
#define LGMVOXELVISUALIZATION_H


#include "OpenGLSymbols.h"
#include "OpenGLfunctions.h"
#include "OpenGLFunctor.h"
#include "OpenGL.h"

#include <VoxelSpace.h>

namespace Lignum
{

class LGMVoxelVisualization
{
  public:

  private:
  void DrawVoxelSpace(VoxelSpace &space, bool blackBG);
};

}

#endif
