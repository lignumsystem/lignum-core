
#ifndef GLSETTINGS
#define GLSETTINGS


#include <OpenGLinterface.h>



class GLSettings
{
public:
  GLSettings();
	bool antialising_on;
	bool foliage_on;
	bool textures_on;
	bool lighting_on;
	bool fog_on;
	bool show_voxel_on;
	bool boolVoxelWithLines;

	float LightPosition[4];
	LIGHT_VAL light;

	float cam_x;
	float cam_y;
	float cam_z;

	float lookat_x;
	float lookat_y;
	float lookat_z;

	float m_xRotate;
	float m_yRotate;
	float m_xrRotate;
	float m_yrRotate;

	bool blackBackGround;

	int window1; //mika merkitys?
	int window2; //mika merkitys?

	float x_move;
	float y_move;
	float z_move;

	float mouse_x;
	float mouse_y;

	int LEFTBUTTON;
	int MIDDLEBUTTON;
	int RIGHTBUTTON;

	float lightx;
	float lighty;
	float lightz;
	float lightw;

	int head_xy;
	float head_z;

	int WINDOW_SIZE_X;
	int WINDOW_SIZE_Y;

	bool MOVEMENT;
	
};


#endif
