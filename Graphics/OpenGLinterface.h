#ifndef OPENGLINTERFACE_H
#define OPENGLINTERFACE_H


#include <Lignum.h>

//And the vendors just can't agree where the headers are...
#if defined(__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

//#include <GL/glaux.h>





class CLignumWBDoc;

void DrawFirmament();

void InitOpenGL();

void SetShadeModel();

void DrawTree();

void DrawFoliage();

void DrawBuds();

void DrawCross();

void DrawWireModel();

void CountCamera();

inline void SetViewPort();

void SetDrawModes();

void SetLight();

void SetLightPosition();

void DrawNeedles();



template <class TS,class BUD>
void ForestNeedles(Tree<TS,BUD> &tree);

template <class TS,class BUD>
void ForestLeaves(Tree<TS,BUD> &tree,int xsize, int ysize);

template <class TS,class BUD>
void MakeForestTree(Tree<TS,BUD> &tree);

template <class TS,class BUD,class S>
void MakeLeaveList(Tree<TS,BUD> &tree,int xsize=6, int ysize=6);

template <class TS,class BUD>
void MakeTreeList(Tree<TS,BUD> &tree, LGMdouble limit);

template <class TS,class BUD>
void MakeNeedlesList(Tree<TS,BUD> &tree);

void DrawOrderedFoliage();


#include "OpenGLinterfaceI.h"

#endif
