#ifndef GLDRAWER_H
#define GLDRAWER_H

#include <QGLWidget>
#include <QList>
#include <QMultiHash>
#include <BSPTree.h>
#include <BSPLoaderThread.h>
#include <BSPPolygon.h>
#include <BSPPolygonMaterial.h>
#include <LGMPolygonTree.h>
#include <VisualizationParameters.h>

class GLDrawer : public QGLWidget
{
  Q_OBJECT
  
public: 
  GLDrawer(QWidget* parent = 0);
  BSPPolygonSet* makeSquare(double height, double width, Point point, PositionVector direction, BSPPolygonMaterial* material, int texture, int detail = 10);
  int loadTexture(std::string fileName);

  void mousePressEvent(QMouseEvent* event);
  //void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
  void keyPressEvent(QKeyEvent* event);
  //  void keyReleaseEvent(QKeyEvent* event);
  VisualizationParameters getParameters() const;

  BSPPolygonMaterial *green;
  BSPPolygonMaterial *red;
  BSPPolygonMaterial *white;
  BSPPolygonMaterial *budAlive;
  BSPPolygonMaterial *budDead;
  BSPPolygonMaterial *budDormant;
  BSPPolygonMaterial *budFlower;
  BSPPolygonMaterial *dominant;
  BSPPolygonMaterial *nondominant;
  BSPPolygonMaterial *shoot;
  BSPPolygonMaterial *shootAbove;
  


protected:

  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL(); 

public slots:
  void rotateCameraUp();
  void rotateCameraDown();
  void rotateCameraLeft();
  void rotateCameraRight();
  void moveCameraForward();
  void moveCameraBackward();
  void toggleWireModel();
  void toggleLights();
  void toggleTexturing();
  void resetVisualization();
  void resetVisualization(QList<QString> files);
  void addTree(QString fileName);
  void setTreeFile(QString fileName);
  void setCylinderRDetail(int detail);
  void setCylinderHDetail(int detail);
  bool setCylinderTexture(QString fileName);
  bool setLeafTexture(QString fileName);
  bool setFoliageTexture(QString fileName);
  void resetCamera();
  void useBSP(bool use);
  void useLeafTextures(bool use);
  void setLeafDetail(int detail);
  void changeSettings(VisualizationParameters params);
  void orbitCameraMode();
  void moveCenterMode();
  void freeRoamMode();
  void setObjectsSelected(QHash<QString, QList<int> >);
  void setFocus(Point point, PositionVector direction, double height);
  void switchMaterials();
  void updateTrees(BSPTree *tree, Point t_point, PositionVector r_axis,
		   double t_height, QHash<QString, QMultiHash<int, SceneObject*>* > *sceneObjects);
  
 signals:
  void textOutput(QString text);
  void loadingTrees();
  void treesLoaded();

private:
  bool isExtensionSupported(char* szTargetExtension);
  void initMaterials();
  void initLights();
  void initTextureSettings();
  void setParameterSettings();
  bool setTextures();

  GLfloat*  light0_position;                   // Position of light0
  GLfloat*  light0_direction;                  // Direction of light0
  GLfloat   camera_x, camera_y, camera_z;      // Position of camera
  GLfloat   cam_rot_x, cam_rot_y, cam_rot_z;   // Rotation of camera
  GLfloat   cam_mov_speed, cam_rot_speed;      // Movement and rotation speed of camera
  GLfloat   distance;
  GLfloat   tree_trans_x, tree_trans_y, tree_trans_z; 
  PositionVector r_axis;                       // Root axis of central tree in visualization
  Point t_point;                               // Origin of the central tree
  double t_height;                             // Height of the tallest tree 
  GLfloat t_rot_y;
  GLfloat t_rot_x;

  GLfloat   DEGTORAD;                          // Conversion coefficient from degrees to radians
  //  static const GLfloat PI = 3.14159265;  
  GLfloat   PI;                                // PI
  //BSPTree   *tree;                             // BSP-tree object
  /*bool      wire;                              // Is wireframe on
  bool      lights_on;                         // Are lights on
  bool      use_textures;                      // Are textures used
  int       tex1;   */
  QPoint    m_last_pos;
  double    m_look_speed;
  QString   tree_file;
  VisualizationParameters parameters;          // Parameters of the visualization
  QHash<QString, int> textures;
  bool      settingsChanged;
  int       control_mode;
  enum { MOUSE_LOOK, MOVE_TREE, ORBIT };

  BSPLoaderThread thread;

  BSPTree* tree;
  QHash<QString, QMultiHash<int, SceneObject*>* > *sceneObjects;
  QHash<QString, QList<int> > selectedObjects;
  QHash<QString, QList<SceneObject*> > objectLists;
  

};

#endif
