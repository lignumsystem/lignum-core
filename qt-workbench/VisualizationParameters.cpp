#include <VisualizationParameters.h>

using namespace std;

VisualizationParameters::VisualizationParameters(int c_r_detail,
						 int c_h_detail,
						 int l_detail,
						 int c_tex,
						 int l_tex,
						 int f_tex,
						 BSPPolygonMaterial* mat,
						 BSPPolygonMaterial* leafMat,
						 BSPPolygonMaterial* petioleMat) :
  cylinder_r_detail(c_r_detail), cylinder_h_detail(c_h_detail), leaf_detail(l_detail), 
  cylinder_tex(c_tex), leaf_tex(l_tex), foliage_tex(f_tex), material(mat), leafMaterial(leafMat),
  petioleMaterial(petioleMat), use_BSP(true) {
  if(leaf_tex == 0)
    useLeafTex == false;
  else 
  useLeafTex == true;

}

VisualizationParameters::VisualizationParameters() :
  cylinder_r_detail(20), cylinder_h_detail(1), leaf_detail(10), 
  cylinder_tex(0), leaf_tex(0), foliage_tex(0), material(NULL), leafMaterial(NULL),
  petioleMaterial(NULL), use_BSP(false), useLeafTex(false) {
}

VisualizationParameters::~VisualizationParameters() {

}

int VisualizationParameters::getCylinderRDetail() const {
  return cylinder_r_detail;
}

int VisualizationParameters::getCylinderHDetail() const {
  return cylinder_h_detail;
}

int VisualizationParameters::getLeafDetail() const {
  return leaf_detail;
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

void VisualizationParameters::setLeafDetail(int detail) {
  cout << "detail: " << detail << endl;
  if(detail > 3 && (detail % 2 == 0)) {
    cout << "HERE" << endl;
    leaf_detail = detail;
  }
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

int VisualizationParameters::getFoliageTexture() const {
  return foliage_tex;
}

void VisualizationParameters::setFoliageTexture(int texture) {
  foliage_tex = texture;
}

void VisualizationParameters::setMaterial(BSPPolygonMaterial* mat) {
  material = mat;
}

void VisualizationParameters::setLeafMaterial(BSPPolygonMaterial* mat) {
  leafMaterial = mat;
}

void VisualizationParameters::setPetioleMaterial(BSPPolygonMaterial* mat) {
  petioleMaterial = mat;
}


BSPPolygonMaterial* VisualizationParameters::getMaterial() const {
  return material;
}


BSPPolygonMaterial* VisualizationParameters::getLeafMaterial() const {
  return leafMaterial;
}

BSPPolygonMaterial* VisualizationParameters::getPetioleMaterial() const {
  return petioleMaterial;
}

void VisualizationParameters::setBSPUsage(bool uBSP) {
  use_BSP = uBSP;
}

bool VisualizationParameters::useBSP() const {
  return use_BSP;
}

void VisualizationParameters::setLeafTextureUsage(bool use_tex) {
  useLeafTex = use_tex;
}

bool VisualizationParameters::useLeafTextures() const {
  return useLeafTex;
}
