

#include "OpenGLUnix.h"
#include <Tree.h>
using namespace Lignum;

#include <list>
//#include <MyTreeSegment.h>
#include <algorithm>
//#include <MyBud.h>

#include <math.h>
//#include <unistd.h>

#include <iostream>
#include <string>

#include <stdlib.h>
#include <stdio.h>

//And the vendors just can't agree where the headers are...
#if defined(__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glut.h>
#endif

#include "OpenGL.h"
#include "OpenGLinterface.h"
#include "OpenGLSymbols.h"
#include <CTexture.h>
#include <texture.h>
#include <tga.h>
#include <VoxelSpace.h>

//#include <dpylc.h>
//#include <CTexture.h>
//#include <textures.h>

#define LEAVE_VERT 33
#define LEAVE_SIZE 500
#define LEAVE_LINES 8
#define MAKE_LEAVES 3
#define SHSEGMENT_RADIUS 21
#define TEXT_ODD 600
#define PETIOLE_SIZE 1

float TEXTURE_LIMIT_MAX = 0.20;  // The radius limit to choose the texture
float TEXTURE_LIMIT_MIN = 0.05;        

bool boolVoxelWithLines = false;
bool boolShowVoxel = true;
bool boolVisualizeVoxelSpace = false;
VoxelSpace *voxel = NULL;

int hours = 6;
double minutes = 0;

#define UP 0
#define DOWN 1

/*
int current_axis = 1;
extern color_style coloring;
extern windows lay_out;

template <class TS,class BUD>
LGMdouble GetTranspiration(TreeSegment<TS,BUD> &ts);

template <class TS, class BUD >
void TraverseAxis(Axis<TS, BUD>& ax, int mode);

template <class TS, class BUD >
void FindLeaves(Axis<TS, BUD>& ax);

template <class TS, class BUD>
void drawTreeSegment(TreeSegment<TS, BUD> *I, int mode);

template <class TS,class BUD>
void WaterFlow(LGMdouble time_step, ConnectionMatrix<TS, BUD> *cm);
*/
extern CTexture text;

/*
extern Tree<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> > digi_tree;
extern ConnectionMatrix<Lignum::BetulaWithFlow, DefaultBud<Lignum::BetulaWithFlow> > *cm;
extern TreeSegment<Lignum::BetulaWithFlow, DefaultBud<Lignum::BetulaWithFlow> > *current;
extern GUS<Lignum::BetulaWithFlow, DefaultBud<Lignum::BetulaWithFlow> > gus;
*/


void DrawVoxelCubes();
//void make_color_palette();
//void subRedraw(void);
//void subRedraw2(void);
void LoadImage(char *filename);
void redraw(void);
/*
void redraw2(void);
void drawTree(int);
void drawWiremodel(void);
void drawLeaves(void);
void makeDigiTree();
void make_stem(void);
void make_leave(float, float);
void make_cylinder(float radius, float lenght, float radius_top=0.0);
*/
void check_values(void);
void setLight(void);


/*
void setSubLight(void);
void Make_Leaves(void);

template <class TS, class BUD>
void setColor(TreeSegment<TS, BUD> *I);
void draw_ground(void);
void draw_heartwood(void);
void draw_scenery(void);
void draw_lightvector(void);
void draw_buds(void);
void initTextures();
void outPutBIG(float x, float y, char *string);
void calculate_light();
void outPut(float x, float y, char *string);
*/



Display        *dpy;
Window          win;

GLboolean       MOVEMENT = true;
GLboolean       TEXTURES_ON = false;
GLboolean       FOLIAGE_ON = false;
GLboolean       SHADOWS = true;
GLboolean       HEARTWOOD = false;

GLboolean       GRAP_ON_ALL_TIME = false;
GLboolean       LIGHT_DIRECTION = false;
GLboolean       LEAVES_ON = false;
GLboolean       WALL_ON = false;
GLboolean       GROUND_ON = true;
GLboolean       ANTIALIASING_ON = true;
GLboolean       LIGHTING_ON = false;
GLboolean       READ_LEAVES = false;
GLboolean       drawed = false;
GLboolean       blackBackGround = false;

CTexture        text;

GLfloat lightx=1, lighty=3, lightz=2, lightw=0;
GLfloat lightZeroPosition[] = {lightx, lighty, lightz, lightw};
GLfloat lightPosition[] = {0,0,0,0};


int window1 = 0;
int window2 = 0;
int sub_window = 0;
int sub_window2 = 0;
/*
GLfloat cam_x;
GLfloat cam_y;
GLfloat cam_z;
*/
double cam_x_old=5.0;
double cam_y_old=0.0;
double cam_z_old=1.0;

int list_number=11;
int WINDOW_SIZE_X = 800;
int WINDOW_SIZE_Y = 600;

int WINDOW2_SIZE_X = 300;
int WINDOW2_SIZE_Y = 600;

int number_of_trees=1;

double mouse_x=WINDOW_SIZE_X/2;
double mouse_y=WINDOW_SIZE_Y/2;

//float dist=3, height=1.2, height_old=0; 
float xAngle=1, zAngle=20;

float x_move = 1;
float y_move = 0;
float z_move = 0;

int LEFT_BUTTON=UP;
int MIDDLE_BUTTON=UP;
int RIGHT_BUTTON=UP;
int head_xy=0;
float head_z=1.4;

int n_lea = 0;




vector<SmallCube> cubes;



void redrawAll()
{
  redraw();
 
}



// This function draws the picture
void redraw(void)
{
  float hx=0,hy=0, hz=0;  

 
  glutSetWindow(window1);
  //glLoadIdentity();
  if (blackBackGround)
    glClearColor(0.0, 0.0, 0.0, 1.0);
  else 
    glClearColor(1.0, 1.0, 1.0, 1.0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  

 
 
  glPushMatrix();
  setLight();
  glLoadIdentity();    
  check_values(); 
  
  
  // Check the camera coordinates 
  hx = cos(x_move*0.1*2*PI_VALUE/360) * 8;
  hy = sin(x_move*0.1*2*PI_VALUE/360) * 8;
  hz = hz + z_move * 0.01;

  //hx = 0;
  //hy = 0;
  //hz = 0.6;

  cam_x = (cam_x - hx) * 0.001 * y_move; // * cos(y_move*2*PI/360) * 0.01;
  cam_y = (cam_y - hy) * 0.001 * y_move; //cam_y + y_move * sin(y_move*2*PI/360) * 0.01;
  //cam_z = 1;

  

  gluLookAt (cam_x, cam_y, cam_z,      // camera x,y,z  
	     hx, hy, hz-cam_z,          // look at x,y,z    
	     0.0, 0.0, 1.0);           // which way up    

  
  setLight();

  
  if (glIsList(FOREST_LIST_STEMS))
    {
      glCallList(FOREST_LIST_STEMS);
      glCallList(FOREST_LIST_NEEDLES);
    }
  else
    {
      DrawTree();
      DrawBuds();
      DrawFoliage();
    }

  if (boolVisualizeVoxelSpace)
    if (voxel)
      {
	//	cout << "Visualization of VoxelSpace " << endl;
	voxel->draw(true);
      }

  //vanha tapa
  //if (boolShowVoxel)
  //  DrawVoxelCubes();  

  glPopMatrix();   
  glutSwapBuffers();        // Swap buffers  
  //glutPostRedisplay ();
}




void DrawVoxelCubes()
{
  int num = cubes.size();
  
  if (num == 0)
    {
      boolShowVoxel = false;
      return;
    }


  
  //cout << "kuutiota " << num << endl;
  vector<SmallCube> ordered_cubes;

  for (int i=0; i<num; i++)
    {
      SmallCube &cube = cubes[i];
      LGMdouble xx = cube.x_coord;
      LGMdouble yy = cube.y_coord;
      LGMdouble zz = cube.z_coord;
      cube.dist = pow(cam_x-xx, 2) + pow(cam_y-yy, 2) + pow(cam_z-zz, 2); 
      cube.ready = false;
     
    }


  
  for (int i = 0; i<num; i++)
    {
      int max_dist = -10;
      int mem_num = -1;
      int a = cubes.size();
      for (int ii=0; ii<a; ii++)
	{
	  SmallCube c = cubes[ii];
	  
	  if (c.ready == false)
	    {
	      
	      if (c.dist > max_dist)
		{
		  mem_num = ii;
		  
		  
		}
	    }
	}
     
      if (mem_num > -1)
	{
	  
	  SmallCube &c = cubes[mem_num];
	  c.ready = true;
	  ordered_cubes.push_back(c);
	}
    }

  glPushMatrix();
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_LINE);
  glDisable(GL_LIGHTING);
  
  glLineWidth(1);
  glColor3f(1,0.2,0.2);
  
  glBegin(GL_LINES);
  glVertex3f(0,0,0);
  glVertex3f(5,0,0);
  
  glVertex3f(0,0,0);
  glVertex3f(0,5,0);
  
  glVertex3f(0,0,0);
  glVertex3f(0,0,5);
  glEnd();
  
  glLineWidth(1);
  
  int s = ordered_cubes.size();
  // cout << "toinen koko " << s << endl;
  for (int i = 0; i< s; i++)
    {
      SmallCube cube = ordered_cubes[i];
     
      
      glColor3f(0.2,0.2,1);
      
      //puolikas sivusta
      float hedge = cube.edge * 0.5;

      // cout << "sivu " << hedge << endl;

      //pikkukuution keskipiste: 
      float xx = cube.x_coord;
      float yy = cube.y_coord;
      float zz = cube.z_coord;



      //  cout << xx << " " << yy << " " << zz << " " << hedge << endl;
      
      if (boolVoxelWithLines)
	{
	  
	  glBegin(GL_LINE_LOOP);
	  glVertex3f(xx+hedge, yy-hedge, zz+hedge);
	  glVertex3f(xx+hedge, yy+hedge, zz+hedge);
	  glVertex3f(xx+hedge, yy+hedge, zz-hedge);
	  glVertex3f(xx+hedge, yy-hedge, zz-hedge);
	  glEnd();
	  
	  glBegin(GL_LINE_LOOP);
	  glVertex3f(xx-hedge, yy-hedge, zz+hedge);
	  glVertex3f(xx-hedge, yy+hedge, zz+hedge);
	  glVertex3f(xx-hedge, yy+hedge, zz-hedge);
	  glVertex3f(xx-hedge, yy-hedge, zz-hedge);
	  glEnd();
	  
	  glBegin(GL_LINES);
	  glVertex3f(xx+hedge, yy-hedge, zz+hedge);
	  glVertex3f(xx-hedge, yy-hedge, zz+hedge);
	  glVertex3f(xx+hedge, yy+hedge, zz+hedge);
	  glVertex3f(xx-hedge, yy+hedge, zz+hedge);
	  
	  glVertex3f(xx+hedge, yy+hedge, zz-hedge);
	  glVertex3f(xx-hedge, yy+hedge, zz-hedge);
	  glVertex3f(xx+hedge, yy-hedge, zz-hedge);
	  glVertex3f(xx-hedge, yy-hedge, zz-hedge);
	  glEnd();
	}
      
      float shadow_odd = 0.1 + cube.areaden * (0.3 * pow((2*hedge),3)); 
      
      

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(0.0, 0.8, 0.0, shadow_odd);
      
      glBegin(GL_POLYGON);
      glVertex3f(xx-hedge, yy-hedge, zz+hedge);
      glVertex3f(xx-hedge, yy+hedge, zz+hedge);
      glVertex3f(xx-hedge, yy+hedge, zz-hedge);
      glVertex3f(xx-hedge, yy-hedge, zz-hedge);
      glEnd();
      
      glBegin(GL_POLYGON);
      glVertex3f(xx+hedge, yy-hedge, zz+hedge);
      glVertex3f(xx+hedge, yy-hedge, zz-hedge);
      glVertex3f(xx+hedge, yy+hedge, zz-hedge);
      glVertex3f(xx+hedge, yy+hedge, zz+hedge);
      glEnd();
      
      
      glBegin(GL_POLYGON);
      glVertex3f(xx-hedge, yy+hedge, zz-hedge);
      glVertex3f(xx-hedge, yy+hedge, zz+hedge);
      glVertex3f(xx+hedge, yy+hedge, zz+hedge);
      glVertex3f(xx+hedge, yy+hedge, zz-hedge);
      glEnd();
      
      glBegin(GL_POLYGON);
      glVertex3f(xx-hedge, yy-hedge, zz-hedge);
      glVertex3f(xx+hedge, yy-hedge, zz-hedge);
      glVertex3f(xx+hedge, yy-hedge, zz+hedge);
      glVertex3f(xx-hedge, yy-hedge, zz+hedge);
      glEnd();



      glBegin(GL_POLYGON);
      glVertex3f(xx-hedge, yy-hedge, zz-hedge);
      glVertex3f(xx-hedge, yy+hedge, zz-hedge);
      glVertex3f(xx+hedge, yy+hedge, zz-hedge);
      glVertex3f(xx+hedge, yy-hedge, zz-hedge);
      glEnd();
      
      glBegin(GL_POLYGON);
      glVertex3f(xx-hedge, yy-hedge, zz+hedge);
      glVertex3f(xx+hedge, yy-hedge, zz+hedge);
      glVertex3f(xx+hedge, yy+hedge, zz+hedge);
      glVertex3f(xx-hedge, yy+hedge, zz+hedge);
      glEnd();
      
      glDisable(GL_BLEND); 
    }

  glEnable(GL_LIGHTING);
  glPopMatrix();

}





// Function checks that the viewpoint is inside limits 
void check_values(void)
{ 
  /*
  if (zAngle > MAX_ANGLE)          
    zAngle=90;  
  if (zAngle < MIN_ANGLE)
    zAngle=0;  
  if (dist <  DISTANCE_MIN)     
    dist = DISTANCE_MIN;  
  if (dist >  DISTANCE_MAX)     
    dist =  DISTANCE_MAX;
  */
}





// This function is called when size of the window changes
void new_window_size (GLsizei new_x, GLsizei new_y)
{
  
  glutSetWindow(window1);

  glViewport (0, 0, new_x, new_y);
  WINDOW_SIZE_X = new_x;
  WINDOW_SIZE_Y = new_y;
  
  glMatrixMode (GL_PROJECTION);    // change to the projection matrix
  glLoadIdentity ();               // Start from a clear table
  
  gluPerspective (25.0,            // Width of field of view 
                  new_x/new_y,     // Shape of new view 
                  .1,              // Shortest visible distance 
                  52);             // Longest visible distance 
  
		  
  glMatrixMode (GL_MODELVIEW);     // change to the modelview matrix
}



// This function quits the program
void quit (void)
{
  exit (0);
}




void arrows(int key, int x, int y)
{
  /*
	if (key == GLUT_KEY_UP)
    {
      gus.v.clear();
      gus.v.insert(gus.v.end(), current);
      gus.flag = 0;      
      gus = Accumulate(digi_tree, gus, GetUpperSegment<Lignum::BetulaWithFlow, 
		       DefaultBud<Lignum::BetulaWithFlow> >());
      
      if (gus.v.size() > 1)
	{
	  current = gus.v[1];
	  
	}
      redrawAll();
    }
  if(key == GLUT_KEY_RIGHT)
    {  
      
      if (gus.v.size() > 1)
	{
	  current_axis++;
	  if (gus.v.size() == current_axis)
	    current_axis = 0;
	  current = gus.v[current_axis];
	  redrawAll();
	}
    }
  if(key == GLUT_KEY_LEFT)
    {
      
      if (gus.v.size() > 1)
	{
	  current_axis--;
	  if (current_axis < 0)
	    current_axis = gus.v.size()-1;
	  current = gus.v[current_axis];
	  redrawAll();
	}
    }
  if (key == GLUT_KEY_DOWN)
    {
      GLS<Lignum::BetulaWithFlow, DefaultBud<Lignum::BetulaWithFlow> > gls;
      gls.current = current;
      gls = Accumulate(digi_tree, gls, GetLowerSegment<Lignum::BetulaWithFlow, 
		       DefaultBud<Lignum::BetulaWithFlow> >());
      if (gls.segment != NULL)
	{
	  current = gls.segment;	  
	  redrawAll();
	} 
      gus.v.clear();
      gus.v.insert(gus.v.end(), current);
      gus.flag = 0;      
      gus = Accumulate(digi_tree, gus, GetUpperSegment<Lignum::BetulaWithFlow, 
		       DefaultBud<Lignum::BetulaWithFlow> >());
    }
	*/
}


// This function is called when a key is pressed
void keypress(unsigned char key, int x, int y)
{
  
  switch(key) {
  
  

  
  case 'q': quit();             // q to quit  
    break;
    
  case 'a': lightx++;           // Move the light source 
    redraw();
    break;    
  case 'z': lightx--;
    redraw();
    break;    
  case 's': lighty++;   
    redraw();
    break;
        
  case 'x': lighty--;   
    redraw();
    break;    
  case 'd': lightz++;   
    redraw();

    break;
  case 'c': lightz--;  
    redraw();
    break;
 
  case '4': head_xy--;          // Turn head
    redraw();
   break;    
  case '6': head_xy++;
    redraw();
    break;
  case '2': cam_z = cam_z - .5;//head_z = head_z - .1;
    redraw();
    break;    
  case '8': cam_z = cam_z + .5;//;head_z = head_z + .1;
    redraw();
    break;
  case '5': cam_z =  1; //head_z = 0.5;         // Reset values
    head_xy = 0;
    redraw();
    break;

  default:printf("%c",key);fflush(NULL);
  }
}




// This function is called when a mouse value is changed
void mouse_button(int button, int state, int x, int y)
{
  MIDDLE_BUTTON=UP;
  RIGHT_BUTTON=UP;
  LEFT_BUTTON=UP; 

  switch(button) {
  case GLUT_LEFT_BUTTON:    // Left button is pressed
    mouse_x=0;
    mouse_y=0;   
    LEFT_BUTTON=DOWN;
    MOVEMENT=true;
    break;

  case GLUT_MIDDLE_BUTTON:  // Middle button is pressed
    mouse_x=0;
    mouse_y=0;
    MIDDLE_BUTTON=DOWN;
    MOVEMENT=true;
    break;
  
  default:
    break;
  }
}


// This function is called when mouse moves. The movement is in parametres x and y. 
void mouse_motion(int x, int y)
{
  MOVEMENT=true;
  
      
      
  if (mouse_x != 0 || mouse_y != 0) // If movement has just begun, write the
    {                               // values down  
      if (MIDDLE_BUTTON == DOWN && mouse_y != y)        // Middle button is pressed 
	{                               
	  z_move = z_move + (mouse_y-y);
	  drawed = false;
	}
     
      if (MIDDLE_BUTTON == DOWN && mouse_x != x)        // Middle button is pressed 
	{                               
	  cam_z += (mouse_x - x)/100.0;
	  drawed = false;
	}

      // Left button is pressed
      if (LEFT_BUTTON == DOWN && (mouse_x != x || mouse_y != y))  
	{    
	  x_move = x_move + (mouse_x-x);
	  y_move = y_move - (mouse_y-y);
	  drawed = false;
	}        
    }    
  mouse_x=x;
  mouse_y=y;
}





// This funtion is called, when nothing happens. 
void loop(void) 
{ 
  if (MOVEMENT == true) // If movement has just stopped the picture is drawn once
    { 
      MOVEMENT = false;
      redrawAll();          
      return;
    }
  /*
  if (!drawed)
    {
      redraw();
      drawed = true;
    }
  */
}






// This function is called when the menu is used
void menu(int value)
{ 
  switch(value)
    { 
    case 1:
      boolShowVoxel = !boolShowVoxel;
      cout << "Voxel on/off" << endl;
      redraw();
      break;

    case 2:
      boolVoxelWithLines = !boolVoxelWithLines;
      cout << "Voxel lines on/off " << endl;
      redraw();
      break;

    case 13:
      glutSetWindow(window1);
      screenShot ("shot.tga", WINDOW_SIZE_X, WINDOW_SIZE_Y);
      break;
    
    case 14:
      LEAVES_ON = !LEAVES_ON;
      redraw();
      break;

    case 15:
      TEXTURES_ON = !TEXTURES_ON;
      redraw();
      break;

    case 16:
      blackBackGround = !blackBackGround;
      redraw();
      break;

    } 
}




// Init the window and handling of events
void init_window () //int argc, char** argv)
{
  
  glutInitDisplayMode (GLUT_DOUBLE |          // Double buffering        
                       GLUT_RGB |             // RGBA- color mode
                       GLUT_DEPTH);           // Depth buffering

 

  glutInitWindowPosition (400, 20);          // Window size and place
  glutInitWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);    
  window1 = glutCreateWindow ("Window"); //argv[0]);                 // Open a window    
  glutReshapeFunc(new_window_size);          // Call this function if the size is changed  
  glutKeyboardFunc(keypress);                // Call this funktion when a key is pressed 
  glutMouseFunc (mouse_button);                      // Mouse events
  glutMotionFunc(mouse_motion);
  glutIdleFunc (loop);                        // This is called when nothing happens
  glutSpecialFunc(arrows);
  glutDisplayFunc(redraw);                    // The draw-function
  glutCreateMenu(menu);                          // Make the menu
 
  glutAddMenuEntry("Leaves on/off__________________", 14);
  glutAddMenuEntry("Textures on/off_________________", 15);
  glutAddMenuEntry("VoxelSpace on/off_______________", 1);
  glutAddMenuEntry("VoxelSpace with lines on/off____", 2);
 

  glutAddMenuEntry("Change background color______________", 16);
  glutAddMenuEntry("Write image", 13);
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);  
  glEnable (GL_DEPTH_TEST); 
  //glEnable (GL_CULL_FACE); //
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the screen 

}




// This function inits the lightning
void setLight(void)
{     
  GLfloat mat_amb[] = {.4,.4,.2,1};
  
  GLfloat lightPosition[] = {lightx, lighty, lightz, lightw};

  //cout << "valo " << lightx <<lighty << lightz <<  lightw << endl;
  glLightfv (GL_LIGHT0, GL_POSITION, lightPosition);
  // glLightfv (GL_LIGHT0, GL_AMBIENT, mat_amb); 
  glEnable (GL_LIGHT0);
  glEnable (GL_LIGHTING);
  
}






/*

void make_leave(float lSize, float angle)
{  
  GLfloat mat_amb[] = { 0.2, 1, 0.2, 1.0 }; 
  GLfloat mat_dif[] = { 0.2, 1, 0.2, 1.0 }; 

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb); 
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);

  
  float leave_size = sqrt(lSize / 800.0) * LEAVE_SIZE;
 

  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, PETIOLE_SIZE/100, 0.0); 
  glEnd();


  glBegin(GL_POLYGON);
  glNormal3f(0,0,1); 
  for (int i=0; i<LEAVE_VERT; i++)  
    {
      glVertex3f(leave[i][0]/leave_size, leave[i][1]/leave_size+PETIOLE_SIZE/100, 0);
      glTexCoord2f(leave[i][0]/TEXT_ODD,leave[i][1]/TEXT_ODD);
    }    
  glEnd();
  
  glBegin(GL_POLYGON); 
  glNormal3f(0,0,1);
  for (i=0; i<LEAVE_VERT; i++)
    {
      int ii = LEAVE_VERT - i - 1;
      glVertex3f(-leave[ii][0]/leave_size, leave[ii][1]/leave_size+PETIOLE_SIZE/100, 0); 
      glTexCoord2f(-leave[ii][0]/TEXT_ODD,leave[ii][1]/TEXT_ODD);
    }  
  glEnd();
  
}






void make_stem()
{
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  //glColor3f(1,1,1);
  Axis<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >& axis = GetAxis(digi_tree);
  TraverseAxis(axis, 1); 
  glDisable(GL_COLOR_MATERIAL);
}





void make_petiole()
{
  
}
*/ 




        

















void CTexture::Load(char *filename, int fw, int fh)
{
  cout << "Ladataan tekstuuri " << endl;

  FILE *f;

  data = new char[(fw*fh)*3+54];
  f = fopen(filename, "rb");
  fseek(f, 54, SEEK_SET);
  fread(data, 1, (fw*fh)*3+54, f);
  fclose(f);
  w = fw;
  h = fh;
  
  glGenTextures(1, &texturenum);

  glBindTexture(GL_TEXTURE_2D, texturenum);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
}

void CTexture::use()
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texturenum);
}

void CTexture::do_not_use()
{
  
  glDisable(GL_TEXTURE_2D);
}

///////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS



void initTextures()
{
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
  glEnable(GL_TEXTURE_2D);
}





void makeDigiTree()
{
}


void LoadImage(char *filename) {
    static unsigned *image;
    static int width, height, components;
    if (filename) {
        image = read_texture(filename, &width, &height, &components);
        if (image == NULL) {
            fprintf(stderr, "Error: Can't load image file \"%s\".\n",
                    filename);
            exit(EXIT_FAILURE);
        } else {
            printf("%d x %d image loaded\n", width, height);
        }
        if (components != 4) {
            printf("must be an RGBA image\n");
            exit(EXIT_FAILURE);
        }
    } else {
        int i, j;
        unsigned char *img;
        components = 4; width = height = 256;
        image = (unsigned *) malloc(width*height*sizeof(unsigned));
        img = (unsigned char *)image;
        for (j = 0; j < height; j++)
            for (i = 0; i < width; i++) {
                int w2 = width/2, h2 = height/2;
                if ((i & 32) ^ (j & 32)) {
                    img[4*(i+j*width)+0] = 0xff;
                    img[4*(i+j*width)+1] = 0xff;
                    img[4*(i+j*width)+2] = 0xff;
                } else {
                    img[4*(i+j*width)+0] = 0x0;
                    img[4*(i+j*width)+1] = 0x0;
                    img[4*(i+j*width)+2] = 0x0;
                }
                if ((i-w2)*(i-w2) + (j-h2)*(j-h2) > 64*64 &&
                    (i-w2)*(i-w2) + (j-h2)*(j-h2) < 300*300) img[4*(i+j*width)+3] = 0xff;
            }

    }
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image);
    glEnable(GL_TEXTURE_2D);
}



void InitGraphics()
{
  InitDrawing();
  InitOpenGL();
  init_window();
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
}



void ForestStemsBegin()
{
  glNewList(FOREST_LIST_STEMS, GL_COMPILE);
 
}

void ForestNeedlesBegin()
{
  glNewList(FOREST_LIST_NEEDLES, GL_COMPILE);
 
}


void ForestEnd()
{
  glEndList();
}


void UseBmpTexture(char *filename)
{
  CTexture tex;
  tex.Load(filename, 512, 512);
  tex.use();
}

void UseTgaTexture(char *filename)
{
  char buff[15];
  tga_t image;
  
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
 
  int num = image.GenId(); // let OpenGL give us a texture id
  image.Load(filename, num);

  cout << "Loading tga-texture!!!!!!!!!!!!!!!!!!!!!!!!!! " << filename << endl;

  glBindTexture(GL_TEXTURE_2D,num);
}


void AddVoxelSpaceToVisualization(VoxelSpace *vs)
{
  boolVisualizeVoxelSpace = true;
  voxel = vs;
}

void StartVisualization()
{
  glutMainLoop ();
}

#include "OpenGLUnixI.h"



