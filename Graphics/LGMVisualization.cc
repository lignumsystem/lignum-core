#include <stdafx.h>

#include <LGMVisualization.h>

using namespace Lignum;

LGMVisualization* LGMVisualization::active_visualization = NULL;

#if defined(__APPLE__) || defined(__MACOSX__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif


namespace Lignum
{

  void LGMTextOutput(double x, double y, double z,void* font,const string& str){
    int len, i;
  
    glRasterPos3f(static_cast<float>(x), static_cast<float>(y),
		  static_cast<float>(z));
    len = static_cast<int>(str.size());
    for (i = 0; i < len; i++) {
      glutBitmapCharacter(font, str[i]);
    }
  }

  LGMVisualization::LGMVisualization()
    :mode(SOLID),order_foliage(false),
     ShowTree(-1),ldistance(100),max_height(0.0),camera_distance(0.0),
     show_tree_metrics(0),show_help(1),help_str("a=Apua/h=Help")
  {
    help_fi="n=Seuraava, m=Kierros, b=Mitat, z=Eteen, x=Taakse, c=Ylos, v=Alas, s=Vasen, d=Oikea, r=Alku, q=Lopeta, a=Apua, h=Help";
    help_en="n=Next, m=Rotate, b=Metrics, z=Forward, x=Backwards, c=Up, v=Down, s=Left, d=Right, r=Reset, q=Quit, a=Apua, h=Help";
    active_visualization = this;
  }
  

  void LGMVisualization::SetVisibleDistance(double l)
  {
    ldistance = l;
  }  
    
    void LGMVisualization::InitVisualization(int argc,char* argv[])
    {
	glutInit(&argc,argv);
	glutInitWindowSize(settings.WINDOW_SIZE_X,settings.WINDOW_SIZE_Y);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	
	//A nice  title with the  program name only: the  program name
	//can contain A-Z,a-z,0-9, also '-' and '_' are accepted. Stop
	//when  e.g. '/' is  seen as  denoting the  previous directory
	//level.
	string s(argv[0]);
	string n;
	int i = s.size()-1;
	while (i && (isalnum(s[i]) || s[i] == '-' || s[i] == '_')){
	  n.insert(n.begin(),s[i]);
	  i--;
	}
	settings.window1 = glutCreateWindow(n.c_str());
	
	InitCallBacks(); 
	SetLight();   
	glClearColor(0.9f, 0.9f, 0.9f, 0.9f);
	glLightfv(GL_LIGHT0, GL_POSITION, settings.light.LightPosition);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glShadeModel(GL_SMOOTH);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	
	
	InitDrawing();
    }
    
    void LGMVisualization::ResetCameraPosition(float height)
    { 
	settings.cam_x = -height*4;
	settings.cam_y = 0;
	settings.cam_z = height/2;   
    }
    
    void LGMVisualization::StartVisualization()
    {
      //If there are no  trees, return. Otherwise the subsequent calls
      //to  for_each  will  cause  segmentation faults.   Both  assume
      //(implicitely) that 'trees' has at least one element (a wrapper
      //pointer capturing a tree).
      if (trees.size() == 0)
	return;

      if (mode == SOLID)
	{
	  for_each(trees.begin(),trees.end(),MakeDisplayLists(order_foliage));
	}
      else
	{
	    for_each(trees.begin(),trees.end(), MakeWireModelLists());
	}
      GoNextTree();
      glutMainLoop ();
    }
    
    
    
    
    void LGMVisualization::SetAntialising(bool antialisingOn)
    {
	
    }
    
    
    
    //Draw-funktions
    void LGMVisualization::CountCamera(void)
    {
	//OpenGLinterface
    }
    
    
    void LGMVisualization::SetLight(void)
    {
	GLfloat mat_amb[] = {.4,.4,.2,1};
	
	GLfloat lightPosition[] = {settings.lightx, settings.lighty, 
				   settings.lightz, settings.lightw};
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
    
    void LGMVisualization::ReDraw(void)
    {
	ReDrawWindow();

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
	// SetLight();
	CheckValues(); 
	
	
	// Check the settings.camera coordinates 
	hx = cos(settings.x_move*0.1*2*PI_VALUE/360) * 8;
	hy = sin(settings.x_move*0.1*2*PI_VALUE/360) * 8;
	hz = hz + settings.z_move * 0.01;
	
	
	settings.cam_x = settings.cam_x + (settings.cam_x - hx) * 0.001 * settings.y_move; 
	settings.cam_y = settings.cam_y + (settings.cam_y - hy) * 0.001 * settings.y_move; 
	//settings.cam_z = 1;   


	
	gluLookAt(settings.cam_x, settings.cam_y, settings.cam_z,// settings.camera x,y,z  
		  settings.lookat_x, settings.lookat_y, settings.lookat_z, // look at x,y,z    
		  0.0, 0.0, 1.0);	// which way up    
	
	drawTrees();
	if (show_tree_metrics)
	  for_each(trees.begin(),trees.end(),DrawTreeMetrics());
	if (show_help){
	  //Set the help_str in front of the camera
	  Point p1(settings.cam_x, settings.cam_y, settings.cam_z);
	  Point p2(settings.lookat_x,settings.lookat_y,settings.lookat_z);
	  //Direction from camera to point of focus
	  PositionVector d1(p2-p1);
	  d1.normalize();
	  //10 units away from camera towards the point of focus
	  Point p3 = p1+10.0*(Point)d1;
	  PositionVector d2(p3);
	  //Move help_str a bit to the left
	  d2.rotate(p1,PositionVector(0,0,1),0.19);
	  //and down
	  LGMTextOutput(d2.getX(),d2.getY(),d2.getZ()-2.0,
			GLUT_BITMAP_HELVETICA_12,help_str);
	}
	glPopMatrix(); 
	glutSwapBuffers();        // Swap buffers  
	glutPostRedisplay ();
	glFlush();
    }
    
    
    
    void LGMVisualization::NewWindowSize(GLsizei new_x, GLsizei new_y)
    {
	glutSetWindow(settings.window1);
	
	glViewport (0, 0, new_x, new_y);
	settings.WINDOW_SIZE_X = new_x;
	settings.WINDOW_SIZE_Y = new_y;
	
	glMatrixMode (GL_PROJECTION);    // change to the projection matrix
	glLoadIdentity ();               // Start from a clear table
	
	gluPerspective (25.0,            // Width of field of view 
			new_x/new_y,     // Shape of new view 
			.1,              // Shortest visible distance 
			ldistance);             // Longest visible distance 
	
	
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
    
    
    void LGMVisualization::GoNextTree()
    {
      Point p;
      LGMdouble h=0.0;
      //Initially  this sets  the  camera to  look at  Point(x,y,h/2),
      //where x and  y is the position of the middle  tree in the list
      //of trees and  'max_height' is height of the  tallest tree. (If
      //there is  one tree,  the indexing returns  0). This  lines the
      //trees from the left part of  the window to the right aiming to
      //achieve overall centering appearance.
      if (ShowTree == -1){
	double transfer = 0.0;
	if (camera_distance > R_EPSILON){
	  //camera distance is given
	  transfer = camera_distance;
	}
	else{
	  //This should show the largest tree
	  transfer = max_height*2.3;
	}
	WrapperBase *middle_tree = trees[static_cast<int>(floor(trees.size()/2.0))];
	middle_tree->GetTreeMetrics(p,h);
	//This  will set  the camera  position.  Especially  cam_x and
        //cam_y set the distance from the tree. cam_z is the camera height
        settings.cam_x = p.getX()+transfer; //move away from the tree
        settings.cam_y = 0.0;//set y to 0,  this however is ideal only
			     //when  the trees are  lined up  e.g.  as
			     //(0,y1,0),  (0,y2,0),...,  (0,yN,0).  If
			     //there  is  a  forest  with  practically
			     //random tree  positions, one should move
			     //outside the forest, or go in the forest
			     //and let the camera turn 360.
        settings.cam_z = max_height/2.0;
	//Look at the first tree
	settings.lookat_x = p.getX();
	settings.lookat_y = p.getY();
	settings.lookat_z = max_height/2.0;
      }
      //Otherwise set one  tree at a time to the  center of the window
      //and go  so close  to it  that the tree  is visible  its height
      //matching the height of the window
      else{
	WrapperBase *tree = trees[ShowTree];
	tree->GetTreeMetrics(p, h);
	//This  will set  the camera  position.  Especially  cam_x and
	//cam_y set the distance from the tree. By experimenting a bit
	//h*2.3 and h/2.0 seems to  show the whole tree (of all sizes)
	//in the window.  But consult also Mika.
	settings.cam_x = p.getX()+h*2.3;
	settings.cam_y = p.getY()+h/2.0; 
	settings.cam_z = h/2.0;
	//Look at the current tree 
	settings.lookat_x = p.getX();
	settings.lookat_y = p.getY();
	settings.lookat_z = h/2.0;
      }
      ReDraw();
      //Reset to intial view
      if (ShowTree == trees.size() - 1){
	ShowTree = -1;
      }
      //ShowTree modulo trees.size() rotates the current tree
      else{
	ShowTree = (ShowTree+1) % trees.size();
      }
    }
    
  //Zoom in (dir=1) and out (dir=-1)
  void LGMVisualization::Zoom(int dir)
  {
    Point p1(settings.cam_x,settings.cam_y,settings.cam_z);
    Point p2(settings.lookat_x,settings.lookat_y,settings.lookat_z);
    PositionVector d1(p2-p1);
    d1.normalize();
    Point p3 = p1+3.0*dir*(Point)d1;
    Point p4 = p2+3.0*dir*(Point)d1;
    settings.cam_x = p3.getX();
    settings.cam_y = p3.getY();
    settings.cam_z = p3.getZ();
    settings.lookat_x = p4.getX();
    settings.lookat_y = p4.getY();
    settings.lookat_z = p4.getZ();
  }
  //Up/down and left/right camera movement and the point of focus
  void LGMVisualization::Translate(PositionVector& d1)
  {
    Point p1(settings.cam_x,settings.cam_y,settings.cam_z);
    Point p2(settings.lookat_x,settings.lookat_y,settings.lookat_z);
    d1.normalize();
    Point p3 = p1+1.0*(Point)d1;
    Point p4 = p2+1.0*(Point)d1;
    settings.cam_x = p3.getX();
    settings.cam_y = p3.getY();
    settings.cam_z = p3.getZ();
    settings.lookat_x = p4.getX();
    settings.lookat_y = p4.getY();
    settings.lookat_z = p4.getZ();
  }

  void LGMVisualization::StartAnimation()
  {
    Point p;
    double h;
    //Now that we have all the translations, it is quite possible that
    //the  point of focus  is no  longer the  ShowTree tree.   Make it
    //so. The logic  here is to assume that the  user has selected the
    //tree of  interest with  'n' and has  moved closer. Now  the user
    //wants to  rotate round the  tree.  In GoNextTree()  ShowTree has
    //already  increased ShowTree  so  it is  ShowTree-1  the user  is
    //looking at.
    WrapperBase *tree = NULL;
    if (ShowTree == -1)
      tree = trees[trees.size()-1];
    else if (ShowTree == 0)//One tree case and/or coming from reset in
			   //several  trees case.  Look at  the middle
			   //tree as in the beginning.
      tree = trees[static_cast<int>(floor(trees.size()/2.0))];
    else
      tree = trees[ShowTree-1];
    tree->GetTreeMetrics(p, h);

    //Look at the current tree 
    settings.lookat_x = p.getX();
    settings.lookat_y = p.getY();

    double dx = settings.lookat_x - settings.cam_x;
    double dy = settings.lookat_y - settings.cam_y;
    double dz = settings.lookat_z - settings.cam_z;

    double dist = sqrt(dx*dx+dy*dy);

    for (float ii=0; ii<36; ii++)
      {
	    
	settings.cam_z = settings.lookat_z;

	settings.cam_y = settings.lookat_y + sin(ii/36.0*2*PI_VALUE)*dist;
	settings.cam_x = settings.lookat_x + cos(ii/36.0*2*PI_VALUE)*dist;
	  
	ReDraw();
      }
  }


    
    void LGMVisualization::RedrawMovement(double odd)
    {
	double x1,y1,z1,x2,y2,z2;
	GetCameraPos(x1,y1,z1,x2,y2,z2, odd);
	
	glutSetWindow(settings.window1);
	
	if (settings.blackBackGround)
	    glClearColor(0.0, 0.0, 0.0, 1.0);
	else 
	    glClearColor(1.0, 1.0, 1.0, 1.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	glLoadIdentity(); 
	CheckValues(); 
	
	
	
	gluLookAt(x1,y1,z1, // settings.camera x,y,z  
		  x2,y2,z2, // look at x,y,z    
		  0.0, 0.0, 1.0);	// which way up    
	
	drawTrees();
	
	glPopMatrix();   
	glutSwapBuffers();        // Swap buffers  
	glutPostRedisplay ();
    }
    
    
    void LGMVisualization::GetCameraPos(double &x1, double &y1, double &z1,
					double &x2, double &y2, double &z2,
					double odd)
    {
	if (ShowTree == -1) 
	    return;
	
	WrapperBase *tree = trees[ShowTree];
	Point p;
	LGMdouble h;
	tree->GetTreeMetrics(p,h);
	
	z1 = h / 2.0;
	z2 = h/2.0;
	
	float dx = sin(2*PI_VALUE*odd/1.0)*3.0*h;
	float dy = cos(2*PI_VALUE*odd/1.0)*3.0*h;
	
	x1 = p.getX() + dx;
	y1 = p.getY() + dy;
	
	x2 = p.getX();
	y2 = p.getY();
/*
  float l = sqrt(x2*x2+y2*y2);
  x2 = x2 / l;
  y2 = y2 / l;*/
    }
    
    
    
    
    
    
  // This function is called when a key is pressed
  void LGMVisualization::Keypress(unsigned char key, int x, int y)
  {
    switch(key) 
      {	    
      case 'q': Quit();  
	break; 
      case 'a': //Toggle help in Finnish
	if (help_str == help_fi){
	  show_help = (show_help+1)%2;
	}
	else{//Switch to Finnish
	  help_str = help_fi;
	  show_help = 1;
	}
	ReDraw();
	break;
      case 'b'://Show H and Dbh
	show_tree_metrics = (show_tree_metrics+1)%2;
	ReDraw();
	break;
      case 'c'://Translate Up the camera and the point of focus
	{PositionVector d(0,0,-1);
	  Translate(d);
	  ReDraw();
	}
	break;
      case 'd'://Translate Right the camera and the point of focus
	{PositionVector d(0,-1,0);
	  Translate(d);
	  ReDraw();
	}
	break;
      case 'h'://Toggle help in English
	if (help_str == help_en){
	  show_help = (show_help+1)%2;
	}
	else{//Switch to English
	  help_str = help_en;
	  show_help = 1;
	}
	ReDraw();
	break;
      case 'm': //Rotate 360 around current ShowTree tree
	StartAnimation();
	break;
      case 'n':	//Next tree, current tree view
	GoNextTree();
	break;		
      case 'r'://Reset to the initial, all trees view
	ShowTree = -1;
	GoNextTree();
	break;
      case 's':
	//Translate Left the camera and the point of focus
	{PositionVector d(0,1,0);
	  Translate(d);
	  ReDraw();
	}
	break;
      case 'v':
	//Translate Down the camera and the point of focus
	{PositionVector d(0,0,1);
	  Translate(d);
	  ReDraw();
	}
	break;
      case 'x':
	Zoom(-1);
	ReDraw();
	break;
      case 'z':
	Zoom(1);
	ReDraw();
	break;
      default://Toggle help
	show_help = (show_help+1)%2;
	ReDraw();
      }
  }
    
    
    
  // This function is called when a mouse value is changed
  void LGMVisualization::ChangeMouseButton(int button, int state, int x, int y)
  {
    settings.MIDDLEBUTTON=UP;
    settings.RIGHTBUTTON=UP;
    

  
    switch(button) {
    case GLUT_LEFT_BUTTON:    // Left button is pressed
      settings.mouse_x=0;
      settings.mouse_y=0;   
      if (settings.LEFTBUTTON == DOWN)
      {
	  settings.LEFTBUTTON=UP;
	  settings.MOVEMENT=false;
      }
      else
      {
	  settings.LEFTBUTTON=DOWN;
	  settings.MOVEMENT=true;
      }
      
     

     
      break;

    case GLUT_MIDDLE_BUTTON:  // Middle button is pressed
      settings.mouse_x=0;
      settings.mouse_y=0;
      settings.MIDDLEBUTTON=DOWN;
      settings.MOVEMENT=true;
      break;
  
    default:
      break;
    }
  }



  void LGMVisualization::MouseMotion(int x, int y)
  {
      cout << "mouse motion " << endl;
      settings.MOVEMENT=true;
       
      
    if (settings.mouse_x != 0 || settings.mouse_y != 0) // If movement has just begun, write the
      {                               // values down  
	if (settings.MIDDLEBUTTON == DOWN && settings.mouse_y != y)        // Middle button is pressed 
	  {                               
	    settings.z_move = settings.z_move + (settings.mouse_y-y);
	    drawed = false;
	  }
	else if (settings.MIDDLEBUTTON == DOWN && settings.mouse_x != x)        // Middle button is pressed 
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
	  {
	settings.MOVEMENT = false;
	ReDraw(); 
	drawed = true;
	  }
	return;
      }
  }


  void LGMVisualization::Menu(int value)
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
	glutSetWindow(settings.window1);
	screenShot ("shot.tga", settings.WINDOW_SIZE_X, settings.WINDOW_SIZE_Y);
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
    glutReshapeFunc(StaticNewWindowSize);          // Call this function if the size is changed  
    glutKeyboardFunc(StaticKeyPress);              // Call this funktion when a key is pressed 
    glutMouseFunc (StaticChangeMouseButton);       // Mouse events
    glutMotionFunc(StaticMouseMotion);
    glutIdleFunc (StaticLoop);                     // This is called when nothing happens
    glutSpecialFunc(StaticArrows);
    glutDisplayFunc(StaticReDraw);                 // The draw-function
    glutCreateMenu(StaticMenu);                    // Make the menu
//     glutAddMenuEntry("Leaves on/off__________________", 14);
//     glutAddMenuEntry("Textures on/off_________________", 15);
//     glutAddMenuEntry("VoxelSpace on/off_______________", 1);
//     glutAddMenuEntry("VoxelSpace with lines on/off____", 2);
//     glutAddMenuEntry("Change background color______________", 16);
//     glutAddMenuEntry("Write image", 13);
    glutAttachMenu(GLUT_RIGHT_BUTTON);  
    glEnable (GL_DEPTH_TEST); 
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the screen 
  }


  void LGMVisualization::StaticMouseMotion(int x, int y)
  {
      //  cout << "hiiri liikkuu " << endl;
      active_visualization->MouseMotion(x, y);  
  }


  void LGMVisualization::StaticLoop(void)
  {
    active_visualization->Loop();  
  }


  void LGMVisualization::StaticArrows(int key, int x, int y)
  {
    active_visualization->Arrows(key, x, y);  
  }


  void LGMVisualization::StaticReDraw(void)
  {
    active_visualization->ReDraw();  
  }


  void LGMVisualization::StaticMenu(int value)
  {
    active_visualization->Menu(value);  
  }

  void LGMVisualization::StaticChangeMouseButton(int button, int state, int x, int y)
  {
    active_visualization->ChangeMouseButton(button,state,x,y);  
  }



  void LGMVisualization::StaticKeyPress(unsigned char key, int x, int y)
  {
    active_visualization->Keypress(key, x, y);  
  }



  void LGMVisualization::StaticNewWindowSize(int new_x, int new_y)
  {
    active_visualization->NewWindowSize(new_x, new_y); 
  }




  int LGMVisualization::GetTgaTexNumber(string filename)
  {
     	int s =  LoadedTgas.size();
	for (int i=0; i<s; i++)
	{
	    LoadedTexture lt =  LoadedTgas[i];
	    if (lt.fname == filename) return lt.number;
	}
	
	int num = -1;
	LoadTgaTexture(num, filename);

	return num;
  }

 int LGMVisualization::GetBmpTexNumber(string filename)
  {
     	int s =  LoadedBmps.size();
	for (int i=0; i<s; i++)
	{
	    LoadedTexture lt =  LoadedTgas[i];
	    if (lt.fname == filename) return lt.number;
	}
	
	int num = -1;

//	LoadTgaTexture(num, filename);

	return num;
  }

 

void LGMVisualization:: drawTrees()
{
    for_each(trees.begin(),trees.end(),DrawTrees(settings.cam_x,settings.cam_y,
						 settings.cam_z));
}






 
}


