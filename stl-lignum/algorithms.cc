
#include <Lignum.h>
#include <MyTreeSegment.h>
#include <MyBud.h>
#include <Shading.h>
#include <Collision.h>

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
  Tree<MyHwTreeSegment,MyBud> hw_tree(Point(0,0,0),
				      PositionVector(0,0,1.0));
  //by default the tree is from namespace Lignum
  Tree<MyCfTreeSegment,MyBud> cf_tree(Point(0,0,0),
				      PositionVector(0,0,1.0));

  FTree<FirmamentWithMask,MyCfTreeSegment,MyBud> ftree1(Point(0,0,0),
							PositionVector(0,0,1.0));
  FTree<Firmament,MyCfTreeSegment,MyBud> ftree2(Point(0,0,0),
						PositionVector(0,0,1.0));
  string clarg,empty;

  clarg = ParseCommandLine(argc,argv,"-file");
  if (clarg != empty)
    InitializeTree(hw_tree,clarg);
 
 
   
  //Example 1.
  //create a tree with a structure [TS,[[B],[B]],B]
  //i.e, [TS,BP,B] which expands to [TS,[A,A],B] and to [TS,[[B],[B]],B]
  //A= Axis<MyHwTreeSegment,MyBud>, BP = BranchingPoint<MyHwTreeSegment,MyBud>, 
  //TS = TreeSegment<MyHwTreeSegment>,MyBud<MyHwTreeSegment,MyBud> and 
  //B = Bud<MyHwTreeSegment,MyBud>
  Axis<MyHwTreeSegment,MyBud>& axis = GetAxis(hw_tree);
  //create the first tree segment
  MyHwTreeSegment *ts = 
    new  MyHwTreeSegment(Point(0,0,0),PositionVector(0,0,1.0),
			 0,1,0.5,0.2,&hw_tree);
  //create the branching point
  BranchingPoint<MyHwTreeSegment,MyBud> *bp = 
    new BranchingPoint<MyHwTreeSegment,MyBud>(Point(0,0,0),
				      PositionVector(0,0,1.0),&hw_tree);
  //create the terminating bud
  Bud<MyHwTreeSegment,MyBud> *bud = new  Bud<MyHwTreeSegment,MyBud>(Point(0,0,0),
						    PositionVector(0,0,1.0),
						    0,
						    &hw_tree);
  //create a branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new Bud<MyHwTreeSegment,MyBud>(Point(0,0,0),
						  PositionVector(0,0,1.0),
						  0,
						  &hw_tree));
  //create another branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new Bud<MyHwTreeSegment,MyBud>(Point(0,0,0),
						  PositionVector(0,0,1.0),
						  0,
						  &hw_tree));


  //The tree will now look as  [TS,[[B],[B]],B]
  InsertTreeCompartment(axis,ts);
  InsertTreeCompartment(axis,bp);
  InsertTreeCompartment(axis,bud);

  //traverse the tree and print out  the datatypes of tree compartments
  //using the ForEach algorithm

  cout << "Testing ForEach algorithm with DisplayType" << endl;
  ForEach(hw_tree,DisplayType<MyHwTreeSegment,MyBud>());
  cout << endl;

  cout << "Example 1: Tree<MyHwTreeSegment,MyBud> with TreeSegment<MyHwTreeSegment,MyBud>" << endl;
  cout << "Testing ForEach algorithm with DisplayType2" << endl;
  
  
  ForEach(hw_tree,DisplayType2<MyHwTreeSegment,MyBud>());
  cout << endl;
  int i = 0;

  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing Accumulate algorithm with CountCompartments" << endl;
  int cc = Accumulate(hw_tree,i,CountCompartments<MyHwTreeSegment,MyBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;

  cout << endl;
  i = 0;

  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with "
       << "CountCompartmentsReverse" << endl; 
  cc = AccumulateDown(hw_tree,i,CountCompartmentsReverse<MyHwTreeSegment,MyBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i=0;
  cc= 0;
  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with CountCompartments" << endl;
  cc = AccumulateDown(hw_tree,i,CountCompartments<MyHwTreeSegment,MyBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i = 0;
  //traverse the tree, echo  and count the number branches
  cout << "Testing PropagateUp algorithm with MyExampleSignal" << endl;
  PropagateUp(hw_tree,i,MyExampleSignal<MyHwTreeSegment,MyBud>());


  

  //Example 2.
  //create a tree with a structure [TS,[[B],[B]],B]
  //i.e, [TS,BP,B] which expands to [TS,[A,A],B] and to [TS,[[B],[B]],B]
  //A= Axis<MyCfTreeSegment,MyBud>, BP = BranchingPoint<MyCfTreeSegment,MyBud>, 
  //TS = MyCfTreeSegment and B = Bud<MyCfBud,MyBud> 
  Axis<MyCfTreeSegment,MyBud>& cf_axis = GetAxis(cf_tree);
  //create the first tree segment
  MyCfTreeSegment *cf_ts = 
    new MyCfTreeSegment(Point(0,0,0),PositionVector(0,0,1.0),
			0,1,0.5,0.2,&cf_tree);
  SetValue(*cf_ts, Qabs, 100.0);                //this segment has absorbed radiation
  //create the branching point
  BranchingPoint<MyCfTreeSegment,MyBud> *cf_bp = 
    new BranchingPoint<MyCfTreeSegment,MyBud>(Point(0,0,0),
				      PositionVector(0,0,1.0),&cf_tree);
  //create the terminating bud
  Bud<MyCfTreeSegment,MyBud> *cf_bud = new  Bud<MyCfTreeSegment,MyBud>(Point(0,0,0),
						    PositionVector(0,0,1.0),
						    0,
						    &cf_tree);
  //create a branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*cf_bp,new Bud<MyCfTreeSegment,MyBud>(Point(0,0,0),
						  PositionVector(0,0,1.0),
						  0,
						  &cf_tree));
  //create another branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*cf_bp,new Bud<MyCfTreeSegment,MyBud>(Point(0,0,0),
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
  cout << "Example 2: Tree<MyCfTreeSegment,MyBud> with MyCfTreeSegment" << endl;
  cout << "Testing ForEach algorithm with DisplayType2" << endl;
  cout << "Testing ForEach algorithm with DisplayType2" << endl;

  
  ForEach(cf_tree,DisplayType2<MyCfTreeSegment,MyBud>());

  cout << endl;
  i = 0;

  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing Accumulate algorithm with CountCompartments" << endl;
  cc = Accumulate(cf_tree,i,CountCompartments<MyCfTreeSegment,MyBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;

  cout << endl;
  i = 0;

  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with "
       << "CountCompartmentsReverse" << endl; 
  cc = AccumulateDown(cf_tree,i,CountCompartmentsReverse<MyCfTreeSegment,MyBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i=0;
  cc= 0;
  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with CountCompartments" << endl;
  cc = AccumulateDown(cf_tree,i,CountCompartments<MyCfTreeSegment,MyBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i = 0;
  //traverse the tree, echo  and count the number branches
  cout << "Testing PropagateUp algorithm with MyExampleSignal" << endl;
  PropagateUp(cf_tree,i,MyExampleSignal<MyCfTreeSegment,MyBud>());

  cout << endl;
  //traverse the tree and display the structure
  cout << "Testing function DisplayStructure" << endl;
  DisplayStructure(cf_tree);
  cout << endl;

  //traverse the tree and display the structure
  cout << "Testing PropagateUp algorithm with DisplayStructureFunctor" << endl;
  DisplayStructureData id;
  PropagateUp(cf_tree,id,DisplayStructureFunctor<MyCfTreeSegment,MyBud>());
  cout << endl;

//Radiation
  EvaluateRadiationForTree(hw_tree, WrapRadiationEvaluations<
		    EvaluateRadiationForHwTreeSegment<MyHwTreeSegment,MyBud>,
		    MyHwTreeSegment,MyBud>() );
  //	    MyHwTreeSegment,MyBud>("Radiationextinction.txt") );

  EvaluateRadiationForTree(cf_tree,WrapRadiationEvaluations<
		    EvaluateRadiationForCfTreeSegment<MyCfTreeSegment,MyBud>,
		    MyCfTreeSegment,MyBud>("Radiationextinction.txt") );


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


   //Collision

   ForEach(cf_tree, EvaluateCollisionForAllBuds<MyCfTreeSegment,MyBud>());

   ForEach(hw_tree, EvaluateCollisionForAllBuds<MyHwTreeSegment,MyBud>
	   (PI_VALUE, 0.1));
}


