#ifndef LIGNUM2LSTRING_H
#define LIGNUM2LSTRING_H

#include <string.h>
#include <stack>
#include <list>

using namespace std;

#include <lstring.h>
#include <lstriter.h>

#include <Turtle.h>
#include <Lignum.h>
using namespace Lignum;

template <class TS, class BUD>
int Lignum2Lstring(list<Axis<TS,BUD>*>& ls, typename list<Axis<TS,BUD>*>::iterator current, 
		   LstringIterator& ltr)
{

  //Lstring must not end in a branching point 
  if (ltr.AtEnd()){
    cerr << "BP error end of string" << endl;
    return -1; //exit
  }
  
  const char* name = ltr.GetCurrentModuleName();
  
  //Branching point sees "SB" --> axis
  if (strcmp(name,"SB") == 0){
    if (current == ls.end()){
      cout << "BP error 1 structures should match" << endl;
    }
    else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*> (*current)){
      ltr++;
      //Proceed to the axis
      list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
      Lignum2Lstring(tc_ls,tc_ls.begin(),ltr);
      //Proceed to next axis
      current++;
    }
    else{
      cerr << "BP error 2 current not axis" << endl;
      //If control reaches here we are seriously wrong,
      //there can only be axes in an axis list
    }
  }
  //Branching point sees "EB" --> end of Axis
  //Go to next symbol
  else if (strcmp(name,"EB") == 0){
    ltr++;
  }
  //This can only be some symbol  "S" in between "EB" and "SB": "] S [".
  //It means end of branching point, return and let the calling Axis see the symbol S
  else{
    return 0; //end of bp
  }
  //Proceed to next axis
  return Lignum2Lstring(ls,current,ltr);
}
      
/**************************************************************
 *Add new structure to Lignum. It is assumed that the Lstring *
 *and Lignum match except the new structure in the Lstring.   *
 *This algorithm is similar to  L2Lignum but Lignum2Lstring   *
 *adds only the new structure in Lstring into Lignum          *
 **************************************************************/
template <class TS, class BUD>
int Lignum2Lstring(list<TreeCompartment<TS,BUD>*>& ls,
		   typename list<TreeCompartment<TS,BUD>*>::iterator current,
		   LstringIterator& ltr)
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
    //proceed into the branching point
    //Don't go forward in LString, let the ltr iterator see "SB" again
    if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*> (*current)){
      //Proceed into the branching point
      list<Axis<TS,BUD>*>& al= GetAxisList(*bp);
      //Note we DO NOT return here but will construct the branching point
      Lignum2Lstring(al,al.begin(),ltr);
      //Branching point done, move the current to the next tree segment
      current++;
    }
    //Current tree compartment is bud but the symbol is "SB" --> new branching point
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*> (*current)){
      cout << "Axis error 1 current is Bud structures should match" << endl; 
    }
    else{
      //We don't have other choices
      cerr << "Axis error 2 L file does not generate Lignum structure" << endl;
    }
  } 
  //The symbol F means a tree segment
  else if (strcmp(name,"F") == 0){
    if (ls.empty()){
      cout << "Axis error 3 list empty structres should match" << endl;
    }
    //If the current tree compartment is a tree segment,
    //udate iterators
    else if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*> (*current)){
      //Get the argument of "F" to update the argument
      caller_data.Strct.AddModuleAddr(ltr.Ptr());
      LGMdouble arg1 = GetValue(*ts,L);
      caller_data.Reset();
      caller_data.Strct.AddModuleAddr(ltr.Ptr());
      //Update the length of turtle forward command to the length of the segment
      memcpy(const_cast<char*>(caller_data.Strct.pArg(0)),&arg1,sizeof(double));
      //Update iterators 
      ltr++;
      current++;
    }
    //Current tree compartment is bud but the symbol is "F" --> new tree segment
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*> (*current)){
      cout << "Axis error 4 current is Bud structures should match" << endl;
    }
    else{
      cerr << "Axis error 5  L file does not generate Lignum " << endl;
      //If control comes here it is an error
    }
  }
  //The symbol B means bud
  else if (strcmp(name,"B") == 0){
    //if the axis is empty --> new bud 
    if (ls.empty()){
      cout << "Axis error 6 structures should match" << endl;
    }
    //If the current tree compartment is also bud
    //move the Lstring iterator forward
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*> (*current)){
      //Move forward in the string
      ltr++;
    }
    else{
      cerr << "Axis error 7 L file does not generate Lignum structure" << endl;
      //If control reaches here it is an error
    }
  }
  //Take care of three turtle commands
  //Turn
  else if (strcmp(name,"Turn") == 0){
    ltr++;
  }
  //Pitch
  else if (strcmp(name,"Pitch") == 0){
    ltr++;
  }
  //Roll
  else if (strcmp(name,"Roll") == 0){
    ltr++;
  }
  //Ignore  other symbols, go forward in the string
  else{
    ltr++;
  }
  //Deal with the  next symbol
  return Lignum2Lstring(ls,current,ltr);
}

/*********************************************************
 *Update the structure pf LIGNUM and Lstring             *
 *Currently only the length of the segment i.e.,         *
 *the argument of turtle command F is updated.           *
 *The algorithm is essentially the same as Lstring2Lignum*
 *so other operations are easily added                   *
 *********************************************************/ 
template <class TS, class BUD>
int Lignum2Lstring(Tree<TS,BUD>& t, const Lstring& s)
{
  LstringIterator ltr(s);
  Axis<TS,BUD>& axis = GetAxis(t);
  list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);
  return Lignum2Lstring(ls,ls.begin(),ltr);
}



#endif
