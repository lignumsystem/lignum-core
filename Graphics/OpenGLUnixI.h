
#ifndef OPENGLUNIXI_H
#define OPENGLUNIXI_H

#include <Tree.h>
#include "OpenGL.h"
#include "OpenGLinterface.h"
#include "OpenGLSymbols.h"

#include "CTexture.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glut.h>

using namespace Lignum;


CTexture stemtexture;

namespace Lignum{


template <class TS,class BUD>
int VisualizeLGMTree(Tree<TS,BUD> &tree)
{ 
  // init_window();
  cout << "InitDrawing******************************************************" << endl;
  InitDrawing();
  InitOpenGL();
      
  init_window();
  //setLight();
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
 
  stemtexture.Load("Manty.bmp", 512, 512);
  

  cout << "tekstuurit kaytossa******************************************** " << endl;

  //  TreeHeight<TS,BUD> th;

  cout << "rakennetaan puu.." << endl;

  MakeTreeList(tree, 0.05);
  //elavat budit
  MakeBudList(tree, true);
 
  
 //kuolleet budit
  MakeBudList(tree, false);
  
  
  
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





template <class TS, class BUD>
void drawBud(Bud<TS,BUD> *bud, DRAW_TYPE mode)
{
  float length;
  float radius;
  float rot_x, rot_y, rot_angle;

  Point position = GetPoint(*bud);;
  PositionVector direction = GetDirection(*bud);

  cout << "budi paikka " << position << endl;

  rot_x = -1 * direction.getVector()[1];
  rot_y = direction.getVector()[0];
  rot_angle = (360.0 / (2*PI_VALUE)) * acos((double)direction.getVector()[2]);

  glPushMatrix();
  
  glTranslatef( position.getX(), position.getY(), position.getZ());
  
  if (rot_angle > 0.01)
    glRotatef( rot_angle, rot_x, rot_y, 0);
  
  make_bud();
  glPopMatrix();

}




}//closing namespace Lignum



#endif
