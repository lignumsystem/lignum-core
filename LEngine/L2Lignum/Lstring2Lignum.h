#ifndef LSTRING2LIGNUM_H
#define LSTRING2LIGNUM_H

#include <string.h>
#include <stack>
using namespace std;

#include <lstring.h>
#include <lstriter.h>

#include <Turtle.h>
#include <Lignum.h>
using namespace Lignum;

template <class TS, class BUD>
int Lstring2Lignum(list<Axis<TS,BUD>*>& ls, list<Axis<TS,BUD>*>::iterator current, 
		   const Tree<TS,BUD>& tree, LstringIterator& ltr, stack<Turtle>& ts)
{  
  //Lstring must not end in a branching point 
  if (iterator.AtEnd()){
    cerr<< "BP Error end of string" << endl;
    return -1; //exit
  }
  
  const char* name = iterator.GetCurrentModuleName();
  
  //Branching point sees "SB" --> axis
  if (strcmp(name,"SB") == 0){
    //push the turtle to the top of the stack
    turtle_stack.push(turtle_stack.top());
    //If the last axis passed then new Axis is needed
    if (current == ls.end()){
      Axis<TS,BUD>* axis = new Axis<TS,BUD>(GetPoint(turtle_stack.top()),
					    GetHeading(turtle_stack.top()),
					    &tree);
      ls.insert(current,axis);
      //Go to the first symbol of the new axis
      ltr++;
      list<TreeCompartment<TS,BUD>& tc_ls = GetTreeComartmentList(*axis);
      L2Lignum(tc_ls,tc_ls.begin(),tree,ltr,turtle_stack);
    }
    //If axis exists no new structure is needed
    //Note: this assumes that if new axes emerge 
    //they are added last in the Lstring
    //Example: [A,A,A] ---> [A,A,A,Anew]
    else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*> (current)){
      //Go to the first symbol of the new axis
      ltr++;
      list<TreeCompartment<TS,BUD>& tc_ls = GetTreeComartmentList(*axis);
      L2Lignum(tc_ls,tc_ls.begin(),tree,ltr,turtle_stack);
      //Proceed to next axis
      current++;
    }
    else{
      //If control reaches here we are seriously wrong,
      //there can only be axes in an axis list
    }
  }
  //Branching point sees "EB" --> end of Axis
  //Go to next symbol
  else if (strcmp(name,"EB") == 0){
    //Pop the turtle from the stack
    turtle_stack.pop();
    ltr++;
  }
  //This can only be some symbol  "S" in between "EB" and "SB": "] S [".
  //It means end of branching point, return and let the calling Axis see the symbol S
  else{
    return 0; //end of bp
  }
  //Proceed to next axis
  return L2Lignum(ls,current,tree,ltr,turtle_stack);
}
      
//Add new structure to Lignum. It is assumed that the Lstring
//and Lignum match except the new structure in the Lstring.
//This algorithm is similar to  L2Lignum but Lstring2Lignum
//adds only the new structure in Lstring into Lignum 
template <class TS, class BUD>
int Lstring2Lignum(list<TreeCompartment<TS,BUD>*>& ls,
		   list<TreeCompartment<TS,BUD>*>::iterator current,
		   const Tree<TS,BUD>& tree,
		   LstringIterator& ltr,
		   stack<Turtle>& ts)
{
  CallerData caller_data;

  //Check the end of Lstring
  if (iterator.AtEnd()){
    //cout << "Axis end of string" << endl;
    return 1; //exit
  }

  const char* name =  ltr.GetCurrentModuleName();
  
  //If axis sees "EB" --> end of axis
  //we should be in some branching point so return
  //and let the branching point scan the string forward
  if (strcmp(name,"EB") == 0){
    return 2;
  } 
  //The symbol F means a tree segment
  else if (strcmp(name,"F") == 0){
    //Get the argument of "F" to move the turtle
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    //If the current tree compartment is a tree segment,
    //no new structure but update turtle and iterators
    if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*> (*current)){
      //Update turtle 
      ts.top().forward(arg1);
      //Update iterators 
      ltr++;
      current++;
    }
    //Current tree compartment is bud but the symbol is "F" --> new tree segment
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*> (*current)){
      //Lstring tells only the structure, use initial dimensions
      //and the gravelius order of the terminating bud
      TS* ts = new TS(GetPoint(turtle_stack.top()),GetHeading(turtle_stack.top()),
		      GetValue(*bud,omega),arg1,0.01,0.05,&tree);
      ls.insert(current,ts);
      //Update turtle
      ts.top().forward(arg1);
      //Update the position of the bud to the end point of the segment
      SetPoint(*bud,GetEndPoint(*ts))
      //Update Lstring iterator 
      ltr++;
    }
    else{
      //If control comes here it is an error
    }
  }
  //Axis sees "SB" --> Branching point begins
  else if (strcmp(name,"SB") == 0){
    //If the current tree compartment is a branching point
    //no new structure, proceed into the branching point
    //Don't go forward in LString, let the ltr iterator see "SB" again
    if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*> (*current)){
      list<Axis*>& al= GetAxisList(*bp);
      //Proceed into the branching point
      //Note we DO NOT return here but will deal with the brannching point
      Lstring2Lignum(al,al.begin(),tree,ltr,turtle_stack);
    }
    //Current tree compartment is bud but the symbol is "SB" --> new branching point
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*> (*current)){
      BranchingPoint<TS,BUD>* bp = new BranchingPoint<TS,BUD>(GetPoint(turtle_stack.top()),
							      GetHeading(turtle_stack.top()),
							      &tree);
      ls.insert(current,bp);
      list<Axis*>& al= GetAxisList(*bp);
      //Proceed into the branching point
      //Note we DO NOT return here but will deal with the brannching point
      Lstring2Lignum(al,al.begin(),tree,ltr,turtle_stack);
    }
    else{
      //If control reaches here it is an error
    }
  }
  //Take care of three turtle commands
  //Turn
  else if (strcmp(name,"Turn") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(iterator.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().turn(arg1);
    ltr++;
  }
  //Pitch
  else if (strcmp(name,"Pitch") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(iterator.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().pitch(arg1);
    ltr++;
  }
  //Roll
  else if (strcmp(name,"Roll") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(iterator.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().roll(arg1);
    ltr++;
  }
  //The symbol B means bud
  else if (strcmp(name,"B") == 0){
    //if the axis is empty --> new bud 
    if (ls.empty()){
      //The gravelius order is a problem
      //Possible solutions are:
      //1. The second argument of "B" will be reserved for gravelius order
      //2. Carry and update the gravelius order as part of this algorithm
      //3. Make a functor and update the tree with ForEach (probably the easieast)
      BUD* bud = new BUD(GetPoint(turtle_stack.top()),
			 GetHeading(turtle_stack.top()),
			 0.0,&tree);
      ls.insert(current,bud);
      ltr++;
    }
    //If the current tree compartment is also bud
    //move the Lstring iterator forward
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*> (*current)){
      ltr++;
    }
    else{
      //If control reaches here it is an error
    }
  }
  //Ignore  other symbols, go forward in the string
  else{
    ltr++;
  }
  //Deal with the  next symbol
  return L2Lignum(ls,current,tree,ltr,turtle_stack);
}

//Structural development of a tree
//The lstring 's' has been expanded and 
//the changes will be added to Lignum structure
template <class TS, class BUD>
int Lstring2Lignum(const Tree<TS,BUD>& t, const lstring& s)
{
  Turtle turtle;
  stack<Turtle> ts.push(turtle);
  LstringIterator ltr(s);
  Axis<TS,BUD>& axis = GetAxis(t);

  list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);
  return Lstring2Lignum(ls,ls.begin(),t,ltr,ts);
}

#endif
