#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <BSPPolygonMaterial.h>

//class BSPPolygonMaterial;

class SceneObject {
public :
  SceneObject(BSPPolygonMaterial *material, int s_id, bool transparent);
  SceneObject(BSPPolygonMaterial *material, int s_id, int texture_id, bool transparent);
  SceneObject(BSPPolygonMaterial *material, BSPPolygonMaterial *s_material,
	      int s_id, bool transparent);
  SceneObject(BSPPolygonMaterial *material, BSPPolygonMaterial *s_material,
	      int s_id, int texture_id, bool transparent);
  ~SceneObject();
  int    getId() const;
  int    getMaterialId() const;
  int    getSelectionId() const;
  void   setMaterial() const;
  int    getComponentCount() const;
  void   increaseComponentCount();
  void   decreaseComponentCount();
  bool   isTransparent() const;
  bool   hasTexture() const;
  void   setTempMaterial(BSPPolygonMaterial* material);
  void   unsetTempMaterial();
  void   switchMaterial();
  int    id;
  int    selection_id;
  static int n_objects;
private:
  int    component_count;
  int    texture_id;
  bool   transparent;
  bool   use_secondary_mat;

  BSPPolygonMaterial *material;
  BSPPolygonMaterial *s_material;
  BSPPolygonMaterial *backup;
};

class SceneObjectComponent {
public:
  SceneObjectComponent(SceneObject* object, int component_index);
  ~SceneObjectComponent();
  void buildDrawList();
  void drawComponent() ;
  inline friend bool operator < (const SceneObjectComponent& component1,
				 const SceneObjectComponent& component2);

private:
  SceneObject* object;
  int component_index;
  int draw_index;
  int used_material;
  
};

#endif
