#include <stdlib.h>
#include <iostream.h>
#include <list>
#include <MyTreeSegment.h>
#include <TreeFunctor.h>
#include <algorithm>
#include <list>

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

MyTreeSegment::MyTreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
			     const METER l, const METER r, const METER rn, 
			     Tree<MyTreeSegment>* t)
  :TreeSegment<MyTreeSegment>(p,d,go,l,r,rn,t)
{
  cout << "Hello from MyTreeSegment!!!" <<endl;
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
  Axis<MyTreeSegment>* axis2 = new Axis<MyTreeSegment>();
  Axis<MyTreeSegment>* axis3 = new Axis<MyTreeSegment>();
  Axis<MyTreeSegment>& axis = GetAxis(tree);
  //create the first tree segment
  TreeSegment<MyTreeSegment> *ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.2),PositionVector(0,0,1.0),
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


  //The tree will now look as  [TS,[[B],[B]],B]

  InsertAxis(*bp, axis2);
  InsertAxis(*bp, axis3);



  InsertTreeCompartment(axis,ts);
  InsertTreeCompartment(axis,bp);
  InsertTreeCompartment(axis,bud);
  
  ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.3),PositionVector(0,0,1.0),
				   0,1,0.5,0.2,&tree);

  bud = new  Bud<MyTreeSegment>(Point<METER>(0,0,0),
				PositionVector(0,0,1.0),
				0,
				&tree);

  InsertTreeCompartment(*axis2, ts);

 ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.5),PositionVector(0,0,1.0),
				   0,1,0.5,0.2,&tree);

 

  InsertTreeCompartment(*axis2, ts);

  InsertTreeCompartment(*axis2,bud);


  ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.2),PositionVector(0,0,1.0),
  				   0,1,0.5,0.2,&tree);
  
  InsertTreeCompartment(*axis3, ts);
  
  ts =   new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0.4),PositionVector(0,0,1.0),
					0,1,0.5,0.2,&tree);
  InsertTreeCompartment(*axis3, ts);
  
  
  for (int i=0; i<120; i++)
    tree.UpdateWaterFlow(0.4);
 
  
}






