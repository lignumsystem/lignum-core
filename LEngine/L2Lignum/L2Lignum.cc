#include <string.h>
#include <stack> 
#include <Lignum.h>
#include <Turtle.h>
#include <lstring.h>
#include <lstringiter.h>

using namespace std;

template <class TS, class BUD>
void L2Lignum(BranchingPoint<TS,BUD>& bp, LstringIterator& iterator, 
	      stack<Turtle>& turtle_stack)
{
  const char* name = iterator.GetCurrentModuleName();

  //Branching point sees "SB" --> new Axis
  if (strcmp(name,"SB") == 0){
    Axis<TS,BUD>* axis = new Axis<TS,BUD>(GetPoint(turtle_stack.top()),
					  GetHeading(turtle_stack.top()),
					  &GetTree(bp));
    InsertAxis(bp,axis);
    //Go to the first symbol of the new axis
    L2Lignum(*axis,iterator++,turtle_stack);
  }
  //Branching point sees "EB" --> end of Axis
  //Go to next symbol
  else if (strcmp(name,"EB") == 0){
    L2Lignum(bp,iterator++,turtle_stack);
  }
  //This can only be a symbol  "S" in between "SB" and "EB": "] S ["
  //It means end of branching point, return and let the Axis see the symbol S
  else return;
}
  
template <class TS, class BUD>
void L2Lignum(Axis<TS,BUD>& axis, LstringIterator& iterator, 
	      stack<Turtle>& turtle_stack)
{
  const char* name = NULL;

  if (iterator.AtEnd())
    return;
  
  name = iterator.GetCurrentModuleName(); 
  //End of Axis, return
  //Let the Branching point see the "EB" again
  if (strcmp(name,"EB") == 0){
    turtle_stack.pop();
    return;
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
    //Create the branching point
    L2Lignum(*bp,iterator,turtle_stack);
  }
  //Forward, also create a segment
  else if (strcmp(name,"F") == 0){
    double arg1 = 0.0;
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    TreeSegment<TS,BUD>* ts = new TreeSegment<TS,BUD>(GetPoint(turtle_stack.top()),
						      GetHeading(turtle_stack.top()),
						      0.0,arg1,0.10,0.05,&GetTree(axis));
    InsertTreeCompartment(axis,ts);
    turtle_stack.top().forward(arg1);
  }
  //Turn
  else if (strcmp(name,"Turn") == 0){
    double arg1 = 0.0;
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().turn(arg1);
  }
  //Pitch
  else if (strcmp(name,"Pitch") == 0){
    double arg1 = 0.0;
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().pitch(-arg1);
  }
  //Roll
  else if (strcmp(name,"Roll") == 0){
    double arg1 = 0.0;
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().pitch(-arg1);
  }
  //Bud
  else if (strcmp(name,"B") == 0){
    Bud<TS,BUD>* bud = new Bud<TS,BUD>(GetPoint(turtle_stack.top()),
				       GetHeading(turtle_stack.top()),0.0,,&GetTree(axis));
  }
  //Ignore other symbols, go forward in the string
  return L2Lignum(bp,iterator++,turtle_stack);

}

template <class TS, class BUD>
void L2Lignum(Tree<TS,BUD>& t,const Lstring& s)
{
  stack<Turtle> turtle_stack;
  Turtle turtle;
  LstringIterator iterator(s); 
  Axis<TS,BUD>& a = GetAxis(t);
  turtle_stack.push(turtle);

  L2Lignum(a,iterator,turtle_stack);
}
