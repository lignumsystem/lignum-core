#ifndef OPENGLINTERFACE_H
#define OPENGLINTERFACE_H


#include <Tree.h>

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>



enum LIGHT_TYPE { AMBIENT, DIFFUSE, AMBIENT_AND_DIFFUSE, SPECULAR };
enum DRAW_TYPE {stem, wiremodel, waterflow, betula_make_leaves, betula_leaves, betula_ani_leaves, needles, needles_tex, needles_tex_ordered, buds_dead, gliricidia_leaves,buds_alive, year_lines, year_lines_secround};
enum REDRAW_MODE { rd_normal, rd_waterdraw, rd_yearline_gp, rd_yearcircles, rd_manybetulas, rd_cross };
enum CAMERA_MODE { turn_camera, move_camera };


struct LIGHT
{
	LIGHT_TYPE type;
	GLfloat value[4];
};

struct LIGHT_VAL 
{
	GLfloat LightPosition[4];  
	LIGHT ambient;
	LIGHT specular;
	LIGHT diffuse;
};


class CLignumWBDoc;

void DrawFirmament();

void InitOpenGL();

void SetShadeModel();

//void DrawAllTrees(CLignumWBDoc *doc);

//void DrawAllFoliage(CLignumWBDoc *doc);

void DrawTree();

void DrawFoliage();

void DrawBuds();

void DrawCircles(CLignumWBDoc *doc);

void DrawCross();

void DrawWireModel();

//void RenderScene(CLignumWBDoc *doc);

void CountCamera();

inline void SetViewPort();

void SetDrawModes();

void SetLight();

void SetLightPosition();

//float MakeTreeLists(CLignumWBDoc *doc);
						
//void MakeLeaveList(CLignumWBDoc *doc);

template <class TS,class BUD>
void MakeLeaveList(Tree<TS,BUD> &tree,int xsize=6, int ysize=6);

template <class TS,class BUD>
void MakeTreeList(Tree<TS,BUD> &tree, LGMdouble limit);

void DrawOrderedFoliage();


#include "OpenGLinterfaceI.h";

#endif