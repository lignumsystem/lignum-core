//Include Lignum implementation 
#include <Lignum.h>
//Include the implementation of the tree segment and bud
#include "Bearberry.h"

//Impelements VisualizeLGMTree
#include <OpenGLUnix.h>

//Includes all kinds of stuff, turtle graphics etc.
#include <lengine.h>

//LSystem captures the rewriting process
//for bearberry, see also bearberry.L in lsys.
namespace Bearberry{
#include <LSystem.h>
}


int main(int argc, char** argv)
{

  Bearberry::LSystem<BearberrySegment,BearberryBud,LGMAD,LGMdouble> bearberryL;
  Tree<BearberrySegment,BearberryBud> bearberry(Point(0,0,0),
					  PositionVector(0,0,1.0));

  bearberryL.start();
  bearberryL.lstringToLignum(bearberry,1,LGMstatus);
  for (int i=0; i < bearberryL.derivationLength() ; i++)
  {
    cout << "Step: " << i << endl;    
    ForEach(bearberry,DropAllLeaves<BearberrySegment,BearberryBud>());
    bearberryL.lignumToLstring(bearberry,1,LGMstatus);  
    bearberryL.derive();
    bearberryL.lstringToLignum(bearberry,1,LGMstatus);
    vector<PositionVector> pv;
    AccumulateDown(bearberry,pv,
    		   AppendSequence<vector<PositionVector> >(),
    		   CreateLeaves<BearberrySegment,BearberryBud>(0.5,0.5,0.5));
  }
  bearberryL.end();  

  cout << endl;
  //Visualize LIGNUM - Graphics project needs to be fixed
  VisualizeHwTree(bearberry);
}
