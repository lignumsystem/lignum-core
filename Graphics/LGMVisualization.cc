#include <stdafx.h>

#include <LGMVisualization.h>

#if defined( APPLE ) || defined(MACOSX)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/gl.h>
#endif



namespace Lignum
{

LGMVisualization::LGMVisualization()
{
}


void LGMVisualization::InitVisualization()
{
	glClearColor(0.9f, 0.9f, 0.9f, 0.9f);

	glLightfv(GL_LIGHT0, GL_POSITION, settings.light.LightPosition);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glShadeModel(GL_SMOOTH);
}


void LGMVisualization::SetAntialising(bool antialisingOn)
{
	
}


void LGMVisualization::AddScotsPine(Tree<ScotsPineVisual, ScotsBud> *tree)
{
	scotspine.push_back(tree);
}



void LGMVisualization::DrawScotsPine(Tree<ScotsPineVisual, ScotsBud> &tree, DRAWMODE mode)
{
  if (mode == STEM_MODE) //runko
    {
      GLfloat mat_amb[] = { 0.2, 0.3, 0.4, 1.0 }; 
      GLfloat mat_dif[] = { 0.2, 0.4, 0.4, 1.0 }; 
  
      GLfloat mat_amb2[] = { 1.0, 0.5, 0.4, 1.0 }; 
      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb); 
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);     

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);  
  
      glDisable(GL_LIGHTING);
      DrawStemFunctorTree<ScotsPineVisual, ScotsBud> stemfunctor;
      stemfunctor.min_rad = -99;
      stemfunctor.max_rad = 999;
      ForEach(tree, stemfunctor);
    }
  
  if (mode == FOLIAGE_MODE) //neulaset
    {
      glEnable(GL_BLEND);
      //UseTextures();
      DrawNeedlesFunctor<Tree<ScotsPineVisual, ScotsBud> needles_functor;

      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDisable(GL_LIGHTING);
      
      glPushMatrix();
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);  
      ForEach(tree, needles_functor); 
      glCullFace(GL_BACK); 
      ForEach(tree, needles_functor); 
      
      glDisable(GL_CULL_FACE);
      glPopMatrix();    
    
      glDisable(GL_BLEND);
         
    }
}



//Draw-funktions
void LGMVisualization::CountCamera(void)
{
	//OpenGLinterface
}


void LGMVisualization::SetLight(void)
{
	GLfloat mat_amb[] = {.4,.4,.2,1};
  
	GLfloat lightPosition[] = {lightx, lighty, lightz, lightw};

	glLightfv (GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable (GL_LIGHT0);
	glEnable (GL_LIGHTING);
}


void LGMVisualization::SetValues(void)
{
	//OpenGLinterface
}

void LGMVisualization::CheckValues(void)
{
	//Arvojen tarkastus jos haluaa rajoituksia
}


void LGMVisualization::ReDrawWindow(void)
{
  float hx=0,hy=0, hz=0;  

 
  glutSetWindow(settings.window1);
  
  if (settings.blackBackGround)
    glClearColor(0.0, 0.0, 0.0, 1.0);
  else 
    glClearColor(1.0, 1.0, 1.0, 1.0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  

 
 
  glPushMatrix();
  glLoadIdentity(); 
  SetLight();
  CheckValues(); 
  
  
  // Check the settings.camera coordinates 
  hx = cos(settings.x_move*0.1*2*PI_VALUE/360) * 8;
  hy = sin(settings.x_move*0.1*2*PI_VALUE/360) * 8;
  hz = hz + settings.z_move * 0.01;

  //hx = 0;
  //hy = 0;
  //hz = 0.6;

  settings.settings.cam_x = (settings.settings.cam_x - hx) * 0.001 * settings.y_move; 
  settings.settings.cam_y = (settings.settings.cam_y - hy) * 0.001 * settings.y_move; 
  //settings.cam_z = 1;

  

  gluLookAt(settings.cam_x, settings.cam_y, settings.cam_z,         // settings.camera x,y,z  
			hx, hy, hz-settings.cam_z,								// look at x,y,z    
			0.0, 0.0, 1.0);											// which way up    

  
 

  //Drawing
  /*
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
*/



  glPopMatrix();   
  glutSwapBuffers();        // Swap buffers  
  //glutPostRedisplay ();
}



void LGMVisualization::NewWindowSize(GLsizei new_x, GLsizei new_y)
{
  glutSetWindow(window1);

  glViewport (0, 0, new_x, new_y);
  settings.WINDOW_SIZE_X = new_x;
  settings.WINDOW_SIZE_Y = new_y;
  
  glMatrixMode (GL_PROJECTION);    // change to the projection matrix
  glLoadIdentity ();               // Start from a clear table
  
  gluPerspective (25.0,            // Width of field of view 
                  new_x/new_y,     // Shape of new view 
                  .1,              // Shortest visible distance 
                  52);             // Longest visible distance 
  
		  
  glMatrixMode (GL_MODELVIEW);     // change to the modelview matrix	
}


// This function quits the program
void LGMVisualization::Quit (void)
{
  exit (0);
}


//Näppäin kutsut
void LGMVisualization::Arrows(int key, int x, int y)
{
}



// This function is called when a key is pressed
void LGMVisualization::Keypress(unsigned char key, int x, int y)
{
  switch(key) {
  
  case 'q': Quit();             // q to quit  
    break; 
  case 'a': settings.lightx++;           // Move the light source 
    ReDraw();
    break;    
  case 'z': settings.lightx--;
    ReDraw();
    break;    
  case 's': settings.lighty++;   
    ReDraw();
    break;       
  case 'x': settings.lighty--;   
    ReDraw();
    break;    
  case 'd': settings.lightz++;   
    ReDraw();
    break;
  case 'c': settings.lightz--;  
    ReDraw();
    break;
  case '4': settings.head_xy--;          // Turn head
    ReDraw();
   break;    
  case '6': settings.head_xy++;
    ReDraw();
    break;
  case '2': settings.cam_z = settings.cam_z - .5;
    ReDraw();
    break;    
  case '8': settings.cam_z = settings.cam_z + .5;//
    ReDraw();
    break;
  case '5': settings.cam_z =  1; //Reset values
    settings.head_xy = 0;
    ReDraw();
    break;

  default:printf("%c",key);fflush(NULL);
  }
}



// This function is called when a mouse value is changed
void LGMVisualization::ChangeMouseButton(int button, int state, int x, int y)
{
  settings.MIDDLEBUTTON=UP;
  settings.RIGHTBUTTON=UP;
  settings.LEFTBUTTON=UP; 

  switch(button) {
  case GLUT_LEFT_BUTTON:    // Left button is pressed
    settings.mouse_x=0;
    settings.mouse_y=0;   
    settings.LEFTBUTTON=DOWN;
    MOVEMENT=true;
    break;

  case GLUT_MIDDLE_BUTTON:  // Middle button is pressed
    settings.mouse_x=0;
    settings.mouse_y=0;
    settings.MIDDLEBUTTON=DOWN;
    MOVEMENT=true;
    break;
  
  default:
    break;
  }
}



void LGMVisualization::MouseMotion(int x, int y)
{
  settings.MOVEMENT=true;
       
      
  if (settings.mouse_x != 0 || settings.mouse_y != 0) // If movement has just begun, write the
    {                               // values down  
      if (settings.MIDDLEBUTTON == DOWN && settings.mouse_y != y)        // Middle button is pressed 
	{                               
	  settings.z_move = settings.z_move + (settings.mouse_y-y);
	  drawed = false;
	}
     
      if (settings.MIDDLEBUTTON == DOWN && settings.mouse_x != x)        // Middle button is pressed 
	{                               
	  settings.cam_z += (settings.mouse_x - x)/100.0;
	  drawed = false;
	}

    // Left button is pressed
    if (settings.LEFTBUTTON == DOWN && (settings.mouse_x != x || settings.mouse_y != y))  
	{    
	  settings.x_move = settings.x_move + (settings.mouse_x-x);
	  settings.y_move = settings.y_move - (settings.mouse_y-y);
	  drawed = false;
	}        
    }    
  settings.mouse_x=x;
  settings.mouse_y=y;
}


void LGMVisualization::Loop(void) 
{ 
  if (settings.MOVEMENT == true) // If movement has just stopped the picture is drawn once
    { 
      settings.MOVEMENT = false;
      ReDraw();          
      return;
    }
}


void LGMVisualization:Menu(int value)
{ 
  switch(value)
    { 
    case 1:
      settings.show_voxel_on = !settings.show_voxel_on;
      cout << "Voxel on/off" << endl;
      ReDraw();
      break;

    case 2:
      settings.boolVoxelWithLines = !settings.boolVoxelWithLines;
      cout << "Voxel lines on/off " << endl;
      ReDraw();
      break;

    case 13:
      glutSetWindow(window1);
      screenShot ("shot.tga", WINDOW_SIZE_X, WINDOW_SIZE_Y);
      break;
    
    case 14:
      settings.foliage_on = !settings.foliage_on;
      ReDraw();
      break;

    case 15:
      settings.textures_on = !settings.textures_on;
      ReDraw();
      break;

    case 16:
      settings.blackBackGround = !settings.blackBackGround;
      ReDraw();
      break;

    } 
}

void LGMVisualization::InitCallBacks() 
{
  
  glutInitDisplayMode (GLUT_DOUBLE |          // Double buffering        
                       GLUT_RGB |             // RGBA- color mode
                       GLUT_DEPTH);           // Depth buffering

 

  glutInitWindowPosition (400, 20);          // Window size and place
  glutInitWindowSize(settings.WINDOW_SIZE_X, settings.WINDOW_SIZE_Y);    
  window1 = glutCreateWindow ("Window"); //argv[0]);                 // Open a window    
  glutReshapeFunc(NewWindowSize);          // Call this function if the size is changed  
  glutKeyboardFunc(KeyPress);                // Call this funktion when a key is pressed 
  glutMouseFunc (ChangeMouseButton);                      // Mouse events
  glutMotionFunc(MouseMotion);
  glutIdleFunc (Loop);                        // This is called when nothing happens
  glutSpecialFunc(Arrows);
  glutDisplayFunc(ReDraw);                    // The draw-function
  glutCreateMenu(Menu);                          // Make the menu
 
  glutAddMenuEntry("Leaves on/off__________________", 14);
  glutAddMenuEntry("Textures on/off_________________", 15);
  glutAddMenuEntry("VoxelSpace on/off_______________", 1);
  glutAddMenuEntry("VoxelSpace with lines on/off____", 2);
 

  glutAddMenuEntry("Change background color______________", 16);
  glutAddMenuEntry("Write image", 13);
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);  
  glEnable (GL_DEPTH_TEST); 
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the screen 
}


}