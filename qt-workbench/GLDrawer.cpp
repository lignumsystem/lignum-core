#include <QtGui>
#include <QtOpenGL>

#include <BSPTree.h>
#include <math.h>
#include <iostream>
#include "GLDrawer.h"
#include <SceneObject.h>
//#include <LGMPolygonTree.h>
#include <XMLTree.h>
#include <ScotsPine.h>

using namespace std;

GLDrawer::GLDrawer(QWidget* parent)
  : QGLWidget(parent) {
  resize(400, 300);
  camera_x = 5;
  camera_y = 0.5;
  camera_z = -4.8;
  cam_rot_x = 0;
  cam_rot_y = 0;
  cam_mov_speed = 0.01;
  cam_rot_speed = 1;
  cyl_x = 0;
  cyl_y = 0;
  cyl_z = -2;
  cyl_rot_angle = 0;
  cyl_rot_x = 0;
  cyl_rot_y = 0;
  cyl_rot_z = 0;
  DEGTORAD = 2*3.14159265/360.0;
  wire = false;
  
  (void) new QShortcut(Qt::Key_W, this, SLOT(moveCameraForward()));
  (void) new QShortcut(Qt::Key_S, this, SLOT(moveCameraBackward()));
  (void) new QShortcut(Qt::Key_A, this, SLOT(rotateCameraLeft()));
  (void) new QShortcut(Qt::Key_D, this, SLOT(rotateCameraRight()));
  (void) new QShortcut(Qt::Key_Q, this, SLOT(rotateCameraUp()));
  (void) new QShortcut(Qt::Key_E, this, SLOT(rotateCameraDown()));
  (void) new QShortcut(Qt::Key_I, this, SLOT(toggleWireModel()));
}

void GLDrawer::initMaterials() {
  GLfloat color1[] = {0.2, 0.9, 0.2, 1.0,
		      0.1, 0.9, 0.1, 1.0,
		      0.1, 0.9, 0.1, 1.0,
		      50};
  GLfloat color2[] = {0.9, 0.2, 0.2, 0.8,
		      0.9, 0.1, 0.1, 0.8,
		      1.0, 0.1, 0.1, 0.8,
		      50};
  green = new BSPPolygonMaterial(color1);
  red = new BSPPolygonMaterial(color2);
}

void GLDrawer::initLights() {
  GLfloat light0_position[] = { 0, 1, -1, 0 };
  GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 0.2 };
  GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
 
  glEnable(GL_LIGHT0);

  glEnable(GL_LIGHTING);

}

void GLDrawer::initializeGL()
{  
  //glClearColor(0.4, 0.4, 0.6, 0.4);
  glClearColor(0, 0, 0, 0);
  //glEnable(GL_DEPTH_TEST);
  glDisable(GL_DEPTH_TEST);
  glFrontFace(GL_CW);
  glEnable(GL_CULL_FACE);
  
  // Wireframe
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(1);

  initMaterials();
  initLights();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  tree = new BSPTree();
  BSPPolygonSet polygons;
  //Point p1(0,0,-0.5);
  //Point p2(0,1,-0.5);
  //Point p3(1,0,-0.5);
  //PositionVector v(-1*Cross(PositionVector(p1-p2), PositionVector(p2-p3)));
  
  //cout << v.getX() << " " << v.getY() << " " << v.getZ() << endl;
  //BSPPolygon* poly1 = new BSPPolygon(Point(0,0,-0.5), Point(0,1,-0.5), Point(1,0,-0.5), NULL, green);
  //BSPPolygon* poly2 = new BSPPolygon(Point(0,0.5,0.5), Point(0.5,0.5,0), Point(0.5, 0.5, 0.5), NULL, red);

  //  polygons.addPolygon(poly2);
  //polygons.addPolygon(poly1);

  //cout << "side:" << poly2->calculateSide(*poly1) << endl;
  //cout << poly2->classifyPoint(p1) << endl;
  //cout << poly2->classifyPoint(p2) << endl;
  //cout << poly2->classifyPoint(p3) << endl;
 
  Tree<ScotsPineSegment, ScotsPineBud> pine2(Point(0,0,0), PositionVector(0,1,0));
  XMLDomTreeReader<ScotsPineSegment, ScotsPineBud> reader;
  reader.readXMLToTree(pine2, "test.xml");

  LGMPolygonTree<ScotsPineSegment, ScotsPineBud, Ellipse> constructor(this);

  polygons.addPolygons(constructor.buildTree(pine2));
  // constructor.foo();

 

  Point origo(0,0,0);
  Point pos1(0,-1,0);
  PositionVector up(0,1,0);
  PositionVector left(1,0,0);
  PositionVector d1(0.5, 0.5, -1);
  PositionVector d2(0, -1, 0);
  
  BSPPolygonSet* cylinder2 = makeCylinder(0.001, 0.1, Point(0,-0.8,0) , d1, false, false, green, 30);
  polygons.addPolygons(cylinder2);
  
  //BSPPolygonSet* cylinder = makeCylinder(0.5, 1, origo, d1, false, false, red, 60);
  //polygons.addPolygons(cylinder);
  
  //BSPPolygonSet* cylinder3 = makeCylinder(0.2, 0.7, pos1, d2, false, false, red, 60);
  //polygons.addPolygons(cylinder3);

  tree->buildBSPTree(polygons);
  cout << "polygons: " << tree->countPolygons() << endl;
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
  cam_rot_x -= cam_rot_speed;
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
  camera_y += cam_mov_speed*sin(-cam_rot_x*DEGTORAD);
  updateGL();
}

void GLDrawer::moveCameraBackward() {
  camera_x -= cam_mov_speed*sin(cam_rot_y*DEGTORAD);
  camera_z += cam_mov_speed*cos(cam_rot_y*DEGTORAD);
  camera_y -= cam_mov_speed*sin(-cam_rot_x*DEGTORAD);
  updateGL();
}

void GLDrawer::toggleWireModel() {
  if(wire) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    wire = false;
  }
  else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    wire = true;
  }
  updateGL();
}

void GLDrawer::paintGL()  {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(cam_rot_x, 1, 0, 0);
  glRotatef(cam_rot_y, 0, 1, 0);
  glTranslatef(-camera_x, -camera_y, -camera_z);
  //glColor3f(1, 0, 0);

  Point eye(camera_x, camera_y, camera_z);
  tree->drawTree(eye);
  glFlush();
}

BSPPolygonSet* GLDrawer::makeCylinder(double radius, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, BSPPolygonMaterial* material, int detail) {
  double sine, cosine, sine_next, cosine_next;
  BSPPolygonSet* polygons = new BSPPolygonSet();
  SceneObject* object = new SceneObject(material);
  //  glBegin(GL_TRIANGLES);
  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);

  Point origo(0,0,0);
  
  for(int i = 0; i < detail; i++) {
    sine = radius*sin(i*2.0*PI/detail);
    cosine = radius*cos(i*2.0*PI/detail);
    sine_next = radius*sin((i+1)*2.0*PI/detail);
    cosine_next = radius*cos((i+1)*2.0*PI/detail);
    
    //cout << "sine:" << sine << endl << "sine_next:" << sine_next << endl;

    PositionVector v1(sine, 0, cosine);
    PositionVector v2(sine, height, cosine);
    PositionVector v3(sine_next, 0, cosine_next);
    v1 = v1.rotate(origo, dir, PI);
    v2 = v2.rotate(origo, dir, PI);
    v3 = v3.rotate(origo, dir, PI);
    
    polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					Point(v2)+point,
					Point(v3)+point,
					NULL, object));

    v1 = PositionVector(sine_next, 0, cosine_next);
    v2 = PositionVector(sine, height, cosine);
    v3 = PositionVector(sine_next, height, cosine_next);
    v1 = v1.rotate(origo, dir, PI);
    v2 = v2.rotate(origo, dir, PI);
    v3 = v3.rotate(origo, dir, PI);
    
    polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					Point(v2)+point,
					Point(v3)+point,
					NULL, object));
    
    if(drawTop) {
      v1 = PositionVector(sine, height, cosine);
      v2 = PositionVector(0, height, 0);
      v3 = PositionVector(sine_next, height, cosine_next);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  NULL, object));
    }
    
    if(drawBottom) {
      v1 = PositionVector(sine, 0, cosine);
      v2 = PositionVector(sine_next, 0, cosine_next);
      v3 = PositionVector(0, 0, 0);
      
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  NULL, object));
    }
    /*

    polygons->addPolygon(new BSPPolygon(Point(sine, 0, cosine),
					Point(sine, height, cosine),
					Point(sine_next, 0, cosine_next),
					NULL, NULL));

    polygons->addPolygon(new BSPPolygon(Point(sine_next, 0, cosine_next),
					Point(sine, height, cosine),
					Point(sine_next, height, cosine_next),
					NULL, NULL));

    polygons->addPolygon(new BSPPolygon(Point(sine, height, cosine),
					Point(0, height, 0),
					Point(sine_next, height, cosine_next),
					NULL, NULL));
    
    polygons->addPolygon(new BSPPolygon(Point(sine, 0, cosine),
					Point(0, 0, 0),
					Point(sine_next, 0, cosine_next),
					NULL, NULL));
    */

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
