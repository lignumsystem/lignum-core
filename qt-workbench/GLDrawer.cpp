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
#include <SugarMaple.h>
#include <vector>
#include <ctime>
#include <Lignum.h>

using namespace std;
using namespace Lignum;

GLDrawer::GLDrawer(QWidget* parent)
  : QGLWidget(parent)  {
  resize(400, 300);
  camera_x = 5;
  camera_y = 0.5;
  camera_z = -4.8;
  cam_rot_x = 0;
  cam_rot_y = 0;
  cam_rot_z = 0;
  cam_mov_speed = 0.01;
  cam_rot_speed = 1;
  r_axis = PositionVector(0,1,0);
  t_point = Point(0,0,0);
  t_height = 1;

  DEGTORAD = 2*3.14159265/360.0;
  wire = false;
  lights_on = true;
  use_textures = true;
  PI = 3.14159265;
  m_look_speed = 0.3;
  setFocusPolicy(Qt::ClickFocus);
  
  srand((unsigned)time(0)); 
  
  tree_file = QString("test.xml");

  tree = new BSPTree();
  setCylinderRDetail(8);
  setCylinderHDetail(1);
  setLeafDetail(10);
  
}

void GLDrawer::initMaterials() {
  GLfloat color1[] = {0.1, 0.8, 0.1, 1.0,
		      0.1, 0.8, 0.1, 1.0,
		      0.0, 0.1, 0.0, 1.0,
		      5};
  GLfloat color2[] = {0.9, 0.2, 0.2, 0.5,
		      0.9, 0.1, 0.1, 0.5,
		      0.2, 0.1, 0.1, 0.5,
		      50};
  GLfloat color3[] = {1.0, 1.0, 1.0, 1.0,
		      1.0, 1.0, 1.0, 1.0,
		      0.2, 0.2, 0.2, 1.0,
		      50};
  
  green = new BSPPolygonMaterial(color1);
  red = new BSPPolygonMaterial(color2);
  white = new BSPPolygonMaterial(color3);
  parameters.setMaterial(white);
  parameters.setLeafMaterial(green);
  parameters.setPetioleMaterial(green);
}

void GLDrawer::initLights() {
  light0_position = new GLfloat(4);
  /*light0_position[0] = 5;
  light0_position[1] = 0.7;
  light0_position[2] = -3.4;
  light0_position[3] = 1;*/

  light0_position[0] = 0;
  light0_position[1] = 1;
  light0_position[2] = -1;
  light0_position[3] = 0;

  /*light0_direction = new GLfloat(4);
  light0_direction[0] = 0;
  light0_direction[1] = -0.5;
  light0_direction[2] = -1;
  light0_direction[3] = 1;*/

  GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light0_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
  //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
 

  //glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);

  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  
  GLfloat specular[] = { 1, 1, 1, 1 };
  GLfloat emission[] = { 0, 0, 0, 1 };
  
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_EMISSION, emission);
}

void GLDrawer::initTextureSettings() {
  //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
  //  glShadeModel(GL_SMOOTH);

  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int GLDrawer::loadTexture(std::string fileName) {
  cout << fileName << endl;
  return bindTexture(QImage(QString(fileName.c_str())));
}

void GLDrawer::initializeGL()
{  
  glClearColor(0.9, 0.9, 0.9, 0.9);
  //glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CW);
  glEnable(GL_CULL_FACE);
  
  initMaterials();
  initLights();
  initTextureSettings();
  setCylinderTexture(QString("pine_texture.png"));
  setLeafTexture(QString("maple_texture.png"));
  setFoliageTexture(QString("foliage.png"));

  if(isExtensionSupported("GL_ARB_vertex_buffer_object"))
    emit textOutput("VBOs are supported!");
  else
    emit textOutput("VBOs are not supported!");
}

void GLDrawer::resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)width/(GLfloat)height, 0.0001, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void GLDrawer::rotateCameraUp() {
  cam_rot_x += cam_rot_speed;
  if(cam_rot_x > 180)
    cam_rot_x = -180;
  updateGL();
}
void GLDrawer::rotateCameraDown() {
  cam_rot_x -= cam_rot_speed;
  if(cam_rot_x < -180)
    cam_rot_x= 180;
  updateGL();
}
void GLDrawer::rotateCameraLeft() {
  cam_rot_y -= cam_rot_speed;
  if(cam_rot_y < -180)
    cam_rot_y = 180;
  updateGL();
}
void GLDrawer::rotateCameraRight() {
  cam_rot_y += cam_rot_speed;
  if(cam_rot_y > 180)
    cam_rot_y = -180;
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

void GLDrawer::toggleLights() {
  if(lights_on) {
    lights_on = false;
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
  }
  else {
    lights_on = true;
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
  }
  updateGL();
}

void GLDrawer::toggleTexturing() {
  if(use_textures) {
    use_textures = false;
    glDisable(GL_TEXTURE_2D);
  }
  else {
    use_textures = true;
    glEnable(GL_TEXTURE_2D);
  }
  updateGL();
}

void GLDrawer::changeTree() {
  QFile file(tree_file);
  
  if(!file.exists()) {
    emit textOutput(QString("Tree file %1 is not found!").arg(tree_file));
  }
  else {
    delete tree;
    
    tree = new BSPTree();
    BSPPolygonSet polygons;
    
    //Tree<ScotsPineSegment, ScotsPineBud> pine2(Point(0,0,0), PositionVector(0,1,0));
    Tree<SugarMapleSegment, SugarMapleBud> pine2(Point(0,0,0), PositionVector(0,1,0));
        
    //XMLDomTreeReader<ScotsPineSegment, ScotsPineBud> reader;
    XMLDomTreeReader<SugarMapleSegment, SugarMapleBud> reader;
    reader.readXMLToTree(pine2, tree_file.toStdString());
    
    //LGMPolygonTree<ScotsPineSegment, ScotsPineBud> constructor;
    LGMPolygonTree<SugarMapleSegment, SugarMapleBud> constructor;
    
    BSPPolygonSet* treePolygons = constructor.buildTree(pine2, parameters);
    polygons.addPolygons(treePolygons);
    delete treePolygons;
    
    
    //BSPPolygonSet* ground = makeSquare(10, 10, Point(5,0,-5), PositionVector(0,1,0), green, 0, 2);
    //polygons.addPolygons(ground);
    //delete ground;
    
    list<CylinderVolume>* cylinders = constructor.getCylinders();
    //polygons.removeHiddenPolygons(cylinders);
    
    
    tree->buildBSPTree(polygons, cylinders);

    cout << "polygons: " << tree->countPolygons() << endl;
    updateGL();
    cout << "components: " << tree->countComponents() << endl;
    cout << "depth:" << tree->getDepth() << endl;
    cout << "nodes:" << tree->getNodeCount() << endl;
    delete cylinders;
    
    r_axis = GetDirection(GetRootAxis(pine2));
    t_point = GetPoint(pine2);
    t_height = GetValue(pine2, LGAH);
    r_axis = r_axis.normalize();
    r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
    t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
    
    resetCamera();
    
    updateGL();
    
    emit textOutput(QString("Tree file %1 has been loaded.").arg(tree_file));
    //PositionVector cross(Cross(PositionVector(0,1,0), PositionVector(0,2,0)));
    //cout << "cross: " << cross.getX() << " " << cross.getY() << " " << cross.getZ() << endl;
  }
}
  

void GLDrawer::paintGL()  {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();


  glRotatef(cam_rot_x, 1, 0, 0);  
  glRotatef(cam_rot_y, 0, 1, 0);


  glTranslatef(-camera_x, -camera_y, -camera_z);   
  glRotatef(-90, 1, 0, 0);

  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);

  PositionVector pv(camera_x, camera_y, camera_z);
  pv = pv.rotate(Point(0,0,0), PositionVector(1,0,0), DEGTORAD*90);
  Point eye(pv.getX(), pv.getY(), pv.getZ());
  
  PositionVector direction(sin(cam_rot_y*DEGTORAD),
			   cos(cam_rot_y*DEGTORAD),
			   sin(-cam_rot_x*DEGTORAD));
  tree->drawTree(eye, direction);
  glFlush();
}

BSPPolygonSet* GLDrawer::makeCylinder(double radius, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, BSPPolygonMaterial* material, int texture, int detail) {

  double sine, cosine, sine_next, cosine_next;
  BSPPolygonSet* polygons = new BSPPolygonSet();
  SceneObject* object = new SceneObject(material, texture, false);
  //  glBegin(GL_TRIANGLES);
  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);

  Point origo(0,0,0);
  vector<Point> vertices(3);
  vector<Point> t_vertices(3);
  
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
    
    /*vertices[0] = Point(v1)+point;
    vertices[1] = Point(v2)+point;
    vertices[2] = Point(v3)+point;
    t_vertices[0] = Point(i/(double)detail, 0, 0);
    t_vertices[1] = Point(i/(double)detail, 1, 0);
    t_vertices[2] = Point((i+1)/(double)detail, 0, 0);
    polygons->addPolygon(new BSPPolygon(vertices, t_vertices, object));*/
    

    polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					 Point(v2)+point,
					 Point(v3)+point,
					 Point(i/(double)detail, 0, 0),
					 Point(i/(double)detail, 1, 0),
					 Point((i+1)/(double)detail, 0, 0),
					 object));

    v1 = PositionVector(sine_next, 0, cosine_next);
    v2 = PositionVector(sine, height, cosine);
    v3 = PositionVector(sine_next, height, cosine_next);
    v1 = v1.rotate(origo, dir, PI);
    v2 = v2.rotate(origo, dir, PI);
    v3 = v3.rotate(origo, dir, PI);

    /*    vertices[0] = Point(v1)+point;
    vertices[1] = Point(v2)+point;
    vertices[2] = Point(v3)+point;
    t_vertices[0] = Point((i+1)/(double)detail, 0, 0);
    t_vertices[1] = Point(i/(double)detail, 1, 0);
    t_vertices[2] = Point((i+1)/(double)detail, 1, 0);
    poygons->addPolygon(new BSPPolygon(vertices, t_vertices, object));*/
    
    polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					Point(v2)+point,
					Point(v3)+point,
					Point((i+1)/(double)detail, 0, 0),
					Point(i/(double)detail, 1, 0),
					Point((i+1)/(double)detail, 1, 0),
					object));


    if(drawTop) {
      v1 = PositionVector(sine, height, cosine);
      v2 = PositionVector(0, height, 0);
      v3 = PositionVector(sine_next, height, cosine_next);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);

      /*vertices[0] = Point(v1)+point;
      vertices[1] = Point(v2)+point;
      vertices[2] = Point(v3)+point;
      polygons->addPolygon(new BSPPolygon(vertices, object));*/
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  object));

      
    }
    
    if(drawBottom) {
      v1 = PositionVector(sine, 0, cosine);
      v2 = PositionVector(sine_next, 0, cosine_next);
      v3 = PositionVector(0, 0, 0);
      
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);

      /*vertices[0] = Point(v1)+point;
      vertices[1] = Point(v2)+point;
      vertices[2] = Point(v3)+point;      
      polygons->addPolygon(new BSPPolygon(vertices, object));*/
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  object));
      
      
    }
  }
  return polygons;
}

BSPPolygonSet* GLDrawer::makeSquare(double height, double width, Point point, PositionVector direction, BSPPolygonMaterial* material, int texture, int detail) {

  double x1, z1, x2, z2;
  double tx1, tz1, tx2, tz2;
  BSPPolygonSet* polygons = new BSPPolygonSet();
  SceneObject* object = new SceneObject(material, texture, false);

  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);

  Point origo(0,0,0);
  vector<Point> vertices(3);
  vector<Point> t_vertices(3);

  for(int i = 0; i < detail; i++) {
    z1 = height*(i     / (double)detail-0.5);
    z2 = height*((i+1) / (double)detail-0.5);
    tz1 = i     / (double)detail;
    tz2 = (i+1) / (double)detail;
    for(int j = 0; j < detail; j++) {
      x1 = width*(j     / (double)detail-0.5);
      x2 = width*((j+1) / (double)detail-0.5);
      tx1 = j     / (double)detail;
      tx2 = (j+1) / (double)detail;

      PositionVector v1(x1, 0, z1);
      PositionVector v2(x1, 0, z2);
      PositionVector v3(x2, 0, z1);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      /*vertices[0] = Point(v1)+point;
      vertices[1] = Point(v3)+point;
      vertices[2] = Point(v2)+point;
      t_vertices[0] = Point(tx1, tz1, 0);
      t_vertices[1] = Point(tx2, tz1, 0);
      t_vertices[2] = Point(tx1, tz2, 0);
      polygons->addPolygon(new BSPPolygon(vertices, t_vertices, object));*/

      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v3)+point,
					  Point(v2)+point,
					  Point(tx1, tz1, 0),
					  Point(tx2, tz1, 0),
					  Point(tx1, tz2, 0),
					  object));
      
      
      v1 = PositionVector(x2, 0, z1);
      v2 = PositionVector(x1, 0, z2);
      v3 = PositionVector(x2, 0, z2);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);

      /*vertices[0] = Point(v1)+point;
      vertices[1] = Point(v3)+point;
      vertices[2] = Point(v2)+point;
      t_vertices[0] = Point(tx2, tz1, 0);
      t_vertices[1] = Point(tx2, tz2, 0);
      t_vertices[2] = Point(tx1, tz2, 0);
      polygons->addPolygon(new BSPPolygon(vertices, t_vertices, object));*/

      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v3)+point,
					  Point(v2)+point,
					  Point(tx2, tz1, 0),
					  Point(tx2, tz2, 0),
					  Point(tx1, tz2, 0),
					  object));
    }
  }
  return polygons;
}

bool GLDrawer::isExtensionSupported(char* szTargetExtension) {
	const unsigned char *pszExtensions = NULL;
	const unsigned char *pszStart;
	unsigned char *pszWhere, *pszTerminator;

	// Extension names should not have spaces
	pszWhere = (unsigned char *) strchr( szTargetExtension, ' ' );
	if( pszWhere || *szTargetExtension == '\0' )
		return false;

	// Get Extensions String
	pszExtensions = glGetString( GL_EXTENSIONS );

	// Search The Extensions String For An Exact Copy
	pszStart = pszExtensions;
	for(;;)
	{
		pszWhere = (unsigned char *) strstr( (const char *) pszStart, szTargetExtension );
		if( !pszWhere )
			break;
		pszTerminator = pszWhere + strlen( szTargetExtension );
		if( pszWhere == pszStart || *( pszWhere - 1 ) == ' ' )
			if( *pszTerminator == ' ' || *pszTerminator == '\0' )
				return true;
		pszStart = pszTerminator;
	}
	return false;
}

void GLDrawer::mousePressEvent(QMouseEvent* event) {
  m_last_pos = event->pos();
}

void GLDrawer::mouseReleaseEvent(QMouseEvent* event) {

}

void GLDrawer::mouseMoveEvent(QMouseEvent* event) {
  int dx = event->x() - m_last_pos.x();
  int dy = event->y() - m_last_pos.y();

  if (event->buttons() & Qt::LeftButton) {
    cam_rot_x += m_look_speed*dy;
    if(cam_rot_x > 180)
      cam_rot_x = -180;
    else if(cam_rot_x < -180)
      cam_rot_x = 180;

    cam_rot_y += m_look_speed*dx;
    if(cam_rot_y > 180)
      cam_rot_y = -180;
    else if(cam_rot_y < -180)
      cam_rot_y = 180;
  } 
  else if (event->buttons() & Qt::RightButton) {
    camera_x += 0.01*dy*sin(cam_rot_y*DEGTORAD);
    camera_z -= 0.01*dy*cos(cam_rot_y*DEGTORAD);
    camera_y += 0.01*dy*sin(-cam_rot_x*DEGTORAD);
  }
  updateGL();
  m_last_pos = event->pos();
}

void GLDrawer::keyPressEvent(QKeyEvent* event) {
  int key = event->key();
  switch(key) 
    {
    case Qt::Key_W:
      moveCameraForward();
      break;
    case Qt::Key_S:
      moveCameraBackward();
      break;
    case Qt::Key_A:
      rotateCameraLeft();
      break;
    case Qt::Key_D:
      rotateCameraRight();
      break;
    case Qt::Key_Q:
      rotateCameraUp();
      break;
    case Qt::Key_E:
      rotateCameraDown();
      break;
    case Qt::Key_I:
      toggleWireModel();
      break;
    case Qt::Key_L:
      toggleLights();
      break;
    case Qt::Key_J:
      changeTree();
      break;
    case Qt::Key_T:
      toggleTexturing();
      break;
    }
  //    updateGL();
}

void GLDrawer::keyReleaseEvent(QKeyEvent* event) {

}

void GLDrawer::setTreeFile(QString fileName) {
  tree_file = fileName;
}

void GLDrawer::setCylinderRDetail(int detail) {
  parameters.setCylinderRDetail(detail);
}

void GLDrawer::setCylinderHDetail(int detail) {
  parameters.setCylinderHDetail(detail);
}

void GLDrawer::setCylinderTexture(QString texture) {
  QFile file(texture);
  
  if(file.exists()) {
    int tex = loadTexture(texture.toStdString());
    parameters.setCylinderTexture(tex);
  }
  else 
    cout << "Texture file: " << texture.toStdString() << " is not found!" << endl;
}

void GLDrawer::setLeafTexture(QString texture) {
  QFile file(texture);
  
  if(file.exists()) {
    int tex = loadTexture(texture.toStdString());
    parameters.setLeafTexture(tex);
  }
  else 
    cout << "Texture file: " << texture.toStdString() << " is not found!" << endl;
}

void GLDrawer::setFoliageTexture(QString texture) {
  QFile file(texture);
  
  if(file.exists()) {
    int tex = loadTexture(texture.toStdString());
    parameters.setFoliageTexture(tex);
  }
  else 
    cout << "Texture file: " << texture.toStdString() << " is not found!" << endl;
}


void GLDrawer::resetCamera() {

  
  double translate = 2*t_height;
  cout << "point: " << t_point.getX() << " " << t_point.getY() << " " << t_point.getZ() << endl;
  cout << "height: " << t_height << endl;
  camera_x = t_point.getX();
  camera_y = t_point.getY() - t_height/2*r_axis.getZ();
  camera_z = t_point.getZ() + translate;
  Point camera(camera_x, camera_y, camera_z);
  cout << "camera: " << camera_x << " " << camera_y << " " << camera_z << endl;

  Point p(t_point.getX(), t_point.getY() - (t_height/2.0)*r_axis.getZ(), t_point.getZ());
  PositionVector direction(PositionVector(p - camera));
  direction = direction.normalize();
  cout << "direction: " << direction.getX() << " " << direction.getY() << " " << direction.getZ() << endl;
  cam_rot_x = 1/DEGTORAD*asin(direction.getY());
  cam_rot_y = 1/DEGTORAD*asin(direction.getX());
  cam_rot_z = 1/DEGTORAD*acos(r_axis.getZ());
  
  updateGL();
}

void GLDrawer::useBSP(bool use) {
  parameters.setBSPUsage(use);
}

void GLDrawer::useLeafTextures(bool use) {
  parameters.setLeafTextureUsage(use);
}
 
void GLDrawer::setLeafDetail(int detail) {
  parameters.setLeafDetail(detail);
}