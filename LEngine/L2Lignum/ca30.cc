//Include Lignum implementation 
#include <Lignum.h>
//Include the implementation of the tree segment and bud
#include <MyTreeSegment.h>
#include <MyBud.h>
#include <VisualFunctor.h>

//Impelements VisualizeLGMTree
#include <OpenGLUnix.h>

//Includes all kinds of stuff, turtle graphics etc.
#include <lengine.h>

//CA Rule 30
namespace ca30{
#include <LSystem.h>
}

int main(int argc, char** argv)
{
  ca30::LSystem<MyCfTreeSegment,MyCfBud>  p30;  

  p30.start();
  //Naturally, one can use  other termination conditions than just the
  //derivation length.
  for (int i=0; i < 200; i++)
  {
    //Update L-strings, no interchange  of information.
    //Structural development for the trees.
    p30.derive();

  }
  //Clean up.
  p30.end();  
  cout << endl;
}
