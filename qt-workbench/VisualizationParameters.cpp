#include <VisualizationParameters.h>

VisualizationParameters::VisualizationParameters(int c_r_detail,
			int c_h_detail,
			int c_tex,
			BSPPolygonMaterial* mat) :
  cylinder_r_detail(c_r_detail), cylinder_h_detail(c_h_detail), 
  cylinder_tex(c_tex), material(mat) {
}

VisualizationParameters::VisualizationParameters() :
  cylinder_r_detail(20), cylinder_h_detail(1), cylinder_tex(0),
  material(NULL) {
}

VisualizationParameters::~VisualizationParameters() {

}

int VisualizationParameters::getCylinderRDetail() const {
  return cylinder_r_detail;
}

int VisualizationParameters::getCylinderHDetail() const {
  return cylinder_h_detail;
}

int VisualizationParameters::getCylinderTexture() const {
  return cylinder_tex;
}

void VisualizationParameters::setCylinderTexture(int texture) {
  cylinder_tex = texture;
}

void VisualizationParameters::setMaterial(BSPPolygonMaterial* mat) {
  material = mat;
}

BSPPolygonMaterial* VisualizationParameters::getMaterial() const {
  return material;
}
