#include <VisualizationParameters.h>

using namespace std;

VisualizationParameters::VisualizationParameters(int s_r_detail,
						 int s_h_detail,
						 int l_detail,
						 int s_tex,
						 int l_tex,
						 int f_tex,
						 BSPPolygonMaterial* mat,
						 BSPPolygonMaterial* leafMat,
						 BSPPolygonMaterial* petioleMat) :
  segment_r_detail(s_r_detail),
  segment_h_detail(s_h_detail),
  leaf_detail(l_detail),
  bud_lo_detail(4),
  bud_la_detail(8),
  foliage_detail(6),
  segment_tex(s_tex),
  leaf_tex(l_tex),
  foliage_tex(f_tex),
  material(mat),
  leafMaterial(leafMat),
  petioleMaterial(petioleMat),
  budAliveMaterial(NULL),
  budDeadMaterial(NULL),
  budDormantMaterial(NULL),
  budFlowerMaterial(NULL),
  use_BSP(true),
  use_wireframe(false),
  use_lighting(true),
  use_texturing(true),
  use_buds(true) {
  if(leaf_tex == 0)
    use_leaftex == false;
  else 
    use_leaftex == true;

}

VisualizationParameters::VisualizationParameters() :
  segment_r_detail(20),
  segment_h_detail(1),
  leaf_detail(10),
  bud_lo_detail(4),
  bud_la_detail(8),
  foliage_detail(6),
  segment_tex(0),
  leaf_tex(0),
  foliage_tex(0),
  material(NULL),
  leafMaterial(NULL),
  petioleMaterial(NULL),
  budAliveMaterial(NULL),
  budDeadMaterial(NULL),
  budDormantMaterial(NULL),
  budFlowerMaterial(NULL),
  use_BSP(false),
  use_leaftex(false),
  use_wireframe(false),
  use_lighting(true),
  use_texturing(true),
  use_buds(true){
}

void VisualizationParameters::setSegmentTextureFile(string texture) {
  segment_texture_file = texture;
}

void VisualizationParameters::setLeafTextureFile(string texture) {
  leaf_texture_file = texture;
}

void VisualizationParameters::setFoliageTextureFile(string texture) {
  foliage_texture_file = texture;
}

string VisualizationParameters::getSegmentTextureFile() const {
  return segment_texture_file;
}

string VisualizationParameters::getLeafTextureFile() const {
  return leaf_texture_file;
}

string VisualizationParameters::getFoliageTextureFile() const {
  return foliage_texture_file;
}

VisualizationParameters::~VisualizationParameters() {

}

int VisualizationParameters::getSegmentRDetail() const {
  return segment_r_detail;
}

int VisualizationParameters::getSegmentHDetail() const {
  return segment_h_detail;
}

int VisualizationParameters::getLeafDetail() const {
  return leaf_detail;
}

int VisualizationParameters::getBudLoDetail() const {
  return bud_lo_detail;
}

int VisualizationParameters::getBudLaDetail() const {
  return bud_la_detail;
}

int VisualizationParameters::getFoliageDetail() const {
  return foliage_detail;
}

void VisualizationParameters::setSegmentRDetail(int detail) {
  if(detail >= 3)
    segment_r_detail = detail;
  else 
    segment_r_detail = 3;
}

void VisualizationParameters::setSegmentHDetail(int detail) {
  if(detail >= 1)
    segment_h_detail = detail;
  else 
    segment_h_detail = 1;
}

void VisualizationParameters::setLeafDetail(int detail) {
  if(detail > 3 && (detail % 2 == 0)) {
    leaf_detail = detail;
  }
}


void VisualizationParameters::setBudLoDetail(int detail) {
  if(detail >= 4)
    bud_lo_detail = detail;
  else 
    bud_lo_detail = 4;
}

void VisualizationParameters::setBudLaDetail(int detail) {
  if(detail >= 4)
    bud_la_detail = detail;
  else 
    bud_la_detail = 4;
}

void VisualizationParameters::setFoliageDetail(int detail) {
  if(detail >= 0)
    foliage_detail = detail;
}
int VisualizationParameters::getSegmentTexture() const {
  return segment_tex;
}

void VisualizationParameters::setSegmentTexture(int texture) {
  segment_tex = texture;
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

void VisualizationParameters::setBudAliveMaterial(BSPPolygonMaterial* mat) {
  budAliveMaterial = mat;
}

void VisualizationParameters::setBudDeadMaterial(BSPPolygonMaterial* mat) {
  budDeadMaterial = mat;
}

void VisualizationParameters::setBudDormantMaterial(BSPPolygonMaterial* mat) {
  budDormantMaterial = mat;
}

void VisualizationParameters::setBudFlowerMaterial(BSPPolygonMaterial* mat) {
  budFlowerMaterial = mat;
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

BSPPolygonMaterial* VisualizationParameters::getBudAliveMaterial() const {
  return budAliveMaterial;
}

BSPPolygonMaterial* VisualizationParameters::getBudDeadMaterial() const {
  return budDeadMaterial;
}

BSPPolygonMaterial* VisualizationParameters::getBudDormantMaterial() const {
  return budDormantMaterial;
}

BSPPolygonMaterial* VisualizationParameters::getBudFlowerMaterial() const {
  return budFlowerMaterial;
}




void VisualizationParameters::setBSPUsage(bool uBSP) {
  use_BSP = uBSP;
}

bool VisualizationParameters::useBSP() const {
  return use_BSP;
}

void VisualizationParameters::setLeafTextureUsage(bool use_tex) {
  use_leaftex = use_tex;
}

bool VisualizationParameters::useLeafTextures() const {
  return use_leaftex;
}

void VisualizationParameters::setWireframeUsage(bool useWireframe) {
  use_wireframe = useWireframe;
}

bool VisualizationParameters::useWireframe() const {
  return use_wireframe;
}

void VisualizationParameters::setLightingUsage(bool useLighting) {
  use_lighting = useLighting;
}

bool VisualizationParameters::useLighting() const {
  return use_lighting;
}

void VisualizationParameters::setTexturingUsage(bool useTexturing) {
  use_texturing = useTexturing;
}

bool VisualizationParameters::useTexturing() const {
  return use_texturing;
}

void VisualizationParameters::setBudUsage(bool useBuds) {
  use_buds = useBuds;
}

bool VisualizationParameters::useBuds() const {
  return use_buds;
}
