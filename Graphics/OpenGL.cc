#include "stdafx.h"
#include "OpenGL.h"
#include <OpenGLinterface.h>

#include <math.h>

//And the vendors just can't agree where the headers are...
#if defined(__APPLE__) || defined(__MACOSX__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <vector>



int max_leave_angle = 30;
int min_leave_angle = -30;
bool random_leave_angles = true;

const float leave_length=0.157;  // gliricidian lehtia varten


float texX_odd = 86;  //kerroin tekstuurin mappaykseen
float texY_odd = 22;

float texX_min_odd  = 26;  //kerroin tekstuurin mappaykseen
float texY_min_odd  = 22;

float leave_size_x = 1;
float leave_size_y = 1;

float torus_a = 0.28;
float torus_b = 1.8;

float c_x=0;
float c_y=0;
float c_z=0;

int needle_plane_number = 100;
std::vector<NEEDLE_PLANE> nplanes;

bool initialized = false;
float my_cosine[MY_EDGES];
float my_sine[MY_EDGES];

float my_cosine_big[MY_EDGES_BIG];
float my_sine_big[MY_EDGES_BIG];

float my_cosine_min[MY_EDGES_MIN];
float my_sine_min[MY_EDGES_MIN];


float BUD_SIZE_MAX_RADIUS = 0.002;//0.002; // The diameter of a bud  
float BUD_SIZE_LENGTH = 0.012; //0.012;     // The length of a bud

double overstate = 1; // liioittelu 
double overstateTran = 3; //15 & 50

LGMdouble needle_length = 0.05;

bool ONLY_LAST_SEGMENT_TRANSPIRATION=true;

LGMdouble height_odd = 29;




void Make3DLeave(float xodd, float yodd, float rad)
{
	glTranslatef(0,rad,0);

	xodd = xodd * 2;
	glBegin(GL_TRIANGLES);
	
	for (int i=0; i< 5; i++)
	{
		float y= i * 0.2;
		for(int a=0; a<5; a++)
		{
			float x = a*0.2;			
			Point p1 = mapping[a][i];
			Point p2 = mapping[a][i+1];
			Point p3 = mapping[a+1][i];

			PositionVector pp1(p2.getX()-p1.getX(),   p2.getY()-p1.getY(),   p2.getZ()-p1.getZ());
			PositionVector pp2(p3.getX()-p1.getX(),   p3.getY()-p1.getY(),   p3.getZ()-p1.getZ());

			PositionVector normal = Cross(pp2, pp1);	
			normal.normalize();
			glNormal3f(normal.getX(), normal.getY(), normal.getZ());		
			glTexCoord2f(x, y);		glVertex3f(p1.getX()*xodd, p1.getY()*yodd, p1.getZ());			
			glTexCoord2f(x, y+.2);	glVertex3f(p2.getX()*xodd, p2.getY()*yodd, p2.getZ());
			glTexCoord2f(x+.2, y);	glVertex3f(p3.getX()*xodd, p3.getY()*yodd, p3.getZ());

		
			p1 = mapping[a][i+1];
			p2 = mapping[a+1][i+1];
			p3 = mapping[a+1][i];

		    pp1 = PositionVector(p1.getX()-p2.getX(),   p1.getY()-p2.getY(),   p1.getZ()-p2.getZ());
			pp2 = PositionVector(p3.getX()-p2.getX(),   p3.getY()-p2.getY(),   p3.getZ()-p2.getZ());
			normal = Cross(pp1, pp2);
			normal.normalize();

			glNormal3f(normal.getX(), normal.getY(), normal.getZ());
			glTexCoord2f(x, y+.2);		glVertex3f(p1.getX()*xodd, p1.getY()*yodd, p1.getZ());			
			glTexCoord2f(x+.2, y+.2);	glVertex3f(p2.getX()*xodd, p2.getY()*yodd, p2.getZ());			
			glTexCoord2f(x+.2, y);		glVertex3f(p3.getX()*xodd, p3.getY()*yodd, p3.getZ());						
			
	  }
	}
	glEnd();
}




void MakeLeave(float x, float y, float rad)
{  
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
	  
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, 0+rad, 0);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, y+rad, 0);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( x, y+rad, 0);
  glTexCoord2f(1.0f, 0.0f); glVertex3f( x, 0+rad, 0);
  glEnd();	

  return;   
}


void MakeLeaveTable()
{
	float x,y;
	for (int i=0; i<6; i++)
	{
		x = -0.5 + i*0.2;
		for(int a=0; a<6; a++)
		{
			float y = a * 0.2;
			mapping[i][a] = GetPoint(x,y);
		}
	}
}


Point GetPoint(float x, float y)
{
	float xx,yy,zz;

	float alpha = y / (2*PI_VALUE*(torus_b - torus_a));
	yy = sin(alpha) * (torus_b - torus_a);
	
	float z_ = sqrt((torus_b - torus_a)*(torus_b - torus_a) + yy*yy);

	int x_odd = 1;
	if (x<0)
	{
		x_odd = -1;
		x = -x;
	}

	alpha = x / (2*PI_VALUE*torus_a);
	xx = sin(alpha) * torus_a;

	zz = - z_ + torus_b - torus_a + torus_a - cos(alpha) * torus_a;

	return Point(xx*x_odd, yy, zz);
}















void InitDrawing()
{
	const float PI = (float)3.14159265;

	if (initialized == false)
	{
	  
		initialized = true;
	}
	
	for (int a=0; a<MY_EDGES; a++)
	{
		my_cosine[a] = cos(1+a*2*PI/MY_EDGES);
		my_sine[a] = sin(1+a*2*PI/MY_EDGES);
	}

	for (int a=0; a<MY_EDGES_BIG; a++)
	{
		my_cosine_big[a] = cos(1+a*2*PI/MY_EDGES_BIG);
		my_sine_big[a] = sin(1+a*2*PI/MY_EDGES_BIG);
	}

	for (int a=0; a<MY_EDGES_MIN; a++)
	{
		my_cosine_min[a] = cos(1+a*2*PI/MY_EDGES_MIN);
		my_sine_min[a] = sin(1+a*2*PI/MY_EDGES_MIN);
	}

	for (int i=0; i<TABLESIZE; i++)
	{
		float s = rand() % 100 + 50;
		s = s / 100;
		s = sqrt(sqrt(sqrt(sqrt(sqrt(s)))));
		s = s * 0.9;
		odd_table[i] = s;
	}
}

/*
void DrawCone(branch_in &bri)
{
	Point position = bri.start;
	PositionVector direction = bri.direction;
	GLfloat length = bri.length;
	GLfloat radius = bri.rad/100;
	GLfloat max_radius = bri.max_rad / 100;

    float rot_x;
	float rot_y;
	float rot_angle;



    
	rot_x = -1*direction.getVector()[1];
	rot_y =    direction.getVector()[0];
	rot_angle = (360/(2*PI_VALUE))*acos((double)direction.getVector()[2]);


	float tmp = sqrt(rot_x*rot_x + rot_y*rot_y);
	length = length / tmp;

	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), position.getZ());
	glRotatef( rot_angle, rot_x, rot_y, 0);
	MakeCone(length, radius, max_radius); 	 
	glPopMatrix();
}
*/


void MakeCone(float length, float radius, float max_radius)
{
  const float PI = (float)3.14159265;
  int edges = 16;

  GLfloat cosine,sine, x=0, y=last_texY;
  GLfloat tex_x= (float)(radius * 3.14 / edges) / 0.3;  //!! kerroin pienempiin oksiiin

  GLfloat tex_y= length;
  GLfloat len;

  if (length <= 0 || radius <= 0)
	  return;

  y=0;

  
  glPushAttrib(GL_COLOR_BUFFER_BIT);
  //glColor3f(0.4,0.4,0.4);
  glBegin(GL_QUAD_STRIP); 
  for (int i = 0; i < edges ; i++)
    {
      x=x+tex_x;
	  cosine= my_cosine_min[i]; 
	  sine= my_sine_min[i];

      //Set the normal    
      glNormal3f(cosine, sine,0);
      cosine *= radius;
      sine *= radius; 

      glTexCoord2f(x, y);                 glVertex3f(0, 0, 0);
      glTexCoord2f(x, y+tex_y);           glVertex3f(cosine,sine, length);     
   }
  x=x+tex_x; 
  cosine=my_cosine[0];
  sine=my_sine[0]; 
  
  //len = sqrt(cosine*cosine+sine*sine);  //Set the normal
  float d = -1 / length;

  len = sqrt(cosine*cosine+sine*sine+ d*d);
  glNormal3f(cosine/len, sine/len, d/len); 
  cosine *= radius;
  sine *= radius; 
  
  glTexCoord2f(x, y);       glVertex3f(0, 0, 0);
  glTexCoord2f(x, y+tex_y); glVertex3f(cosine, sine, length);
  glEnd(); 

  last_texY = last_texY + length;

  if (last_texY > 1)
	last_texY = last_texY - (int)(last_texY);

   
    // Kansi sylinterille
	glDisable(GL_TEXTURE_2D);
  	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	//glColor3f(0.5, 0.5, 0.0);
	
	for (int i = 0; i < edges ; i++)
	{    
	  cosine= my_cosine_min[i]; 
	  sine= my_sine_min[i];
		  
	  cosine *= radius;
	  sine *= radius; 
	  glNormal3f(0,0,1);	
	  glVertex3f(cosine, sine , length);
	}
	
    glEnd();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glPopAttrib();
}




void outPut(float x, float y, char *string)
{

  int len, i;
  //glColor3f (1.0, 0.4, 0.4);
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  
  for (i = 0; i < len; i++) 
    {
      //glutStrokeCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
    }
}


void MakeCylinder(float radius, float rad_top, float length, float rad_limit, float xx, float yy)
{
 const float PI = (float)3.14159265;
  int edges = 16;
 edges = (int)(radius / 0.0001);
 

  if (edges>60)
	edges = 100;
  else if (edges<30)
	  edges=16;
  else edges = 36;

  edges = 36;
  if (rad_top == 0 || rad_top > radius)
	  rad_top = radius;

  //cout << "särmiä " << edges << endl;

  GLfloat cosine,sine, x=0, y=last_texY, cos_top, sin_top;
  GLfloat tex_x= texX_odd*(float)(radius * 3.14 / edges);  
  float d = tex_x * edges;
  GLfloat tex_y= texY_odd*length;

  tex_x = tex_x * 0.06;
  tex_y = tex_y * 0.06;

  if (rad_limit == 0)
  {
   
	last_texY = 0;
	tex_x = texX_odd * 0.003;
  }	
 
 
  if (rad_limit<0)
  {
		tex_x= texX_min_odd*(float)(radius * 3.14 / edges);  
		d = tex_x * edges;
		tex_y= texY_min_odd*length;
  }

  int i;
  GLfloat len;
  if (length <= 0 || radius <= 0)
    return;
  
  while(y > 1)
    y--;
  
  
  
  float *position1 = new float[255];
  float *position2 = new float[255];
  float *normals = new float[255];
  float *tex1 = new float[255];
  float *tex2 = new float[255];
  
  
  
  
  //glBegin(GL_QUAD_STRIP); 
  for (i = 0; i < edges ; i++)
    {	
      if (edges == 16)
	{
	  cosine= my_cosine_min[i]; // cos((i)*2*PI/edges);
	  sine= my_sine_min[i];		//sin((i)*2*PI/edges); 
	}
      
      else if (edges == 36)
	{
	  cosine= my_cosine[i]; // cos((i)*2*PI/edges);
	  sine= my_sine[i];		//sin((i)*2*PI/edges); 
	}
      else if (edges == 100)
	{
	  cosine= my_cosine_big[i]; // cos((i)*2*PI/edges);
	  sine= my_sine_big[i];		//sin((i)*2*PI/edges); 
	}
      
      
      //Set the normal    
      //glNormal3f(cosine, sine,0);
      cos_top = cosine * rad_top;
      sin_top = sine * rad_top;
      
      //cout << "normal " << cosine << " " << sine << endl;
      cosine *= radius;
      sine *= radius; 
      
      position1[0+i*3] = cosine+xx;
      position1[1+i*3] = sine+yy;
      position1[2+i*3] = 0;
      
      position2[0+i*3] = cos_top+xx;
      position2[1+i*3] = sin_top+yy;
      position2[2+i*3] = length;
      
      normals[i*3+0] = cosine;
      normals[i*3+1] = sine;
      normals[i*3+2] = 0;

      tex1[0+i*2] = x;
      tex1[1+i*2] = y;
      tex2[0+i*2] = x;
      tex2[1+i*2] = y+tex_y;
      
      //cout << x << " " << y << " " << y+tex_y << endl;
      
      x=x+tex_x;
    }
  
  cosine=my_cosine[0]; //cos(0);
  sine=my_sine[0]; //sin(0); 
  len = sqrt(cosine*cosine+sine*sine);  //Set the normal
  // glNormal3f(cosine/len, sine/len,0); 
  cos_top = cosine * rad_top;
  sin_top = sine * rad_top;
  cosine *= radius;
  sine *= radius; 
  
  position1[0+i*3] = cosine+xx;
  position1[1+i*3] = sine+yy;
  position1[2+i*3] = 0;
  
  position2[0+i*3] = cos_top+xx;
  position2[1+i*3] = sin_top+yy;
  position2[2+i*3] = length;
  
  normals[i*3+0] = cosine;
  normals[i*3+1] = sine;
  normals[i*3+2] = 0;

  tex1[0+i*2] = x;
  tex1[1+i*2] = y;
  tex2[0+i*2] = x;
  tex2[1+i*2] = y+tex_y;
  
  glBegin(GL_QUAD_STRIP); 
  for (i = 0; i < edges+1 ; i++)
    {
      glNormal3fv(&normals[i*3]);
      glTexCoord2fv(&tex1[i*2]);		glVertex3fv(&position1[i*3]);
      glTexCoord2fv(&tex2[i*2]);		glVertex3fv(&position2[i*3]);
      glNormal3fv(&position1[i*3]);
    }
  glEnd();
  
  last_texY = last_texY + length;
  
  if (last_texY > 1)
    last_texY = last_texY - (int)(last_texY);
  
  delete position1;
  delete position2;
  delete tex1;
  delete tex2;
}



void CrossCylinder(float length, float radius, float rad_top, float ang, float ang_top)  //ang rad
{
  const float PI = (float)3.14159265;
  int edges = 40;
  GLfloat cosine,sine, x=0, y=last_texY, cos_top, sin_top;	
  
  float round = PI * (radius+rad_top); //ymparysmitta sateiden keskiarvosta;
  float yy = .4*length;	  
  float tmp = (ang - ang_top) / (2*PI) * round;

  cosine=cos(ang_top);
  sine=sin(ang_top); 		

  float delta_ang = 2 * (PI - ang) / edges;
  float tex_x = tmp + (PI - ang) * radius;
  float d_tex_x = .4*(PI - ang)/(2*PI) * radius;
  
  glBegin(GL_QUAD_STRIP);
  glTexCoord2f(tmp, 0);     glVertex3f(cosine*radius,  sine*radius,  0);
  glTexCoord2f(tmp, yy);    glVertex3f(cosine*rad_top, sine*rad_top, length);
  
  for (int i=0; i< edges; i++)
	{
		ang = ang + delta_ang;
		cosine=cos(ang);
		sine=sin(ang); 	

		glNormal3f(cosine, sine,0);
		glTexCoord2f(tex_x, 0);     glVertex3f(cosine*radius,  sine*radius,  0);
		glTexCoord2f(tex_x, yy);    glVertex3f(cosine*rad_top, sine*rad_top, length);
		tex_x = tex_x + d_tex_x;	
	}
	glEnd();
}

	


int make_texfoliage_planes_lists(Point position, float rot_angle, float rot_x, float rot_y, int number, float lenght, float radius, float fol_mas, int age)
{ 
  float mult=sqrt(0.5); 
  float amount;
  float random=1;

  
  LGMdouble needle_plane_width = 0.035;
  

  amount = 0.23 * fol_mas * 28.6 / NEEDLE_AREA;
  
  int amount2 = static_cast<int>(fol_mas / 0.0000035);
  
  LGMdouble tex_len = 0.1;
  LGMdouble tex_per_plane = lenght / tex_len;
  int needles_per_tex = 30;

  int needles_per_plane = static_cast<int>(tex_per_plane * needles_per_tex);

  if (needles_per_plane == 0)
	  return number;
  int directions = static_cast<int>(amount2 / needles_per_plane);

  //float t = amount / directions / 10;

  float tt = lenght / tex_len;	


  if (directions == 0)
	  return number;

  float r = 360/directions;


  if (age>6)
	  return number;

  LGMdouble leaning = age*10+30; //200.0;
	
  LGMdouble Lx = sin(2*PI_VALUE*leaning/360.0) * needle_length;
  LGMdouble Ly = cos(2*PI_VALUE*leaning/360.0) * needle_length;

  
  for (int a=0; a<directions; a++)
    {  
	  double ran = (double)(rand()%100)/100;
      
	  if (glIsList(number))
		glDeleteLists(number, 1);

      glNewList(number, GL_COMPILE);
	  glPushMatrix();
	  
	  glTranslatef(position.getX(), position.getY(), position.getZ());
	  if (rot_angle > 0)
		glRotatef( rot_angle, rot_x, rot_y, 0);
	  
	  if (a*r != 0.0)
		glRotatef(a*r,0,0,1);
      glTranslatef(radius,0,0);
        
	  glBegin(GL_QUADS);
	  glTexCoord2f(1.0f,	0.0f+ran);		glVertex3f(  0.0f,	0,	0);
	  glTexCoord2f(1.0f,	tt+ran);		glVertex3f(  0.0f,	0,	lenght);
	  glTexCoord2f(0.0f,	tt+ran);		glVertex3f(  Lx,	0,	lenght+Ly);
	  glTexCoord2f(0.0f,	0.0f+ran);		glVertex3f(  Lx,	0,	0.0f+Ly);
	  glEnd();

	  glPopMatrix();
	  
	  glEndList();
     
	  number++;
    }
  return number;
}




void draw_texfoliage_planes(float lenght, float radius, float fol_mas, int age)
{ 
  float mult=sqrt(0.5); 
  float amount;
  float random=1;
  float directions=6;

  amount = 0.23 * fol_mas * 28.6 / NEEDLE_AREA;
  
 
  float t = amount / directions / 10;

  float tt = lenght / 0.10f;	


  float r = 360/directions;

  for (int a=0; a<directions; a++)
    {  
      glPushMatrix();
      glRotatef(a*r,0,0,1);
      glTranslatef(radius,0,0);
        
	  glBegin(GL_QUADS);
	  glTexCoord2f(1.0,	0.0f);		glVertex3f(  0.0f,	0,	0);
	  glTexCoord2f(1.0,	tt);		glVertex3f(  0.0f,	0,	lenght);
	  glTexCoord2f(0.0f,tt);		glVertex3f(  0.05f,	0,	lenght);
	  glTexCoord2f(0.0f,0.0f);		glVertex3f(  0.05f,	0,	0.0f);
	  glEnd();
	
      glPopMatrix();
    }   
}







void MakeWireModel(float radius, float length)
{
  const float PI = (float)3.14159265;
  GLfloat cosine,sine, sine_next, cosine_next, sine_opp, cosine_opp; 
 
  if (length == 0)
    return;
  int edges=20;

  glBegin(GL_LINES);
  for (int i = 0; i < edges; i++)
    {
      cosine=cos(i*2*PI/edges)*radius;
      sine=sin(i*2*PI/edges)*radius; 
      
      glVertex3f(cosine,sine,0);
      glVertex3f(cosine,sine, length);
      
      cosine_next=cos((i+1)*2*PI/edges)*radius;
      sine_next=sin((i+1)*2*PI/edges)*radius; 
      
      cosine_opp=cos((i+edges/2)*2*PI/edges)*radius;
      sine_opp=sin((i+edges/2)*2*PI/edges)*radius; 

      for (float a=0; a<=length; a=a+0.02)
        {
          glVertex3f(cosine,sine, a);
          glVertex3f(cosine_next,sine_next, a);
	  if (i <= edges/2)
	    {
	      glVertex3f(cosine,sine, a);
	      glVertex3f(cosine_opp,sine_opp, a);
	    }
	} 
      

      glVertex3f(cosine,sine, length);
      glVertex3f(cosine_next,sine_next, length);      
    }   
  glEnd(); 
}







void make_bud(DRAW_TYPE mode)
{
  

  float radius=0.0;
  float radius2;
  float rad_gro = BUD_SIZE_MAX_RADIUS/3.0;
  float rad_minus = rad_gro*2/10.0;
  float dist=BUD_SIZE_LENGTH/10.0;
  float xy_angle;
  float sine,cosine;
  float z_coord;
  float len;
  int edges=10;

  for (int i=0; i<11; i++)
    {
      radius2=radius+rad_gro;
      rad_gro=rad_gro-rad_minus;
      glBegin(GL_QUAD_STRIP);      
      for (int a=0; a<=edges; a++)
        {         
          cosine=cos(a*2*PI_VALUE/edges);
          sine=sin(a*2*PI_VALUE/edges); 
          xy_angle = atan(rad_gro/dist);     // the angle betweed the plane normal and xy_plane
          z_coord = -sin(xy_angle);          // z-coordinate of the normal
          len=sqrt(cosine*cosine+sine*sine+z_coord*z_coord); // the length of normal vector
          glNormal3f(cosine/len, sine/len, z_coord/len);     // normalize the normal vector
          glVertex3f( cosine*radius, sine*radius, i*dist);
          glVertex3f( cosine*radius2, sine*radius2, (i+1)*dist);          
        }
      glEnd();
      radius=radius2;
    }
}




void MakeCylinderWithTop(float radius, float rad_top, float length, float rad_limit, std::vector<METER> &an_rings, int age, float odd)
{
  const float PI = (float)3.14159265;
  int edges = 16;

  edges = (int)(radius / 0.0001);

  if (edges>60)
	edges = 100;
  else if (edges<10)
	  edges=16;
  else edges = 36;

  cout << "särmiä " << edges << endl;
  if (rad_top == 0)
	  rad_top = radius;


  GLfloat cosine,sine, x=0, y=last_texY, cos_top, sin_top;
  GLfloat tex_x= texX_odd*(float)(radius * 3.14 / edges);  
  float d = tex_x * edges;
  GLfloat tex_y= texY_odd*length;
 
  if (rad_limit<0)
  {
		tex_x= texX_min_odd*(float)(radius * 3.14 / edges);  
		d = tex_x * edges;
		tex_y= texY_min_odd*length;
  }

	
  float r = radius*(1-odd) + rad_top*odd;
  float d_rad = radius - r;
  radius = r;

  GLfloat len;

  if (length <= 0 || radius <= 0)
	  return;

  while(y > 1)
	  y--;

  int i;
  
  glBegin(GL_QUAD_STRIP); 
  for (i = 0; i < edges ; i++)
    {
      x=x+tex_x;
	  if (edges == 16)
	  {
		cosine= my_cosine_min[i]; // cos((i)*2*PI/edges);
		sine= my_sine_min[i];		//sin((i)*2*PI/edges); 
	  }

	  if (edges == 36)
	  {
		cosine= my_cosine[i]; // cos((i)*2*PI/edges);
		sine= my_sine[i];		//sin((i)*2*PI/edges); 
	  }

	  if (edges == 100)
	  {
		cosine= my_cosine_big[i]; // cos((i)*2*PI/edges);
		sine= my_sine_big[i];		//sin((i)*2*PI/edges); 
	  }


      //len = sqrt(cosine*cosine+sine*sine);  //Set the normal    
      glNormal3f(cosine, sine, 0);
	  cos_top = cosine * rad_top;
	  sin_top = sine * rad_top;

	  cosine *= radius;
      sine *= radius; 
      glTexCoord2f(x, y);                 glVertex3f(cosine,sine,0);
      glTexCoord2f(x, y+tex_y);           glVertex3f(cos_top,sin_top, length);     
   }
  x=x+tex_x; 
  cosine=my_cosine[0]; //cos(0);
  sine=my_sine[0]; // sin(0); 
  
  glNormal3f(cosine, sine,0); 
  cos_top = cosine * rad_top;
  sin_top = sine * rad_top;
  cosine *= radius;
  sine *= radius; 
  
  glTexCoord2f(x, y);			glVertex3f(cosine,sine, 0);
  glTexCoord2f(x, y+tex_y);     glVertex3f(cos_top,sin_top, length);
  glEnd(); 
	

  last_texY = last_texY + length;

  if (last_texY > 1)
	last_texY = last_texY - (int)(last_texY);

  
  glDisable(GL_LIGHTING);	 
  glDisable(GL_TEXTURE_2D);
  //glColor4f(0.8f, 0.8f,0.0f,0.7f);                 
  glBlendFunc(GL_SRC_ALPHA,GL_SRC_COLOR); 
  glEnable(GL_BLEND);             

  // kansi	 
  glNormal3f(0,0,1);
  glBegin(GL_POLYGON);
  for (i = 0; i < edges ; i++)
		{
		  cosine=cos((i)*2*PI/edges);
		  sine=sin((i)*2*PI/edges);    
		  
		  cosine *= radius;
		  sine *= radius; 
		  glVertex3f(cosine, sine , length);
		}
  glEnd();


  length = length + 0.001;
  //glDisable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glShadeModel(GL_SMOOTH);

  //float d_rad = radius / (age+1);
  
  glPushMatrix();
	for (i=0; i<an_rings.size(); i++)
	{
		
		float rad = GetMeter(i+1 , an_rings) / 2 - d_rad;
		if (rad > 0 && rad<0.3)
		{
		  //glColor3f(0.2, 0.2, 0.0);
			glBegin(GL_LINE_STRIP); //_LOOP);
			for (int ii = 0; ii < MY_EDGES_BIG ; ii++)
			{
				cosine=my_cosine_big[ii]; 
				sine= my_sine_big[ii];      
		  
				cosine *=  rad;
				sine *= rad; 
				
				
				glVertex3f(cosine, sine , length);
				
			}
			glEnd();
		}
	}
	
  glPopMatrix();
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glDisable(GL_BLEND);
  glDisable(GL_LINE_SMOOTH);
}



void MakeYearLines(float radius, float rad_top, float length, std::vector<METER> &an_rings)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	//glColor3f(1,1,0);

	glVertex2f(-radius, 0);
	glVertex2f(-rad_top, length/height_odd);
	glVertex2f(rad_top,  length/height_odd);
	glVertex2f(radius,  0);
	glEnd();
	glPopMatrix();
}



void MakeYearLines(std::vector<year_point> l)
{	
/*
	std::list<year_point>::iterator I = l.begin();
	std::list<year_point>::iterator start = l.begin();
    std::list<year_point>::iterator last = l.end();
*/

  //glColor3f(1,1,1);
	int size = l.size();

	for(int n=1; n<68; n++)
	{
		
		glBegin(GL_LINE_STRIP);
		glPushMatrix();
		for(int a=0; a<n; a++)
		{
			year_point p = l[a];
			METER m = GetMeter(n, p.rads);			
			float h = p.height;
			if (m>0 && h>0)
				glVertex2f(-m*10, -h);
		}
		
		glPopMatrix();
		glEnd();
	}
}



//   Funktio hakee listasta n:nnen arvon ja palauttaa sen
METER GetMeter(int n, std::vector<METER> l)
{
/*
	std::list<METER>::iterator I = l.begin();
    std::list<METER>::iterator last = l.end();	
*/
	if (n> l.size())
		return -1;

	/*
	METER ret;
	while(I != last)
	{	
		ret = *I;
		n--;
		if (n == 0)
			return ret;
		I++;
	}
	*/
	return l[n-1];
}


float MyGetValue(char *line, int index)
{	
	while(*line == ' ' && *line!='\0')
		line++;
	
	while(index>1)
	{	
		index--;
		while(*line != ' ' && *line!='\0')
			line++;
		while(*line == ' ' && *line!='\0')
			line++;
	}
	if (line == '\0')
		return -1;


	const char *start=line; 
	char number[255];
	int counter = 0;
	int odd = 1;

	while(*line != ' ' && *line != '\0')
    {
      counter++;
      line++;
    }
 
	int ind=0;  
	while (counter>0)
    {
		if (*start == '-')
			odd=-1;		      
		else 
		{
			number[ind]=*start;
			ind++;
		}
      start++;
      counter--;
    }
  number[ind] = '\0';    
  return (float)atof(number) * odd;
}





// y=0 return 0
float GetAngle(PositionVector p)
{
	const float PI = (float)3.14159265;
	float angle=0;
	float x = p.getX();
	float y = p.getY();

	if (x<0 && y>=0)
	{
		angle = tan(-x/y);
	}

	else if (x>=0 && y>=0)
	{
		angle = -tan(x/y);
	}
	
	if (x<0 && y<0)
	{
		angle = tan(-x/-y)+PI/2;
	}

	else if (x>=0 && y<0)
	{
		angle = tan(x/-y)-PI/2;
	}

	angle = angle * 360 / (2*PI);

	return angle;
}




void make_leave(Point petiole_begin, Point petiole_end, PositionVector leaf_normal, double major, double minor)
{
  glPushMatrix();
 
  Point petiol_xy = Point(0,0,0);
  Point petiol = petiole_end - petiole_begin; 
  Point petiol_proj = Point(0,0,1);

  if ((Point)leaf_normal == petiol)
    {
      //cout << " " << endl;
    }
  else
    {
      PositionVector v1 = PositionVector(Cross(leaf_normal, PositionVector(petiol)));
   
      PositionVector v2 = PositionVector(Cross(v1, leaf_normal));
      petiol_proj = (Point)v2;
      petiol_xy  = normalize_xy(petiol_proj);
    }

  Point normal = (Point)leaf_normal;
  glTranslatef(petiole_end.getX(),petiole_end.getY(), petiole_end.getZ());

  
  float rot_angle = acos(petiol_xy.getY())* 360 / 6.28;
  if (petiol_xy.getX() > 0)
    rot_angle = rot_angle * -1;
 
  float rot_x = normal.getY();
  float rot_y = normal.getX();
  float rot_z = normal.getZ();
  
  glRotatef(rot_angle, rot_x, rot_y, rot_z);
  
  rot_x = -1*normal.getY();
  rot_y =    normal.getX();
  rot_angle = 57.29*acos(normal.getZ());

 	

  glRotatef(rot_angle, rot_x, rot_y, 0);   
  glScalef(major/leave_length, minor/0.018/4, 1);
  GLfloat mat_amb1[] = { 0.12, 0.5, 0.12, 1.0 };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb1);
  //glCallList(ONE_LEAVE);  
  make_leave();
  glPopMatrix();
} 


void make_leave(void)
{
  glBegin(GL_LINES);

  glVertex3f(0, leave_length, 0);
  glVertex3f(0,0, 0);
  glEnd();
  float size=.4;
  for (float i=1; i<6; i++)
    {   
      if (i<4)
        size=size+.2;
      else size=size-.2;          
      glPushMatrix();           
      glTranslatef(0, i*leave_length/5, 0); 
      glRotatef( 90, 0, 1, 0);
   
      glScalef(size, size, size);
      glRotatef( 90, 0, 0, 1);
      make_leaflet();            
      glPopMatrix();     

      glPushMatrix();           
      glTranslatef(0, i*leave_length/5, 0); 
      glRotatef( -90, 0, 1, 0);
      glScalef(size, size, size);
      glRotatef( -90, 0, 0, 1);
      make_leaflet();            
      glPopMatrix(); 
    }
  glPushMatrix();           
  glTranslatef(0, leave_length, 0);
  glRotatef( 180, 0, 1, 0);
  glRotatef( -90, 1, 0, 0);
  glScalef(.5, .5, .5);
  make_leaflet();        
  glPopMatrix(); 
}


Point normalize_xy(Point point)
{
  float length = sqrt(point.getY()*point.getY()+point.getX()*point.getX());
  if (length == 0)
    return  Point(0,0,0);
  Point p = Point(point.getX()/length,point.getY()/length, 0);  
  return p;
}


void make_leaflet()
{
  float LEAVE_HEIGHT = 0.072;
  float LEAVE_WIDTH = 0.018;
  float LEAVE_BASE = 0.006;
  float YMINUS = 0.002;
  float x = 0;
  float width=0;
  float z = LEAVE_BASE;
  float y_change = .0025;;
  float y=0;
  float len=0;

  glBegin(GL_LINES); 
  glVertex3f(0, 0, 0);   glVertex3f(0, 0, z);
  glEnd();

  glBegin(GL_QUAD_STRIP);
  glVertex3f(0, 0, z);
  glVertex3f(0, 0, z);
  for(float c=0; c<=LEAVE_HEIGHT; c=c+LEAVE_HEIGHT/10)
    {
      width = sin(c*2*3.14/LEAVE_HEIGHT/2)*LEAVE_WIDTH;
      z = LEAVE_BASE + c;
      y = y + y_change;      
      len = sqrt(16*y_change*y_change + LEAVE_HEIGHT/10*LEAVE_HEIGHT/10+ YMINUS*YMINUS);  //Set the normal    
      glNormal3f(YMINUS/len, LEAVE_HEIGHT/10/len, 4*y_change/len);
      glVertex3f(x-width, y-YMINUS, z);      glVertex3f(x, y, z);
      y_change = y_change - .0005;                   
    }    
  glEnd();

  
  x = 0;
  width=0;
  z = LEAVE_BASE;
  y_change = .0025;
  y=0;
  glBegin(GL_QUAD_STRIP);
  glVertex3f(0, 0, z);
  glVertex3f(0, 0, z);
  for(float c=0; c<=LEAVE_HEIGHT; c=c+LEAVE_HEIGHT/10)
    {
      width = sin(c*2*3.14/LEAVE_HEIGHT/2)* LEAVE_WIDTH;
      z = LEAVE_BASE + c;
      y = y + y_change;     
      len = sqrt(16*y_change*y_change + LEAVE_HEIGHT/10*LEAVE_HEIGHT/10 + YMINUS*YMINUS);  
      //Set the normal          
      glNormal3f(YMINUS/len, LEAVE_HEIGHT/10/len, 4*y_change/len);      
      glVertex3f(x+width, y-YMINUS, z);      glVertex3f(x, y, z);     
      y_change = y_change - .0005;                   
    }    
  glEnd();  
}


void make_petiole(Point begin, Point end)
{
  
  GLfloat mat_amb1[] = { 0.3, 1.0, 0.3, 1.0 };
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb1);
  
  glPushMatrix();
  glLineWidth(5);
  glBegin(GL_LINES); 
  glVertex3f(begin.getX(), begin.getY(), begin.getZ());
  glVertex3f(end.getX(), end.getY(), end.getZ());
  glEnd(); 
  glLineWidth(1);
  glPopMatrix();
}
