//Include Lignum implementation 
#include <Lignum.h>
//Include the implementation of the tree segment and bud
#include <MyTreeSegment.h>
#include <MyBud.h>

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

//and for pine, also scotspine9bp.L in lsys.
namespace Pine{
#include <LSystem.h>
}


int main(int argc, char** argv)
{
  //Create the pl and l to run the rewriting
  Pine::LSystem pl;
  Bearberry::LSystem l;

  //Create two trees, bearberry and pine
  Tree<MyTreeSegment,MyBud> bearberry(Point(0,0,0),
				 PositionVector(0,0,1.0));
  Tree<MyTreeSegment,MyBud> pine(Point(0,0,0),
				 PositionVector(0,0,1.0));

  //Bearberry
  //Typical loop in rewriting
  //Expand the axiom
  l.start();
  //Update  LIGNUM with  interchange of  information In  each  bud the
  //attributes  LGMtype,LGMstatus and  LGMcollision  are updated.   In
  //bearberry.L the symbol B contains  (at lest) 3 arguments and their
  //meaning is the same from left to right.
  l.lstring2Lignum<MyTreeSegment,MyBud,LGMAD,LGMdouble>(bearberry,3,LGMtype,LGMstatus,LGMcollision);
  //Loop derivation length of times
  for (int i=0; i < l.derivationLength(); i++)
  {
    cout << "Step: " << i << endl;
    //Detect collision, other metabolic processes may follow
    ForEach(bearberry,EvaluateCollisionForAllBuds<MyTreeSegment,MyBud>(90.0*2.0*PI_VALUE/360.0,0.10));
    //Update the string; LGMtype,LGMstatus,LGMcollision are copied from buds to symbols B in the string
    l.lignum2Lstring<MyTreeSegment,MyBud,LGMAD,LGMdouble>(bearberry,3,LGMtype,LGMstatus,LGMcollision);  
    //Expand the string
    l.derive();
    //Update  LIGNUM with  interchange of  information
    l.lstring2Lignum<MyTreeSegment,MyBud,LGMAD,LGMdouble>(bearberry,3,LGMtype,LGMstatus,LGMcollision);
  }
  //Some clean up if defined in L-file; otherwise end is a dummy method
  l.end();  


  //Scots pine
  pl.start();
  pl.lstring2Lignum<MyTreeSegment,MyBud,LGMAD,LGMdouble>(pine);
  //Naturally, one can use  other termination conditions than just the
  //derivation length.
  for (int i=0; i < 7; i++)
  {
    cout << "Step: " << i << endl;
    //No interchange  of information, but so  far LGMAD,LGMdouble must
    //be used  to complete the  template arguments. May change  in the
    //future if possible (default tempalte arguments). 
    pl.lignum2Lstring<MyTreeSegment,MyBud,LGMAD,LGMdouble>(pine);  
    pl.derive();
    pl.lstring2Lignum<MyTreeSegment,MyBud,LGMAD,LGMdouble>(pine);
  }
  pl.end();  

  //Finally visualize the tree.
  VisualizeLGMTree(pine);

}
