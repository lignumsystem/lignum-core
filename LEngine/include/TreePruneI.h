//Branching point  has the  list of  axes. If an  empty axis  is found
//update the L-string by pruning it.
template <class TS, class BUD, class T, class F>
int LSystem<TS,BUD,T,F>::prune(list<Axis<TS,BUD>*>& ls, 
			       typename list<Axis<TS,BUD>*>::iterator current, 
			       LstringIterator& ltr, vector<T>& vav)
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
      cerr << "BP error 1 structures should match" << endl;
    }
    else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*> (*current)){
      ltr++;
      //Proceed to the axis
      list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
      //Do the pruning in the L-string  if the list is empty
      if (tc_ls.empty()){
	//The end branch is here or will be here
	const char* start = ltr.Ptr();
	//To find the end of branch
	LstringIterator eb(ltr);
	//The string is not pruned 
	if (strcmp(eb.GetCurrentModuleName(),"EB") != 0){
	  //The L-string is like: SB F ... EB SB ... EB F ... B, and we are
	  //at the first F.
	  eb.FindEOB();
	  //Now we are at the first EB 
	  int eb_position = eb.CurrentPosition();
	  int last_byte = eb.GetEndPosition();
	  //The distance from the first EB the last B (end of string)
	  int size_to_move = last_byte - eb_position;
	  //now move the tail of  the L-string, the string looks like:
	  //SB EB SB ... EB F ... B
	  ltr.prune(eb_position,size_to_move);
	}
	//The string is like: SB EB SB ... EB F ... B, so the branch is already pruned
      }
      //Return to the algorithm 
      prune(tc_ls,tc_ls.begin(),ltr,vav);
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
  return prune(ls,current,ltr,vav);
}
      
//Update  the structure of  LIGNUM and  Lstring. If  an empty  axis is
//found update the L-string
template <class TS, class BUD,class T, class F>
int LSystem<TS,BUD,T,F>::prune(list<TreeCompartment<TS,BUD>*>& ls,
			       typename list<TreeCompartment<TS,BUD>*>::iterator current,
			       LstringIterator& ltr, vector<T>& vav)
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
      prune(al,al.begin(),ltr,vav);
      //Branching point done, move the current to the next tree segment
      current++;
    }
    //Current tree compartment is bud but the symbol is "SB" --> new branching point
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*> (*current)){
      cerr << "Axis error 1 current is Bud  with branching order: " 
	   << GetValue(*bud,LGAomega)  << " structures should match " << endl; 
    }
    else{
      //We don't have other choices
      cerr << "Axis error 2 L file does not generate Lignum structure" << endl;
    }
  } 
  //The symbol F means a tree segment
  else if (strcmp(name,"F") == 0){
    if (ls.empty()){
      cerr << "Axis error 3 list empty structres should match" << endl;
    }
    //If the current tree compartment is a tree segment,
    //udate iterators
    else if (TS* ts = dynamic_cast<TS*> (*current)){
      //Get the argument of "F" to update the argument
      LGMdouble arg1 = GetValue(*ts,LGAL);
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
      cerr << "Axis error 4 current is Bud with omega: " 
	   << GetValue(*bud,LGAomega) << " structures should match" << endl;
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
      cerr << "Axis error 6 structures should match" << endl;
    }
    //If the current tree compartment is also bud
    //move the Lstring iterator forward
    else if (BUD* bud = dynamic_cast<BUD*> (*current)){
      caller_data.Reset();
      caller_data.Strct.AddModuleAddr(ltr.Ptr());
      //Check if Bud indeed has parameters (it may not!)
      if (caller_data.Strct.hasParameters() > 0){
	const char* pArg = caller_data.Strct.pArg(0);
	for (int i = 0; i < static_cast<int>(vav.size()); i++){
	  F arg = GetValue(*bud,vav[i]);
	  memcpy(const_cast<char*>(pArg),&arg,sizeof(F));
	  pArg += sizeof(F);
	}
      }
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
  //Hroll
  else if (strcmp(name,"Roll") == 0){
    ltr++;
  }
  //Ignore  other symbols, go forward in the string
  else{
    ltr++;
  }
  //Deal with the  next symbol
  return prune(ls,current,ltr,vav);
}

//Get the main axis and with  the user given data in vav start syncing
//LIGNUM and Lstring
template <class TS, class BUD, class N, class F>
int LSystem<TS,BUD,N,F>::prune(Tree<TS,BUD>& t, vector<N>& vav)
{
  LstringIterator ltr(mainstring);
  Axis<TS,BUD>& axis = GetAxis(t);
  list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);
  return prune(ls,ls.begin(),ltr,vav);;
}


//Prune the tree, i.e. remove dead  branhes. An axis or branch is dead
//if  the   buds  area   dead  and  none   of  its   segments  contain
//foliage.  After  the  pruning  update  the structure  of  LIGNUM  to
//Lstring.  The algorithm is essentially the same as Lstring2Lignum.
template <class TS, class BUD, class N, class F>
int LSystem<TS,BUD,N,F>::prune(Tree<TS,BUD>& t, int argnum,...)
{
  va_list ap;
  vector<N> vav;

  //The C library standard requires  that in call to va_arg the second
  //(last)  type parameter  must *not*  be array,  function,  float or
  //integer type that changes  when promoted. Unfortunately this means
  //that the  enumeration N that will  denote the set of  names of the
  //variables of type F cannot be  used. But we pass int to va_arg and
  //type cast  the return value back  to N. Some  compilers accept (as
  //SGI CC) N as such but it should be an error.
  va_start(ap,argnum);
  for (int i = 0; i < argnum; i++){
    vav.push_back(static_cast<N>(va_arg(ap,int)));
  }
  va_end(ap);

  //Prune the tree
  double foliage = 0.0;
  AccumulateDown(t,foliage,DeleteDeadBranches<TS,BUD>());
  return prune(t,vav);
}

