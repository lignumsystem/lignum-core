// Qt includes
#include <QtGui>
#include <QtOpenGL>
#include <QHash>
#include <QMultiHash>

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

#include <QMetaType>

using namespace std;
using namespace Lignum;

GLDrawer::GLDrawer(QWidget* parent)
  : QGLWidget(parent) {
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
  t_rot_y = 0;
  t_rot_x = 0;

  distance = 1;

  tree_trans_x = 0;
  tree_trans_y = 0;
  tree_trans_z = 0;

  DEGTORAD = 2*3.14159265/360.0;

  parameters.setWireframeUsage(false);
  parameters.setLightingUsage(true);
  parameters.setTexturingUsage(true);

  parameters.setSegmentTextureFile(std::string("pine_texture.png"));
  parameters.setLeafTextureFile(std::string("maple_texture.png"));
  parameters.setFoliageTextureFile(std::string("foliage.png"));

  PI = 3.14159265;
  m_look_speed = 0.3;
  setFocusPolicy(Qt::ClickFocus);
  
  srand((unsigned)time(0)); 
  
  tree_file = QString("test.xml");
  
  tree = new BSPTree();
  setCylinderRDetail(10);
  setCylinderHDetail(1);
  setLeafDetail(10);

  settingsChanged = true;
  
  control_mode = ORBIT;

  qRegisterMetaType<BSPTree*>("BSPTree*");
  qRegisterMetaType<Point>("Point");
  qRegisterMetaType<PositionVector>("PositionVector");
  qRegisterMetaType<SceneObject*>("SceneObject*");
  qRegisterMetaType<QMultiHash<int, SceneObject*>* >("QMultiHash<int, SceneObject*>*");

  qRegisterMetaType<QHash<QString, QMultiHash<int, SceneObject*>* >* >("QHash<QString, QMultiHash<int, SceneObject*>* >*");
  connect(&thread, SIGNAL(treesLoaded(BSPTree*, Point, PositionVector, double,
				      QHash<QString, QMultiHash<int, SceneObject*>* >*)),
	  this, SLOT(updateTrees(BSPTree*, Point, PositionVector, double,
				      QHash<QString, QMultiHash<int, SceneObject*>* >*)));
}

void GLDrawer::initMaterials() {
  GLfloat color1[] = {0.0, 100.0/255.0, 0.0, 1.0,
		      0.0, 100.0/255.0, 0.0, 1.0,
		      0.0, 0.1, 0.0, 1.0,
		      5};
  GLfloat color2[] = {0.9, 0.2, 0.2, 1.0,
		      0.9, 0.1, 0.1, 1.0,
		      0.2, 0.1, 0.1, 1.0,
		      50};
  GLfloat color3[] = {1.0, 1.0, 1.0, 1.0,
		      1.0, 1.0, 1.0, 1.0,
		      0.2, 0.2, 0.2, 1.0,
		      50};

  GLfloat budAliveColor[]   = {255.0/255.0, 185.0/255.0, 15.0/255.0, 1.0,
			       255.0/255.0, 185.0/255.0, 15.0/255.0, 1.0,
			       0.2, 0.2, 0.2, 1.0,
			       50};
  GLfloat budDeadColor[]    = {0.0, 0.0, 0.0, 1.0,
			       0.0, 0.0, 0.0, 1.0,
			       0.2, 0.2, 0.2, 1.0,
			       50};
  GLfloat budDormantColor[] = {72.0/255.0, 118.0/255.0, 255/255.0, 1.0,
			       72.0/255.0, 118.0/255.0, 255/255.0, 1.0,
			       0.2, 0.2, 0.2, 1.0,
			       50};
  GLfloat budFlowerColor[]  = {255.0/255.0, 48.0/255.0, 48.0/255.0, 1.0,
			       255.0/255.0, 48.0/255.0, 48.0/255.0, 1.0,
			       0.2, 0.2, 0.2, 1.0,
			       50};
  GLfloat dominantColor[]  = {255.0/255.0, 185.0/255.0, 15.0/255.0, 1.0,
			      255.0/255.0, 185.0/255.0, 15.0/255.0, 1.0,
			      0.2, 0.2, 0.2, 1.0,
			      50};
  GLfloat nondominantColor[]  = {255.0/255.0, 48.0/255.0, 48.0/255.0, 1.0,
				 255.0/255.0, 48.0/255.0, 48.0/255.0, 1.0,
				 0.2, 0.2, 0.2, 1.0,
				 50};
  GLfloat shootColor[]  = {72.0/255.0, 118.0/255.0, 255.0/255.0, 1.0,
			   72.0/255.0, 118.0/255.0, 255.0/255.0, 1.0,
			   0.2, 0.2, 0.2, 1.0,
			   50};
  GLfloat shootAboveColor[]  = {255.0/255.0, 140.0/255.0, 0.0/255.0, 1.0,
				255.0/255.0, 140.0/255.0, 0.0/255.0, 1.0,
				0.2, 0.2, 0.2, 1.0,
				50};
  
  green = new BSPPolygonMaterial(color1);
  red = new BSPPolygonMaterial(color2);
  white = new BSPPolygonMaterial(color3);
  budAlive = new BSPPolygonMaterial(budAliveColor);
  budDead = new BSPPolygonMaterial(budDeadColor);
  budDormant = new BSPPolygonMaterial(budDormantColor);
  budFlower = new BSPPolygonMaterial(budFlowerColor);
  dominant = new BSPPolygonMaterial(dominantColor);
  nondominant = new BSPPolygonMaterial(nondominantColor);
  shoot = new BSPPolygonMaterial(shootColor);
  shootAbove = new BSPPolygonMaterial(shootAboveColor);
  
  parameters.setMaterial(white);
  parameters.setLeafMaterial(green);
  parameters.setPetioleMaterial(green);
  parameters.setBudAliveMaterial(budAlive);
  parameters.setBudDeadMaterial(budDead);
  parameters.setBudDormantMaterial(budDormant);
  parameters.setBudFlowerMaterial(budFlower);
  parameters.setDominantMaterial(dominant);
  parameters.setNondominantMaterial(nondominant);
  parameters.setShootMaterial(shoot);
  parameters.setShootAboveMaterial(shootAbove);
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
  glShadeModel(GL_SMOOTH);
  
  initMaterials();
  initLights();
  initTextureSettings();

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
  gluPerspective(60.0, (GLfloat)width/(GLfloat)height, 0.01, 20.0);
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

bool GLDrawer::setTextures() {
  setCylinderTexture(QString(parameters.getSegmentTextureFile().c_str()));
  
  setLeafTexture(QString(parameters.getLeafTextureFile().c_str()));
  
  setFoliageTexture(QString(parameters.getFoliageTextureFile().c_str()));
  
  return true;
}

void GLDrawer::setParameterSettings() {
  if(settingsChanged) {
    settingsChanged = false;
    
    if(parameters.useWireframe())
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if(parameters.useLighting()) 
      glEnable(GL_LIGHTING);
    else
      glDisable(GL_LIGHTING);
    
    if(parameters.useTexturing())
      glEnable(GL_TEXTURE_2D);
    else
      glDisable(GL_TEXTURE_2D);
    
    /* setCylinderTexture(QString(parameters.getSegmentTextureFile().c_str()));
    setLeafTexture(QString(parameters.getLeafTextureFile().c_str()));
    setFoliageTexture(QString(parameters.getFoliageTextureFile().c_str()));*/
  }
}

void GLDrawer::toggleWireModel() {
  parameters.setWireframeUsage(!parameters.useWireframe());
  settingsChanged = true;
  updateGL();
}

void GLDrawer::toggleLights() {
  parameters.setLightingUsage(!parameters.useLighting());
  settingsChanged = true;
  updateGL();
}

void GLDrawer::toggleTexturing() {
  parameters.setTexturingUsage(!parameters.useTexturing());
  settingsChanged = true;
  updateGL();
}

/*void GLDrawer::changeTree(const QDomDocument& doc) 
{
  
}*/

void GLDrawer::resetVisualization() {
  delete tree;
  tree = NULL;
  QList<QString> objects = sceneObjects->keys();
  for(int i = 0; i < objects.size(); i++) {
    if(sceneObjects->contains(objects[i])) {
      delete sceneObjects->value(objects[i]);
    }
  }
  sceneObjects->clear();
  delete sceneObjects;
  selectedObjects.clear();
  objectLists.clear();
  updateGL();
}

void GLDrawer::resetVisualization(QList<QString> files) {
  //  resetVisualization();
  //for(int i = 0; i < files.size(); i++) {
  //	 addTree(files[i]);
  //}
  setTextures();
  thread.loadTrees(files, parameters);
}

void GLDrawer::addTree(QString fileName) {
  /*  setTextures();

  QFile file(fileName);

  if(!file.exists()) {
    emit textOutput(QString("Tree file %1 is not found!").arg(tree_file));
  }
  else {

    BSPPolygonSet polygons;
        
    XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud> cf_reader;

    if(cf_reader.treeType(fileName.toStdString()) == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::Cf) {
      Tree<GenericCfTreeSegment, GenericCfBud> cftree(Point(0,0,0), PositionVector(0,1,0));
      cf_reader.readXMLToTree(cftree, fileName.toStdString());

      LGMPolygonTree<GenericCfTreeSegment, GenericCfBud> constructor;
      BSPPolygonSet* treePolygons = constructor.buildTree(cftree, parameters,
							  cf_reader.getTreeCompartmentHash(),
							  cf_reader.getLeafHash());
      polygons.addPolygons(treePolygons);
      delete treePolygons;
      sceneObjects.insert(fileName, constructor.getSceneObjects());

      r_axis = GetDirection(GetRootAxis(cftree));
      t_point = GetPoint(cftree);
      t_height = GetValue(cftree, LGAH);
      r_axis = r_axis.normalize();
      r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
      t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
      }
    else {
      if(cf_reader.leafType(fileName.toStdString()) == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::TRIANGLE) {
	
	XMLDomTreeReader<GenericHwTriangleTreeSegment, GenericHwTriangleBud, Triangle> hwt_reader;	
	Tree<GenericHwTriangleTreeSegment, GenericHwTriangleBud> hwtree(Point(0,0,0), PositionVector(0,1,0));
	hwt_reader.readXMLToTree(hwtree, fileName.toStdString());

	LGMPolygonTree<GenericHwTriangleTreeSegment, GenericHwTriangleBud, Triangle> constructor;
	BSPPolygonSet* treePolygons = constructor.buildTree(hwtree, parameters,
							    hwt_reader.getTreeCompartmentHash(),
							    hwt_reader.getLeafHash());
	polygons.addPolygons(treePolygons);
	delete treePolygons;
	sceneObjects.insert(fileName, constructor.getSceneObjects());
	
	r_axis = GetDirection(GetRootAxis(hwtree));
	t_point = GetPoint(hwtree);
	t_height = GetValue(hwtree, LGAH);
	r_axis = r_axis.normalize();
	r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
	t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
      }
      else if (cf_reader.leafType(fileName.toStdString()) == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::ELLIPSE) {
	XMLDomTreeReader<GenericHwEllipseTreeSegment, GenericHwEllipseBud, cxxadt::Ellipse> hwt_reader;	
	Tree<GenericHwEllipseTreeSegment, GenericHwEllipseBud> hwtree(Point(0,0,0), PositionVector(0,1,0));
	hwt_reader.readXMLToTree(hwtree, fileName.toStdString());

	LGMPolygonTree<GenericHwEllipseTreeSegment, GenericHwEllipseBud, cxxadt::Ellipse> constructor;
	BSPPolygonSet* treePolygons = constructor.buildTree(hwtree, parameters,
							    hwt_reader.getTreeCompartmentHash(),
							    hwt_reader.getLeafHash());
	polygons.addPolygons(treePolygons);
	delete treePolygons;
	sceneObjects.insert(fileName, constructor.getSceneObjects());
	
	r_axis = GetDirection(GetRootAxis(hwtree));
	t_point = GetPoint(hwtree);
	t_height = GetValue(hwtree, LGAH);
	r_axis = r_axis.normalize();
	r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
	t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
      }
    }
    
    //BSPPolygonSet* ground = makeSquare(10, 10, Point(t_point.getX(), -t_point.getZ(), t_point.getY()),
    //				       PositionVector(r_axis.getX(), -r_axis.getZ(), r_axis.getY()), green, 0, 2);
    //polygons.addPolygons(ground);
    //delete ground;

    // tree->buildBSPTree(polygons);
    QList<QString> files = sceneObjects.keys();
    for(int i = 0; i < files.size(); i++) {
      if(sceneObjects.contains(files[i])) {
	objectLists.insert(files[i], sceneObjects.value(files[i])->values());
      }
    }

    tree->addPolygonsToTree(polygons);

    cout << "polygons: " << tree->countPolygons() << endl;
    updateGL();
    cout << "components: " << tree->countComponents() << endl;
    cout << "depth:" << tree->getDepth() << endl;
    cout << "nodes:" << tree->getNodeCount() << endl;
    
    resetCamera();

    updateGL();
    }*/
}
  

void GLDrawer::paintGL()  {
  // Clear buffers and load identity matrix
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  setParameterSettings();

  PositionVector pv(0.0, 0.0, 0.0);
  if(control_mode == MOUSE_LOOK) {
    glRotatef(cam_rot_x, 1, 0, 0);  
    glRotatef(cam_rot_y, 0, 1, 0);
    glTranslatef(-camera_x, -camera_y, -camera_z);   
    
    //glScalef(-1.0, 0, 0);
    
    glTranslatef(t_point.getX(), t_point.getY() + 0.5*t_height, t_point.getZ());
    glRotatef(t_rot_x, 1, 0, 0);
    glTranslatef(0, -0.5*t_height, 0); 
    glRotatef(t_rot_y, r_axis.getX(), r_axis.getZ(), -r_axis.getY());
    glTranslatef(-t_point.getX(), -t_point.getY(), -t_point.getZ());
    
    pv = PositionVector(camera_x, camera_y, camera_z);
    
    pv = pv.rotate(Point(t_point.getX(), t_point.getY() + 0.5*t_height, t_point.getZ()),
		   PositionVector(1,0,0), -DEGTORAD*t_rot_x);
    pv = pv.rotate(Point(t_point.getX(), t_point.getY(), t_point.getZ()),
		   PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY()), -DEGTORAD*t_rot_y);
    pv = pv.rotate(Point(0,0,0), PositionVector(1,0,0), DEGTORAD*90);
  }
  else {

    glTranslatef(0.0, 0.0, -distance);
    glRotatef(-cam_rot_x, 1.0, 0.0, 0.0);
    glRotatef(cam_rot_y, 0.0, 1.0, 0.0);
    glTranslatef(-tree_trans_x,
		 -tree_trans_y,
		 -tree_trans_z);
    
    // Rotate the position of the eye accordingly 
    pv = PositionVector(0, 0, distance);
    
    pv = pv.rotate(Point(0,0,0), PositionVector(1, 0, 0), DEGTORAD*cam_rot_x);
    pv = pv.rotate(Point(0,0,0), PositionVector(0, 1, 0), -DEGTORAD*cam_rot_y);
 
    pv = pv + PositionVector(tree_trans_x, tree_trans_y, tree_trans_z);
    pv = pv.rotate(Point(0,0,0), PositionVector(1,0,0), DEGTORAD*90);
   
  }
  Point eye(pv.getX(), pv.getY(), pv.getZ());
  
  PositionVector direction(sin(cam_rot_y*DEGTORAD),
			   cos(cam_rot_y*DEGTORAD),
			   sin(-cam_rot_x*DEGTORAD));
  
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

  // Transform from LIGNUM-coordinates to OpenGL-coordinates
  glRotatef(-90, 1, 0, 0);
  


  if(tree)
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
    if(control_mode == MOVE_TREE) {
      //tree_trans_x += 0.01*dx;
      //tree_trans_z += 0.01*dy;
      Turtle turtle;
      turtle.turn(-cam_rot_y*DEGTORAD);
      PositionVector heading = GetHeading(turtle);
      tree_trans_x -= dy*0.01*heading.getX();
      tree_trans_z -= dy*0.01*heading.getZ();
      
      turtle.turn(PI/2);
      heading = GetHeading(turtle);
      tree_trans_x -= dx*0.01*heading.getX();
      tree_trans_z -= dx*0.01*heading.getZ();

    }
    else {
      cam_rot_x += m_look_speed*dy;
      if(cam_rot_x > 90)
	cam_rot_x = 90;
      else if(cam_rot_x < -90)
	cam_rot_x = -90;
      
      cam_rot_y += m_look_speed*dx;
      if(cam_rot_y > 180)
	cam_rot_y = -180;
      else if(cam_rot_y < -180)
	cam_rot_y = 180;
    }
  } 
  else if (event->buttons() & Qt::RightButton) {
    if(control_mode == MOUSE_LOOK) {
      Turtle turtle;
      turtle.turn(-cam_rot_y*DEGTORAD);
      turtle.pitch(cam_rot_x*DEGTORAD);
      
      PositionVector heading = GetHeading(turtle);
      camera_x -= dy*0.01*heading.getX();
      camera_y += dy*0.01*heading.getY();
      camera_z -= dy*0.01*heading.getZ();
    }
    else if(control_mode == ORBIT) {
      distance += dy*0.05;
      if(distance < 0.05) 
	distance = 0.05;
    }
    else {
      tree_trans_y += 0.01*dy;
    }
  }
  updateGL();
  m_last_pos = event->pos();
}

void GLDrawer::keyPressEvent(QKeyEvent* event) {
  int key = event->key();
  switch(key) 
    {
    case Qt::Key_W:
      if(control_mode == MOUSE_LOOK)
	t_rot_x -= 2;
      else 
	cam_rot_x -= 2;
      break;
    case Qt::Key_S:
      if(control_mode == MOUSE_LOOK)
	t_rot_x += 2;
      else 
	cam_rot_x += 2;
      break;
    case Qt::Key_A:
      if(control_mode == MOUSE_LOOK)
	t_rot_y += 2;
      else 
	cam_rot_y -= 2;
      break;
    case Qt::Key_D:
      if(control_mode == MOUSE_LOOK)
	t_rot_y -= 2;
      else 
	cam_rot_y += 2;
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
      resetVisualization();
      break;
    case Qt::Key_T:
      toggleTexturing();
      break;
    }
  updateGL();
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

bool GLDrawer::setCylinderTexture(QString texture) {
  if(textures.contains(texture)) {
    parameters.setSegmentTexture(textures.value(texture));
    return true;
  }
  else {
    QFile file(texture);
    
    if(file.exists()) {
      int tex = loadTexture(texture.toStdString());
      if(tex != 0) {
	textures.insert(texture, tex);
	parameters.setSegmentTexture(tex);
	return true;
      }
      else
	return false;
    }
    else {
      cout << "Texture file: " << texture.toStdString() << " is not found!" << endl;
      return false;
    }
  }
}
  
bool GLDrawer::setLeafTexture(QString texture) {
  if(textures.contains(texture)) {
    parameters.setLeafTexture(textures.value(texture));
    return true;
  }
  else {
    QFile file(texture);
    
    if(file.exists()) {
      int tex = loadTexture(texture.toStdString());
      if(tex != 0) {
	parameters.setLeafTexture(tex);
	textures.insert(texture, tex);
	return true;
      }
      else 
	return false;
    }
    else {
      cout << "Texture file: " << texture.toStdString() << " is not found!" << endl;
      return false;
    }
  }
}

bool GLDrawer::setFoliageTexture(QString texture) {
  if(textures.contains(texture)) {
    parameters.setFoliageTexture(textures.value(texture));
    return true;
  }
  else {
    QFile file(texture);
    
    if(file.exists()) {
      int tex = loadTexture(texture.toStdString());
      if(tex != 0) {
	parameters.setFoliageTexture(tex);
	textures.insert(texture, tex);
	return true;
      }
      else
	return false;
    }
    else {
      cout << "Texture file: " << texture.toStdString() << " is not found!" << endl;
      return false;
    }
  }
}

void GLDrawer::resetCamera() {
  t_rot_y = 0;
  t_rot_x = 0;

  tree_trans_x = t_point.getX() + r_axis.getX()*t_height/2;
  tree_trans_y = t_point.getY() - r_axis.getZ()*t_height/2;
  tree_trans_z = t_point.getZ() + r_axis.getY()*t_height/2;
  distance = abs(4*t_height);
  if(distance > 18)
    distance = 18;
  else if(distance < 0.2)
    distance = 0.2;
  
  //cout << "point: " << t_point.getX() << " " << t_point.getY() << " " << t_point.getZ() << endl;
  //cout << "height: " << t_height << endl;
  camera_x = t_point.getX()+ r_axis.getX()*t_height/2;
  //camera_y = t_point.getY() - t_height/2*r_axis.getZ();
  camera_y = t_point.getY() - r_axis.getZ()*t_height/2;
  camera_z = t_point.getZ() + r_axis.getY()*t_height/2+ distance;
  Point camera(camera_x, camera_y, camera_z);
  //  cout << "camera: " << camera_x << " " << camera_y << " " << camera_z << endl;

  //Point p(t_point.getX(), t_point.getY() - (t_height/2.0)*r_axis.getZ(), t_point.getZ());
  Point p(t_point.getX() + r_axis.getX()*t_height/2,
	  t_point.getY() - r_axis.getZ()*t_height/2.0,
	  t_point.getZ() + r_axis.getY()*t_height/2);
  PositionVector direction(PositionVector(p - camera));
  direction = direction.normalize();
  //cout << "direction: " << direction.getX() << " " << direction.getY() << " " << direction.getZ() << endl;
  cam_rot_x = 1/DEGTORAD*asin(direction.getY());

  if(direction.getX() >= 0 && direction.getZ() >= 0)
    cam_rot_y = 180-1/DEGTORAD*asin(direction.getX());
  else if(direction.getX() < 0 && direction.getZ() >= 0)
    cam_rot_y = -(180-1/DEGTORAD*asin(-direction.getX()));
  else if(direction.getX() < 0 && direction.getZ() < 0)
    cam_rot_y = -(1/DEGTORAD*asin(-direction.getX()));
  else 
    cam_rot_y = (1/DEGTORAD*asin(direction.getX()));

  //  cam_rot_z = 1/DEGTORAD*acos(r_axis.getZ());
  
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

VisualizationParameters GLDrawer::getParameters() const {
  return parameters;
}

void GLDrawer::changeSettings(VisualizationParameters params) {
  params.setMaterial(parameters.getMaterial());
  params.setLeafMaterial(parameters.getLeafMaterial());
  params.setPetioleMaterial(parameters.getPetioleMaterial());
  params.setBudAliveMaterial(parameters.getBudAliveMaterial());
  params.setBudDeadMaterial(parameters.getBudDeadMaterial());
  params.setBudDormantMaterial(parameters.getBudDormantMaterial());
  params.setBudFlowerMaterial(parameters.getBudFlowerMaterial());
  params.setDominantMaterial(parameters.getDominantMaterial());
  params.setNondominantMaterial(parameters.getNondominantMaterial());
  params.setShootMaterial(parameters.getShootMaterial());
  params.setShootAboveMaterial(parameters.getShootAboveMaterial());
  parameters = params;
  settingsChanged = true;
  updateGL();
}

void GLDrawer::orbitCameraMode() {
  if(control_mode == MOUSE_LOOK)
    resetCamera();
  control_mode = ORBIT;
}

void GLDrawer::moveCenterMode() {
  if(control_mode == MOUSE_LOOK)
    resetCamera();
  control_mode = MOVE_TREE;
}

void GLDrawer::freeRoamMode() {
  if(control_mode != MOUSE_LOOK)
    resetCamera();  
  control_mode = MOUSE_LOOK;
}

void GLDrawer::setObjectsSelected(QHash<QString, QList<int> > selected) {


  QList<QString> files = selectedObjects.keys();

  for(int i = 0; i < files.size(); i++) {
    if(sceneObjects->contains(files[i])) {
      QMultiHash<int, SceneObject*>* scene_objects = sceneObjects->value(files[i]);
      QList<int> objects = selectedObjects.value(files[i]);
      for(int j = 0; j < objects.size(); j++) {
	if(scene_objects->contains(objects[j])) {
	  QList<SceneObject*> s_objects = scene_objects->values(objects[j]);
	  for(int k = 0; k < s_objects.size(); k++) {
	    s_objects[k]->unsetTempMaterial();
	  }
	}  
      }
    }    
  }

  selectedObjects = selected;
  files = selected.keys();
  for(int i = 0; i < files.size(); i++) {
    if(sceneObjects->contains(files[i])) {
      QMultiHash<int, SceneObject*>* scene_objects = sceneObjects->value(files[i]);
      QList<int> objects = selectedObjects.value(files[i]);
      for(int j = 0; j < objects.size(); j++) {
	if(scene_objects->contains(objects[j])) {
	  QList<SceneObject*> s_objects = scene_objects->values(objects[j]);
	  for(int k = 0; k < s_objects.size(); k++) {
	    s_objects[k]->setTempMaterial(red);
	  }
	}  
      }
    }    
  }
   
    /*  if(sceneObjects) {
    // Reset previous selection
    for(int i = 0; i < selectedObjects.size(); i++) {
      if(sceneObjects->contains(selectedObjects[i])) {
	QList<SceneObject*> objectList = sceneObjects->values(selectedObjects[i]);
	for(int j = 0; j < objectList.size(); j++) {
	  objectList[j]->unsetTempMaterial();
	}
      }
    }
    
    // Select new objects
    selectedObjects = selected;
    for(int i = 0; i < selectedObjects.size(); i++) {
      if(sceneObjects->contains(selectedObjects[i])) {
	QList<SceneObject*> objectList = sceneObjects->values(selectedObjects[i]);
	for(int j = 0; j < objectList.size(); j++) {
	  objectList[j]->setTempMaterial(red);
	}
      }
    }
    }*/
  updateGL();
      
}

void GLDrawer::setFocus(Point point, PositionVector direction, double height) {
  r_axis = direction.normalize();
  t_point = point;
  r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
  t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
  t_height = height;

  tree_trans_x = t_point.getX() + r_axis.getX()*t_height/2;
  tree_trans_y = t_point.getY() + r_axis.getY()*t_height/2;
  tree_trans_z = t_point.getZ() + r_axis.getZ()*t_height/2;
  
  updateGL();
  //resetCamera();
}

void GLDrawer::switchMaterials() {
  QList<QString> files = objectLists.keys();
  for(int i = 0; i < files.size(); i++) {
    QList<SceneObject*> objects = objectLists.value(files[i]);
    for(int j = 0; j < objects.size(); j++) {
      objects[j]->switchMaterial();
    }
  }
  updateGL();

}

void GLDrawer::updateTrees(BSPTree *tree, Point t_point, PositionVector r_axis,
		   double t_height, QHash<QString, QMultiHash<int, SceneObject*>* > *sceneObjects)
{
  resetVisualization();
  this->tree = tree;
  this->sceneObjects = sceneObjects;
  this->t_point = t_point;
  this->r_axis = r_axis;
  this->t_height = t_height;
  
  QList<QString> files = sceneObjects->keys();
  for(int i = 0; i < files.size(); i++) {
    if(sceneObjects->contains(files[i])) {
      objectLists.insert(files[i], sceneObjects->value(files[i])->values());
    }
  }

  resetCamera();
  updateGL();
}
