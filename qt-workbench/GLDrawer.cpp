#include <QtGui>
#include <QtOpenGL>

#include <BSPTree.h>
#include <math.h>
#include <iostream>
#include "GLDrawer.h"

using namespace std;

GLDrawer::GLDrawer(QWidget* parent)
  : QGLWidget(parent) {
  resize(400, 300);
  camera_x = 0;
  camera_y = 0;
  camera_z = 0;
  cam_rot_x = 0;
  cam_rot_y = 0;
  cam_mov_speed = 0.1;
  cam_rot_speed = 2;
  cyl_x = 0;
  cyl_y = 0;
  cyl_z = -2;
  cyl_rot_angle = 0;
  cyl_rot_x = 0;
  cyl_rot_y = 0;
  cyl_rot_z = 0;
  DEGTORAD = 2*3.14159265/360.0;

  (void) new QShortcut(Qt::Key_W, this, SLOT(moveCameraForward()));
  (void) new QShortcut(Qt::Key_S, this, SLOT(moveCameraBackward()));
  (void) new QShortcut(Qt::Key_Q, this, SLOT(rotateCameraLeft()));
  (void) new QShortcut(Qt::Key_E, this, SLOT(rotateCameraRight()));
}

void GLDrawer::initializeGL()
{  
  //glClearColor(0.4, 0.4, 0.6, 0.4);
  glClearColor(0, 0, 0, 0);
  //glEnable(GL_DEPTH_TEST);
  glDisable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);
  // Wireframe
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(3);
   
  tree = new BSPTree();
  BSPPolygonSet polygons;
  Point p1(0,0,-1);
  Point p2(0,1,-1);
  Point p3(1,0,-1);
  PositionVector v(Cross(PositionVector(p1-p2), PositionVector(p2-p3)));
  cout << v.getX() << " " << v.getY() << " " << v.getZ() << endl;
  //polygons.addPolygon(new BSPPolygon(Point(0,0,-2), Point(0,1,-2), Point(1,0,-2), NULL));
  //polygons.addPolygon(new BSPPolygon(Point(0,0,-1), Point(0,1,-1), Point(1,0,-1), NULL));
  //polygons.addPolygon(new BSPPolygon(Point(0,0,-2.5), Point(0,1,-1.5), Point(0,0,-0.5), NULL));
  polygons.addPolygons(makeCylinder(2, 0.5, 120));

  tree->buildBSPTree(polygons);
}

void GLDrawer::resizeGL(int width, int height)
{
  //int side = qMin(width, height);
  //glViewport((width - side) / 2, (height - side) / 2, side, side);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)width/(GLfloat)height, 0.01, 20.0);
  //glFrustum(-1.0, +1.0, -1.0, 1.0, 5.0, 60.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //  glTranslated(0.0, 0.0, -40.0);
	
}

void GLDrawer::rotateCameraUp() {
  cam_rot_x += cam_rot_speed;
  updateGL();
}
void GLDrawer::rotateCameraDown() {
  cam_rot_y -= cam_rot_speed;
  updateGL();
}
void GLDrawer::rotateCameraLeft() {
  cam_rot_y -= cam_rot_speed;
  updateGL();
}
void GLDrawer::rotateCameraRight() {
  cam_rot_y += cam_rot_speed;
  updateGL();
}

void GLDrawer::moveCameraForward() {
  camera_x += cam_mov_speed*sin(cam_rot_y*DEGTORAD);
  camera_z -= cam_mov_speed*cos(cam_rot_y*DEGTORAD);
  updateGL();
}

void GLDrawer::moveCameraBackward() {
  camera_x -= cam_mov_speed*sin(cam_rot_y*DEGTORAD);
  camera_z += cam_mov_speed*cos(cam_rot_y*DEGTORAD);
  updateGL();
}

void GLDrawer::paintGL()  {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(cam_rot_x, 1, 0, 0);
  glRotatef(cam_rot_y, 0, 1, 0);
  glTranslatef(-camera_x, -camera_y, -camera_z);
  glColor3f(1, 0, 0);

  Point eye(camera_x, camera_y, camera_z);
  tree->drawTree(eye);
}

BSPPolygonSet* GLDrawer::makeCylinder(double radius, double height, int detail) {
  double sine, cosine, sine_next, cosine_next;
  BSPPolygonSet* polygons = new BSPPolygonSet();
  //  glBegin(GL_TRIANGLES);
  for(int i = 0; i < detail; i++) {
    sine = radius*sin(i*2.0*PI/detail);
    cosine = radius*cos(i*2.0*PI/detail);
    sine_next = radius*sin((i+1)*2.0*PI/detail);
    cosine_next = radius*cos((i+1)*2.0*PI/detail);
    
    //cout << "sine:" << sine << endl << "sine_next:" << sine_next << endl;

    polygons->addPolygon(new BSPPolygon(Point(sine, 0, cosine),
				       Point(sine, height, cosine),
				       Point(sine_next, 0, cosine_next),
				       NULL));

    polygons->addPolygon(new BSPPolygon(Point(sine_next, 0, cosine_next),
				       Point(sine, height, cosine),
				       Point(sine_next, height, cosine_next),
				       NULL));

    polygons->addPolygon(new BSPPolygon(Point(sine, height, cosine),
				       Point(0, height, 0),
				       Point(sine_next, height, cosine_next),
				       NULL));

    polygons->addPolygon(new BSPPolygon(Point(sine, 0, cosine),
				       Point(0, 0, 0),
				       Point(sine_next, 0, cosine_next),
				       NULL));
    /*glVertex3f(sine, 0, cosine);
    glVertex3f(sine, height, cosine);
    glVertex3f(sine_next, 0, cosine_next);
    
    glVertex3f(sine_next, 0, cosine_next);
    glVertex3f(sine, height, cosine);
    glVertex3f(sine_next, height, cosine_next);

    glVertex3f(sine, height, cosine);
    glVertex3f(0, height, 0);
    glVertex3f(sine_next, height, cosine_next);

    glVertex3f(sine, 0, cosine);
    glVertex3f(0, 0, 0);
    glVertex3f(sine_next, 0, cosine_next);
    */

  }
  return polygons;
  //  glEnd();
}
