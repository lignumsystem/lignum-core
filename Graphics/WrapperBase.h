
#ifndef WRAPPERBASE
#define WRAPPERBASE

#include <Lignum.h>

namespace Lignum{

class WrapperBase
{
public:
  WrapperBase(): intStemTexture(0),intFoliageTexture(0),intDisplaylistStem(0),
		 intDisplaylistFoliage(0){}
  virtual void VisualizeTree()=0;
  virtual void VisualizeStem(int &active_texture)=0;
  virtual void VisualizeFoliage(int &active_texture)=0; 

 int intStemTexture;    //texture number of stem
 int intFoliageTexture; //texture number of foliage
 int intDisplaylistStem; //displaylists
 int intDisplaylistFoliage;
};



template <class TS, class BUD> 
class CfWrapper: public WrapperBase 
{
public:
  
  CfWrapper(const Tree<TS,BUD>& t):WrapperBase(),tree(t){}

  void VisualizeTree();
  void VisualizeStem(int &active_texture);
  void VisualizeFoliage(int &active_texture);


  Tree<TS,BUD>& tree;
};

template <class TS, class BUD>
class HwWrapper: public WrapperBase 
{
public:
  HwWrapper(Tree<TS,BUD>& t):WrapperBase(),tree(t){}

  void VisualizeTree();
  void VisualizeStem(int &active_texture);
  void VisualizeFoliage(int &active_texture);
  
 
  Tree<TS,BUD>& tree;
};



}

#include <WrapperBaseI.h>

#endif
