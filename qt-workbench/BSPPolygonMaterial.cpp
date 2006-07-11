
#include <BSPPolygonMaterial.h>
//#include <QtOpenGL>


BSPPolygonMaterial::BSPPolygonMaterial(GLfloat* materials) {
  ambient[0] = materials[0];
  ambient[1] = materials[1];
  ambient[2] = materials[2];
  ambient[3] = materials[3];
  diffuse[0] = materials[4];
  diffuse[1] = materials[5];
  diffuse[2] = materials[6];
  diffuse[3] = materials[7];
  specular[0] = materials[8];
  specular[1] = materials[9];
  specular[2] = materials[10];
  specular[3] = materials[11];
  shine[0] = materials[12];
  
  n_materials++;
  id = n_materials;
}

int BSPPolygonMaterial::n_materials = 0;

void BSPPolygonMaterial::setMaterial() {
  //glColor4fv(color);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shine);
  
}



int BSPPolygonMaterial::getId() {
  return id;
}
