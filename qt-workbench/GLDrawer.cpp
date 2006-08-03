// Qt includes
#include <QtGui>
#include <QtOpenGL>
#include <QHash>

// Standard C/C++ includes
#include <vector>
#include <ctime>
#include <math.h>
#include <iostream>

// Workbench includes
#include "BSPTree.h"
#include "GLDrawer.h"
#include "SceneObject.h"

// Lignum related includes
#include <Lignum.h>
#include <GenericCfTree.h>
#include <GenericHwTree.h>
#include <XMLTree.h>
#include <Turtle.h>

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
  setCylinderRDetail(10);
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

  light0_position[0] = 0;
  light0_position[1] = 1;
  light0_position[2] = 1;
  light0_position[3] = 0;

  GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light0_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
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
  GLfloat shine[] = { 50 };
  
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_EMISSION, emission);
  glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}

void GLDrawer::initTextureSettings() {
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glEnable(GL_TEXTURE_2D);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int GLDrawer::loadTexture(std::string fileName) {
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
    
    //XMLDomTreeReader<ScotsPineSegment, ScotsPineBud> cf_reader;
    XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud> cf_reader;


    /*if(cf_reader.treeType(tree_file.toStdString()) == XMLDomTreeReader<ScotsPineSegment, ScotsPineBud>::Cf) {
      Tree<ScotsPineSegment, ScotsPineBud> cftree(Point(0,0,0), PositionVector(0,1,0));
      cf_reader.readXMLToTree(cftree, tree_file.toStdString());
      LGMPolygonTree<ScotsPineSegment, ScotsPineBud> constructor;
      BSPPolygonSet* treePolygons = constructor.buildTree(cftree, parameters);
      polygons.addPolygons(treePolygons);
      delete treePolygons;

      r_axis = GetDirection(GetRootAxis(cftree));
      t_point = GetPoint(cftree);
      t_height = GetValue(cftree, LGAH);
      r_axis = r_axis.normalize();
      r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
      t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
      }*/
    if(cf_reader.treeType(tree_file.toStdString()) == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::Cf) {
      Tree<GenericCfTreeSegment, GenericCfBud> cftree(Point(0,0,0), PositionVector(0,1,0));
      cf_reader.readXMLToTree(cftree, tree_file.toStdString());
      LGMPolygonTree<GenericCfTreeSegment, GenericCfBud> constructor;
      BSPPolygonSet* treePolygons = constructor.buildTree(cftree, parameters);
      polygons.addPolygons(treePolygons);
      delete treePolygons;

      r_axis = GetDirection(GetRootAxis(cftree));
      t_point = GetPoint(cftree);
      t_height = GetValue(cftree, LGAH);
      r_axis = r_axis.normalize();
      r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
      t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
      }
    else {
      if(cf_reader.leafType(tree_file.toStdString()) == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::TRIANGLE) {
	XMLDomTreeReader<GenericHwTriangleTreeSegment, GenericHwTriangleBud> hwt_reader;	
	Tree<GenericHwTriangleTreeSegment, GenericHwTriangleBud> hwtree(Point(0,0,0), PositionVector(0,1,0));
	hwt_reader.readXMLToTree(hwtree, tree_file.toStdString());
	LGMPolygonTree<GenericHwTriangleTreeSegment, GenericHwTriangleBud> constructor;
	BSPPolygonSet* treePolygons = constructor.buildTree(hwtree, parameters);
	polygons.addPolygons(treePolygons);
	delete treePolygons;
	
	r_axis = GetDirection(GetRootAxis(hwtree));
	t_point = GetPoint(hwtree);
	t_height = GetValue(hwtree, LGAH);
	r_axis = r_axis.normalize();
	r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
	t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
      }
      else if (cf_reader.leafType(tree_file.toStdString()) == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::ELLIPSE) {
	XMLDomTreeReader<GenericHwEllipseTreeSegment, GenericHwEllipseBud> hwt_reader;	
	Tree<GenericHwEllipseTreeSegment, GenericHwEllipseBud> hwtree(Point(0,0,0), PositionVector(0,1,0));
	hwt_reader.readXMLToTree(hwtree, tree_file.toStdString());
	LGMPolygonTree<GenericHwEllipseTreeSegment, GenericHwEllipseBud> constructor;
	BSPPolygonSet* treePolygons = constructor.buildTree(hwtree, parameters);
	polygons.addPolygons(treePolygons);
	delete treePolygons;
	
	r_axis = GetDirection(GetRootAxis(hwtree));
	t_point = GetPoint(hwtree);
	t_height = GetValue(hwtree, LGAH);
	r_axis = r_axis.normalize();
	r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
	t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
      }
    }
    /*else {
      Tree<SugarMapleSegment, SugarMapleBud> hwtree(Point(0,0,0), PositionVector(0,1,0));
      hw_reader.readXMLToTree(hwtree, tree_file.toStdString());
      LGMPolygonTree<SugarMapleSegment, SugarMapleBud> constructor;
      BSPPolygonSet* treePolygons = constructor.buildTree(hwtree, parameters);
      polygons.addPolygons(treePolygons);
      delete treePolygons;

      r_axis = GetDirection(GetRootAxis(hwtree));
      t_point = GetPoint(hwtree);
      t_height = GetValue(hwtree, LGAH);
      r_axis = r_axis.normalize();
      r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
      t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
      }*/
      
    
      //BSPPolygonSet* ground = makeSquare(10, 10, Point(5,0,-5), PositionVector(0,1,0), green, 0, 2);
      //polygons.addPolygons(ground);
      //delete ground;
    
    tree->buildBSPTree(polygons);

    cout << "polygons: " << tree->countPolygons() << endl;
    updateGL();
    cout << "components: " << tree->countComponents() << endl;
    cout << "depth:" << tree->getDepth() << endl;
    cout << "nodes:" << tree->getNodeCount() << endl;
    
    resetCamera();
    
    updateGL();
    
    emit textOutput(QString("Tree file %1 has been loaded.").arg(tree_file));
  }
}
  

void GLDrawer::paintGL()  {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glRotatef(cam_rot_x, 1, 0, 0);  
  glRotatef(cam_rot_y, 0, 1, 0);
  glTranslatef(-camera_x, -camera_y, -camera_z);   

  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glRotatef(-90, 1, 0, 0);


  PositionVector pv(camera_x, camera_y, camera_z);
  pv = pv.rotate(Point(0,0,0), PositionVector(1,0,0), DEGTORAD*90);
  Point eye(pv.getX(), pv.getY(), pv.getZ());
  
  PositionVector direction(sin(cam_rot_y*DEGTORAD),
			   cos(cam_rot_y*DEGTORAD),
			   sin(-cam_rot_x*DEGTORAD));

  tree->drawTree(eye, direction);
  glFlush();
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

/*void GLDrawer::mouseReleaseEvent(QMouseEvent* event) {

}*/

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
    Turtle turtle;
    turtle.turn(-cam_rot_y*DEGTORAD);
    turtle.pitch(cam_rot_x*DEGTORAD);

    PositionVector heading = GetHeading(turtle);
    camera_x -= dy*0.01*heading.getX();
    camera_y += dy*0.01*heading.getY();
    camera_z -= dy*0.01*heading.getZ();
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

/*void GLDrawer::keyReleaseEvent(QKeyEvent* event) {

}*/

void GLDrawer::setTreeFile(QString fileName) {
  tree_file = fileName;
}

void GLDrawer::setCylinderRDetail(int detail) {
  parameters.setSegmentRDetail(detail);
}

void GLDrawer::setCylinderHDetail(int detail) {
  parameters.setSegmentHDetail(detail);
}

void GLDrawer::setCylinderTexture(QString texture) {
  if(textures.contains(texture)) {
    parameters.setSegmentTexture(textures.value(texture));
  }
  else {
    QFile file(texture);
    
    if(file.exists()) {
      int tex = loadTexture(texture.toStdString());
      parameters.setSegmentTexture(tex);
      textures.insert(texture, tex);
    }
    else 
      cout << "Texture file: " << texture.toStdString() << " is not found!" << endl;
  }
}
  
void GLDrawer::setLeafTexture(QString texture) {
  if(textures.contains(texture)) {
    parameters.setLeafTexture(textures.value(texture));
  }
  else {
    QFile file(texture);
    
    if(file.exists()) {
      int tex = loadTexture(texture.toStdString());
      parameters.setLeafTexture(tex);
      textures.insert(texture, tex);
    }
    else 
      cout << "Texture file: " << texture.toStdString() << " is not found!" << endl;
  }
}

void GLDrawer::setFoliageTexture(QString texture) {
  if(textures.contains(texture)) {
    parameters.setFoliageTexture(textures.value(texture));
  }
  else {
    QFile file(texture);
    
    if(file.exists()) {
      int tex = loadTexture(texture.toStdString());
      parameters.setFoliageTexture(tex);
      textures.insert(texture, tex);
    }
    else 
      cout << "Texture file: " << texture.toStdString() << " is not found!" << endl;
  }
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
