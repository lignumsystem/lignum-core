
#ifndef LGMVISUALIZATIONI
#define LGMVIZUALIZATIONI


namespace Lignum{


 template <class TS, class BUD>
 void LGMVisualization::AddHwTree(Tree<TS,BUD>& t)
{
	HwWrapper<TS,BUD> *wb = new HwWrapper<TS,BUD>(t);

	trees.push_back((WrapperBase *)wb);
}

  
 template <class TS, class BUD>
 void LGMVisualization::AddCfTree(Tree<TS,BUD>& t)

{	
	CfWrapper<TS,BUD> *wb = new CfWrapper<TS,BUD>(t);

	trees.push_back((WrapperBase *)wb);
}


}
#endif
