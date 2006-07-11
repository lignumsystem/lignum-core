#include <SceneObject.h>
#include <QtOpenGL>
#include <iostream>
//#include <BSPPolygon.h>

using namespace std;

SceneObject::SceneObject(BSPPolygonMaterial* mat)
  : component_count(0), material(mat), texture_id(0) {
  n_objects++;
  id = n_objects;
}

SceneObject::SceneObject(BSPPolygonMaterial* mat, int t_id) 
  : component_count(0), material(mat), texture_id(t_id) {
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
  if(texture_id != 0) {
    //glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
  }
  /*else {
    glDisable(GL_TEXTURE_2D);
    }*/
}

int SceneObject::getComponentCount() {
  return component_count;
}

void SceneObject::increaseComponentCount() {
  component_count++;
}

void SceneObject::decreaseComponentCount() {
  component_count--;
}

int SceneObject::n_objects = 0;

SceneObject::~SceneObject() {
  //delete material;
}

SceneObjectComponent::~SceneObjectComponent() {
  object->decreaseComponentCount();
  if(object->getComponentCount() == 0) {
    //    cout << "SceneObject deleted" << endl;
    delete object;
  }
}

SceneObjectComponent::SceneObjectComponent(SceneObject* obj, int c_index)
  : object(obj), component_index(c_index), used_material(-1) {
  obj->increaseComponentCount();
}

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
    
