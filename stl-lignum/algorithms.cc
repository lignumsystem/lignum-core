#include <stdlib.h>
#include <iostream.h>
#include <list>
#include <algorithm>
#include <list>
#include <MyTreeSegment.h>
#include <MyBud.h>
#include <HwTreeSegment.h>
#include <CfTreeSegment.h>
#include <TreeFunctor.h>
#include <Algorithms.h>

using namespace std;

CString ParseCommandLine(int argc, char *argv[],const CString& flag)
{
  int i = 1;
  CString clarg;

  //loop through command line options, argc - 1 checks possible missing last argument
  //to command line option does not cause core dump
  while (i < argc - 1){ 
    if (CString(argv[i]) == flag){
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
  //MyTreeSegment ts(Point<METER>(0,0,0),PositionVector(0,0,1.0),0,1,1,1,NULL);
  Tree<MyHwTreeSegment,MyBud> hw_tree(Point<METER>(0,0,0),PositionVector(0,0,1.0));
  Tree<MyCfTreeSegment> cf_tree(Point<METER>(0,0,0),PositionVector(0,0,1.0));
  CString clarg,empty;

  clarg = ParseCommandLine(argc,argv,"-file");
  if (clarg != empty)
    InitializeTree(hw_tree,clarg);
  //create a tree with a structure [TS,[[B],[B]],B]
  //i.e, [TS,BP,B] which expands to [TS,[A,A],B] and to [TS,[[B],[B]],B]
  //A= Axis, BP = BranchingPoint, TS = TreeSegment and B = Bud 
  Axis<MyHwTreeSegment,MyBud>& axis = GetAxis(hw_tree);
  //create the first tree segment
  TreeSegment<MyHwTreeSegment,MyBud> *ts = 
    new TreeSegment<MyHwTreeSegment,MyBud>(Point<METER>(0,0,0),PositionVector(0,0,1.0),
				   0,1,0.5,0.2,&hw_tree);
  //create the branching point
  BranchingPoint<MyHwTreeSegment,MyBud> *bp = 
    new BranchingPoint<MyHwTreeSegment,MyBud>(Point<METER>(0,0,0),
				      PositionVector(0,0,1.0),&hw_tree);
  //create the terminating bud
  Bud<MyHwTreeSegment,MyBud> *bud = new  Bud<MyHwTreeSegment,MyBud>(Point<METER>(0,0,0),
						    PositionVector(0,0,1.0),
						    0,
						    &hw_tree);
  //create a branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new Bud<MyHwTreeSegment,MyBud>(Point<METER>(0,0,0),
						  PositionVector(0,0,1.0),
						  0,
						  &hw_tree));
  //create another branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new Bud<MyHwTreeSegment,MyBud>(Point<METER>(0,0,0),
						  PositionVector(0,0,1.0),
						  0,
						  &hw_tree));


  //The tree will now look as  [TS,[[B],[B]],B]
  InsertTreeCompartment(axis,ts);
  InsertTreeCompartment(axis,bp);
  InsertTreeCompartment(axis,bud);

  //traverse the tree and print out  the datatypes of tree compartments
  //using the ForEach algorithm
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
}






