
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

namespace Lignum{




class LGMVisualization
{
  static LGMVisualization* active_visualization;
  public:

  template <class TS, class BUD>
  void AddHwTree(Tree<TS, BUD>& t);
  
  template <class TS, class BUD>
  void AddCfTree(Tree<TS, BUD>& t);

  LGMVisualization();
  void InitVisualization();
  void SetAntialising(bool antialisingOn);
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

  void InitCallBacks();
  void ReDrawWindow(void);
  void ReDraw();

  void CountCamera(void);
  void SetLight(void);
  void SetValues(void);
  void CheckValues(void);

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
