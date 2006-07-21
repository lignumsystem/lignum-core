#include <VisualizationParameters.h>

VisualizationParameters::VisualizationParameters(int c_r_detail,
						 int c_h_detail,
						 int c_tex,
						 int l_tex,
						 BSPPolygonMaterial* mat,
						 BSPPolygonMaterial* leafMat) :
  cylinder_r_detail(c_r_detail), cylinder_h_detail(c_h_detail), 
  cylinder_tex(c_tex), leaf_tex(l_tex), material(mat), leafMaterial(leafMat) {
}

VisualizationParameters::VisualizationParameters() :
  cylinder_r_detail(20), cylinder_h_detail(1), cylinder_tex(0),
  material(NULL), leafMaterial(NULL) {
}

VisualizationParameters::~VisualizationParameters() {

}

int VisualizationParameters::getCylinderRDetail() const {
  return cylinder_r_detail;
}

int VisualizationParameters::getCylinderHDetail() const {
  return cylinder_h_detail;
}

void VisualizationParameters::setCylinderRDetail(int detail) {
  if(detail >= 3)
    cylinder_r_detail = detail;
  else 
    cylinder_r_detail = 3;
}

void VisualizationParameters::setCylinderHDetail(int detail) {
  if(detail >= 1)
    cylinder_h_detail = detail;
  else 
    cylinder_h_detail = 1;
}

int VisualizationParameters::getCylinderTexture() const {
  return cylinder_tex;
}

void VisualizationParameters::setCylinderTexture(int texture) {
  cylinder_tex = texture;
}

int VisualizationParameters::getLeafTexture() const {
  return leaf_tex;
}

void VisualizationParameters::setLeafTexture(int texture) {
  leaf_tex = texture;
}

void VisualizationParameters::setMaterial(BSPPolygonMaterial* mat) {
  material = mat;
}

void VisualizationParameters::setLeafMaterial(BSPPolygonMaterial* mat) {
  leafMaterial = mat;
}

BSPPolygonMaterial* VisualizationParameters::getMaterial() const {
  return material;
}


BSPPolygonMaterial* VisualizationParameters::getLeafMaterial() const {
  return leafMaterial;
}
