//Include Lignum implementation 
#include <Lignum.h>
//Include the implementation of the tree segment and bud
#include <MyTreeSegment.h>
#include <MyBud.h>


//Impelements VisualizeLGMTree
#include <OpenGLUnix.h>

//Includes all kinds of stuff, turtle graphics etc.
#include <lengine.h>

//LSystem captures the rewriting process
//for bearberry, see also bearberry.L in lsys.
namespace Birch{
#include <LSystem.h>
}

namespace Pine{
#include <LSystem.h>
}

int main(int argc, char** argv)
{

  Birch::LSystem<MyHwTreeSegment,MyHwBud,LGMAD,LGMdouble> birchL;
  Pine::LSystem<MyCfTreeSegment,MyCfBud,LGMAD,LGMdouble> pineL;
  Tree<MyHwTreeSegment,MyHwBud> birch(Point(0,0,0),
				      PositionVector(0,0,1.0));
  
  Tree<MyCfTreeSegment,MyCfBud> pine(Point(0.3,0.3,0),
				     PositionVector(0,0,1.0));
  birchL.start();
  birchL.lstringToLignum(birch,1,LGMstatus);
  for (int i=0; i < 5 ; i++)
  {
    cout << "Step: " << i << endl;    
    ForEach(birch,DropAllLeaves<MyHwTreeSegment,MyHwBud>());
    birchL.lignumToLstring(birch,1,LGMstatus);  
    birchL.derive();
    birchL.lstringToLignum(birch,1,LGMstatus);
    vector<PositionVector> pv;
    AccumulateDown(birch,pv,
    		   AppendSequence<vector<PositionVector> >(),
    		   CreateLeaves<MyHwTreeSegment,MyHwBud>(0.5,0.2,0.1));
  }
  birchL.end();  


  pineL.start();
  pineL.lstringToLignum(pine,1,LGMstatus);
  for (int i=0; i < 5 ; i++)
  {
    cout << "Step: " << i << endl;    
    pineL.lignumToLstring(pine,1,LGMstatus);  
    pineL.derive();
    pineL.lstringToLignum(pine,1,LGMstatus);
  }
  pineL.end();  

  Forest f;
  InsertCfTree(f,pine);
  InsertHwTree(f,birch);
  Initialize3DForest<Tree<MyCfTreeSegment, MyCfBud> >(f);
  VisualizeForest<Tree<MyHwTreeSegment, MyHwBud> >(f);
}
