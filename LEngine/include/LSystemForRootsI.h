/**********************************************************************
 *Implementing  conversion  algorithms for  root  system and  L-string.
 *Obviously, due  to analogue  structure of the  root system  and above
 *ground part of the tree the conversion algorithms are essentially the
 *same.
 *********************************************************************/

/*********************************************************
 *RootBranchingPoint part: traverse the list of root axes.
 *********************************************************/
template <class TS,class BUD,class T, class F>
  int LSystem<TS,BUD,T,F>::rootSystem2Lstring(list<RootAxis<Tree<TS,BUD> >*>& ls,
					      typename list<RootAxis<Tree<TS,BUD> >*>::iterator
					      current,
					      LstringIterator& ltr, vector<T>& vav)
{

  //Lstring must not end in a branching point
  if (ltr.AtEnd()){
    cerr << "BP error end of string" << endl;
    return -1; //exit
  }
  
  const char* name = ltr.GetCurrentModuleName();
  
  //Branching point sees "SB" --> root axis
  if (strcmp(name,"SB") == 0){
    if (current == ls.end()){
      cerr << "BP error 1 structures should match" << endl;
    }
    else if (RootAxis<Tree<TS,BUD> >* root_axis = dynamic_cast<RootAxis<Tree<TS,BUD> >*> (*current)){
      ltr++;
      //Proceed to the axis
      list<RootCompartment<Tree<TS,BUD> >*>& rc_ls = GetRootCompartmentList(*root_axis);
      rootSystem2Lstring(rc_ls,rc_ls.begin(),ltr,vav);
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
  return rootSystem2Lstring(ls,current,ltr,vav);
}
      
/*********************************************************************
 *Update the structure of Root  system and Lstring. Currently only the
 *length  of the segment  i.e., the  argument of  turtle command  F is
 *updated.     The   algorithm    is   essentially    the    same   as
 *lstring2RootSystem so other operations are easily added.
 *********************************************************************/
template <class TS, class BUD, class T, class F>
  int LSystem<TS,BUD,T,F>::rootSystem2Lstring(list<RootCompartment<Tree<TS,BUD> >*>& ls,
					      typename list<RootCompartment<Tree<TS,BUD> >*>::iterator
					      current,
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
    if (RootBranchingPoint<Tree<TS,BUD> >* rbp =
	dynamic_cast<RootBranchingPoint<Tree<TS,BUD> >*> (*current)){
      //Proceed into the branching point
      list<RootAxis<Tree<TS,BUD> >*>& ral= GetAxisList(*rbp);
      //Note we DO NOT return here but will construct the branching point
      rootSystem2Lstring(ral,ral.begin(),ltr,vav);
      //Branching point done, move the current to the next tree segment
      current++;
    }
    //Current root compartment is bud but the symbol is "SB" --> error
    //(structures should match)
    else if (RootTip<Tree<TS,BUD> >* rt = dynamic_cast<RootTip<Tree<TS,BUD> >*> (*current)){
      cerr << "Axis error 1 current is root tip structures should match" << endl;
    }
    else{
      //We don't have other choices (we should never enter here)
      cerr << "Axis error 2 L file does not generate RootSystem structure" << endl;
    }
  }
  //The symbol F means a root segment
  else if (strcmp(name,"F") == 0){
    if (ls.empty()){
      cerr << "Axis error 3 list empty structres should match" << endl;
    }
    //If the current tree compartment is a tree segment,
    //udate iterators
    else if (RootSegment<Tree<TS,BUD> >* rs = dynamic_cast<RootSegment<Tree<TS,BUD> >*> (*current)){
      //Get the argument of "F" to update the argument
      LGMdouble arg1 = GetValue(*rs,LGAL);
      caller_data.Reset();
      caller_data.Strct.AddModuleAddr(ltr.Ptr());
      //Update the length of turtle forward command to the length of the segment
      memcpy(const_cast<char*>(caller_data.Strct.pArg(0)),&arg1,sizeof(double));
      //Update iterators
      ltr++;
      current++;
    }
    //Current tree compartment is bud  but the symbol is "F" --> error
    //(structures should match)
    else if (RootTip<Tree<TS,BUD> >* rt = dynamic_cast<RootTip<Tree<TS,BUD> >*> (*current)){
      cerr << "Axis error 4 current is root tip structures should match" << endl;
    }
    else{
      cerr << "Axis error 5  L file does not generate RootSystem " << endl;
      //If control comes here it is an error (we should never enter here)
    }
  }
  //The symbol B means root tip
  else if (strcmp(name,"B") == 0){
    //if the axis is empty --> error (structures should match)
    if (ls.empty()){
      cerr << "Axis error 6 structures should match" << endl;
    }
    //If the current tree compartment is also bud
    //move the Lstring iterator forward
    else if (RootTip<Tree<TS,BUD> >* rt = dynamic_cast<RootTip<Tree<TS,BUD> >*> (*current)){
      caller_data.Reset();
      caller_data.Strct.AddModuleAddr(ltr.Ptr());
      //Check if root tip indeed has parameters (it may not!)
      if (caller_data.Strct.hasParameters() > 0){
	const char* pArg = caller_data.Strct.pArg(0);
	for (int i = 0; i < vav.size(); i++){
	  F arg = GetValue(*rt,vav[i]);
	  memcpy(const_cast<char*>(pArg),&arg,sizeof(F));
	  pArg += sizeof(F);
	}
      }
      ltr++;
    }
    else{
      cerr << "Axis error 7 L file does not generate RootSystem structure" << endl;
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
  return rootSystem2Lstring(ls,current,ltr,vav);
}

/********************************************************************
 *Get the  main root axis and with  the user given data  in vav start
 *syncing Root system and Lstring
 ********************************************************************/
template <class TS, class BUD,class N, class F>
int LSystem<TS,BUD,N,F>::rootSystem2Lstring(Tree<TS,BUD>& t, vector<N>& vav)
{
  LstringIterator ltr(mainstring);
  RootAxis<Tree<TS,BUD> >& root_axis = GetRootAxis(t);
  list<RootCompartment<Tree<TS,BUD> >*>& ls = GetRootCompartmentList(root_axis);

  return rootSystem2Lstring(ls,ls.begin(),ltr,vav);
}

/*********************************************************************
 *Update  the structure  of root  system to  Lstring.    Currently the
 *length  of the segment  i.e., the  argument of  turtle command  F is
 *updated implicetly. User  can keep the symbol B for root tip in sync
 *with RootSystem  by giving  the meaning of  the symbols in  order of
 *appearance   in   the   argument   list.  For   example   the   call
 *rootSystem2Lstring<MySegment,MyBud,LGMAD,LGMdouble(t,2,LGMtype,LGMstatus)
 *will update the  type and the status of the bud  from root system to
 *Lstring. The algorithm is essentially the same as lstring2RootSystem
 *so other operations are easily added and kept in sync.
 ********************************************************************/
template <class TS, class BUD, class N, class F>
int LSystem<TS,BUD,N,F>::rootSystemToLstring(Tree<TS,BUD>& t, int argnum,...)
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

  return rootSystem2Lstring(t,vav);
}

/**********************************************************************
 *Lstring2RootSystem for Root Branching points.  Scan for SB's and EB's
 *for the beginning and end of axes respectively.
 **********************************************************************/
template <class TS, class BUD, class T,class F>
  int LSystem<TS,BUD,T,F>::lstring2RootSystem(list<RootAxis<Tree<TS,BUD> >*>& ls,
					      typename list<RootAxis<Tree<TS,BUD> >*>::iterator current,
					      Tree<TS,BUD>& tree, LstringIterator& ltr,
					      stack<Turtle>& turtle_stack, vector<T>& vav)
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
      RootAxis<Tree<TS,BUD> >* root_axis = new RootAxis<Tree<TS,BUD> >(GetPoint(turtle_stack.top()),
								       GetHeading(turtle_stack.top()),
								       tree);
      ls.insert(current,root_axis);
      //Go to the first symbol of the new axis
      ltr++;
      list<RootCompartment<Tree<TS,BUD> >*>& rc_ls = GetRootCompartmentList(*root_axis);
      lstring2RootSystem(rc_ls,rc_ls.begin(),tree,ltr,turtle_stack,vav);
    }
    //If root axis exists no new structure is needed
    //Note: this assumes that if new axes emerge
    //they are added last in the Lstring
    //Example: [A,A,A] ---> [A,A,A,Anew]
    else if (RootAxis<Tree<TS,BUD> >* root_axis = dynamic_cast<RootAxis<Tree<TS,BUD> >*> (*current)){
      //Update point and direction
      SetPoint(*root_axis,GetPoint(turtle_stack.top()));
      SetDirection(*root_axis,GetHeading(turtle_stack.top()));
      //Go to the first symbol of the new axis
      ltr++;
      list<RootCompartment<Tree<TS,BUD> >*>& rc_ls = GetRootCompartmentList(*root_axis);
      lstring2RootSystem(rc_ls,rc_ls.begin(),tree,ltr,turtle_stack,vav);
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
  return lstring2RootSystem(ls,current,tree,ltr,turtle_stack,vav);
}
      
/**********************************************************************
 *Add new structure  to RootSystem. It is assumed  that the Lstring and
 *RootSystem  match i.e.  the  new structure  in  the Lstring will
 *create root system structure.  
 *********************************************************************/
template <class TS, class BUD, class T, class F>
  int LSystem<TS,BUD,T,F>::lstring2RootSystem(list<RootCompartment<Tree<TS,BUD> >*>& ls,
					      typename list<RootCompartment<Tree<TS,BUD> >*>::iterator 
					      current,
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
    if (RootBranchingPoint<Tree<TS,BUD> >* rbp =
	dynamic_cast<RootBranchingPoint<Tree<TS,BUD> >*> (*current)){
      //Update point and direction
      SetPoint(*rbp,GetPoint(turtle_stack.top()));
      SetDirection(*rbp,GetHeading(turtle_stack.top()));
      //Proceed into the branching point
      list<RootAxis<Tree<TS,BUD> >*>& ral= GetAxisList(*rbp);
      //Note we DO NOT return here but will construct the branching point
      lstring2RootSystem(ral,ral.begin(),tree,ltr,turtle_stack,vav);
      //Branching point done, move the current to the next tree segment
      current++;
    }
    //Current tree compartment is bud but the symbol is "SB" --> new branching point
    else if (RootTip<Tree<TS,BUD> >* rt = dynamic_cast<RootTip<Tree<TS,BUD> >*> (*current)){
      RootBranchingPoint<Tree<TS,BUD> >* rbp =
	new RootBranchingPoint<Tree<TS,BUD> >(GetPoint(turtle_stack.top()),
					      GetHeading(turtle_stack.top()),
					      tree);
      ls.insert(current,rbp);
      list<RootAxis<Tree<TS,BUD> >*>& ral= GetAxisList(*rbp);
      //Proceed into the branching point
      //Note we DO NOT return here but will deal with the brannching point
      lstring2RootSystem(ral,ral.begin(),tree,ltr,turtle_stack,vav);
    }
    else{
      //We don't have other choices
      cerr << "Axis error 1 L file does not generate RootSystem structure" << endl;
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
      RootTip<Tree<TS,BUD> >* rt = new RootTip<Tree<TS,BUD> >(GetPoint(turtle_stack.top()),
							      GetHeading(turtle_stack.top()),
							      turtle_stack.size(),//Gravelius order
							      tree);
      //We will update this bud when its possible (matching bud in the string)
      ls.insert(ls.begin(),rt);
      //Initialize current!!
      current = ls.begin();
      //Do not update Lstring iterator
    }
    //If the current tree compartment is a tree segment,
    //no new structure but update turtle and iterators
    else if (RootSegment<Tree<TS,BUD> >* rs = dynamic_cast<RootSegment<Tree<TS,BUD> >*> (*current)){
      //Update point and direction
      SetPoint(*rs,GetPoint(turtle_stack.top()));
      SetDirection(*rs,GetHeading(turtle_stack.top()));
      //Should we update the length may be a matter of discussion
      //But when the turtle is 'in charge' we should (c.f symbodial growth)
      SetValue(*rs,LGAL,arg1);
      //Move the turtle
      turtle_stack.top().forward(arg1);
      //Update iterators
      ltr++;
      current++;
    }
    //Current tree compartment is bud but the symbol is "F" --> new tree segment
    else if (RootTip<Tree<TS,BUD> >* rt = dynamic_cast<RootTip<Tree<TS,BUD> >*> (*current)){
      //Lstring tells only the structure, use initial dimensions
      //and the gravelius order of the terminating bud
      RootSegment<Tree<TS,BUD> >* rs = new RootSegment<Tree<TS,BUD> >(GetPoint(turtle_stack.top()),
								      GetHeading(turtle_stack.top()),
								      arg1,//length
								      0.01,//radius
								      0.01,//radius at top
								      0.00,//heartwood radius
								      0.02,//radius to root hair
								      turtle_stack.size(),//Gravelius
								      tree);
      ls.insert(current,rs);
      //Update turtle
      turtle_stack.top().forward(arg1);
      //Update the position of the bud to the end point of the segment
      SetPoint(*rt,GetEndPoint(*rs));
      //Update Lstring iterator
      ltr++;
    }
    else{
      cerr << "Axis error 2  L file does not generate RootSystem " << endl;
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
      RootTip<Tree<TS,BUD> >* rt = new RootTip<Tree<TS,BUD> >(GetPoint(turtle_stack.top()),
							      GetHeading(turtle_stack.top()),
							      turtle_stack.size(),//Gravelius order
							      tree);
      caller_data.Reset();
      caller_data.Strct.AddModuleAddr(ltr.Ptr());
      //Check if root tip indeed has parameters (it may not)
      if (caller_data.Strct.hasParameters() ){
	const char* pArg = caller_data.Strct.pArg(0);
	for (int i = 0; i < vav.size(); i++){
	  F arg = GetValue(*rt,vav[i]);
	  memcpy((char*)&arg,pArg,sizeof(F));
	  SetValue(*rt,vav[i],arg);
	  pArg += sizeof(F);
	}
      }
      ls.insert(ls.begin(),rt);
      current = ls.begin();
      ltr++;
    }
    //If the current tree compartment is also bud
    //move the Lstring iterator forward
    else if (RootTip<Tree<TS,BUD> >* rt = dynamic_cast<RootTip<Tree<TS,BUD> >*>(*current)){
      //Update heading and position
      SetPoint(*rt,GetPoint(turtle_stack.top()));
      SetDirection(*rt,GetHeading(turtle_stack.top()));
      caller_data.Reset();
      caller_data.Strct.AddModuleAddr(ltr.Ptr());
      //Check if the root tip indeed has parameters (it may not!)
      if (caller_data.Strct.hasParameters()){
	const char* pArg = caller_data.Strct.pArg(0);
	for (int i = 0; i < vav.size(); i++){
	  F arg = GetValue(*rt,vav[i]);
	  memcpy((char*)&arg,pArg,sizeof(F));
	  SetValue(*rt,vav[i],arg);
	  pArg += sizeof(F);
	}
      }
      ltr++;
    }
    else{
      cerr << "Axis error 3 L file does not generate RootSystem structure" << endl;
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
  //HRoll
  else if (strcmp(name,"HRoll") == 0){
    turtle_stack.top().hroll();
    ltr++;
  }
  //Ignore  other symbols, go forward in the string
  else{
    ltr++;
  }
  //Deal with the  next symbol
  return lstring2RootSystem(ls,current,tree,ltr,turtle_stack,vav);
}

/*********************************************************************
 *Create Turtle, get the main axis and with the user defined variables
 *to be updated start syncing lstring and root system.
 ********************************************************************/
template <class TS, class BUD, class N, class F>
int LSystem<TS,BUD,N,F>::lstring2RootSystem(Tree<TS,BUD>& t, vector<N>& vav)
{

  Turtle turtle(GetPoint(t));
  stack<Turtle> turtle_stack;
  LstringIterator ltr(mainstring);
  RootAxis<Tree<TS,BUD> >& root_axis = GetRootAxis(t);
  turtle_stack.push(turtle);
  list<RootCompartment<Tree<TS,BUD> >*>& ls = GetRootCompartmentList(root_axis);

  return lstring2RootSystem(ls,ls.begin(),t,ltr,turtle_stack,vav);
}

/**********************************************************************
 *Update the structure of Lstring to root system.  Currently the length
 *of  the segment i.e.,  the argument  of turtle  command F  is updated
 *implicetly.   User  can  keep the  symbol  B  for  bud in  sync  with
 *RootSystem  by  giving  the  meaning  of  the  symbols  in  order  of
 *appearance   in   the   argument   list.   For   example   the   call
 *lstring2RootSystem<MySegment,MyBud,LGMAD,LGMdouble(t,2,LGMtype,LGMstatus)
 *will update the  type and the status of the bud  from Lstring to root
 *system.  The algorithm is  essentially the same as rootSystem2Lstring
 *so other operations are easily added and kept in sync.
 **********************************************************************/
template <class TS, class BUD, class N, class F>
int LSystem<TS,BUD,N,F>::lstringToRootSystem(Tree<TS,BUD>& t, int argnum,...)
{
  va_list ap;
  vector<N> vav;

  //The C library standard requires  that in call to va_arg the second
  //(last)  type parameter  must *not*  be array,  function,  float or
  //integer type that changes  when promoted. Unfortunately this means
  //that the  enumeration N that will  denote the set of  names of the
  //variables of type F cannot be  used. But we pass int to va_arg and
  //type cast the  return value back to N. Some  compilers (as SGI CC)
  //accept N as such but it should be an error.
  va_start(ap,argnum);
  for (int i = 0; i < argnum; i++){
    vav.push_back(static_cast<N>(va_arg(ap,int)));
  }
  va_end(ap);
  return lstring2RootSystem(t,vav);
}
