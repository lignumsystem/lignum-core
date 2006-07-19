#ifndef VISUALIZATIONPARAMETERS_H
#define VISUALIZATIONPARAMETERS_H

#include <iostream>
#include <BSPPolygonMaterial.h>

class VisualizationParameters {
 public:
  VisualizationParameters(int cylinder_r_detail, int cylinder_h_detail,
			  int cylinder_tex, BSPPolygonMaterial* material);
  VisualizationParameters();
  ~VisualizationParameters();
  
  int getCylinderRDetail() const ;
  int getCylinderHDetail() const ;
  int getCylinderTexture() const ;
  void setCylinderTexture(int texture);
  void setMaterial(BSPPolygonMaterial* material);
  BSPPolygonMaterial* getMaterial() const ;

 private:

  int cylinder_r_detail;
  int cylinder_h_detail;
  int cylinder_tex;
  BSPPolygonMaterial* material;

};

#endif
