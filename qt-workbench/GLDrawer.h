#ifndef GLDRAWER_H
#define GLDRAWER_H

#include <QGLWidget>
#include <BSPTree.h>
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
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
  void keyPressEvent(QKeyEvent* event);
  void keyReleaseEvent(QKeyEvent* event);
  

  BSPPolygonMaterial* green;
  BSPPolygonMaterial* red;
  BSPPolygonMaterial* white;
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
  void changeTree();
  void setTreeFile(QString fileName);
  void setCylinderRDetail(int detail);
  void setCylinderHDetail(int detail);
  void setCylinderTexture(QString fileName);
  void setLeafTexture(QString fileName);
  void setFoliageTexture(QString fileName);
  void resetCamera();
  void useBSP(bool use);
  void useLeafTextures(bool use);
  void setLeafDetail(int detail);
  //void moveCameraLeft();
  //void moveCameraRight();
  //void moveCameraUp();
  //void moveCameraDown();
  
 signals:
  void textOutput(QString text);

private:
  bool isExtensionSupported(char* szTargetExtension);
  void initMaterials();
  void initLights();
  void initTextureSettings();

  GLfloat*  light0_position;                   // Position of light0
  GLfloat*  light0_direction;                  // Direction of light0
  GLfloat   camera_x, camera_y, camera_z;      // Position of camera
  GLfloat   cam_rot_x, cam_rot_y, cam_rot_z;   // Rotation of camera
  GLfloat   cam_mov_speed, cam_rot_speed;      // Movement and rotation speed of camera
  PositionVector r_axis;                       // Root axis of central tree in visualization
  Point t_point;                               // Origin of the central tree
  double t_height;                             // Height of the tallest tree 
  GLfloat   DEGTORAD;                          // Conversion coefficient from degrees to radians
  //  static const GLfloat PI = 3.14159265;  
  GLfloat   PI;                                // PI
  BSPTree   *tree;                             // BSP-tree object
  bool      wire;                              // Is wireframe on
  bool      lights_on;                         // Are lights on
  bool      use_textures;                      // Are textures used
  int       tex1;   
  QPoint    m_last_pos;
  double    m_look_speed;
  QString   tree_file;
  VisualizationParameters parameters;          // Parameters of the visualization
  QHash<QString, int> textures;
};

#endif
