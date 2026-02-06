
#ifndef OPENGLUNIXI_H
#define OPENGLUNIXI_H

#include <Lignum.h>
#include "OpenGL.h"
#include "OpenGLinterface.h"
#include "OpenGLSymbols.h"

#include "CTexture.h"

#include <vector>

using namespace Lignum;

extern vector<SmallCube> cubes;

extern CTexture cfstemtexture;
extern CTexture hwstemtexture;
extern CTexture stemtexture;

extern bool several_species;

namespace voxelspace{

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

  LoadGLTextures(const_cast<char*>(string("neulaset5.tga").c_str()));
  

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





 template <class TS,class BUD, class S>
   int VisualizeHwTree(Tree<TS,BUD> &tree)
{ 
  init_window();
  
  // init_window();
  cout << "InitDrawing.........1.13" << endl;
  InitDrawing();
  InitOpenGL();
      

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
 
  stemtexture.Load("koivu.bmp", 512, 512);

  LoadGLTextures(const_cast<char*>(string("lehti.tga").c_str()));  //**** HwLoadGLTextures
  


  cout << "Ei lehtia, rakennetaan puu.." << endl;

  MakeTreeList(tree, 0.05);

  
  cout << "Rakennetaan lehdet " << endl;
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
  LoadGLTextures(const_cast<char*>(string("neulaset5.tga").c_str()));  //**** CFLoadGLTextures
  


  cout << "Rakennetaan puu.." << endl;
  
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











template <class TS,class BUD>
  int VisualizeTreesAndVoxelSpace(vector<Tree<TS,BUD> *> trees 
     ,VoxelSpace &vs)
  {
       
 

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
void AddScotsPine(Tree<TS,BUD> &tree, int mode)
{
  if (mode == 1) //runko
    {
      GLfloat mat_amb[] = { 0.2, 0.3, 0.4, 1.0 }; 
      GLfloat mat_dif[] = { 0.2, 0.4, 0.4, 1.0 }; 
  
      GLfloat mat_amb2[] = { 1.0, 0.5, 0.4, 1.0 }; 
      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb); 
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
      

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);  
  
      glDisable(GL_LIGHTING);
      DrawStemFunctor<TS,BUD> stemfunctor;
      stemfunctor.min_rad = -99;
      stemfunctor.max_rad = 999;
      ForEach(tree, stemfunctor);
    }
  
  if (mode == 2) //neulaset
    {
      /*
      // Jos piirretaan ilman l‰pin‰kyvyytta niin muistia s‰‰styy
      DrawNeedlesFunctor<TS, BUD> needles_functor;
      glDisable(GL_LIGHTING);
      glPushMatrix();
      ForEach(tree, needles_functor);
      glPopMatrix();
      */

      // t‰ss‰ l‰pin‰kyvyydell‰      
      glEnable(GL_BLEND);
      //UseTextures();
      DrawNeedlesFunctor<TS, BUD> needles_functor;

      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDisable(GL_LIGHTING);
      
      glPushMatrix();
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);  
      ForEach(tree, needles_functor); 
      glCullFace(GL_BACK); 
      ForEach(tree, needles_functor); 
      
      glDisable(GL_CULL_FACE);
      glPopMatrix();    
    
      glDisable(GL_BLEND);
         
    }
}

 




}//closing namespace Lignum



#endif
