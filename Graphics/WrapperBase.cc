#include <stdafx.h>

#include <Wrapperbase.h>


using namespace Lignum;


#if defined( APPLE ) || defined(MACOSX)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glut.h>
#endif



namespace Lignum
{


// Number of active is given as a parameter
void CfWrapper::VisualizeStem(int &active_texture)
{
	
}


void CfWrapper::VisualizeFoliage(int &active_texture)
{
	
}


void HwWrapper::VisualizeStem(int &active_texture)
{
	
}


void HwWrapper::VisualizeFoliage(int &active_texture)
{
	
}

void CfWrapper::VisualizeTree()
{
	
	
}


void HwWrapper::VisualizeTree()
{
}

}


