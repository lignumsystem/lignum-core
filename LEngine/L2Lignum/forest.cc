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
  const int N = 10;
  vector<Birch::LSystem<MyHwTreeSegment,MyHwBud,LGMAD,LGMdouble>*> birchLV(N);
  vector<Tree<MyHwTreeSegment,MyHwBud>*> birchV(N);
						 
  vector<Pine::LSystem<MyCfTreeSegment,MyCfBud,LGMAD,LGMdouble>*> pineLV(N);
  vector<Tree<MyCfTreeSegment,MyCfBud>*> pineV(N);

  for (int i = 0; i <  birchLV.size(); i++){
    birchLV[i] = new Birch::LSystem<MyHwTreeSegment,MyHwBud,LGMAD,LGMdouble>();
    pineLV[i] = new Pine::LSystem<MyCfTreeSegment,MyCfBud,LGMAD,LGMdouble>();
  }

  int x = 0; int y = 0;
  for (int i = 0; i < N; i++){
    birchV[i] = new Tree<MyHwTreeSegment,MyHwBud>(Point(x,y,0),
						  PositionVector(0,0,1));
    x+=2.0;
    pineV[i] = new Tree<MyCfTreeSegment,MyCfBud>(Point(x,y,0),
						 PositionVector(0,0,1));
    x+=2.0;
    if (x == 8){
      x = 0;
      y += 2;
    }
    cout << "i: " << i << endl;
  }

  for (int i = 0; i <  birchLV.size(); i++){
    cout << "Pine start i: " << i << endl;
    pineLV[i]->start();
    pineLV[i]->lstringToLignum(*pineV[i]);
  }
  for (int i = 0; i <  birchLV.size(); i++){
    cout << "Birch start i: " << i << endl;
    birchLV[i]->start();
    birchLV[i]->lstringToLignum(*birchV[i]);
  }


  const int BDL = 9;
  for (int s = 0; s < BDL; s++){
    for (int i = 0; i <  birchLV.size(); i++){
      cout << "Birch step: " << s << endl;    
      ForEach(*(birchV[i]),DropAllLeaves<MyHwTreeSegment,MyHwBud>());
      birchLV[i]->lignumToLstring(*(birchV[i]),1,LGMstatus);  
      birchLV[i]->derive();
      birchLV[i]->lstringToLignum(*(birchV[i]),1,LGMstatus);
      vector<PositionVector> pv;
      AccumulateDown(*(birchV[i]),pv,
		     AppendSequence<vector<PositionVector> >(),
		     CreateLeaves<MyHwTreeSegment,MyHwBud>(0.5,0.2,0.1));
    }
  }

  const int PDL = 7;
  for (int s = 0; s < PDL; s++){
    for (int i = 0; i <  pineLV.size(); i++){
      cout << "Pine step: " << s << endl;    
      pineLV[i]->lignumToLstring(*(pineV[i]));  
      pineLV[i]->derive();
      pineLV[i]->lstringToLignum(*(pineV[i]));
    }
  }

  Forest f;

  for (int i = 0; i < pineV.size(); i++){
    InsertCfTree(f,*(pineV[i]));
  }

  for (int i = 0; i < birchV.size(); i++){
    InsertHwTree(f,*(birchV[i]));
  }
  METER d = 0;
  AccumulateDown<Tree<MyCfTreeSegment,MyCfBud> >(f,d,
						 SampleDiameterGrowth<MyCfTreeSegment, MyCfBud>());
  KGC fm = 0.0;
  AccumulateDown<Tree<MyCfTreeSegment,MyCfBud> >(f,fm,SubtractFoliage<KGC>(0.06),
						 SampleFoliageMass<MyCfTreeSegment, MyCfBud>(0.200));
  d = 0.0;
  AccumulateDown<Tree<MyHwTreeSegment,MyHwBud> >(f,d,
						 SampleDiameterGrowth<MyHwTreeSegment, MyHwBud>());

  Initialize3DForest<Tree<MyCfTreeSegment, MyCfBud> >(f);
  VisualizeForest<Tree<MyHwTreeSegment, MyHwBud> >(f);
}
