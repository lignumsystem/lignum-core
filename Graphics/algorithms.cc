
#include <MyTreeSegment.h>
#include <Lignum.h>
#include <MyBud.h>
#include <Shading.h>
#include <OpenGLUnix.h>

using namespace std;
using namespace Lignum;
using namespace sky;

string ParseCommandLine(int argc, char *argv[],const string& flag)
{
  int i = 1;
  string clarg;

  //loop through command line options, argc - 1 checks possible missing last argument
  //to command line option does not cause core dump
  while (i < argc - 1){ 
    if (string(argv[i]) == flag){
      clarg = argv[++i]; //pick the argument to command line option
      break; 
    }
    else
      i++;   //jump to next 
    i++;     //command line option
  }
  return clarg;
}

int main(int argc, char *argv[])
{
  
  //using explicitely Tree from  namespace Lignum;
  Tree<MyHwTreeSegment,MyHwBud> hw_tree(Point(0,0,0),
				      PositionVector(0,0,1.0));
  //by default the tree is from namespace Lignum
  Tree<MyCfTreeSegment,MyCfBud> cf_tree(Point(0,0,0),
				      PositionVector(0,0,1.0));

  FTree<FirmamentWithMask,MyCfTreeSegment,MyCfBud> ftree1(Point(0,0,0),
							PositionVector(0,0,1.0));
  FTree<Firmament,MyCfTreeSegment,MyCfBud> ftree2(Point(0,0,0),
						PositionVector(0,0,1.0));
  string clarg,empty;

  clarg = ParseCommandLine(argc,argv,"-file");
  /*  
if (clarg != empty)
    InitializeTree(hw_tree,clarg);
  */
 
   
  //Example 1.
  //create a tree with a structure [TS,[[B],[B]],B]
  //i.e, [TS,BP,B] which expands to [TS,[A,A],B] and to [TS,[[B],[B]],B]
  //A= Axis<MyHwTreeSegment,MyHwBud>, BP = BranchingPoint<MyHwTreeSegment,MyHwBud>, 
  //TS = TreeSegment<MyHwTreeSegment>,MyBud<MyHwTreeSegment,MyHwBud> and 
  //B = Bud<MyHwTreeSegment,MyHwBud>
  Axis<MyHwTreeSegment,MyHwBud>& axis = GetAxis(hw_tree);
  //create the first tree segment
  MyHwTreeSegment *ts = 
    new  MyHwTreeSegment(Point(0,0,0),PositionVector(0,0,1.0),
			 0,1,0.5,0.2,&hw_tree);
  //create the branching point
  BranchingPoint<MyHwTreeSegment,MyHwBud> *bp = 
    new BranchingPoint<MyHwTreeSegment,MyHwBud>(Point(0,0,0),
				      PositionVector(0,0,1.0),&hw_tree);
  //create the terminating bud
  Bud<MyHwTreeSegment,MyHwBud> *bud = new  Bud<MyHwTreeSegment,MyHwBud>(Point(0,0,1),
						    PositionVector(-1,1,1.0),
						    0,
						    &hw_tree);
  //create a branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new Bud<MyHwTreeSegment,MyHwBud>(Point(0,0,1.1),
						  PositionVector(0,1,1.0),
						  0,
						  &hw_tree));
  //create another branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new Bud<MyHwTreeSegment,MyHwBud>(Point(0,0,1.05),
						  PositionVector(0,2,1.0),
						  0,
						  &hw_tree));


  //The tree will now look as  [TS,[[B],[B]],B]
  InsertTreeCompartment(axis,ts);
  InsertTreeCompartment(axis,bp);
  InsertTreeCompartment(axis,bud);

  //traverse the tree and print out  the datatypes of tree compartments
  //using the ForEach algorithm

  cout << "Testing ForEach algorithm with DisplayType" << endl;
  ForEach(hw_tree,DisplayType<MyHwTreeSegment,MyHwBud>());
  cout << endl;

  cout << "Example 1: Tree<MyHwTreeSegment,MyHwBud> with TreeSegment<MyHwTreeSegment,MyHwBud>" << endl;
  cout << "Testing ForEach algorithm with DisplayType2" << endl;
  
  
  ForEach(hw_tree,DisplayType2<MyHwTreeSegment,MyHwBud>());
  cout << endl;
  int i = 0;

  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing Accumulate algorithm with CountCompartments" << endl;
  int cc = Accumulate(hw_tree,i,CountCompartments<MyHwTreeSegment,MyHwBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;

  cout << endl;
  i = 0;

  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with "
       << "CountCompartmentsReverse" << endl; 
  cc = AccumulateDown(hw_tree,i,CountCompartmentsReverse<MyHwTreeSegment,MyHwBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i=0;
  cc= 0;
  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with CountCompartments" << endl;
  cc = AccumulateDown(hw_tree,i,CountCompartments<MyHwTreeSegment,MyHwBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i = 0;
  //traverse the tree, echo  and count the number branches
  cout << "Testing PropagateUp algorithm with MyExampleSignal" << endl;
  PropagateUp(hw_tree,i,MyExampleSignal<MyHwTreeSegment,MyHwBud>());


  

  //Example 2.
  //create a tree with a structure [TS,[[B],[B]],B]
  //i.e, [TS,BP,B] which expands to [TS,[A,A],B] and to [TS,[[B],[B]],B]
  //A= Axis<MyCfTreeSegment,MyBud>, BP = BranchingPoint<MyCfTreeSegment,MyBud>, 
  //TS = MyCfTreeSegment and B = Bud<MyCfBud,MyBud> 
  Axis<MyCfTreeSegment,MyCfBud>& cf_axis = GetAxis(cf_tree);
  //create the first tree segment
  MyCfTreeSegment *cf_ts = 
    new MyCfTreeSegment(Point(0,0,0),PositionVector(0,0,1.0),
			0,1,0.1,0.2,&cf_tree);
  SetValue(*cf_ts, Qabs, 100.0);                //this segment has absorbed radiation
  //create the branching point
  BranchingPoint<MyCfTreeSegment,MyCfBud> *cf_bp = 
    new BranchingPoint<MyCfTreeSegment,MyCfBud>(Point(0,0,0),
				      PositionVector(0,0,1.0),&cf_tree);
  //create the terminating bud
  Bud<MyCfTreeSegment,MyCfBud> *cf_bud = new  Bud<MyCfTreeSegment,MyCfBud>(Point(0,0,1.0),
						    PositionVector(0,-1,1.0),
						    0,
						    &cf_tree);
  //create a branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*cf_bp,new Bud<MyCfTreeSegment,MyCfBud>(Point(0,0,1.1),
						  PositionVector(0,1,1.0),
						  0,
						  &cf_tree));
  //create another branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*cf_bp,new Bud<MyCfTreeSegment,MyCfBud>(Point(0,0,1.05),
						  PositionVector(0,0,1.0),
						  0,
						  &cf_tree));


  //The tree will now look as  [TS,[[B],[B]],B]
  InsertTreeCompartment(cf_axis,cf_ts);
  InsertTreeCompartment(cf_axis,cf_bp);
  InsertTreeCompartment(cf_axis,cf_bud);

  //traverse the tree and print out  the datatypes of tree compartments
  //using the ForEach algorithm
  cout << endl;
  cout << "Example 2: Tree<MyCfTreeSegment,MyCfBud> with MyCfTreeSegment" << endl;
  cout << "Testing ForEach algorithm with DisplayType2" << endl;
  cout << "Testing ForEach algorithm with DisplayType2" << endl;

  
  ForEach(cf_tree,DisplayType2<MyCfTreeSegment,MyCfBud>());

  cout << endl;
  i = 0;

  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing Accumulate algorithm with CountCompartments" << endl;
  cc = Accumulate(cf_tree,i,CountCompartments<MyCfTreeSegment,MyCfBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;

  cout << endl;
  i = 0;

  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with "
       << "CountCompartmentsReverse" << endl; 
  cc = AccumulateDown(cf_tree,i,CountCompartmentsReverse<MyCfTreeSegment,MyCfBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i=0;
  cc= 0;
  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with CountCompartments" << endl;
  cc = AccumulateDown(cf_tree,i,CountCompartments<MyCfTreeSegment,MyCfBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i = 0;
  //traverse the tree, echo  and count the number branches
  cout << "Testing PropagateUp algorithm with MyExampleSignal" << endl;
  PropagateUp(cf_tree,i,MyExampleSignal<MyCfTreeSegment,MyCfBud>());

  cout << endl;
  //traverse the tree and display the structure
  cout << "Testing function DisplayStructure" << endl;
  DisplayStructure(cf_tree);
  cout << endl;

  //traverse the tree and display the structure
  cout << "Testing PropagateUp algorithm with DisplayStructureFunctor" << endl;
  DisplayStructureData id;
  PropagateUp(cf_tree,id,DisplayStructureFunctor<MyCfTreeSegment,MyCfBud>());
  cout << endl;

//Radiation
  EvaluateRadiationForTree(hw_tree, WrapRadiationEvaluations<
		    EvaluateRadiationForHwTreeSegment<MyHwTreeSegment,MyHwBud>,
		    MyHwTreeSegment,MyHwBud>() );
  //	    MyHwTreeSegment,MyCfBud>("Radiationextinction.txt") );

  EvaluateRadiationForTree(cf_tree,WrapRadiationEvaluations<
		    EvaluateRadiationForCfTreeSegment<MyCfTreeSegment,MyCfBud>,
		    MyCfTreeSegment,MyCfBud>("Radiationextinction.txt") );


  //Photosynthesis
   SetValue(cf_tree, pr, 1.0);      //Set the photosynthesis parameter
   SetValue(hw_tree, pr, 1.0);
   hw_tree.photosynthesis();
   cout << endl << "Photosynthesis (should be = ?): "
	 << GetValue(hw_tree, P) << endl;
   cf_tree.photosynthesis();
   cout << endl << "Photosynthesis (should be = 1*100): "
	<< GetValue(cf_tree, P) << endl;
   cf_tree.respiration();
   cout << endl << "cf_tree Photosynthesis (): "
	<< GetValue(cf_tree, M) << endl;
   hw_tree.respiration();
   cout << endl << "hw_tree Respiration (): "
	<< GetValue(cf_tree, M) << endl;

   //VisualizeLGMTree(cf_tree);
   Forest f;
   InsertCfTree(f,cf_tree);
   VisualizeForest<Tree<MyCfTreeSegment, MyCfBud> >(f);
}


