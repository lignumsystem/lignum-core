#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <BSPPolygonMaterial.h>

//class BSPPolygonMaterial;

class SceneObject {
public :
  SceneObject(BSPPolygonMaterial* material);
  SceneObject(BSPPolygonMaterial* material, int texture_id);
  ~SceneObject();
  int getId() const;
  int getMaterialId() const;
  void setMaterial() const;
  int getComponentCount() const;
  void increaseComponentCount();
  void decreaseComponentCount();
  int id;
  static int n_objects;
private:
  int component_count;
  int texture_id;
  BSPPolygonMaterial* material;
};

class SceneObjectComponent {
public:
  SceneObjectComponent(SceneObject* object, int component_index);
  ~SceneObjectComponent();
  void drawComponent() ;

private:
  SceneObject* object;
  int component_index;
  int draw_index;
  int used_material;
  
};

#endif
