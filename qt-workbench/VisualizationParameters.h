#ifndef VISUALIZATIONPARAMETERS_H
#define VISUALIZATIONPARAMETERS_H

#include <iostream>
#include <BSPPolygonMaterial.h>

using namespace std;

class VisualizationParameters {
 public:
  VisualizationParameters(int segment_r_detail, int segment_h_detail,
			  int leaf_detail,
			  int segment_tex,
			  int leaf_tex,
			  int foliage_tex,
			  BSPPolygonMaterial* material,
			  BSPPolygonMaterial* leafMat,
			  BSPPolygonMaterial* petioleMaterial);
  VisualizationParameters();
  ~VisualizationParameters();
  
  void                  setSegmentTextureFile(string texture);
  void                  setLeafTextureFile(string texture);
  void                  setFoliageTextureFile(string texture);

  string                getSegmentTextureFile() const;
  string                getLeafTextureFile() const;
  string                getFoliageTextureFile() const;

  void                  setSegmentRDetail(int detail);
  void                  setSegmentHDetail(int detail);
  void                  setLeafDetail(int detail);
  int                   getSegmentRDetail() const ;
  int                   getSegmentHDetail() const ;
  int                   getLeafDetail() const;

  void                  setLeafTexture(int texture);
  void                  setFoliageTexture(int texture);
  void                  setSegmentTexture(int texture);
  int                   getSegmentTexture() const ;
  int                   getLeafTexture() const;
  int                   getFoliageTexture() const;

  BSPPolygonMaterial*   getMaterial() const ;
  BSPPolygonMaterial*   getLeafMaterial() const;
  BSPPolygonMaterial*   getPetioleMaterial() const;

  void                  setMaterial(BSPPolygonMaterial* material);
  void                  setLeafMaterial(BSPPolygonMaterial* material);
  void                  setPetioleMaterial(BSPPolygonMaterial* material);

  void                  setBSPUsage(bool useBSP);
  void                  setLeafTextureUsage(bool useLeafTextures);
  void                  setWireframeUsage(bool useWireframe);
  void                  setLightingUsage(bool useLighting);
  void                  setTexturingUsage(bool useTexturing);

  bool                  useBSP() const;
  bool                  useLeafTextures() const;
  bool                  useWireframe() const;
  bool                  useLighting() const;
  bool                  useTexturing() const;

 private:
  string segment_texture_file;
  string leaf_texture_file;
  string foliage_texture_file;
  int segment_r_detail;
  int segment_h_detail;
  int leaf_detail;
  int segment_tex;
  int leaf_tex;
  int foliage_tex;
  BSPPolygonMaterial* material;
  BSPPolygonMaterial* leafMaterial;
  BSPPolygonMaterial* petioleMaterial;
  bool use_BSP;
  bool use_leaftex;
  bool use_wireframe;
  bool use_lighting;
  bool use_texturing;
};

#endif
