#ifndef TREEVAR_HPP
#define TREEVAR_HPP

#define LEAVE_VERT 33
#define LEAVE_SIZE 50
#define LEAVE_LINES 8
#define PETIOLE_SIZE 1
#define TEXT_ODD 600

//And the vendors just can't agree where the headers are...
#if defined(__APPLE__) || defined(__MACOSX__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif


static GLfloat leave[LEAVE_VERT][2] = { 
                                { 0.2, 1.0},
                                { 0.7, 1.55},
								{ 1.4, 1.6},
								{ 1.2, 1.9},
								{ 2.1, 2.0},
								{ 1.95, 2.15},
								{ 2.3, 2.25},
								{ 2.9, 2.6},
								{ 2.6, 2.6},
								{ 3.25, 3},
								{ 3.35, 3.6},
								{ 3.2, 3.55},
								{ 3.4, 4},
								{ 3.3, 4},
								{ 3.32, 4.6},
								{ 3.1, 4.55},
								{ 3.2, 5.15},
								{ 3.0, 5.05},
								{ 2.95, 5.9},
				{ 2.55, 5.85},
				{ 2.45, 6.5},
				{ 2.1, 6.35},
				{ 2.05, 7.15},
				{ 1.7, 7.05},
				{ 1.3, 8.1},
				{ 1.1, 8.05},
				{ 1, 9},
				{ 0.85, 8.85},
				{ 0.6, 9.5},
				{ 0.35, 9.3},
				{ 0.0, 9.7},
				{ 0, 0},
				{ 0.2, 0}};


#endif
