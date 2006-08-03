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
  string                getSegmentTextureFile();
  void                  setLeafTextureFile(string texture);
  string                getLeafTextureFile();

  int                   getSegmentRDetail() const ;
  void                  setSegmentRDetail(int detail);
  int                   getSegmentHDetail() const ;
  void                  setSegmentHDetail(int detail);
  int                   getSegmentTexture() const ;
  void                  setSegmentTexture(int texture);

  int                   getLeafDetail() const;
  void                  setLeafDetail(int detail);
  int                   getLeafTexture() const;
  void                  setLeafTexture(int texture);

  int                   getFoliageTexture() const;
  void                  setFoliageTexture(int texture);

  BSPPolygonMaterial*   getMaterial() const ;
  void                  setMaterial(BSPPolygonMaterial* material);
  BSPPolygonMaterial*   getLeafMaterial() const;
  void                  setLeafMaterial(BSPPolygonMaterial* material);
  BSPPolygonMaterial*   getPetioleMaterial() const;
  void                  setPetioleMaterial(BSPPolygonMaterial* material);

  void                  setBSPUsage(bool useBSP);
  bool                  useBSP() const;
  void                  setLeafTextureUsage(bool useLeafTextures);
  bool                  useLeafTextures() const;

 private:
  string segment_texture_file;
  string leaf_texture_file;
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
  bool useLeafTex;
};

#endif
