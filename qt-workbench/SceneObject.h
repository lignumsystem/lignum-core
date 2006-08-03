#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <BSPPolygonMaterial.h>

//class BSPPolygonMaterial;

class SceneObject {
public :
  SceneObject(BSPPolygonMaterial* material, bool transparent);
  SceneObject(BSPPolygonMaterial* material, int texture_id, bool transparent);
  ~SceneObject();
  int    getId() const;
  int    getMaterialId() const;
  void   setMaterial() const;
  int    getComponentCount() const;
  void   increaseComponentCount();
  void   decreaseComponentCount();
  bool   isTransparent() const;
  bool   hasTexture() const;
  int    id;
  static int n_objects;
private:
  int    component_count;
  int    texture_id;
  bool   transparent;
  BSPPolygonMaterial* material;
};

class SceneObjectComponent {
public:
  SceneObjectComponent(SceneObject* object, int component_index);
  ~SceneObjectComponent();
  void buildDrawList();
  void drawComponent() ;
  inline friend bool operator < (const SceneObjectComponent& component1, const SceneObjectComponent& component2);

private:
  SceneObject* object;
  int component_index;
  int draw_index;
  int used_material;
  
};

#endif
