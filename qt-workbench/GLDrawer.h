#ifndef GLDRAWER_H
#define GLDRAWER_H

#include <QGLWidget>
#include <BSPTree.h>
#include <BSPPolygon.h>
#include <BSPPolygonMaterial.h>

class GLDrawer : public QGLWidget
{
  Q_OBJECT
  
public: 
  GLDrawer(QWidget* parent = 0);
  BSPPolygonSet* makeCylinder(double radius, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, BSPPolygonMaterial* material, int detail = 20);

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
  //void moveCameraLeft();
  //void moveCameraRight();
  //void moveCameraUp();
  //void moveCameraDown();
  
private:
  void initMaterials();
  void initLights();
  

  GLfloat camera_x, camera_y, camera_z;
  GLfloat cam_rot_x, cam_rot_y;
  GLfloat cam_mov_speed, cam_rot_speed;
  GLfloat cyl_x, cyl_y, cyl_z;
  GLfloat cyl_rot_angle, cyl_rot_x, cyl_rot_y, cyl_rot_z;
  GLfloat DEGTORAD;
  static const GLfloat PI = 3.14159265;
  BSPTree *tree;
  BSPPolygonMaterial* green;
  BSPPolygonMaterial* red;
  bool wire;
};

#endif
