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
  Pine::LSystem<MyCfTreeSegment,MyCfBud> pl2;
  Pine::LSystem<MyCfTreeSegment,MyCfBud> pl3;
  Pine::LSystem<MyCfTreeSegment,MyCfBud> pl4;
  Pine::LSystem<MyCfTreeSegment,MyCfBud> pl5;

  Tree<MyCfTreeSegment,MyCfBud> pine1(Point(0,3,0),
				      PositionVector(0,0,1.0));
  Tree<MyCfTreeSegment,MyCfBud> pine2(Point(0,2.5,0),
				      PositionVector(0,0,1.0));
  Tree<MyCfTreeSegment,MyCfBud> pine3(Point(0,1.3,0),
				      PositionVector(0,0,1.0));
  Tree<MyCfTreeSegment,MyCfBud> pine4(Point(0,-0.5,0),
				      PositionVector(0,0,1.0));
  Tree<MyCfTreeSegment,MyCfBud> pine5(Point(0,-2.8,0),
				      PositionVector(0,0,1.0));
  Tree<MyHwTreeSegment,MyHwBud> birch(Point(0,-4,0),
				      PositionVector(0,0,1.0));
  
  //Scots  pines. Demonstrate that several individuals  of the same
  //species can be simulated.
  //Expand axioms.
  pl1.start();
  pl1.lstringToLignum(pine1);
  //Naturally, one can use  other termination conditions than just the
  //derivation length.
  for (int i=0; i < 1; i++)
  {
    cout << "Step: " << i << endl;
    //Update L-strings, no interchange  of information.
    pl1.lignumToLstring(pine1);
    //Structural development for the trees.
    pl1.derive();
    //Update pine structures, no interchange  of information.
    pl1.lstringToLignum(pine1);
  }
  //Clean up.
  pl1.end();  

  pl2.start();
  pl2.lstringToLignum(pine2);
  //Naturally, one can use  other termination conditions than just the
  //derivation length.
  for (int i=0; i < 2; i++)
  {
    cout << "Step: " << i << endl;
    //Update L-strings, no interchange  of information.
    pl2.lignumToLstring(pine2);
    //Structural development for the trees.
    pl2.derive();
    //Update pine structures, no interchange  of information.
    pl2.lstringToLignum(pine2);
  }
  //Clean up.
  pl2.end();  
 
  pl3.start();
  pl3.lstringToLignum(pine3);
  //Naturally, one can use  other termination conditions than just the
  //derivation length.
  for (int i=0; i < 3; i++)
  {
    cout << "Step: " << i << endl;
    //Update L-strings, no interchange  of information.
    pl3.lignumToLstring(pine3);
    //Structural development for the trees.
    pl3.derive();
    //Update pine structures, no interchange  of information.
    pl3.lstringToLignum(pine3);
  }
  //Clean up.
  pl3.end();  
  
  pl4.start();
  pl4.lstringToLignum(pine4);
  //Naturally, one can use  other termination conditions than just the
  //derivation length.
  for (int i=0; i < 4; i++)
  {
    cout << "Step: " << i << endl;
    //Update L-strings, no interchange  of information.
    pl4.lignumToLstring(pine4);
    //Structural development for the trees.
    pl4.derive();
    //Update pine structures, no interchange  of information.
    pl4.lstringToLignum(pine4);
  }
  //Clean up.
  pl4.end();  
  
  pl5.start();
  pl5.lstringToLignum(pine5);
  //Naturally, one can use  other termination conditions than just the
  //derivation length.
  for (int i=0; i < 5; i++)
  {
    cout << "Step: " << i << endl;
    //Update L-strings, no interchange  of information.
    pl5.lignumToLstring(pine5);
    //Structural development for the trees.
    pl5.derive();
    //Update pine structures, no interchange  of information.
    pl5.lstringToLignum(pine5);
  }
  //Clean up.
  pl5.end();

  KGC fm = 0.0;
  AccumulateDown(pine5,fm,SubtractFoliage<KGC>(0.3),
		 SampleFoliageMass<MyCfTreeSegment,MyCfBud>(1.00));
  //Visualize LIGNUM
  Forest f;
  InsertCfTree(f,pine1);
  InsertCfTree(f,pine2);
  InsertCfTree(f,pine3);
  InsertCfTree(f,pine4);
  InsertCfTree(f,pine5);
  Initialize3DForest<Tree<MyCfTreeSegment, MyCfBud> >(f);
  VisualizeForest<Tree<MyHwTreeSegment, MyHwBud> >(f);
}
