#ifndef LSTRING2LIGNUM_H
#define LSTRING2LIGNUM_H

#include <stdarg.h>
#include <string.h>
#include <stack>
#include <list>

using namespace std;

#include <lstring.h>
#include <lstriter.h>

#include <Turtle.h>
#include <Lignum.h>
using namespace Lignum;

/************************************************************************
 *Lstring2Lignum for Axes and Branching points.                         *
 *Scan for SB's and EB's for the beginning and end of axes respectively.*
 ************************************************************************/
template <class TS, class BUD,class T,class F>
int Lstring2Lignum(list<Axis<TS,BUD>*>& ls, typename list<Axis<TS,BUD>*>::iterator current, 
		   Tree<TS,BUD>& tree, LstringIterator& ltr, stack<Turtle>& turtle_stack, vector<T>& vav)
{

  //Lstring must not end in a branching point 
  if (ltr.AtEnd()){
    cerr << "BP error end of string" << endl;
    return -1; //exit
  }
  
  const char* name = ltr.GetCurrentModuleName();
  
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
      list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
      Lstring2Lignum<TS,BUD,T,F>(tc_ls,tc_ls.begin(),tree,ltr,turtle_stack,vav);
    }
    //If axis exists no new structure is needed
    //Note: this assumes that if new axes emerge 
    //they are added last in the Lstring
    //Example: [A,A,A] ---> [A,A,A,Anew]
    else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*> (*current)){
      //Update point and direction
      SetPoint(*axis,GetPoint(turtle_stack.top()));
      SetDirection(*axis,GetHeading(turtle_stack.top()));
      //Go to the first symbol of the new axis
      ltr++;
      list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
      Lstring2Lignum<TS,BUD,T,F>(tc_ls,tc_ls.begin(),tree,ltr,turtle_stack,vav);
      //Proceed to next axis
      current++;
    }
    else{
      cerr << "BP error current not axis" << endl;
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
  return Lstring2Lignum<TS,BUD,T,F>(ls,current,tree,ltr,turtle_stack,vav);
}
      
/**************************************************************
 *Add new structure to Lignum. It is assumed that the Lstring *
 *and Lignum match except the new structure in the Lstring.   *
 *This algorithm is similar to  L2Lignum but Lstring2Lignum   *
 *adds only the new structure in Lstring into Lignum          *
 **************************************************************/
template <class TS, class BUD, class T, class F>
int Lstring2Lignum(list<TreeCompartment<TS,BUD>*>& ls,
		   typename list<TreeCompartment<TS,BUD>*>::iterator current,
		   Tree<TS,BUD>& tree,
		   LstringIterator& ltr,
		   stack<Turtle>& turtle_stack,vector<T>& vav)
{
  CallerData caller_data;

  //Check the end of Lstring
  if (ltr.AtEnd()){
    return 1; //exit
  }

  const char* name =  ltr.GetCurrentModuleName();
  
  //If axis sees "EB" --> end of axis
  //we should be in some branching point so return
  //and let the branching point scan the string forward
  if (strcmp(name,"EB") == 0){
    return 2;
  }
  //Axis sees "SB" --> Branching point begins
  else if (strcmp(name,"SB") == 0){
    //If the current tree compartment is a branching point
    //no new structure, proceed into the branching point
    //Don't go forward in LString, let the ltr iterator see "SB" again
    if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*> (*current)){
      //Update point and direction
      SetPoint(*bp,GetPoint(turtle_stack.top()));
      SetDirection(*bp,GetHeading(turtle_stack.top()));
      //Proceed into the branching point
      list<Axis<TS,BUD>*>& al= GetAxisList(*bp);
      //Note we DO NOT return here but will construct the branching point
      Lstring2Lignum<TS,BUD,T,F>(al,al.begin(),tree,ltr,turtle_stack,vav);
      //Branching point done, move the current to the next tree segment
      current++;
    }
    //Current tree compartment is bud but the symbol is "SB" --> new branching point
    else if (BUD* bud = dynamic_cast<BUD*> (*current)){
      BranchingPoint<TS,BUD>* bp = new BranchingPoint<TS,BUD>(GetPoint(turtle_stack.top()),
							      GetHeading(turtle_stack.top()),
							      &tree);
      ls.insert(current,bp);
      list<Axis<TS,BUD>*>& al= GetAxisList(*bp);
      //Proceed into the branching point
      //Note we DO NOT return here but will deal with the brannching point
      Lstring2Lignum<TS,BUD,T,F>(al,al.begin(),tree,ltr,turtle_stack,vav);
    }
    else{
      //We don't have other choices
      cerr << "Axis error 1 L file does not generate Lignum structure" << endl;
    }
  } 
  //The symbol F means a tree segment
  else if (strcmp(name,"F") == 0){
    //Get the argument of "F" to move the turtle
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    //If the list is empty, we may have had in the previous step a symbol that
    //was ignored, but has now created segments and  buds. See for example 
    //symbodial.l. We give a chance and create a bud now, return  to this
    //algorithm and try again create the tree compartments.  
    if (ls.empty()){
      BUD* bud = new BUD(GetPoint(turtle_stack.top()),
			 GetHeading(turtle_stack.top()),
			 turtle_stack.size(),&tree);
      caller_data.Reset();
      caller_data.Strct.AddModuleAddr(ltr.Ptr());
      const char* pArg = caller_data.Strct.pArg(0);
      for (int i = 0; i < vav.size(); i++){
	F arg = GetValue(*bud,vav[i]);
	memcpy(&arg,pArg,sizeof(F));
	SetValue(*(BUD*)bud,vav[i],arg);
	pArg += sizeof(F);
      }
      ls.insert(ls.begin(),bud);
      //Initialize current!!
      current = ls.begin();
      //Do not update Lstring iterator 
    }
    //If the current tree compartment is a tree segment,
    //no new structure but update turtle and iterators
    else if (TS* ts = dynamic_cast<TS*> (*current)){
      //Update point and direction
      SetPoint(*ts,GetPoint(turtle_stack.top()));
      SetDirection(*ts,GetHeading(turtle_stack.top()));
      //Should we update the length may be a matter of discussion
      //But when the turtle is 'in charge' we should (c.f symbodial growth) 
      SetValue(*ts,L,arg1);
      //Move the turtle
      turtle_stack.top().forward(arg1);
      //Update iterators 
      ltr++;
      current++;
    }
    //Current tree compartment is bud but the symbol is "F" --> new tree segment
    else if (BUD* bud = dynamic_cast<BUD*> (*current)){
      //Lstring tells only the structure, use initial dimensions
      //and the gravelius order of the terminating bud
      TS* ts = new TS(GetPoint(turtle_stack.top()),GetHeading(turtle_stack.top()),
		      GetValue(*bud,omega),arg1,0.01,0.05,&tree);
      ls.insert(current,ts);
      //Update turtle
      turtle_stack.top().forward(arg1);
      //Update the position of the bud to the end point of the segment
      SetPoint(*bud,GetEndPoint(*ts));
      //Update Lstring iterator 
      ltr++;
    }
    else{
      cerr << "Axis error 2  L file does not generate Lignum " << endl;
      //If control comes here it is an error
    }
  }
  //The symbol B means bud
  else if (strcmp(name,"B") == 0){
    //if the axis is empty --> new bud 
    if (ls.empty()){
      //The gravelius order is a problem
      //Possible solutions are:
      //1. The second argument of "B" will be reserved for gravelius order
      //2. Carry and update the gravelius order as part of this algorithm
      //3. Make a functor and update the tree with ForEach
      //4. The size of the turtle stack tells the Gravelius order (chosen)
      BUD* bud = new BUD(GetPoint(turtle_stack.top()),
			 GetHeading(turtle_stack.top()),
			 turtle_stack.size(),&tree);
      caller_data.Reset();
      caller_data.Strct.AddModuleAddr(ltr.Ptr());
      const char* pArg = caller_data.Strct.pArg(0);
      for (int i = 0; i < vav.size(); i++){
	F arg = GetValue(*bud,vav[i]);
	memcpy((char*)&arg,pArg,sizeof(F));
	SetValue(*bud,vav[i],arg);
	pArg += sizeof(F);
      }
      ls.insert(ls.begin(),bud);
      current = ls.begin();
      ltr++;
    }
    //If the current tree compartment is also bud
    //move the Lstring iterator forward
    else if (BUD* bud = dynamic_cast<BUD*>(*current)){
      //Update heading and position
      SetPoint(*bud,GetPoint(turtle_stack.top()));
      SetDirection(*bud,GetHeading(turtle_stack.top()));
      caller_data.Reset();
      caller_data.Strct.AddModuleAddr(ltr.Ptr());
      const char* pArg = caller_data.Strct.pArg(0);
      for (int i = 0; i < vav.size(); i++){
	F arg = GetValue(*bud,vav[i]);
	memcpy((char*)&arg,pArg,sizeof(F));
	SetValue(*bud,vav[i],arg);
	pArg += sizeof(F);
      }
      ltr++;
    }
    else{
      cerr << "Axis error 3 L file does not generate Lignum structure" << endl;
      //If control reaches here it is an error
    }
  }
  //Take care of three turtle commands
  //Turn
  else if (strcmp(name,"Turn") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().turn(arg1);
    ltr++;
  }
  //Pitch
  else if (strcmp(name,"Pitch") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().pitch(arg1);
    ltr++;
  }
  //Roll
  else if (strcmp(name,"Roll") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().roll(arg1);
    ltr++;
  }
  //Ignore  other symbols, go forward in the string
  else{
    ltr++;
  }
  //Deal with the  next symbol
  return Lstring2Lignum<TS,BUD,T,F>(ls,current,tree,ltr,turtle_stack,vav);
}

/*******************************************************************************
 *Update the structure of Lstring to  LIGNUM.                                  * 
 *Currently the length of the segment i.e., the argument                       *
 *of turtle command F is updated implicetly.                                   *
 *User can keep the symbol B for bud in sync with Lignum                       *
 *by giving the meaning of the symbols in order of                             *
 *appearance in the argument list. For example the call                        *
 *Lstring2Lignum<MySegment,MyBud,LGMAD,LGMdouble(t,Lstring,2,LGMtype,LGMstatus)*
 *will update the type  and the status of the bud from Lstring to LIGNUM.      *
 *The algorithm is essentially the same as Lignum2Lstring                      *
 *so other operations are easily added and kept in sync.                       *
 ******************************************************************************/ 
template <class TS, class BUD, class N, class F>
int Lstring2Lignum(Tree<TS,BUD>& t, const Lstring& s, int argnum = 0,...)
{
  va_list ap;
  vector<N> vav;

  Turtle turtle;
  stack<Turtle> turtle_stack;
  LstringIterator ltr(s);
  Axis<TS,BUD>& axis = GetAxis(t);
  turtle_stack.push(turtle);
  list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);

  //The C library standard requires that in call to va_arg 
  //the second (last) type parameter must *not* be array, function, float 
  //or integer type that changes when promoted. Unfortunately this means
  //that  the enumeration N that will denote the set of names of 
  //the variables of type F cannot be used. But we pass int to va_arg 
  //and type cast the return value back to N. Some compilers (as SGI CC) 
  //accept N as such but it should be an error.
  va_start(ap,argnum);
  for (int i = 0; i < argnum; i++){
    vav.push_back(static_cast<N>(va_arg(ap,int)));
  }
  va_end(ap);
  return Lstring2Lignum<TS,BUD,N,F>(ls,ls.begin(),t,ltr,turtle_stack,vav);
}

#endif





