#ifndef LTOLIGNUM_H
#define LTOLIGNUM_H

#include <Turtle.h>

#include <string.h>
#include <stack>
using namespace std; 

#include <Lignum.h>

#include <lstring.h>
#include <lstriter.h>


using namespace Lignum;

template <class TS, class BUD>
int L2Lignum(BranchingPoint<TS,BUD>& bp, LstringIterator& iterator, 
	      stack<Turtle>& turtle_stack);

template <class TS, class BUD>
int L2Lignum(Axis<TS,BUD>& axis, LstringIterator& iterator, 
	     stack<Turtle>& turtle_stack);


template <class TS, class BUD>
int L2Lignum(BranchingPoint<TS,BUD>& bp, LstringIterator& iterator, 
	      stack<Turtle>& turtle_stack)
{

  const char* name = iterator.GetCurrentModuleName();
  cout << "BP Module name " << name << endl;

  //Branching point sees "SB" --> new Axis
  if (strcmp(name,"SB") == 0){
    Axis<TS,BUD>* axis = new Axis<TS,BUD>(GetPoint(turtle_stack.top()),
					  GetHeading(turtle_stack.top()),
					  &GetTree(bp));
    InsertAxis(bp,axis);
    //Go to the first symbol of the new axis
    iterator++;
    return L2Lignum(*axis,iterator,turtle_stack);
  }
  //Branching point sees "EB" --> end of Axis
  //Go to next symbol
  else if (strcmp(name,"EB") == 0){
    iterator++;
    return L2Lignum(bp,iterator,turtle_stack);
  }
  //This can only be a symbol  "S" in between "SB" and "EB": "] S ["
  //It means end of branching point, return and let the calling Axis see the symbol S
  else{
    return 0; //end of bp
  }
}
  
template <class TS, class BUD>
int L2Lignum(Axis<TS,BUD>& axis, LstringIterator& iterator, 
	     stack<Turtle>& turtle_stack)
{
  CallerData caller_data;

  if (iterator.AtEnd()){
    return 1; //exit
  }

  const char* name =  iterator.GetCurrentModuleName();
  cout << "Axis module name " << name  << endl; 
  if (strcmp(name,"EB") == 0){
    turtle_stack.pop();
    iterator++;
    return 2; //end of axis
  } 
  //Forward, also create a segment
  else if (strcmp(name,"F") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(iterator.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    TreeSegment<TS,BUD>* ts = new TreeSegment<TS,BUD>(GetPoint(turtle_stack.top()),
						      GetHeading(turtle_stack.top()),
						      0.0,arg1,0.10,0.05,&GetTree(axis));
    InsertTreeCompartment(axis,ts);
    turtle_stack.top().forward(arg1);
    iterator++;
  }
  //Axis sees "SB" --> new Branching point
  //Also push the current status of the turtle to the stack
  //Don't go forward, let the Branching point see the "SB" again
  else if (strcmp(name,"SB") == 0){
    BranchingPoint<TS,BUD>* bp = new BranchingPoint<TS,BUD>(GetPoint(turtle_stack.top()),
							    GetHeading(turtle_stack.top()),
							    &GetTree(axis));
    InsertTreeCompartment(axis,bp);
    turtle_stack.push(turtle_stack.top());
    //Read the branching point
    L2Lignum(*bp,iterator,turtle_stack);
  }
  //Turn
  else if (strcmp(name,"Turn") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(iterator.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().turn(arg1);
    iterator++;
  }
  //Pitch
  else if (strcmp(name,"Pitch") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(iterator.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().pitch(arg1);
    iterator++;
  }
  //Roll
  else if (strcmp(name,"Roll") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(iterator.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().roll(arg1);
    iterator++;
  }
  //Bud
  else if (strcmp(name,"B") == 0){
    Bud<TS,BUD>* bud = new Bud<TS,BUD>(GetPoint(turtle_stack.top()),
				       GetHeading(turtle_stack.top()),
				       0.0,&GetTree(axis));
    InsertTreeCompartment(axis,bud);
    iterator++;
  }
  //Ignore other symbols, go forward in the string
  else{
    iterator++;
  }
  return L2Lignum(axis,iterator,turtle_stack);
}


template <class TS, class BUD>
int L2Lignum(Tree<TS,BUD>& t,const Lstring& s)
{
  stack<Turtle> turtle_stack;
  Turtle turtle;
  LstringIterator literator(s); 
  Axis<TS,BUD>& axis = GetAxis(t);

  turtle_stack.push(turtle);

  return L2Lignum(axis,literator,turtle_stack);
}


#endif
