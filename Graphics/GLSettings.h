
#ifndef GLSETTINGS
#define GLSETTINGS




class GLSettings
{
public:
	bool antialising_on;
	bool folige_on;
	bool textures_on;
	bool lighting_on;
	bool fog_on;
	bool show_voxel_on;
	bool boolVoxelWithLines;

	GLfloat LightPosition[4];
	LIGHT_VAL light;

	GLfloat cam_x;
	GLfloat cam_y;
	GLfloat cam_z;

	GLfloat lookat_x;
	GLfloat lookat_y;
	GLfloat lookat_z;

	GLfloat m_xRotate;
	GLfloat m_yRotate;
	GLfloat m_xrRotate;
	GLfloat m_yrRotate;

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

	GLfloat lightx;
	GLfloat lighty;
	GLfloat lightz;
	GLfloat lightw;

	int head_xy;
	float head_z;

	int WINDOW_SIZE_X;
	int WINDOW_SIZE_Y;

	GLboolean MOVEMENT;
	
};


#endif