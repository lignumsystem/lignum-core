#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdarg.h>

#include <lglobal.h>
#include <lsysintrfc.h>

#include <succstor.h>

#include <iostream>
#include <Lignum.h>
#include <Collision.h>

#include <MyTreeSegment.h>
#include <MyBud.h>
#include <OpenGLUnix.h>
using namespace std;


#include <LSystem.h>


int main(int argc, char** argv)
{
  LSystem l;
  Tree<MyTreeSegment,MyBud> t1(Point(0,0,0),
				 PositionVector(0,0,1.0));

  
  l.start();
  l.lstring2Lignum<MyTreeSegment,MyBud,LGMAD,LGMdouble>(t1,3,LGMtype,LGMstatus,LGMcollision);
  for (int i=0; i < DerivationLength(); i++)
  {
    cout << "Step: " << i << endl;
    ForEach(t1,EvaluateCollisionForAllBuds<MyTreeSegment,MyBud>(90.0*2.0*PI_VALUE/360.0,0.10));
    l.lignum2Lstring<MyTreeSegment,MyBud,LGMAD,LGMdouble>(t1,3,LGMtype,LGMstatus,LGMcollision);  
    l.derive();
    l.lstring2Lignum<MyTreeSegment,MyBud,LGMAD,LGMdouble>(t1,3,LGMtype,LGMstatus,LGMcollision);
  }
  l.end();  

  VisualizeLGMTree(t1);

}
