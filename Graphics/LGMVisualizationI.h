
#ifndef LGMVISUALIZATIONI
#define LGMVIZUALIZATIONI

#include <WrapperBase.h>
#include <CTexture.h>

namespace Lignum{




 template <class TS, class BUD>
 void LGMVisualization::AddHwTree(Tree<TS,BUD>& t, string stemTex, string folTex)
{
    HwWrapper<TS,BUD> *wb = new HwWrapper<TS,BUD>(t);


   
    CTexture stem_texture;
    stem_texture.Load(stemTex.c_str(), 512, 512);
    stem_texture.use();

    wb->intStemTexture = stem_texture.texturenum;
    cout << " rungon TEXTURE numero "<<  stem_texture.texturenum << endl;
 
    
    CTexture fol_texture;
    fol_texture.Load(folTex.c_str(), 512, 512);
    fol_texture.use();
    wb->intFoliageTexture = fol_texture.texturenum;
    cout << " lehden TEXTURE numero "<<  wb->intFoliageTexture << endl;

    //Tätä käytetään jos halutaa visualisoida lehdet läpinäkyvyyden avulla.
    // Tiedosto-muoto .tga
/*
  wb->intFoliageTexture = GetTgaTexNumber(folTex);
  cout << " lehden TEXTURE numero "<<  wb->intFoliageTexture << endl;
*/  
    trees.push_back(wb);
}

  
 template <class TS, class BUD>
 void LGMVisualization::AddCfTree(Tree<TS,BUD>& t, string stemTex, string folTex)

{	
	CfWrapper<TS,BUD> *wb = new CfWrapper<TS,BUD>(t);

	wb->intFoliageTexture = GetTgaTexNumber(folTex);
	trees.push_back(wb);
}


}
#endif
