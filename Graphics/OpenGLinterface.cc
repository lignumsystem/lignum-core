#include "stdafx.h"
#include "LignumWBDoc.h"
#include "OpenGLinterface.h"

#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

#include "tga.h"
#include "Functions.h"
#include "TreeVariables.h"

#include "OpenGLSymbols.h"
#include "OpenGLfunctions.h"
#include "OpenGLFunctor.h"
#include "OpenGL.h"

#include <string>
#include <vector>

GLfloat m_xRotate;   //left button values
GLfloat m_yRotate;
GLfloat m_xrRotate;  //right button values
GLfloat m_yrRotate;

LIGHT_VAL light;
GLfloat LightPosition[4];

GLfloat m_height;
GLfloat dr_height;
REDRAW_MODE rd_mode;

GLfloat groundPlane[4];
GLfloat groundShadow[4][4];
GLfloat shadowLight[4];

CAMERA_MODE c_mode;

GLfloat cam_x;  //camera position
GLfloat cam_y;
GLfloat cam_z;
double height;

GLfloat lookat_x;  // look at
GLfloat lookat_y;
GLfloat lookat_z;

bool antialising_on;
bool foliage_on;
bool textures_on;
bool lighting;
bool fog_on;

int texIds[6];
GLuint texture[3];

/*
CString stem_min_texture;	
CString fol_texture;
CString stem_texture;
*/
//float rad_limit;


GLenum shade_model = GL_FLAT;

extern std::vector<NEEDLE_PLANE> nplanes;


void InitOpenGL()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLightfv(GL_LIGHT0, GL_POSITION, light.LightPosition);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);


	InitDrawing();
	m_xRotate = 0;
	m_yRotate = 0;

	m_xrRotate = 0;
	m_yrRotate = 0;

	shadowLight[0] = -1;
	shadowLight[1] = -2;
	shadowLight[2] = -3;
	shadowLight[3] = 0;

	light.LightPosition[0] = 5.0f;
	light.LightPosition[1] = 5.0f;
	light.LightPosition[2] = 15.0f;
	light.LightPosition[3] = 0.0f;

	light.specular.value[0] = 1.0f;
	light.specular.value[1] = 1.0f;
	light.specular.value[2] = 1.0f;
	light.specular.value[3] = 1.0f;

	light.ambient.value[0] = 0.8f;
	light.ambient.value[1] = 0.8f;
	light.ambient.value[2] = 0.8f;
	light.ambient.value[3] = 1.0f;

	light.diffuse.value[0] = 1.0f;
	light.diffuse.value[1] = 1.0f;
	light.diffuse.value[2] = 1.0f;
	light.diffuse.value[3] = 1.0f;

	cam_x = 1.5;
	cam_y = 0;
	cam_z = height/2; 

	lookat_x = 0; 
	lookat_y = 0;
	lookat_z = height/1.5;

	m_height = 0;
	m_xRotate = 0;
	m_yRotate = 0;

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	SetShadeModel();
	SetLight();
}


void SetShadeModel()
{
	glShadeModel(shade_model);
}


/*
void DrawAllTrees(CLignumWBDoc *doc)
{
	int n= doc->betulas.size();

	GLfloat mat_amb[] = { 1, 1, 1, 1.0 }; 
	GLfloat mat_dif[] = { 1, 1, 1, 1.0 }; 

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb); 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);

	glPushMatrix();
	for (int i=0; i<n; i++)
	{
		glTranslatef( 1, 0, 0 );
		glCallList(MANY_TREES+i*3);
	}
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	for (i=0; i<n; i++)
	{
		glTranslatef( 1, 0, 0 );
		glCallList(MANY_TREES+i*3+1);
	}
	glPopMatrix();

	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
}


void DrawAllFoliage(CLignumWBDoc *doc)
{
	 int n= doc->betulas.size();

	 glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 glBindTexture(GL_TEXTURE_2D, texIds[0]);
	

	 glEnable(GL_LIGHTING);	 
	 glPushMatrix();
	 glEnable(GL_CULL_FACE);
     glCullFace(GL_FRONT);     
	 for (int i=0; i<n; i++)
	 {
		glTranslatef( 1, 0, 0 );
		glCallList(MANY_TREES+i*3+2);
	 } 
	 glPopMatrix();
	 
	 glPushMatrix();
	 glCullFace(GL_BACK);     	 
	 for (i=0; i<n; i++)
	 {
		 glTranslatef( 1, 0, 0 );
		 glCallList(MANY_TREES+i*3+2);
	 }
     glDisable(GL_CULL_FACE);
	 glPopMatrix();
}
*/


void DrawTree()
{	
	///***************
	#ifdef _MSC_VER
		glCallList(TREE);
	
	#else
	GLfloat mat_amb[] = { 1, 1, 1, 1.0 }; 
	GLfloat mat_dif[] = { 1, 1, 1, 1.0 }; 

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb); 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);

	glPushMatrix();
	glCallList(TREE_BIG);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glCallList(TREE_SMALL);
	glPopMatrix();

	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
	#endif
}

void DrawOrderedFoliage()
{
	 glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 glBindTexture(GL_TEXTURE_2D, texIds[0]);
	 glDisable(GL_LIGHTING);

	 glPushMatrix();
	 glEnable(GL_CULL_FACE);
     glCullFace(GL_FRONT);     
	 DrawOrderedNeedles();
 
	 
	 glCullFace(GL_BACK);     	 
	 DrawOrderedNeedles();
     glDisable(GL_CULL_FACE);
	 glPopMatrix();

	 glEnable(GL_LIGHTING);	 
	 glPushMatrix();
	 glEnable(GL_CULL_FACE);
     glCullFace(GL_FRONT);     
	 glCallList(FOLIAGE); 		  
	 glCullFace(GL_BACK);     	 
	 glCallList(FOLIAGE);
     glDisable(GL_CULL_FACE);
	 glPopMatrix();
}


void DrawFoliage()
{	
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 glBindTexture(GL_TEXTURE_2D, texIds[0]);
	 glDisable(GL_LIGHTING);

	 glPushMatrix();
	 glEnable(GL_CULL_FACE);
     glCullFace(GL_FRONT);     
	 glCallList(NEEDLES_TEX); 
	 
	 glCullFace(GL_BACK);     	 
	 glCallList(NEEDLES_TEX);
     glDisable(GL_CULL_FACE);
	 glPopMatrix();

	 glEnable(GL_LIGHTING);	 
	 glPushMatrix();
	 glEnable(GL_CULL_FACE);
     glCullFace(GL_FRONT);     
	 glCallList(FOLIAGE); 		  
	 glCullFace(GL_BACK);     	 
	 glCallList(FOLIAGE);
     glDisable(GL_CULL_FACE);
	 glPopMatrix();

	 return;
}

void DrawFirmament()
{
	glDisable(GL_TEXTURE_2D);
	glCallList(FIRMAMENT_POINTS);
}

void DrawBuds()
{
	GLfloat mat_amb1[] = { 0.7, 0.7, 0.1, 1.0 };
	GLfloat mat_amb2[] = { 0.2, 0.2, 0.1, 1.0 };
      
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb1);
	glCallList(BUDS_ALIVE);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb2);
    glCallList(BUDS_DEAD);  
}


void DrawCircles(CLignumWBDoc *doc)
{
	gluLookAt (0.4, 0.4, dr_height+0.4,		// camera x,y,z  0.5
			   0, 0, dr_height+0.05,		// look at x,y,z    
			   0.0, 0.0, 1.0);				// which way up 

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	TraverseMainAxis(GetAxis(doc->GetScotsPine()), stem, doc, dr_height);	
}


void DrawCross()
{

	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(0,0,0);
	glCallList(CROSS);
	glPopMatrix();
	glEnable(GL_LIGHTING);

	UseTextures();
	GLfloat mat_amb[] = { 1, 1, 1, 1.0 }; 
	GLfloat mat_dif[] = { 1, 1, 1, 1.0 }; 

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb); 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPushMatrix();
	glCallList(STEM_CROSS);
	glPopMatrix();
}


void DrawWireModel()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glCallList(WIREMODEL);	
	glPopMatrix();
	glEnable(GL_LIGHTING);
}


void CountCamera()
{
	if (m_yRotate<100 && rd_mode==rd_yearcircles)
	{
		dr_height = dr_height + m_yRotate / 200;
		m_yRotate = 0;
		return;
	}
	
	if (m_yRotate<100 && m_xRotate<100)
		{
		if(c_mode == turn_camera)
			{
			PositionVector direction(lookat_x-cam_x, lookat_y-cam_y, lookat_z-cam_z);
			direction.normalize();
			lookat_z = lookat_z + m_yRotate / 200;
			lookat_x = lookat_x + m_xRotate * direction.getY() / 200;
			lookat_y = lookat_y + m_xRotate * direction.getX() / 200;
			m_yRotate = 0;
			m_xRotate = 0;
			}
		if(c_mode == move_camera)
			{
				PositionVector direction(lookat_x-cam_x, lookat_y-cam_y, lookat_z-cam_z);			
				direction.normalize();

				cam_x = cam_x + direction.getX() * m_yRotate/20;
				cam_y = cam_y + direction.getY() * m_yRotate/20;
				cam_z = cam_z + direction.getZ() * m_yRotate/20;

				lookat_x = lookat_x + direction.getX() * m_yRotate/40;
				lookat_y = lookat_y + direction.getY() * m_yRotate/40;
				lookat_z = lookat_z + direction.getZ() * m_yRotate/40;

				
				PositionVector origo(-cam_x, -cam_y, 0);
				float l = origo.length();
				float x = origo.getX();
				float y = origo.getY();

				float angle = 0;
				if (x>=0 && y>=0)
				{
					angle = atan(y/x);
				}
				if (x<0 && y>=0)
				{
					angle = 3.14 - atan(y/(-x));
				}
				if (x<0 && y<0)
				{
					angle = 3.14 + atan((-y)/(-x));
				}
				if (x>=0 && y<0)
				{
					angle = 6.28 - atan((-y)/x);
				}
				
				angle = angle + (float)m_xRotate / 40;
				x = cos(angle) * l;
				y = sin(angle) * l;

				cam_x = -x;
				cam_y = -y;


				m_yRotate = 0;
				m_xRotate = 0;
			}
		}
}





void SetDrawModes()
{
	if(antialising_on)
	{
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glShadeModel(GL_FLAT);
	} 
	else
	{
		glDisable(GL_BLEND);
		glDisable(GL_LINE_SMOOTH);
	}

	if (fog_on)
	{
		glEnable(GL_FOG);
		GLfloat color[4] = {0.3, 0.3, 0.3, 1.0};
		glFogfv(GL_FOG_COLOR, color);
		glFogf(GL_FOG_DENSITY, 3);
		glFogf(GL_FOG_START, 1.5);
		glFogf(GL_FOG_END, 5.0);
		glFogi(GL_FOG_MODE, GL_LINEAR);
	}
	else glDisable(GL_FOG);
}



void SetLight()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient.value);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular.value);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse.value);
}

void SetLightPosition()
{
	glLightfv(GL_LIGHT0, GL_POSITION, light.LightPosition);
}





/*
float MakeTreeLists(CLignumWBDoc *doc)
{
	if (glIsList(TREE_BIG))
		glDeleteLists(TREE_BIG, 1);
	if (glIsList(TREE_SMALL))
		glDeleteLists(TREE_SMALL, 1);
	
	float height;
	glPushMatrix();
	glNewList(TREE_BIG, GL_COMPILE);
	
	DrawStemFunctor<WhiteBirch, DefaultBud<WhiteBirch> > WBstemfunctor;
	
	switch(doc->tree_type) 
	{
		case tt_betula :
			height = TraverseAxis(GetAxis(doc->GetBetula()), stem, doc, rad_limit);								
			break;
		case tt_whitebirch :
			WBstemfunctor.min_rad = rad_limit;
			WBstemfunctor.max_rad = 999;
			ForEach(doc->GetWhiteBirch(), WBstemfunctor);
			//height = TraverseAxis(GetAxis(doc->GetWhiteBirch()), stem, doc, rad_limit);								
			break;

		case tt_sugarmaple :
			height = TraverseAxis(GetAxis(doc->GetBetula()), stem, doc, rad_limit);								
			break;
		case tt_digitree:
			height = TraverseAxis(GetAxis(doc->GetDigiTree()), stem, doc, rad_limit);								
			break;
										
		case tt_scotspine :															
			height = TraverseAxis(GetAxis(doc->GetScotsPine()), stem, doc, rad_limit);																		
			break;
		case tt_gliricidia :															
			height = TraverseAxis(GetAxis(doc->GetGliricidia()), stem, doc, rad_limit);																		
			break;
	}
	glEndList();
	glPopMatrix();

	glPushMatrix();
	glNewList(TREE_SMALL, GL_COMPILE);		
	switch(doc->tree_type) 
	{
		case tt_betula :
			height = TraverseAxis(GetAxis(doc->GetBetula()), stem, doc, -rad_limit);								
			break;
		case tt_whitebirch :
			WBstemfunctor.max_rad = rad_limit;
			WBstemfunctor.min_rad = 0;
			ForEach(doc->GetWhiteBirch(), WBstemfunctor);
			//height = TraverseAxis(GetAxis(doc->GetWhiteBirch()), stem, doc, -rad_limit);								
			break;

		case tt_sugarmaple :
			height = TraverseAxis(GetAxis(doc->GetBetula()), stem, doc, -rad_limit);								
			break;

		case tt_digitree:
			height = TraverseAxis(GetAxis(doc->GetDigiTree()), stem, doc, -rad_limit);								
			break;
										
		case tt_scotspine :															
			height = TraverseAxis(GetAxis(doc->GetScotsPine()), stem, doc, -rad_limit);																		
			break;
		case tt_gliricidia :															
			height = TraverseAxis(GetAxis(doc->GetGliricidia()), stem, doc, -rad_limit);																		
			break;
	}
	glEndList();
	glPopMatrix();


	glNewList(TREE, GL_COMPILE);
	GLfloat mat_amb[] = { 1, 1, 1, 1.0 }; 
	GLfloat mat_dif[] = { 1, 1, 1, 1.0 }; 

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb); 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);

	glPushMatrix();
	glCallList(TREE_BIG);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glCallList(TREE_SMALL);
	glPopMatrix();

	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
	glEndList();

	return height;
}


void MakeLeaveList(CLignumWBDoc *doc)
{
	MakeLeaveTable();

	if (glIsList(FOLIAGE))
		glDeleteLists(FOLIAGE, 1);

	num_lea = 0;
	glPushMatrix();
	glNewList(FOLIAGE, GL_COMPILE);	
	UseTextures();

	DrawLeavesFunctor<WhiteBirch, DefaultBud<WhiteBirch> > WBleavesfunctor(9,9);
	Axis<BetulaTortuosa>& axis2 = GetAxis(doc->GetBetula());
	Axis<WhiteBirch>& axis1 = GetAxis(doc->GetWhiteBirch());
	switch(doc->tree_type) 
	{
		case tt_whitebirch :
				ForEach(doc->GetWhiteBirch(), WBleavesfunctor);
				break;
		case tt_betula :
				TraverseAxis(axis2, betula_leaves, doc, 0);
				break;

		case tt_sugarmaple :
				TraverseAxis(axis2, betula_leaves, doc, 0);
				break;
	}
	glEndList();
	glPopMatrix();
}
*/


void DrawOrderedNeedles()
{
	int s = nplanes.size();

	if (cam_x*cam_x + cam_y*cam_y > 10 || rand()%5>0)
	{
		for (int i=0; i<s; i++)
		{
			glCallList(nplanes[i].number);
		}
		return;
	}
		
	
	
	for (int i=0; i< s; i++)
	{
		double dx = nplanes[i].x - cam_x;
		double dy = nplanes[i].y - cam_y;
		double dz = nplanes[i].z - cam_z;
		nplanes[i].dist = dx*dx + dy*dy + dz*dz;
	}

	LGMdouble min_dist = -1.0;
	LGMdouble furthest = 999;
	int num = -1;
	for (int a=0; a<s; a++)
	{
		for (i=0; i<s; i++)
		{
			if (nplanes[i].dist>min_dist && furthest>nplanes[i].dist)
			{
				num = nplanes[i].number;
				min_dist = nplanes[i].dist;
			}
		}
		glCallList(num);
		furthest = min_dist;
		min_dist = -1.0;
	}
}