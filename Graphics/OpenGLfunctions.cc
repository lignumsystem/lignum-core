#include "stdafx.h"
#include "OpenGLfunctions.h"
#include "OpenGLinterface.h"

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

//#include "tga.h"
//#include "Functions.h"
#include "TreeVariables.h"
#include "OpenGLSymbols.h"

extern GLuint texture[3];
extern int texIds[6];




using namespace std;
/*
bool LoadTextures(string stem1, string stem2, string foliage)
{
	char buff[15];
	tga_t image;
   
	texIds[0] = image.GenId(); // let OpenGL give us a texture id
   
	string tmp1;
	string path = "";

	#ifdef _MSC_VER
	tmp1 = (CString)GetLignumPath()+"textures\\";
	tmp1 = tmp1 + foliage;
	string p = (CString)GetLignumPath();
	path = path + p;   
	#endif
   
   char *name = const_cast<char *>(tmp1.c_str());
   image.Load(name, texIds[0]);
   
   const int num_textures = 2;
   AUX_RGBImageRec *TextureImage[num_textures];
   memset(TextureImage,0, sizeof(void *));
   if ((TextureImage[0]=LoadBMP(path+"textures\\" + stem1))   &&   (TextureImage[1]=LoadBMP(path+"textures\\"+stem2)))
	{
		glGenTextures(num_textures, &texture[0]);

		for(int i=0; i<num_textures; i++)
		{
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY,
				0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
		}

		for (i=0; i<num_textures; i++)
		{
			if (TextureImage[i])
			{
				if(TextureImage[i]->data)
				{
					free(TextureImage[i]->data);
				}
				free(TextureImage[i]);
			}
		}
		return true;
	}
	return false;
}


AUX_RGBImageRec* LoadBMP(string filename)
{
	FILE *file=NULL;
	

	file = fopen(filename.c_str(),"r");
	if (file)
	{
		fclose(file);
		return auxDIBImageLoad(filename.c_str());
	}
	return NULL;
}
*/
bool LoadGLTextures()
{
   /*
	char buff[15];
   tga_t image;

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glEnable(GL_DEPTH_TEST);
   //glEnable(GL_BLEND);???
   glEnable(GL_TEXTURE_2D);
   // blend func for transparency
   //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); ???

   
   texIds[0] = image.GenId(); // let OpenGL give us a texture id
   texIds[1] = image.GenId(); 

   std::string tmp1 = GetLignumPath()+"textures\\" + fol_texture;

   char *name = const_cast<char *>(tmp1.c_str());
   image.Load(name, texIds[0]);


  // image.Load("textures\\Lehti.tga", texIds[1]);
//	image.Load("textures\\vaahtera1.tga", texIds[1]);
  // 	image.Load("textures\\koivuvk1.tga", texIds[1]);
  	
	const int num_textures = 1;
	AUX_RGBImageRec *TextureImage[num_textures];
	memset(TextureImage,0, sizeof(void *));

	

	if (TextureImage[0]=LoadBMP(GetLignumPath()+"textures\\" + stem_texture))  // && (TextureImage[2]=LoadBMP("textures\manty3.bmp")))
	{
		glGenTextures(num_textures, &texture[0]);

		for(int i=0; i<num_textures; i++)
		{
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY,
				0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
		}


		for (i=0; i<num_textures; i++)
		{
			if (TextureImage[i])
			{
				if(TextureImage[i]->data)
				{
					free(TextureImage[i]->data);
				}
				free(TextureImage[i]);
			}
		}
		return true;
	}
	*/
	return false;	
	
}





void ShadowMatrix(GLfloat shadowMat[4][4],  GLfloat groundplane[4], GLfloat lightpos[4])
{
  GLfloat dot;
  enum {  X, Y, Z, W };
  enum {  A, B, C, D };
 

  /* Find dot product between light position vector and ground plane normal. */
  dot = groundplane[X] * lightpos[X] +
  groundplane[Y] * lightpos[Y] +
  groundplane[Z] * lightpos[Z] +
  groundplane[W] * lightpos[W];

  shadowMat[0][0] = dot - lightpos[X] * groundplane[X];
  shadowMat[1][0] = 0.f - lightpos[X] * groundplane[Y];
  shadowMat[2][0] = 0.f - lightpos[X] * groundplane[Z];
  shadowMat[3][0] = 0.f - lightpos[X] * groundplane[W];

  shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
  shadowMat[1][1] = dot - lightpos[Y] * groundplane[Y];
  shadowMat[2][1] = 0.f - lightpos[Y] * groundplane[Z];
  shadowMat[3][1] = 0.f - lightpos[Y] * groundplane[W];

  shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
  shadowMat[1][2] = 0.f - lightpos[Z] * groundplane[Y];
  shadowMat[2][2] = dot - lightpos[Z] * groundplane[Z];
  shadowMat[3][2] = 0.f - lightpos[Z] * groundplane[W];

  shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
  shadowMat[1][3] = 0.f - lightpos[W] * groundplane[Y];
  shadowMat[2][3] = 0.f - lightpos[W] * groundplane[Z];
  shadowMat[3][3] = dot - lightpos[W] * groundplane[W];
}



void FindPlane(GLfloat plane[4])
{ 
  GLfloat v0[3] = { -8.0, 8.0, 0.0 };
  GLfloat v1[3] = { 8.0, 8.0, 0.0 };
  GLfloat v2[3] = { -8.0, -8.0, 0.0 };
	
  GLfloat vec0[3], vec1[3];
  enum {  X, Y, Z, W };
  enum {  A, B, C, D };

  /* Need 2 vectors to find cross product. */
  vec0[X] = v1[X] - v0[X];
  vec0[Y] = v1[Y] - v0[Y];
  vec0[Z] = v1[Z] - v0[Z];

  vec1[X] = v2[X] - v0[X];
  vec1[Y] = v2[Y] - v0[Y];
  vec1[Z] = v2[Z] - v0[Z];

  /* find cross product to get A, B, and C of plane equation */
  plane[A] = vec0[Y] * vec1[Z] - vec0[Z] * vec1[Y];
  plane[B] = -(vec0[X] * vec1[Z] - vec0[Z] * vec1[X]);
  plane[C] = vec0[X] * vec1[Y] - vec0[Y] * vec1[X];
  plane[D] = -(plane[A] * v0[X] + plane[B] * v0[Y] + plane[C] * v0[Z]);
}




void UseTextures()
{
	glEnable(GL_TEXTURE_2D);  
}

void NoTextures()
{
	glDisable(GL_TEXTURE_2D);  
}
