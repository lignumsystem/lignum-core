
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


class CfWrapper: public WrapperBase 
{
public:
  CfWrapper(const Tree& t):tree(t){}

  void VisualizeTree();
  void VisualizeStem(int &active_texture);
  void VisualizeFoliage(int &active_texture);
  Tree& tree;
};


class HwWrapper: public WrapperBase 
{
public:
  HwWrapper(const Tree& t):tree(t){}

  void VisualizeTree();
  void VisualizeStem(int &active_texture);
  void VisualizeFoliage(int &active_texture);
  Tree& tree;
};



}

#endif
