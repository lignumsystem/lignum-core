
#ifndef OPENGLUNIXI_H
#define OPENGLUNIXI_H

#include <Tree.h>
#include "OpenGL.h"
#include "OpenGLinterface.h"
#include "OpenGLSymbols.h"


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glut.h>

using namespace Lignum;

namespace Lignum{
template <class TS,class BUD>
int VisualizeLGMTree(Tree<TS,BUD> &tree)
{ 
  // init_window();
  cout << "InitDrawing" << endl;
  InitDrawing();
  InitOpenGL();
      
  init_window();
  //setLight();
  //initTextures(); 
 
  //  TreeHeight<TS,BUD> th;

  cout << "rakennetaan puu.." << endl;
  MakeTreeList(tree, 0.05);
  //ForEach(tree, th);
  
  
  /*
  glNewList(LEAFLET, GL_COMPILE);
  make_leaflet();
  glEndList();
 
 
  glNewList(ONE_LEAVE, GL_COMPILE); 
  make_leave();
  glEndList();


  
  glNewList(ALL_LEAVES, GL_COMPILE);
  Axis<GCSegment, GCBud>& axis = GetAxis(gliricidia);
  FindLeaves(axis);
  glEndList();


  glNewList(STEM, GL_COMPILE);
  axis = GetAxis(gliricidia);
  TraverseAxis(axis, 1);
  glEndList();

  */

 
  glutMainLoop ();
  cout << "Exiting ...." << endl;
  return 0;
}

}//closing namespace Lignum

#endif
