
#ifndef OPENGLUNIXI_H
#define OPENGLUNIXI_H

#include <Lignum.h>
#include "OpenGL.h"
#include "OpenGLinterface.h"
#include "OpenGLSymbols.h"

#include "CTexture.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glut.h>

#include <vector>

using namespace Lignum;

extern vector<SmallCube> cubes;

extern CTexture cfstemtexture;
extern CTexture hwstemtexture;
extern CTexture stemtexture;

extern bool several_species;

namespace Lignum{

template <class TS,class BUD>
  int VisualizeLGMTreesWithVoxelSpace(vector<Tree<TS,BUD> *> trees, 
				      vector<SmallCube> c)
  {
    cubes = c;

    InitDrawing();
    InitOpenGL();
    init_window();

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    
    stemtexture.Load("Manty.bmp", 512, 512);
    
    
    cout << "tekstuurit ladattu..." << endl;

    
    int text_num = 0;
    glNewList(FOREST_LIST, GL_COMPILE);
    // glBindTexture(GL_TEXTURE_2D, text_num);
    
    for (int i=0; i<trees.size(); i++)
      {
	LGMdouble ini = 0.0;
	Tree<TS, BUD>* tree = trees[i];

	
	DrawStemFunctor<TS,BUD> stemfunctor;
        stemfunctor.min_rad = -99;
        stemfunctor.max_rad = 999;
        ForEach(*tree, stemfunctor);      
      }
    glEndList();
    
    cout << "puu esityslistat luotu " << endl;
   
    
    cam_z = 3;
    cam_x = 4;

    lookat_z = 5;

    glutMainLoop ();

    return 1;
  }


template <class TS,class BUD>
int VisualizeLGMTree(Tree<TS,BUD> &tree)
{ 
  // init_window();
  cout << "InitDrawing***********************" << endl;
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

    LoadGLTextures("neulaset5.tga");
  

  cout << "tekstuurit kaytossa******************************************** " << endl;

  //  TreeHeight<TS,BUD> th;

  cout << "rakennetaan puu.." << endl;
  
  MakeTreeList(tree, 0.05);
  MakeNeedlesList(tree);
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


 template <class TREE>
   int Initialize3DForest(Forest &f)
  {
    several_species = true;

    InitDrawing();
    InitOpenGL();
    
    init_window();
    //setLight();
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    //glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    
    //cfstemtexture.Load("Manty.bmp", 512, 512);
    hwstemtexture.Load("koivu.bmp", 512, 512);
    cfstemtexture.Load("Manty.bmp", 512, 512);

    LoadGLTextures("neulaset5.tga", "lehti.tga");
    MakeLeaveTable();
    
    
    list<VTree*>& ls1 =  GetCfTreeList(f);
    list<VTree*>::iterator b1 = ls1.begin();
    list<VTree*>::iterator e1 = ls1.end();
    
    if (glIsList(CFNEEDLES_LIST))
      glDeleteLists(CFNEEDLES_LIST,1);
    
    glNewList(CFNEEDLES_LIST, GL_COMPILE);
    while (b1 != e1)
      {
	//I can  check that the tree type  matches but how to  decide if a
	//tree is coniferous or hardwood, how to see what is behind TREE?
	if (TREE* t = dynamic_cast<TREE*>(*b1))
	  {
	    ForestNeedles(*t);
	  }
	b1++;
      }
    glEndList();

b1 = ls1.begin();
    if (glIsList(CFTREES_LIST))
      glDeleteLists(CFTREES_LIST,1);
    
    glNewList(CFTREES_LIST, GL_COMPILE);
    while (b1 != e1)
      {
	//I can  check that the tree type  matches but how to  decide if a
	//tree is coniferous or hardwood, how to see what is behind TREE?
	if (TREE* t = dynamic_cast<TREE*>(*b1))
	  {
	    cout << "HAVUPUUN RUNKO" << endl;
	    MakeForestTree(*t);
	  }
	b1++;
      }
    glEndList();

   
    
  }


 template <class TREE>
   int VisualizeForest(Forest &f)
   {
     
     list<VTree*>& ls2 =  GetHwTreeList(f);
     list<VTree*>::iterator b2 = ls2.begin();
     list<VTree*>::iterator e2 = ls2.end();
     
     if (glIsList(HWTREES_LIST))
       glDeleteLists(HWTREES_LIST,1);
     
     glNewList(HWTREES_LIST, GL_COMPILE);
     while (b2 != e2)
       {
	 //I can  check that the tree type  matches but how to  decide if a
	 //tree is coniferous or hardwood, how to see what is behind TREE?
	 if (TREE* t = dynamic_cast<TREE*>(*b2))
	   {
	     cout << "lehtipuu " << endl;
	     MakeForestTree(*t);
	   }
	 b2++;
       }
     glEndList();

     //LoadGLTextures("neulaset5.tga");
//  LoadGLTextures("neulaset5.tga", "lehti.tga");
//     MakeLeaveTable();

     b2 = ls2.begin();
     if (glIsList(HWLEAVES_LIST))
       glDeleteLists(HWLEAVES_LIST,1);

     glNewList(HWLEAVES_LIST, GL_COMPILE);
     while (b2 != e2)
       {
	 //I can  check that the tree type  matches but how to  decide if a
	 //tree is coniferous or hardwood, how to see what is behind TREE?
	 if (TREE* t = dynamic_cast<TREE*>(*b2))
	   {
	     cout << "LEHTIPUU" << endl;
	     ForestLeaves(*t,6,6);
	   }
	 b2++;
       }
     glEndList();

     glutMainLoop ();
     cout << "Exiting ...." << endl;
     return 0; 
   }




 template <class TS,class BUD, class S>
   int VisualizeHwTree(Tree<TS,BUD> &tree)
{ 
  // init_window();
  cout << "InitDrawing.........1.13" << endl;
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
 
  stemtexture.Load("koivu.bmp", 512, 512);

  LoadGLTextures("lehti.tga");  //**** HwLoadGLTextures
  


  cout << "ei lehtiä, rakennetaan puu.." << endl;

  MakeTreeList(tree, 0.05);

  
  cout << "rakennetaan lehdet " << endl;
  MakeLeaveList<TS,BUD,S>(tree, 2, 2);
 

  //elavat budit
  MakeBudList(tree, true);
  
 //kuolleet budit
  MakeBudList(tree, false);

 
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

  //cout << "budi paikka " << position << endl;

  rot_x = -1 * direction.getVector()[1];
  rot_y = direction.getVector()[0];
  rot_angle = (360.0 / (2*PI_VALUE)) * acos((double)direction.getVector()[2]);

  glPushMatrix();
  
  glTranslatef( position.getX(), position.getY(), position.getZ());
  
  if (rot_angle > 0.01)
    glRotatef( rot_angle, rot_x, rot_y, 0);
  
  make_bud(mode);
  glPopMatrix();

}


template <class TS,class BUD>
int VisualizeCfTree(Tree<TS,BUD> &tree)
{ 
  // init_window();
  cout << "InitDrawing.........1.13" << endl;
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
  LoadGLTextures("neulaset5.tga");  //**** CFLoadGLTextures
  


  cout << "rakennetaan puu.." << endl;
  
  MakeTreeList(tree, 0.05);
  MakeNeedlesList(tree);
  //elavat budit
  MakeBudList(tree, true);
 
  
 //kuolleet budit
  MakeBudList(tree, false);

 
  glutMainLoop ();
  cout << "Exiting ...." << endl;
  return 0;
}



}//closing namespace Lignum



#endif
