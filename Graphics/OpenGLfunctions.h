#ifndef OPENGLFUNCTIONS_H
#define OPENGLFUNCTIONS_H


#include <string>

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

using namespace std;

void ShadowMatrix(GLfloat shadowMat[4][4],  GLfloat groundplane[4], GLfloat lightpos[4]);

// Loading tree textures.
bool LoadTextures(string stem1, string stem2, string foliage);

// Loading a bmp-texture
AUX_RGBImageRec* LoadBMP(string filename);

bool LoadGLTextures();

void FindPlane(GLfloat plane[4]);

void UseTextures();

void NoTextures();


#endif