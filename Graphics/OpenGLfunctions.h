#ifndef OPENGLFUNCTIONS_H
#define OPENGLFUNCTIONS_H


#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glaux.h>

using namespace std;

void ShadowMatrix(GLfloat shadowMat[4][4],  GLfloat groundplane[4], GLfloat lightpos[4]);

// Loading tree textures.
bool LoadTextures(string stem1, string stem2, string foliage);

// Loading a bmp-texture
//AUX_RGBImageRec* LoadBMP(string filename);

bool LoadGLTextures(char *name);

void FindPlane(GLfloat plane[4]);

void UseTextures();

void NoTextures();


#endif
