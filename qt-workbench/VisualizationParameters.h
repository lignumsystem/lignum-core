#ifndef VISUALIZATIONPARAMETERS_H
#define VISUALIZATIONPARAMETERS_H

#include <iostream>
#include <BSPPolygonMaterial.h>

class VisualizationParameters {
 public:
  VisualizationParameters(int cylinder_r_detail, int cylinder_h_detail,
			  int cylinder_tex,
			  int leaf_tex,
			  BSPPolygonMaterial* material,
			  BSPPolygonMaterial* leafMat);
  VisualizationParameters();
  ~VisualizationParameters();
  
  int getCylinderRDetail() const ;
  int getCylinderHDetail() const ;
  void setCylinderRDetail(int detail);
  void setCylinderHDetail(int detail);
  int getCylinderTexture() const ;
  void setCylinderTexture(int texture);
  int getLeafTexture() const;
  void setLeafTexture(int texture);
  void setMaterial(BSPPolygonMaterial* material);
  void setLeafMaterial(BSPPolygonMaterial* material);
  BSPPolygonMaterial* getMaterial() const ;
  BSPPolygonMaterial* getLeafMaterial() const;

 private:

  int cylinder_r_detail;
  int cylinder_h_detail;
  int cylinder_tex;
  int leaf_tex;
  BSPPolygonMaterial* material;
  BSPPolygonMaterial* leafMaterial;

};

#endif
