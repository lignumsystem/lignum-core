#include "stdafx.h"
#include <Lignum.h>
#include <MyTreeSegment.h>
#include <MyBud.h>
#include <Shading.h>
#include <Collision.h>
#include <VoxelSpace.h>

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

int main(int argc, char *argv[])
{
  
  //using explicitely Tree from  namespace Lignum;
  Tree<MyHwTreeSegment,MyHwBud> hw_tree(Point(0,0,0),
					PositionVector(0,0,1.0));
  //by default the tree is from namespace Lignum
  Tree<MyCfTreeSegment,MyCfBud> cf_tree(Point(0,0,0),
					PositionVector(0,0,1.0));
  cout << "Created Hw and Cf trees" << endl;
  FTree<FirmamentWithMask,MyCfTreeSegment,MyCfBud> ftree1(Point(0,0,0),
							  PositionVector(0,0,1.0));
  FTree<Firmament,MyCfTreeSegment,MyCfBud> ftree2(Point(0,0,0),
						  PositionVector(0,0,1.0));

  Forest f;

  InsertHwTree(f,hw_tree);
  InsertHwTree(f,hw_tree);
   
  string clarg,empty;

  cout << "Parse Command Line" << endl;
  clarg = ParseCommandLine(argc,argv,"-configure");
  if (clarg != empty){
    InitializeTree<MyHwTreeSegment,MyHwBud> init_hw(clarg,VERBOSE);
    InitializeTree<MyCfTreeSegment,MyCfBud> init_cf(clarg,VERBOSE);
    init_hw.initialize(hw_tree);
    init_cf.initialize(cf_tree); 
  }
  //This is how to access functions, note the ParametricCurve is
  //returned as const
  const ParametricCurve& pc = GetFunction(hw_tree,LGMFM);
  //Example 1.
  //create a tree with a structure [TS,[[B],[B]],B]
  //i.e, [TS,BP,B] which expands to [TS,[A,A],B] and to [TS,[[B],[B]],B]
  //A= Axis<MyHwTreeSegment,MyBud>, BP = BranchingPoint<MyHwTreeSegment,MyBud>, 
  //TS = TreeSegment<MyHwTreeSegment>,MyBud<MyHwTreeSegment,MyBud> and 
  //B = Bud<MyHwTreeSegment,MyBud>
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
  Bud<MyHwTreeSegment,MyHwBud> *bud = new  MyHwBud(Point(0,0,0),
						   PositionVector(0,0,1.0),
						   0,
						   &hw_tree);
  //create a branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new MyHwBud(Point(0,0,0),
				       PositionVector(0,0,1.0),
				       0,
				       &hw_tree));
  //create another branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new MyHwBud(Point(0,0,0),
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
  ForEach(hw_tree,DisplayType<MyHwTreeSegment,MyHwBud>());
  cout << endl;

  cout << "Example 1: Tree<MyHwTreeSegment,MyBud> with TreeSegment<MyHwTreeSegment,MyBud>" << endl;
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
			0,1,0.5,0.2,&cf_tree);
  SetValue(*cf_ts, Qabs, 100.0);                //this segment has absorbed radiation
  //create the branching point
  BranchingPoint<MyCfTreeSegment,MyCfBud> *cf_bp = 
    new BranchingPoint<MyCfTreeSegment,MyCfBud>(Point(0,0,0),
						PositionVector(0,0,1.0),&cf_tree);
  //create the terminating bud
  Bud<MyCfTreeSegment,MyCfBud> *cf_bud = new  MyCfBud(Point(0,0,0),
						      PositionVector(0,0,1.0),
						      0,
						      &cf_tree);
  //create a branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*cf_bp,new MyCfBud(Point(0,0,0),
					  PositionVector(0,0,1.0),
					  0,
					  &cf_tree));
  //create another branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*cf_bp,new MyCfBud(Point(0,0,0),
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
  //	    MyHwTreeSegment,MyHwBud>("Radiationextinction.txt") );

  EvaluateRadiationForTree(cf_tree,WrapRadiationEvaluations<
			   EvaluateRadiationForCfTreeSegment<MyCfTreeSegment,MyCfBud>,
			   MyCfTreeSegment,MyCfBud>("Radiationextinction.txt") );


  //Photosynthesis
   SetValue(cf_tree, pr, 1.0);      //Set the photosynthesis parameter
   SetValue(hw_tree, pr, 1.0);
   hw_tree.photosynthesis();
   cout << endl << "Photosynthesis (should be = ?): "
	 << GetValue(hw_tree, TreeP) << endl;
   cf_tree.photosynthesis();
   cout << endl << "Photosynthesis (should be = 1*100): "
	<< GetValue(cf_tree, TreeP) << endl;
   cf_tree.respiration();
   cout << endl << "cf_tree Photosynthesis (): "
	<< GetValue(cf_tree, TreeM) << endl;
   hw_tree.respiration();
   cout << endl << "hw_tree Respiration (): "
	<< GetValue(cf_tree, TreeM) << endl;


   //Collision

   ForEach(cf_tree, EvaluateCollisionForAllBuds<MyCfTreeSegment,MyCfBud>());

   ForEach(hw_tree, EvaluateCollisionForAllBuds<MyHwTreeSegment,MyHwBud>
	   (PI_VALUE, 0.1));


   //Voxelspace


   Matrix<MyCfTreeSegment, MyCfBud > *matrix;
	
   //konstruktoriin menee mitat jotka ovat suurin x-arvo,y-arvo ja
   //z-arvo. Viimeinen on pikkuneliön sivun mitta

   matrix = new Matrix<MyCfTreeSegment, MyCfBud >(&cf_tree, 0,0,0,0.1);

   int idf = 0;
   cout << "Counting compartments in forest" << endl;
   cout << "First Tree<MyCfTreeSegment,MyCfBud>" << endl;
   Accumulate<Tree<MyCfTreeSegment,MyCfBud> >(f,idf,
					      CountCompartments<MyCfTreeSegment,MyCfBud>());
   cout << "Compartments: " << idf << endl;
   cout << "Then Tree<MyHwTreeSegment,MyHwBud>" << endl;
   Accumulate<Tree<MyHwTreeSegment,MyHwBud> >(f,idf,
					      CountCompartments<MyHwTreeSegment,MyHwBud>());

   ForEach<Tree<MyCfTreeSegment,MyCfBud> >(f,EvaluateCollisionForAllBuds<MyCfTreeSegment,MyCfBud>());
   ForEach<Tree<MyHwTreeSegment,MyHwBud> >(f,EvaluateCollisionForAllBuds<MyHwTreeSegment,MyHwBud>());

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

