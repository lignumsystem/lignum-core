#ifndef VISUALIZATIONPARAMETERS_H
#define VISUALIZATIONPARAMETERS_H

#include <iostream>
#include <BSPPolygonMaterial.h>

class VisualizationParameters {
 public:
  VisualizationParameters(int cylinder_r_detail, int cylinder_h_detail,
			  int leaf_detail,
			  int cylinder_tex,
			  int leaf_tex,
			  int foliage_tex,
			  BSPPolygonMaterial* material,
			  BSPPolygonMaterial* leafMat,
			  BSPPolygonMaterial* petioleMaterial);
  VisualizationParameters();
  ~VisualizationParameters();
  
  int                   getCylinderRDetail() const ;
  int                   getCylinderHDetail() const ;
  int                   getLeafDetail() const;
  void                  setCylinderRDetail(int detail);
  void                  setCylinderHDetail(int detail);
  void                  setLeafDetail(int detail);
  int                   getCylinderTexture() const ;
  void                  setCylinderTexture(int texture);
  int                   getLeafTexture() const;
  void                  setLeafTexture(int texture);
  int                   getFoliageTexture() const;
  void                  setFoliageTexture(int texture);
  void                  setMaterial(BSPPolygonMaterial* material);
  void                  setLeafMaterial(BSPPolygonMaterial* material);
  void                  setPetioleMaterial(BSPPolygonMaterial* material);
  BSPPolygonMaterial*   getMaterial() const ;
  BSPPolygonMaterial*   getLeafMaterial() const;
  BSPPolygonMaterial*   getPetioleMaterial() const;
  void                  setBSPUsage(bool useBSP);
  bool                  useBSP() const;
  void                  setLeafTextureUsage(bool useLeafTextures);
  bool                  useLeafTextures() const;

 private:

  int cylinder_r_detail;
  int cylinder_h_detail;
  int leaf_detail;
  int cylinder_tex;
  int leaf_tex;
  int foliage_tex;
  BSPPolygonMaterial* material;
  BSPPolygonMaterial* leafMaterial;
  BSPPolygonMaterial* petioleMaterial;
  bool use_BSP;
  bool useLeafTex;
};

#endif
