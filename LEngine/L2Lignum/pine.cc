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

//and for pine, see also pine9bp.L in lsys.
namespace Pine{
#include <LSystem.h>
}

int main(int argc, char** argv)
{

  //Pine  does not  include data  exchange.  Demonstrate  that several
  //individuals of  the same  species can be  simulated. Note  you can
  //leave out  the attribute  name and type  in the  template argument
  //list.
  Pine::LSystem<MyCfTreeSegment,MyCfBud> pl1;

  Tree<MyCfTreeSegment,MyCfBud> pine1(Point(0,1,0),
				      PositionVector(0,0,1.0));
  
 
  //Expand axiom.
  pl1.start();
  pl1.lstringToLignum(pine1);
  //Naturally, one can use  other termination conditions than just the
  //derivation length.
  for (int i=0; i < 8; i++)
  {
    cout << "Step: " << i << endl;
    //Update L-strings, no interchange  of information.
    pl1.lignumToLstring(pine1);
    //Structural development for the tree.    
    pl1.derive();
    //Update pine structure, no interchange  of information.
    pl1.lstringToLignum(pine1);
  }
  //Clean up.
  pl1.end();  
  DisplayStructureData id;
  PropagateUp(pine1,id,DisplayStructureFunctor<MyCfTreeSegment,MyCfBud>());
  VisualizeCfTree(pine1);

}
