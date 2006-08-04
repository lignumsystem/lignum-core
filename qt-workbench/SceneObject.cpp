#include <SceneObject.h>
#include <QtOpenGL>
#include <iostream>
//#include <BSPPolygon.h>

using namespace std;

SceneObject::SceneObject(BSPPolygonMaterial* mat, bool transp)
  : component_count(0), texture_id(0), transparent(transp), material(mat) {
  n_objects++;
  id = n_objects;
}

SceneObject::SceneObject(BSPPolygonMaterial* mat, int t_id, bool transp) 
  : component_count(0), texture_id(t_id), transparent(transp), material(mat) {
  n_objects++;
  id = n_objects;
}

int SceneObject::getId() const{
  return id;
}

int SceneObject::getMaterialId() const{
  return material->getId();
}

void SceneObject::setMaterial() const{
  static int last_material = -1;
  int id = material->getId();
  if(last_material != id) {
    last_material = id;    
    material->setMaterial();
  }

  static int last_texture = -1;
  if(texture_id != 0 && texture_id != last_texture) {
    //glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    last_texture = texture_id;
  }

}

int SceneObject::getComponentCount() const{
  return component_count;
}

void SceneObject::increaseComponentCount() {
  component_count++;
}

void SceneObject::decreaseComponentCount() {
  component_count--;
}

bool SceneObject::isTransparent() const {
  return transparent;
}

bool SceneObject::hasTexture() const {
  if(texture_id == 0)
    return false;
  else
    return true;
}

int SceneObject::n_objects = 0;

SceneObject::~SceneObject() {
  //delete material;
  //cout << "Object deleted" << endl;
}

SceneObjectComponent::~SceneObjectComponent() {
  object->decreaseComponentCount();
  if(object->getComponentCount() == 0) {
    //    cout << "SceneObject deleted" << endl;
    delete object;
  }
  if(draw_index != 0 && draw_index != component_index)
    glDeleteLists(draw_index, 1);
  glDeleteLists(component_index, 1);
}

SceneObjectComponent::SceneObjectComponent(SceneObject* obj, int c_index)
  : object(obj), component_index(c_index), used_material(-1) {
  obj->increaseComponentCount();
  buildDrawList();
}

void SceneObjectComponent::buildDrawList() {
  /*if(used_material != object->getMaterialId()) {
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
    draw_index = component_index;
  }
  */
  draw_index = component_index;
}

void SceneObjectComponent::drawComponent() {
  /*  if(used_material != object->getMaterialId()) {
    draw_index = glGenLists(1);
    if(draw_index != 0) {
      glNewList(draw_index, GL_COMPILE);
      object->setMaterial();
      glCallList(component_index);
      glEndList();
    }
    cout << "sfsef" << endl;
    used_material = object->getMaterialId();
  }
  else {
    if(draw_index != 0)
      glCallList(draw_index);
    else if(component_index != 0)
      glCallList(component_index);
      }*/
  /* static int last_material = -1;
  int id = object->getMaterialId();
  if(last_material != id) {
    object->setMaterial();
    last_material = id;
    }*/
  object->setMaterial();
  glCallList(draw_index);
}
    
inline bool operator < (const SceneObjectComponent& component1, const SceneObjectComponent& component2) {
  if(component1.object->getMaterialId() <= component2.object->getMaterialId())
    return true;
  else
    return false;
}
