#ifndef OPENGLFUNCTIONS_H
#define OPENGLFUNCTIONS_H


#include <string>

//And the vendors just can't agree where the headers are...
#if defined(__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

//#include <GL/glaux.h>

using namespace std;

void ShadowMatrix(GLfloat shadowMat[4][4],  GLfloat groundplane[4], GLfloat lightpos[4]);

// Loading tree textures.
bool LoadTextures(string stem1, string stem2, string foliage);

// Loading a bmp-texture
//AUX_RGBImageRec* LoadBMP(string filename);

bool LoadGLTextures(char *name);

bool LoadGLTextures(char *name1, char *name2);

void FindPlane(GLfloat plane[4]);

void UseTextures();

void NoTextures();


void makeBGR (unsigned char *p, int size);
void writeTGA (char *name, unsigned char *buff, int w, int h);
int screenShot (char *fName, int winW, int winH);
#endif
