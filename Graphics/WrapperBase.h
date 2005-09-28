#ifndef WRAPPERBASE_H
#define WRAPPERBASE_H

#if defined(__APPLE__) || defined(__MACOSX__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <sstream>


#include <Lignum.h>



namespace Lignum{
  void LGMTextOutput(double x,double y,double z,void* font,const string &str);
class WrapperBase
{
public:
  WrapperBase(): intStemTexture(0),intFoliageTexture(0),intDisplaylistStem(0),
		 intDisplaylistFoliage(0){}
  virtual void VisualizeTree(){cout << "WrapperBase::VisualizeTree()" << endl;}
  virtual void VisualizeFoliage(int &active_texture){cout << "VisualizeFoliage not found" << endl;} 
  virtual void VisualizeStem(int &active_texture)=0;
  virtual void VisualizeWireModel()=0;
  virtual void MakeDisplayLists(bool orderfoliage)=0;
  virtual void MakeWireModelLists()=0;
  virtual void DrawTree(float x, float y, float z)=0;
  virtual void GetTreeMetrics(Point &pos, LGMdouble &h)=0;
  virtual void DrawTreeMetrics()=0;
  // CTexture stem_texture;
  int intStemTexture;    //texture number of stem
  int intFoliageTexture; //texture number of foliage
  int intDisplaylistStem; //displaylists
  int intDisplaylistFoliage;
  bool ordfoliage;
  bool bmpImage;
};



template <class TS, class BUD> 
class CfWrapper: public WrapperBase 
{
public:
  
  CfWrapper(Tree<TS,BUD>& t):WrapperBase(),tree(t){}

  void MakeDisplayLists(bool orderfoliage);
  void MakeWireModelLists();
  void VisualizeTree();
  void VisualizeFoliage(int &active_texture);
  virtual void DrawTree(float x, float y, float z);
  void VisualizeWireModel();
  virtual void VisualizeStem(int &active_texture);
  virtual void GetTreeMetrics(Point &pos, LGMdouble &h);
  virtual void DrawTreeMetrics();
  Tree<TS,BUD>& tree;
};


//Shape pit�� lis�t� luokkaan jotta DrawOrderedLeaves ja koko luokka toimii

template <class TS, class BUD, class SHAPE>
class HwWrapper: public WrapperBase 
{
public:
  HwWrapper(Tree<TS,BUD>& t):WrapperBase(),tree(t){}
  void MakeDisplayLists(bool orderfoliage);
  void MakeWireModelLists();
  void VisualizeTree();
 
  void VisualizeFoliage(int &active_texture);
  virtual void DrawTree(float x, float y, float z);
  void VisualizeWireModel();
  virtual void GetTreeMetrics(Point &pos, LGMdouble &h);
  virtual void DrawTreeMetrics(){LGMMessage("HwWrapper::DrawTreeMetrics Not Implemented");}
  virtual void VisualizeStem(int &active_texture);
  void DrawOrderedLeaves(float x, float y, float z);
  
  Tree<TS,BUD>& tree;
};



}

#endif
#include <WrapperBaseI.h>
