
#ifndef LGMVISUALIZATION
#define LGMVIZUALIZATION


#include "OpenGLSymbols.h"
#include "OpenGLfunctions.h"
#include "OpenGLFunctor.h"
#include "OpenGL.h"
#include <GLSettings.h>
#include <vector>



enum DRAWMODE { STEM_MODE, FOLIAGE_MODE };

class LGMVisualization
{
  public:

  LGMVisualization();
  InitVisualization();
  void SetAntialising(bool antialisingOn);

  void DrawScotsPine(Tree<ScotsPineVisual, ScotsBud> &tree, DRAWMODE mode);
  

  void AddScotsPine(Tree<ScotsPineVisual, ScotsBud> &tree);
private:

  GLSettings settings;


  std::vector<Tree<ScotsPineVisual, ScotsBud> * > scotspines;
  void ReDrawWindow(void);

  void CountCamera(void);
  void SetLight(void);
  void SetValues(void);
  void CheckValues(void);
  void NewWindowSize(GLsizei new_x, GLsizei new_y);
  void Quit(void);
  void Arrows(int key, int x, int y);
  void Keypress(unsigned char key, int x, int y);
  void ChangeMouseButton(int button, int state, int x, int y);
  void MouseMotion(int x, int y);
  void Loop(void);
  void Menu(int value);
  void InitCallBacks();

};

#endif