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

//and for pine, see also pine9bp.L in lsys.
namespace Pine{
#include <LSystem.h>
}

//CSPlants demonstrate the  context sensitive L-systems.  The CSplants
//A, B, D and E produce plants A,  B, C, D and E presented in Fig 1.31
//in  Algorithmic  Beauty  of   Plants,  page  34.   See  cs-plantA.L,
//cs-plantB.L cs-plantC.L, cs-plantD.L, and cs-plant.L in lsys.
namespace CSPlantA{
#include <LSystem.h>
}

namespace CSPlantB{
#include <LSystem.h>
}

namespace CSPlantC{
#include <LSystem.h>
}

namespace CSPlantD{
#include <LSystem.h>
}

namespace CSPlantE{
#include <LSystem.h>
}

int main(int argc, char** argv)
{
  //Create the bl  (bearberry) and pl1 and pl2 (two  pines) to run the
  //L-system  rewriting.  Bearberry  exchanges  data, attributes  from
  //enumeration type LGMAD of type LGMdouble
  Bearberry::LSystem<MyTreeSegment,MyBud,LGMAD,LGMdouble> bl;
  //Pine  does not  include data  exchange.  Demonstrate  that several
  //individuals of  the same  species can be  simulated. Note  you can
  //leave out  the attribute  name and type  in the  template argument
  //list.
  Pine::LSystem<MyTreeSegment,MyBud> pl1;
  Pine::LSystem<MyTreeSegment,MyBud> pl2;

  //CSplants
  CSPlantA::LSystem<MyTreeSegment,MyBud> csla;
  CSPlantB::LSystem<MyTreeSegment,MyBud> cslb;
  CSPlantC::LSystem<MyTreeSegment,MyBud> cslc;
  CSPlantD::LSystem<MyTreeSegment,MyBud> csld;
  CSPlantE::LSystem<MyTreeSegment,MyBud> csle;
  //Create three trees, bearberry and  two pines (well, bearberry is a
  //berry...)
  Tree<MyTreeSegment,MyBud> bearberry(Point(0,0,0),
				      PositionVector(0,0,1.0));
  Tree<MyTreeSegment,MyBud> pine1(Point(0,0,0),
				  PositionVector(0,0,1.0));
  Tree<MyTreeSegment,MyBud> pine2(Point(0,0,0),
				  PositionVector(0,0,1.0));
  Tree<MyTreeSegment,MyBud> csplant(Point(0,0,0),
				    PositionVector(0,0,1.0));
  //Bearberry demonstrates typical loop in L-system rewriting 
  //1. Expand the axiom.
  bl.start();
  //2. Update LIGNUM with  interchange of information.  In each LIGNUM
  //bud the attributes of the name LGMtype, LGMstatus and LGMcollision
  //are updated from symbols B in the L-system string.  In bearberry.L
  //the  symbol  B contains  3  arguments  and  their meaning  and  is
  //LGMtype, LGMstatus  and LGMcollision from left to  right. The data
  //type of these attributes is LGMdouble both in LIGNUM and in symbol
  //B in bearberry.L.
  bl.lstringToLignum(bearberry,3,LGMtype,LGMstatus,LGMcollision);
  //3. Loop derivation length of times: 
  for (int i=0; i < bl.derivationLength() ; i++)
  {
    cout << "Step: " << i << endl;
    //4.       Detect       collision.       The      argument      in
    //EvaluateCollisionForAllBuds  is the  opening  angle in  radians,
    //i.e.  the visibile sector for a bud.  The second argument is the
    //lookahead  distance  in meters.  Other  metabolic processes  may
    //follow.
    ForEach(bearberry,EvaluateCollisionForAllBuds<MyTreeSegment,MyBud>(60.0*2.0*PI_VALUE/360.0,0.10));
    //5. Update the  string; LGMtype,LGMstatus,LGMcollision are copied
    //from LIGNUM buds to symbols B in the string.
    bl.lignumToLstring(bearberry,3,LGMtype,LGMstatus,LGMcollision);  
    //6. Expand the  string. If you have defined  StartEach or EndEach
    //statements derive executes these statements.
    bl.derive();
    //7.   Update LIGNUM  with interchange  of  information.  LGMtype,
    //LGMstatus, LGMcollision are copied  from symbols B in the string
    //to LIGNUM buds.
    bl.lstringToLignum(bearberry,3,LGMtype,LGMstatus,LGMcollision);
  }
  //8. Some clean up if  End statement is defined in L-file; otherwise
  //end is a dummy method.
  bl.end();  


  //Two Scots  pines. Demonstrate that several individuals  of the same
  //species can be simulated.
  //Expand axioms.
  pl1.start();
  pl2.start();
  pl1.lstringToLignum(pine1);
  pl2.lstringToLignum(pine2);
  //Naturally, one can use  other termination conditions than just the
  //derivation length.
  for (int i=0; i < 6; i++)
  {
    cout << "Step: " << i << endl;
    //Update L-strings, no interchange  of information.
    pl1.lignumToLstring(pine1);
    pl2.lignumToLstring(pine2);
    //Structural development for the trees.
    pl1.derive();
    pl2.derive();
    //Update pine structures, no interchange  of information.
    pl1.lstringToLignum(pine1);
    pl2.lstringToLignum(pine2);
  }
  //Clean up.
  pl1.end();  
  pl2.end();

  //CSPlants demonstrates context sensitive L-systems Not that grammar
  //needs  to be modified  for LIGNUM  if one  wants to  update LIGNUM
  //structure  after each  derivation  step. Grammar  does not  create
  //LIGNUM structure. Also note that grammars that insert new segments
  //in the  middle of  the plant  are still a  problem in  LIGNUM, for
  //example:  FaIFaIFaI--> FaIFaIFbiIFaI.   One must  identify somehow
  //the segments (position?) to update.
  csla.start();
  csla.lstringToLignum(csplant);
  for (int i=0; i < csla.derivationLength(); i++){
    cout <<  "Step: " << i << endl;
    csla.derive();
  }
  csla.end(); 
  //Update LIGNUM
  csla.lstringToLignum(csplant);  
  //Visualize LIGNUM
  VisualizeLGMTree(csplant);
}
