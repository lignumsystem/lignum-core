
#ifndef LGMVISUALIZATIONI
#define LGMVIZUALIZATIONI

#include <WrapperBase.h>
#include <CTexture.h>

namespace Lignum{




 template <class TS, class BUD>
 void LGMVisualization::AddHwTree(Tree<TS,BUD>& t, string stemTex, string folTex)
{
    HwWrapper<TS,BUD> *wb = new HwWrapper<TS,BUD>(t);

    wb->intFoliageTexture = GetTgaTexNumber(folTex);
    //  wb->intStemTexture = GetBmpTexNumber(stemTex);
    
    CTexture stem_texture;
    stem_texture.Load(stemTex.c_str(), 512, 512);

    wb->intStemTexture = stem_texture.texturenum;
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
