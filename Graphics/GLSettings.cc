
#include <stdafx.h>

#include <GLSettings.h>
#include <OpenGLSymbols.h>

#if defined(__APPLE__) || defined(__MACOSX__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/gl.h>
#endif




GLSettings::GLSettings()
{
	antialising_on = true;
	foliage_on = false;
	textures_on = true;
	lighting_on = true;
	fog_on = false;
	show_voxel_on = false;
	boolVoxelWithLines = false;;

	this->LightPosition[0] = 5.0f;
	this->LightPosition[1] = 5.0f;
	this->LightPosition[2] = 15.0f;
	this->LightPosition[3] = 0.0f;

	light.LightPosition[0] = 5.0f;
	light.LightPosition[1] = 5.0f;
	light.LightPosition[2] = 15.0f;
	light.LightPosition[3] = 0.0f;

	light.specular.value[0] = 1.0f;
	light.specular.value[1] = 1.0f;
	light.specular.value[2] = 1.0f;
	light.specular.value[3] = 1.0f;

	light.ambient.value[0] = 1.0f;
	light.ambient.value[1] = 1.0f;
	light.ambient.value[2] = 1.0f;
	light.ambient.value[3] = 1.0f;

	light.diffuse.value[0] = 1.0f;
	light.diffuse.value[1] = 1.0f;
	light.diffuse.value[2] = 1.0f;
	light.diffuse.value[3] = 1.0f;

	cam_x = 4.5;
	cam_y = 0;
	cam_z = 0.05;

	lookat_x = 0;
	lookat_y = 0;
	lookat_z = 0.5;

	m_xRotate = 0;
	m_yRotate = 0;
	m_xrRotate = 0;
	m_yrRotate = 0;
		
	blackBackGround = false;

	window1 = 0;
	window2 = 0;

	x_move = 1;
	y_move = 0;
	z_move = 0;

	mouse_x = 400;
	mouse_y = 300;

	LEFTBUTTON = UP;
	MIDDLEBUTTON = UP;
	RIGHTBUTTON = UP;


	lightx = 1;
	lighty = 3;
	lightz = 2;
	lightw = 0;

	head_xy = 0;
	head_z = 1.4;

	WINDOW_SIZE_X = 800;
	WINDOW_SIZE_Y = 600;

	MOVEMENT = true;
	


}
