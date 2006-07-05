#ifndef BSPPOLYGONMATERIAL_H
#define BSPPOLYGONMATERIAL_H

#include <QtOpenGL>

class BSPPolygonMaterial {
public :
  BSPPolygonMaterial(GLfloat* materials);
  void setMaterial();
  int getId();
  static int n_materials;
private : 
  GLfloat diffuse[4];
  GLfloat ambient[4];
  GLfloat specular[4];
  GLfloat shine[1];
  int id;
};

#endif
