#ifndef OPENGLFUNCTIONS_H
#define OPENGLFUNCTIONS_H

#include <OpenGLHFiles.h>
#include <string>



//#include <GL/glaux.h>

using namespace std;

bool LoadTgaTexture(int &number, const string &filename);

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
