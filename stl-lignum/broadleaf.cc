#include <stdlib.h>
#include <iostream.h>
#include <list>
#include <algorithm>
#include <list>
#include <MyTreeSegment.h>
#include <MyBud.h>
#include <HwTreeSegment.h>

#include <TreeFunctor.h>
#include <Algorithms.h>

#include <BroadLeaf.h>

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
  Point<> p1(0,0,0);
  Point<> p2(0,0,1);
  PositionVector d(0,0,1);
  Petiole pe(p1,p2);
  Ellipsis e(4.0,6.0);

  Tree<MyHwTreeSegment,MyBud> hw_tree(Point<>(0,0,0),PositionVector(0,0,1.0));
  BroadLeaf bl(1.0,1.0,3.0,4.0,100,pe,d,e);
	       

  CString clarg,empty;


  clarg = ParseCommandLine(argc,argv,"-file");
  if (clarg != empty)
    InitializeTree(hw_tree,clarg);

  cout << GetCenterPoint(bl) << endl;
  cout << GetAttributeValue(bl,Larea) << endl;
}






