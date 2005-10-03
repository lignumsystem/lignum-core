
#ifndef LGMVISUALIZATIONI
#define LGMVIZUALIZATIONI

#include <WrapperBase.h>
#include <CTexture.h>

namespace Lignum{




  template <class TS, class BUD, class SHAPE>
  void LGMVisualization::AddHwTree(Tree<TS,BUD>& t, string stemTex, string folTex)
  {
    HwWrapper<TS,BUD,SHAPE> *wb = new HwWrapper<TS,BUD,SHAPE>(t);
    //Keep track of the tallest tree.
    max_height = max(max_height,GetValue(t,LGAH));

    //Check if the texture files exist
    ifstream f1(stemTex.c_str());
    if (!f1){
      LGMMessage("Stem texture file missing");
    }
    ifstream f2(folTex.c_str());
    if (!f2){
      LGMMessage("Foliage texture file missing");
    }

    if (f1){
      CTexture stem_texture;
      stem_texture.Load(stemTex.c_str(), 512, 512);
      stem_texture.use();
      wb->intStemTexture = stem_texture.texturenum;
    }
    if (f2){
      bool bmpImage = false;
      if (folTex.find("bmp")< folTex.size() || folTex.find("BMP")< folTex.size())
	{
	  bmpImage = true;	
	}  
      if (bmpImage)
	{
	  CTexture fol_texture;
	  fol_texture.Load(folTex.c_str(), 512, 512);
	  fol_texture.use();
	  wb->intFoliageTexture = fol_texture.texturenum;
	}
      else
	{
	  //Tätä käytetään jos halutaa visualisoida lehdet läpinäkyvyyden avulla.
	  // Tiedosto-muoto .tga
	  wb->intFoliageTexture = GetTgaTexNumber(folTex);	
	}
      wb->bmpImage = bmpImage;
     }
    trees.push_back(wb);
  }

  
 template <class TS, class BUD>
 void LGMVisualization::AddCfTree(Tree<TS,BUD>& t, string stemTex, string folTex)

{
  
  CfWrapper<TS,BUD> *wb = new CfWrapper<TS,BUD>(t);
  //Keep track of the tallest tree.
  max_height = max(max_height,GetValue(t,LGAH));

  //Check if the texture files exist
  ifstream f1(stemTex.c_str());
  if (!f1){
    LGMMessage("Stem texture file missing");
  }
  ifstream f2(folTex.c_str());
  if (!f2){
    LGMMessage("Foliage texture file missing");
  }
  //Load textures
  if (f1){
    CTexture stem_texture;
    stem_texture.Load(stemTex.c_str(), 512, 512);
    stem_texture.use();
    wb->intStemTexture = stem_texture.texturenum;
  }
  if (f2){
    wb->intFoliageTexture = GetTgaTexNumber(folTex);
  }
  trees.push_back(wb);
}







}
#endif
