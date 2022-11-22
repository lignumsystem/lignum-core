#ifndef OPENGLHFILES_H
#define OPENGLHFILES_H
//Mac OS X install OpenGL  and GLUT frameworks differently, the latter
//should work for all others. If anything else is needed, this file is
//intended to capture the inclusions of OpenGL and GLUT headers in one
//place.
#if defined(__APPLE__) || defined(__MACOSX__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif __linux__
#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#endif
