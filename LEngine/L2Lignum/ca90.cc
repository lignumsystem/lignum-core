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

//CA Rule 90
namespace ca90{
#include <LSystem.h>
}

int main(int argc, char** argv)
{
  ca90::LSystem<MyCfTreeSegment,MyCfBud>  p90;  

  p90.start();
  //Naturally, one can use  other termination conditions than just the
  //derivation length.
  for (int i=0; i < 200; i++)
  {
    //Update L-strings, no interchange  of information.
    //Structural development for the trees.
    p90.derive();

  }
  //Clean up.
  p90.end();  
  cout << endl;
}
