#include <stdlib.h>
#include <iostream.h>
#include <list>
#include <algorithm>
#include <list>
#include <MyTreeSegment.h>
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
  Tree<MyTreeSegment> tree(Point<METER>(0,0,0),PositionVector(0,0,1.0));
  CString clarg,empty;

  clarg = ParseCommandLine(argc,argv,"-file");
  if (clarg != empty)
    InitializeTree(tree,clarg);

  //create a tree with a structure [TS,[[B],[B]],B]
  //i.e, [TS,BP,B] which expands to [TS,[A,A],B] and to [TS,[[B],[B]],B]
  //A= Axis, BP = BranchingPoint, TS = TreeSegment and B = Bud 
  Axis<MyTreeSegment>& axis = GetAxis(tree);
  Axis<MyTreeSegment>* axis2 = new Axis<MyTreeSegment>();
  Axis<MyTreeSegment>* axis3 = new Axis<MyTreeSegment>();


 //create the first tree segment
  TreeSegment<MyTreeSegment> *ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0),PositionVector(0,0,1.0),
				   0,1,0.5,0.2,&tree);
  //create the branching point
  BranchingPoint<MyTreeSegment> *bp = 
    new BranchingPoint<MyTreeSegment>(Point<METER>(0,0,0),
				      PositionVector(0,0,1.0),&tree);
  //create the terminating bud
  Bud<MyTreeSegment> *bud = new  Bud<MyTreeSegment>(Point<METER>(0,0,0),
						    PositionVector(0,0,1.0),
						    0,
						    &tree);
  //create a branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new Bud<MyTreeSegment>(Point<METER>(0,0,0),
						  PositionVector(0,0,1.0),
						  0,
						  &tree));
  //create another branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new Bud<MyTreeSegment>(Point<METER>(0,0,0),
						  PositionVector(0,0,1.0),
						  0,
						  &tree));


  TreeSegment<MyTreeSegment> *ts2 = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.3),PositionVector(0,0,1.0),
				   0, 1, 0.5, 0.2,&tree);
  //The tree will now look as  [TS,[[B],[B]],B]
  InsertTreeCompartment(axis,ts);
  InsertTreeCompartment(axis,bp);
  InsertTreeCompartment(axis,ts2);
  InsertTreeCompartment(axis,bud);

  /*
  InsertTreeCompartment(*axis2, ts);

  InsertTreeCompartment(*axis2,bud);


  ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.2),PositionVector(0,0,1.0),
  				   0,1,0.5,0.2,&tree);
  
  InsertTreeCompartment(*axis3, ts);
  
  ts =   new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.4),PositionVector(0,0,1.0),
					0,1,0.5,0.2,&tree);
  InsertTreeCompartment(*axis3, ts);
  */
  char aa = 'a';

  while (aa != 'q')
    { 
      //for (int i=0; i<2; i++)
	tree.UpdateWaterFlow(180.4);
      cout << endl << endl << endl;
      cin >> aa;
    }
  

  /*

  //traverse the tree and print out  the datatypes of tree compartments
  //using the ForEach algorithm
  cout << "Testing ForEach algorithm" << endl;
  ForEach(tree,DisplayType2<MyTreeSegment>());

  cout << endl;
  int i;

  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing Accumulate algorithm" << endl;
  Accumulate(tree,i,CountCompartments<MyTreeSegment>());
  cout << "Number of Compartments: " << i << endl;

  cout << endl;
  i = 0;

  //traverse the tree, echo  and count the number of tree compartments
  cout << "Testing AccumulateDown algorithm" << endl;
  AccumulateDown(tree,i,CountCompartmentsReverse<MyTreeSegment>());
  cout << "Number of Compartments: " << i << endl;

  cout << endl;
  i = 0;
  //traverse the tree, echo  and count the number branches
  cout << "Testing PropagateUp algorithm" << endl;
  PropagateUp(tree,i,MyExampleSignal<MyTreeSegment>());
  */
}






