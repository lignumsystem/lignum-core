
#ifndef WRAPPERBASE
#define WRAPPERBASE

#include <Lignum.h>

namespace Lignum{

class WrapperBase
{
public:
 virtual void VisualizeTree();
 virtual void VisualizeStem(int &active_texture);
 virtual void VisualizeFoliage(int &active_texture); 

 int intStemTexture;    //texture number of stem
 int intFoliageTexture; //texture number of foliage
 int intDisplaylistStem; //displaylists
 int intDisplaylistFoliage;
};



template <class TS, class BUD> 
class CfWrapper: public WrapperBase 
{
public:
  
  CfWrapper(const Tree<TS,BUD>& t):tree(t){}

  void VisualizeTree();
  void VisualizeStem(int &active_texture);
  void VisualizeFoliage(int &active_texture);


  Tree<TS,BUD>& tree;
};

template <class TS, class BUD>
class HwWrapper: public WrapperBase 
{
public:
  HwWrapper(Tree<TS,BUD>& t):tree(t){}

  void VisualizeTree();
  void VisualizeStem(int &active_texture);
  void VisualizeFoliage(int &active_texture);
  
 
  Tree<TS,BUD>& tree;
};



}

#include <WrapperBaseI.h>

#endif
