
#ifndef LGMVISUALIZATION
#define LGMVIZUALIZATION


#include "OpenGLSymbols.h"
#include "OpenGLfunctions.h"
#include "OpenGLFunctor.h"
#include "OpenGL.h"
#include <GLSettings.h>
#include <WrapperBase.h>
#include <vector>

#include <Lignum.h>

enum DRAWMODE { STEM_MODE, FOLIAGE_MODE };

//enum STEMMODE { SOLID, WIREMODEL };

struct LoadedTexture
{
    string fname;
    int number;
};

namespace Lignum{
enum STEMMODE { SOLID, WIREMODEL };
  class Hello{
  public:
    void operator()(WrapperBase* wb){
      wb->hello();
    }
  };



 class MakeWireModelLists{
  public:
   void operator()(WrapperBase* wb){
     wb->MakeWireModelLists();
   }
  };


 class MakeDisplayLists{
  public:
     MakeDisplayLists(bool b) { order = b; };  
     void operator()(WrapperBase* wb){
	 wb->MakeDisplayLists(order);}
     bool order;
   
  };


 class DrawTrees{
  public:
     DrawTrees(float sx, float sy, float sz){ x=sx; y=sy; z=sz; }
     void operator()(WrapperBase* wb){ wb->DrawTree(x,y,z);     }
     float x;
     float y;
     float z;
   
  };


class LGMVisualization
{
  static LGMVisualization* active_visualization;
  public:

  template <class TS, class BUD,class SHAPE>
  void AddHwTree(Tree<TS, BUD>& t, string stemTex, string folTex);
  
  template <class TS, class BUD>
  void AddCfTree(Tree<TS, BUD>& t, string stemTex, string folTex);

  LGMVisualization();
  void InitVisualization();
  void SetAntialising(bool antialisingOn);
  void SetMode(STEMMODE m) { mode = m; }
  void NewWindowSize(GLsizei new_x, GLsizei new_y);
  void Quit(void);
  void Arrows(int key, int x, int y);
  void Keypress(unsigned char key, int x, int y);
  void ChangeMouseButton(int button, int state, int x, int y);
  void MouseMotion(int x, int y);
  void Loop(void);
  void Menu(int value);
  void StartVisualization();
  void OrderFoliage(bool v) {  order_foliage = v; }
  void ResetCameraPosition(float height);

  int GetTgaTexNumber(string filename);
  int GetBmpTexNumber(string filename);



  void drawTrees(); /*{for_each(trees.begin(),trees.end(),DrawTrees());}*/
  void hello(){for_each(trees.begin(),trees.end(),Hello());}
  void makeDisplayLists(){for_each(trees.begin(),trees.end(),MakeDisplayLists(order_foliage));}
 void makeWireModelLists(){for_each(trees.begin(),trees.end(),MakeWireModelLists());}
private:
  bool drawed;
  bool order_foliage;

  GLSettings settings;
  STEMMODE mode;

  void InitCallBacks();
  void ReDrawWindow(void);
  void ReDraw();
 
  void CountCamera(void);
  void SetLight(void);
  void SetValues(void);
  void CheckValues(void);


  std::vector<LoadedTexture> LoadedTgas;
  std::vector<LoadedTexture> LoadedBmps;
  std::vector<WrapperBase *> trees;

  static void StaticLoop(void);
  static void StaticMouseMotion(int x, int y);
  static void StaticArrows(int key, int x, int y);
  static void StaticReDraw(void);
  static void StaticMenu(int value);
  static void StaticChangeMouseButton(int button, int state, int x, int y);
  static void StaticKeyPress(unsigned char key, int x, int y);
  static void StaticNewWindowSize(int new_x, int new_y);
};



} 

#include <LGMVisualizationI.h>

#endif
