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
  if (argc != 7){
    cout << "Usage: auvaursi iter angle distance p1 p2 p3" << endl;
  }
  int iter = atoi(argv[1]);
  double angle =  atof(argv[2]);
  double distance =  atof(argv[3]);
  double nddie = atof(argv[4]);//nondominant
  double sddie = atof(argv[5]);//subdominant
  double ddie = atof(argv[6]); //dominant

  Bearberry::LSystem<BearberrySegment,BearberryBud,LGMAD,LGMdouble> bearberryL;
  Tree<BearberrySegment,BearberryBud> bearberry(Point(0,0,0),
						PositionVector(0,0,1.0));
  KillBud<BearberrySegment,BearberryBud> kill_bud(nddie,sddie,ddie);
  Aging<BearberrySegment,BearberryBud> aging;
  ShortenSegment<BearberrySegment,BearberryBud> shorten_segment;
  
  cout << iter << " iterations " << angle << " degrees " 
       << distance << " meters " 
       << nddie << " p1 " << sddie << " p2 " << ddie << " p3 " << endl;
  
  bearberryL.start();
  bearberryL.lstringToLignum(bearberry,3,LGAtype,LGMstatus,LGMcollision);
  for (int i=0; i < iter ; i++)
  {
    cout << "Step: " << i << endl;    
    ForEach(bearberry,EvaluateCollisionForAllBuds<BearberrySegment,BearberryBud>(angle*PI_VALUE/180.0,distance));
    bearberryL.lignumToLstring(bearberry,3,LGAtype,LGMstatus,LGMcollision);  
    bearberryL.derive();
    bearberryL.lstringToLignum(bearberry,3,LGAtype,LGMstatus,LGMcollision);
    //ForEach(bearberry,aging);
    //ForEach(bearberry,kill_bud);
  }
  bearberryL.end();  

  LGMdouble coll = 0.0;  
  AccumulateDown(bearberry,coll,shorten_segment);
  bearberryL.lignumToLstring(bearberry,3,LGAtype,LGMstatus,LGMcollision);
  bearberryL.lstringToLignum(bearberry,3,LGAtype,LGMstatus,LGMcollision);

//   vector<PositionVector> v;
//   AccumulateDown(bearberry,v,
// 		 AppendSequence<vector<PositionVector> >(),
// 		 CreateLeaves<BearberrySegment,BearberryBud, Ellipse>(0.1,0.1,0.1));
  cout << endl;
  //Visualize LIGNUM - Graphics project needs to be fixed
  VisualizeHwTree<BearberrySegment,BearberryBud,Ellipse>(bearberry);
}
