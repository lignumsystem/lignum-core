#ifndef OPENGLINTERFACEI_H
#define OPENGLINTERFACEI_H




#include "OpenGLSymbols.h"
#include "OpenGLfunctions.h"
#include "OpenGLFunctor.h"
#include "OpenGL.h"

#include <GL/gl.h>
#include <GL/glu.h>


extern GLfloat cam_x;  //camera position
extern GLfloat cam_y;
extern GLfloat cam_z;

extern GLfloat lookat_x;  // look at
extern GLfloat lookat_y;
extern GLfloat lookat_z;

template <class TS,class BUD>
void MakeLeaveList(Tree<TS,BUD> &tree, int xsize, int ysize)
{
	MakeLeaveTable();

	if (glIsList(FOLIAGE))
		glDeleteLists(FOLIAGE, 1);

	glPushMatrix();
	glNewList(FOLIAGE, GL_COMPILE);	
	UseTextures();

	DrawLeavesFunctor<TS, BUD> leaves_functor(xsize, ysize);
	ForEach(tree, leaves_functor);
		
	glEndList();
	glPopMatrix();
}


template <class TS,class BUD>
void MakeBudList(Tree<TS,BUD> &tree, bool alive)
{
 
  glPushMatrix();
  DrawBudFunctor<TS,BUD> budsfunctor;

  if (alive)
    {
      if (glIsList(BUDS_ALIVE))
	glDeleteLists(BUDS_ALIVE, 1);
      glNewList(BUDS_ALIVE, GL_COMPILE);
      budsfunctor.mode = buds_alive;
    }
  else
    {
      if (glIsList(BUDS_DEAD))
	glDeleteLists(BUDS_DEAD, 1);
      glNewList(BUDS_DEAD, GL_COMPILE);
      budsfunctor.mode = buds_dead;
    }

  ForEach(tree, budsfunctor);
  glEndList();
  glPopMatrix();
}


template <class TS,class BUD>
void MakeTreeList(Tree<TS,BUD> &tree, LGMdouble limit)
{
  
	if (glIsList(TREE_BIG))
		glDeleteLists(TREE_BIG, 1);
	if (glIsList(TREE_SMALL))
		glDeleteLists(TREE_SMALL, 1);
  
	cout << "MakeTreeList:tehdaan puu" << endl;

	glPushMatrix();
	glNewList(TREE_BIG, GL_COMPILE);
	DrawStemFunctor<TS,BUD> stemfunctor;
	stemfunctor.min_rad = limit;
	stemfunctor.max_rad = 999;
	ForEach(tree, stemfunctor);
	glEndList();
	glPopMatrix();


	glPushMatrix();
	glNewList(TREE_SMALL, GL_COMPILE);
	stemfunctor.min_rad = 0;
	stemfunctor.max_rad = limit;
	ForEach(tree, stemfunctor);
	glEndList();
	glPopMatrix();
}


inline void SetViewPort()
{
	gluLookAt (cam_x, cam_y, cam_z,				   // camera x,y,z  
			   lookat_x, lookat_y, lookat_z,	   // look at x,y,z    
			   0.0, 0.0, 1.0);					   // which way up 	
}

#endif
