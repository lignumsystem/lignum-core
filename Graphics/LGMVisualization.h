
#ifndef LGMVISUALIZATION
#define LGMVIZUALIZATION


#include "OpenGLSymbols.h"
#include "OpenGLfunctions.h"
#include "OpenGLFunctor.h"
#include "OpenGL.h"
#include <GLSettings.h>
#include <vector>

#include <Lignum.h>
#include <ScotsBud.h>
#include <ScotsPineVisual.h>

namespace Lignum{

enum DRAWMODE { STEM_MODE, FOLIAGE_MODE };



class LGMVisualization
{
  static LGMVisualization* active_visualization;
  public:

  LGMVisualization();
  void InitVisualization();
  void SetAntialising(bool antialisingOn);

  void DrawScotsPine(Tree<ScotsPineVisual, ScotsBud> &tree, DRAWMODE mode);
  

  void AddScotsPine(Tree<ScotsPineVisual, ScotsBud> *tree);


 
  void NewWindowSize(GLsizei new_x, GLsizei new_y);
  void Quit(void);
  void Arrows(int key, int x, int y);
  void Keypress(unsigned char key, int x, int y);
  void ChangeMouseButton(int button, int state, int x, int y);
  void MouseMotion(int x, int y);
  void Loop(void);
  void Menu(int value);
  void StartVisualization();

private:
  bool drawed;

  GLSettings settings;


  std::vector<Tree<ScotsPineVisual, ScotsBud> * > scotspines;

  void InitCallBacks();
  void ReDrawWindow(void);
  void ReDraw();

  void CountCamera(void);
  void SetLight(void);
  void SetValues(void);
  void CheckValues(void);

  static void StaticLoop(void);
  static void StaticMouseMotion(int x, int y);
  static void StaticArrows(int key, int x, int y);
  static void StaticReDraw(void);
  static void StaticMenu(int value);
  static void StaticChangeMouseButton(int button, int state, int x, int y);
  static void StaticKeyPress(unsigned char key, int x, int y);
  static void StaticNewWindowSize(GLsizei new_x, GLsizei new_y);
};


} 

#endif
