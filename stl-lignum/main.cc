#include <stdlib.h>
#include <iostream.h>
#include <list>
#include <algorithm>
#include <list>

#include <Tree.h>

#include <MyTreeSegment.h>
#include <MyBud.h>


using namespace Lignum;

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

  char t;
  cout << "[b] for Big tree" << endl;
  cout << "[x] for special waterfill" << endl;
  cin >> t;

 //create the first tree segment
  TreeSegment<MyTreeSegment> *ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0),PositionVector(0,0,1.0),
				   0, 0.3, 0.3, 0.2,&tree);

  if (t == 'x')
    {
      SetValue(*ts, Wm, GetValue(*ts, Wm)*0.5);
    }
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
  InsertTreeCompartment(axis,ts);
  InsertTreeCompartment(axis,bp);
  TreeSegment<MyTreeSegment> *ts2 = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.3),PositionVector(0,0,1.0),
				   0, 0.3, 0.3, 0.2,&tree);
  if (t == 'x')
    {
      SetValue(*ts2, Wm, GetValue(*ts2, Wm)*1.5);
    }
  InsertTreeCompartment(axis,ts2);

  ts2 = new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.6),PositionVector(0,0,1.0),
				   0, 0.3, 0.3, 0.2,&tree);

 
  InsertTreeCompartment(axis,ts2);
  InsertTreeCompartment(axis,bud);

  
  

  ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.2),PositionVector(0,0,1.0),
  				   0, 0.4, 0.3,0.2,&tree);
  
  InsertTreeCompartment(*axis2, ts);
  ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.2),PositionVector(0,0,1.0),
  				   0, 0.4, 0.3,0.2,&tree);
  
  InsertTreeCompartment(*axis2, ts);
  InsertTreeCompartment(*axis2,bud);
  

  ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.2),PositionVector(0,0,1.0),
  				   0, 0.4, 0.3,0.2,&tree);
  
  InsertTreeCompartment(*axis3, ts);


  
 
  if (t == 'b')
    {
      InsertAxis( *bp, axis2);
      InsertAxis( *bp, axis3);
    }
  
  ts =   new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.4),
					PositionVector(0,0,1.0),
					0, 0.4, 0.3, 0.2, &tree);
  InsertTreeCompartment(*axis3, ts);
  
  int count1 = 0; 
  int count2 = 0;
  char aa = 'a';

  ConnectionMatrix<MyTreeSegment,DefaultBud<MyTreeSegment> > *cm = 
    new ConnectionMatrix<MyTreeSegment,DefaultBud<MyTreeSegment> >(GetAxis(tree)); 
  Accumulate(tree, count1, CountTreeSegments<MyTreeSegment>()); 


  while (aa != 'q')
    {       
      Accumulate(tree, count2, CountTreeSegments<MyTreeSegment>());
      if (count1 != count2)
	{
	  delete cm;
	  cm = new ConnectionMatrix<MyTreeSegment,DefaultBud<MyTreeSegment> >(GetAxis(tree));
	  count1 = count2;
	}
     
      for (int i=0; i<150; i++)     
	tree.UpdateWaterFlow(.25, *cm);
      cm->print();
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






