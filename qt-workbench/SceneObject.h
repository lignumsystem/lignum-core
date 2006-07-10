#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <BSPPolygonMaterial.h>

//class BSPPolygonMaterial;

class SceneObject {
public :
  SceneObject(BSPPolygonMaterial* material);
  int getId();
  int getMaterialId();
  void setMaterial();
  int id;
  static int n_objects;
private:
  BSPPolygonMaterial* material;
};

class SceneObjectComponent {
public:
  SceneObjectComponent(SceneObject* object, int component_index);
  void drawComponent();

private:
  SceneObject* object;
  int component_index;
  int draw_index;
  int used_material;
  
};

#endif
