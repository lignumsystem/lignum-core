//Include Lignum implementation 
#include <Lignum.h>
//Include the implementation of the tree segment and bud
#include "Bearberry.h"
//Simple collition detection algorithm
#include <Collision.h>

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
  KillBud<BearberrySegment,BearberryBud> kill_bud(0.11);
  Aging<BearberrySegment,BearberryBud> aging;
  ShortenSegment<BearberrySegment,BearberryBud> shorten_segment;
  LGMdouble coll = 0.0;

  bearberryL.start();
  bearberryL.lstringToLignum(bearberry,3,LGMtype,LGMstatus,LGMcollision);
  for (int i=0; i < bearberryL.derivationLength() ; i++)
  {
    cout << "Step: " << i << endl;    
    ForEach(bearberry,EvaluateCollisionForAllBuds<BearberrySegment,BearberryBud>(65.0*2.0*PI_VALUE/360.0,0.20));
    bearberryL.lignumToLstring(bearberry,3,LGMtype,LGMstatus,LGMcollision);  
    bearberryL.derive();
    bearberryL.lstringToLignum(bearberry,3,LGMtype,LGMstatus,LGMcollision);
    ForEach(bearberry,aging);
    ForEach(bearberry,kill_bud);
  }
  bearberryL.end();  
  
  AccumulateDown(bearberry,coll,shorten_segment);
  bearberryL.lignumToLstring(bearberry,3,LGMtype,LGMstatus,LGMcollision);
  bearberryL.lstringToLignum(bearberry,3,LGMtype,LGMstatus,LGMcollision);

  vector<PositionVector> v;
  AccumulateDown(bearberry,v,
		 AppendSequence<vector<PositionVector> >(),
		 CreateLeaves<BearberrySegment,BearberryBud, Ellipse>(0.1,0.1,0.1));
  cout << endl;
  //Visualize LIGNUM - Graphics project needs to be fixed
  VisualizeHwTree<BearberrySegment,BearberryBud,Ellipse>(bearberry);
}
