#include "stdafx.h"
#include <Lignum.h>
#include <MyTreeSegment.h>
#include <MyBud.h>
#include <Shading.h>
#include <Collision.h>


using namespace std;
using namespace Lignum;
using namespace sky;

#ifndef _MSC_VER

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


/// \example{lineno} algorithms.cc
int main(int argc, char *argv[])
{
  
  /// Using explicitely Tree from  namespace Lignum;
  Tree<MyHwTreeSegment,MyHwBud> hw_tree(Point(0,0,0),
					PositionVector(0,0,1.0));
  /// By default the tree is from namespace Lignum
  Tree<MyCfTreeSegment,MyCfBud> cf_tree(Point(0,0,0),
					PositionVector(0,0,1.0));
  cout << "Created Hw and Cf trees" << endl;
  FTree<FirmamentWithMask,MyCfTreeSegment,MyCfBud> ftree1(Point(0,0,0),
							  PositionVector(0,0,1.0));
  FTree<Firmament,MyCfTreeSegment,MyCfBud> ftree2(Point(0,0,0),
						  PositionVector(0,0,1.0));

 
   
  string clarg,empty;

  cout << "Parse Command Line" << endl;
  clarg = ParseCommandLine(argc,argv,"-configure");
  if (clarg != empty){
    InitializeTree<MyHwTreeSegment,MyHwBud> init_hw(clarg,VERBOSE);
    InitializeTree<MyCfTreeSegment,MyCfBud> init_cf(clarg,VERBOSE);
    init_hw.initialize(hw_tree);
    init_cf.initialize(cf_tree); 
  }
  /// This is how to access functions, note the ParametricCurve is
  /// returned as const
  const ParametricCurve& pc = GetFunction(hw_tree,LGMFM);
  /// Example 1. HwTree 
  /// create a tree with a structure [TS,[[B],[B]],B]
  /// i.e, [TS,BP,B] which expands to [TS,[A,A],B] and to [TS,[[B],[B]],B]
  /// A= Axis<MyHwTreeSegment,MyBud>, BP = BranchingPoint<MyHwTreeSegment,MyBud>, 
  /// TS = TreeSegment<MyHwTreeSegment>,MyBud<MyHwTreeSegment,MyBud> and 
  /// B = Bud<MyHwTreeSegment,MyBud>
  Axis<MyHwTreeSegment,MyHwBud>& axis = GetAxis(hw_tree);
  //create the first tree segment
  MyHwTreeSegment *ts = 
    new  MyHwTreeSegment(Point(0,0,0),PositionVector(0,0,1.0),
			 0,1,0.5,0.2,&hw_tree);
  /// Create the branching point
  BranchingPoint<MyHwTreeSegment,MyHwBud> *bp = 
    new BranchingPoint<MyHwTreeSegment,MyHwBud>(Point(0,0,0),
				      PositionVector(0,0,1.0),&hw_tree);
  /// Create the terminating bud
  Bud<MyHwTreeSegment,MyHwBud> *bud = new  MyHwBud(Point(0,0,0),
						   PositionVector(0,0,1.0),
						   0,
						   &hw_tree);
  /// Create a branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new MyHwBud(Point(0,0,0),
				       PositionVector(0,0,1.0),
				       0,
				       &hw_tree));
  /// Create another branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new MyHwBud(Point(0,0,0),
				       PositionVector(0,0,1.0),
				       0,
				       &hw_tree));


  /// The tree will now look as  [TS,[[B],[B]],B]
  InsertTreeCompartment(axis,ts);
  InsertTreeCompartment(axis,bp);
  InsertTreeCompartment(axis,bud);

  /// ForEach: traverse the tree and print out  the datatypes of tree compartments
  /// using the ForEach algorithm
  cout << "Testing ForEach algorithm with DisplayType" << endl;
  ForEach(hw_tree,DisplayType<MyHwTreeSegment,MyHwBud>());
  cout << endl;
  cout << "Tree<MyHwTreeSegment,MyBud> with TreeSegment<MyHwTreeSegment,MyBud>" << endl;
  cout << "Testing ForEach algorithm with DisplayType2" << endl;
  ForEach(hw_tree,DisplayType2<MyHwTreeSegment,MyHwBud>());
  cout << endl;
  int i = 0;

  /// Accumulate: traverse the tree, echo  and count the number of tree compartments
  cout << "Testing Accumulate algorithm with CountCompartments" << endl;
  int cc = Accumulate(hw_tree,i,CountCompartments<MyHwTreeSegment,MyHwBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;

  cout << endl;
  i = 0;

  /// AccumulateDown: traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with "
       << "CountCompartmentsReverse" << endl; 
  cc = AccumulateDown(hw_tree,i,CountCompartmentsReverse<MyHwTreeSegment,MyHwBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i=0;
  cc= 0;
  /// AccumulateDown: traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with CountCompartments" << endl;
  cc = AccumulateDown(hw_tree,i,CountCompartments<MyHwTreeSegment,MyHwBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i = 0;
  /// PropagetUp: traverse the tree, echo  and count the number branches
  cout << "Testing PropagateUp algorithm with MyExampleSignal" << endl;
  PropagateUp(hw_tree,i,MyExampleSignal<MyHwTreeSegment,MyHwBud>());

  /// Example 2. CfTree
  /// Create a tree with a structure [TS,[[B],[B]],B]
  /// i.e, [TS,BP,B] which expands to [TS,[A,A],B] and to [TS,[[B],[B]],B]
  /// A= Axis<MyCfTreeSegment,MyBud>, BP = BranchingPoint<MyCfTreeSegment,MyBud>, 
  /// TS = MyCfTreeSegment and B = Bud<MyCfBud,MyBud> 
  Axis<MyCfTreeSegment,MyCfBud>& cf_axis = GetAxis(cf_tree);
  /// Create the first tree segment
  MyCfTreeSegment *cf_ts = 
    new MyCfTreeSegment(Point(0,0,0),PositionVector(0,0,1.0),
			0,1,0.5,0.2,&cf_tree);
  SetValue(*cf_ts, LGAQabs, 100.0);                //this segment has absorbed radiation
  /// Create the branching point
  BranchingPoint<MyCfTreeSegment,MyCfBud> *cf_bp = 
    new BranchingPoint<MyCfTreeSegment,MyCfBud>(Point(0,0,0),
						PositionVector(0,0,1.0),&cf_tree);
  /// Create the terminating bud
  Bud<MyCfTreeSegment,MyCfBud> *cf_bud = new  MyCfBud(Point(0,0,0),
						      PositionVector(0,0,1.0),
						      0,
						      &cf_tree);
  /// Create a branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*cf_bp,new MyCfBud(Point(0,0,0),
					  PositionVector(0,0,1.0),
					  0,
					  &cf_tree));
  /// Create another branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*cf_bp,new MyCfBud(Point(0,0,0),
					  PositionVector(0,0,1.0),
					  0,
					  &cf_tree));


  /// The tree will now look as  [TS,[[B],[B]],B]
  InsertTreeCompartment(cf_axis,cf_ts);
  InsertTreeCompartment(cf_axis,cf_bp);
  InsertTreeCompartment(cf_axis,cf_bud);

  /// ForEach: Traverse the tree and print out  the datatypes of tree compartments
  /// using the ForEach algorithm
  cout << endl;
  cout << "Example 2: Tree<MyCfTreeSegment,MyCfBud> with MyCfTreeSegment" << endl;
  cout << "Testing ForEach algorithm with DisplayType2" << endl;
  cout << "Testing ForEach algorithm with DisplayType2" << endl;
  ForEach(cf_tree,DisplayType2<MyCfTreeSegment,MyCfBud>());

  cout << endl;
  i = 0;

  ///Accumlate: traverse the tree, echo  and count the number of tree compartments
  cout << "Testing Accumulate algorithm with CountCompartments" << endl;
  cc = Accumulate(cf_tree,i,CountCompartments<MyCfTreeSegment,MyCfBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;

  cout << endl;
  i = 0;

  /// AccumulateDown: traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with "
       << "CountCompartmentsReverse" << endl; 
  cc = AccumulateDown(cf_tree,i,CountCompartmentsReverse<MyCfTreeSegment,MyCfBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i=0;
  cc= 0;
  /// AccumukateDown: traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm with CountCompartments" << endl;
  cc = AccumulateDown(cf_tree,i,CountCompartments<MyCfTreeSegment,MyCfBud>());
  cout << "Number of Compartments: " << endl;
  cout << "Return value: " << cc << " Modified identity: " << i << endl;
  cout << endl;

  i = 0;
  /// PropagateUp: traverse the tree, echo  and count the number branches
  cout << "Testing PropagateUp algorithm with MyExampleSignal" << endl;
  PropagateUp(cf_tree,i,MyExampleSignal<MyCfTreeSegment,MyCfBud>());

  cout << endl;
  //traverse the tree and display the structure
  cout << "Testing function DisplayStructure" << endl;
  DisplayStructure(cf_tree);
  cout << endl;

  ///PropagateUp: traverse the tree and display the structure
  cout << "Testing PropagateUp algorithm with DisplayStructureFunctor" << endl;
  DisplayStructureData id;
  PropagateUp(cf_tree,id,DisplayStructureFunctor<MyCfTreeSegment,MyCfBud>());
  cout << endl;

  //Radiation
  EvaluateRadiationForTree(hw_tree, WrapRadiationEvaluations<
			   EvaluateRadiationForHwTreeSegment<MyHwTreeSegment,MyHwBud>,
			   MyHwTreeSegment,MyHwBud>() );
  //	    MyHwTreeSegment,MyHwBud>("Radiationextinction.txt") );

  //Forget wrappers, this is for coniferous segment
  //Constant extinction for demo
  ParametricCurve K(0.2);
  //This computes Qin and Qabs for one segment (pairwise comparison)
  EvaluateRadiationForCfTreeSegment<MyCfTreeSegment,MyCfBud> R(K);
  //For all segments simply call ForEach
  //ForEach(cf_tree,R);
  //Photosynthesis
  SetValue(cf_tree, LGPpr, 1.0);      //Set the photosynthesis parameter
  SetValue(hw_tree, LGPpr, 1.0);
  //hw_tree.photosynthesis();
  //    cout << endl << "Photosynthesis (should be = ?): "
  // 	 << GetValue(hw_tree, TreeP) << endl;
  ForEach(hw_tree, TreePhotosynthesis<MyHwTreeSegment,MyHwBud>());
  LGMdouble sumP = 0.0;
  sumP = Accumulate(hw_tree,sumP,SumTreePhotosynthesis<MyHwTreeSegment,MyHwBud>());
  cout << "P for HwTree is: " << sumP << endl; 
  
  /// ForEach:  cf_tree.photosynthesis();
  ForEach(cf_tree, TreePhotosynthesis<MyCfTreeSegment,MyCfBud>());
  sumP = 0.0;
  sumP = Accumulate(cf_tree,sumP,SumTreePhotosynthesis<MyCfTreeSegment,MyCfBud>());
  cout << "P for CfTree is: " << sumP 
       << " (should be = 1*100): " << endl;
  /// ForEach: cf_tree.respiration();
  ForEach(cf_tree,TreeRespiration<MyCfTreeSegment,MyCfBud>());
  LGMdouble sumM = 0.0;
  sumM = Accumulate(cf_tree,sumM,SumTreeRespiration<MyCfTreeSegment,MyCfBud>());
  sumM += GetValue(cf_tree,LGPmr)*GetValue(cf_tree,TreeWr);
  cout << "M for CfTree is: " << sumM << endl; 
  //hw_tree.respiration();
  cout << endl << "hw_tree Respiration (): "
       << GetValue(cf_tree, TreeM) << endl;


   /// ForEach: Collision detection
   ForEach(cf_tree, EvaluateCollisionForAllBuds<MyCfTreeSegment,MyCfBud>());
   ForEach(hw_tree, EvaluateCollisionForAllBuds<MyHwTreeSegment,MyHwBud>
	   (PI_VALUE, 0.1));


   /// AccumulateDown: delete branches 
   LGMdouble foliage = 0;
   cout << "Testing DeleteDeadBranches CfTree" << endl;
   AccumulateDown(cf_tree,foliage,DeleteDeadBranches<MyCfTreeSegment,MyCfBud>());
   cout << "Testing DeleteDeadBranches CfTree done" << endl;
   cout << "Testing DeleteDeadBranches HwTree" << endl;
   AccumulateDown(hw_tree,foliage,DeleteDeadBranches<MyHwTreeSegment,MyHwBud>());
   cout << "Testing DeleteDeadBranches HwTree done" << endl;

   return 0;
   
}
#endif

