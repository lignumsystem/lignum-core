
#ifndef OPENGLUNIXI_H
#define OPENGLUNIXI_H

#include "OpenGL.h"
#include "OpenGLinterface.h"
#include "OpenGLSymbols.h"

int Visual(int argc, char** argv)
{ 
  

  init_window (argc, argv);    
  //initTextures(); 
 
  TreeHeight<ScotsPineVisual, ScotsBud> th3;
  MakeTreeList(*betula, rad_limit);
  ForEach(*betula, th1);
  
  
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
