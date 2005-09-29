
#ifndef LGMVISUALIZATION
#define LGMVIZUALIZATION
#include <vector>

#include "OpenGLSymbols.h"
#include "OpenGLfunctions.h"
#include "OpenGLFunctor.h"
#include "OpenGL.h"
#include <GLSettings.h>
#include <WrapperBase.h>


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
   void operator()(WrapperBase* wb){ wb->DrawTree(x,y,z);}
     float x;
     float y;
     float z;
   
  };

  class DrawTreeMetrics{
  public:
    void operator()(WrapperBase* wb){ wb->DrawTreeMetrics();}
  };

class LGMVisualization
{
  static LGMVisualization* active_visualization;
  public:

  template <class TS, class BUD,class SHAPE>
  void AddHwTree(Tree<TS, BUD>& t, string stemTex, string folTex);
  
  template <class TS, class BUD>
  void AddCfTree(Tree<TS, BUD>& t, string stemTex, string folTex);


  double ldistance;


  LGMVisualization();
  void SetVisibleDistance(double l);
  void SetCameraDistance(double d){camera_distance = d;}
  void InitVisualization(int argc=0,char* argv[] = NULL);
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

 void GetCameraPos(double &x1, double &y1, double &z1,
		   double &x2, double &y2, double &z2,
		   double odd);
  void drawTrees(); /*{for_each(trees.begin(),trees.end(),DrawTrees());}*/
  void makeDisplayLists(){for_each(trees.begin(),trees.end(),MakeDisplayLists(order_foliage));}
 void makeWireModelLists(){for_each(trees.begin(),trees.end(),MakeWireModelLists());}
private:
  bool drawed;
  bool order_foliage;

  GLSettings settings;
  STEMMODE mode;

  int ShowTree; 

  void StartAnimation();
  void RedrawMovement(double odd);

  void InitCallBacks();
  void ReDrawWindow(void);
  void ReDraw();
  void GoNextTree();
  void Zoom(int dir);//Zooming: dir=1 forward, dir=-1 backwards
  void Translate(PositionVector& d);//move  camera  up/down,left/right
				    //as well as the point of focus
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
private:
  double max_height;//The tree with the maximum height to be visualized
  double camera_distance;//Explicitely set the  distance of the camera
			 //from the current tree (ShowTree)
  int show_tree_metrics;//Toggle display of H and Dbh
  int show_help;//Toggle help display
  string help_str;//Current help string (fi or en)
  string help_fi;//Finnish help
  string help_en;//English help
};



} 

#include <LGMVisualizationI.h>

#endif
