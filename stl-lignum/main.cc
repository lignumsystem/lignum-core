#include <stdlib.h>
#include <iostream.h>
#include <list>
#include <MyTreeSegment.h>

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
}






