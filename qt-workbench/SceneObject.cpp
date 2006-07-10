#include <SceneObject.h>
#include <QtOpenGL>
//#include <BSPPolygon.h>

SceneObject::SceneObject(BSPPolygonMaterial* mat) 
  : material(mat) {
  n_objects++;
  id = n_objects;
}

int SceneObject::getId() {
  return id;
}

int SceneObject::getMaterialId() {
  return material->getId();
}

void SceneObject::setMaterial() {
  material->setMaterial();
}

int SceneObject::n_objects = 0;

SceneObjectComponent::SceneObjectComponent(SceneObject* obj, int c_index)
  : object(obj), component_index(c_index), used_material(-1) {}

void SceneObjectComponent::drawComponent() {
  if(used_material != object->getMaterialId()) {
    draw_index = glGenLists(1);
    if(draw_index != 0) {
      glNewList(draw_index, GL_COMPILE);
      object->setMaterial();
      glCallList(component_index);
      glEndList();
    }
    used_material = object->getMaterialId();
  }
  else {
    if(draw_index != 0)
      glCallList(draw_index);
    else if(component_index != 0)
      glCallList(component_index);
  }
}
    
