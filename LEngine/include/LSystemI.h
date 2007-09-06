
template <class TS, class BUD, class T, class F>
int LSystem<TS,BUD,T,F>::lignum2Lstring(list<Axis<TS,BUD>*>& ls, 
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
      lignum2Lstring(tc_ls,tc_ls.begin(),ltr,vav);
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
  return lignum2Lstring(ls,current,ltr,vav);
}
      
/*********************************************************
 *Update the structure of LIGNUM and Lstring             *
 *Currently only the length of the segment i.e.,         *
 *the argument of turtle command F is updated.           *
 *The algorithm is essentially the same as Lstring2Lignum*
 *so other operations are easily added                   *
 *********************************************************/ 
template <class TS, class BUD,class T, class F>
int LSystem<TS,BUD,T,F>::lignum2Lstring(list<TreeCompartment<TS,BUD>*>& ls,
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
      lignum2Lstring(al,al.begin(),ltr,vav);
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
      cerr << "Axis error 3: list empty, structures should match" << endl;
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
  //The symbol Fd(l,r,rtop) means tree segment with length l, segment
  //radius r and top radius rtop
  else if (strcmp(name,"Fd") == 0){
    if (ls.empty()){
      cerr << "lignum2lstring Axis error in Fd, list empty, structures should match" << endl;
    }
    else if (TS* ts = dynamic_cast<TS*> (*current)){
      //Get the values for turtle Fd(l,r,rtop) 
      LGMdouble arg1 = GetValue(*ts,LGAL);
      LGMdouble arg2 = GetValue(*ts,LGAR);
      LGMdouble arg3 = GetValue(*ts,LGARTop);
      caller_data.Reset();
      caller_data.Strct.AddModuleAddr(ltr.Ptr());
      const char* pArg = caller_data.Strct.pArg(0);
      //Update length in L string
      memcpy(const_cast<char*>(pArg),&arg1,sizeof(double));
      pArg += sizeof(double);
      //Uodate R in L string
      memcpy(const_cast<char*>(pArg),&arg2,sizeof(double));
      pArg += sizeof(double);
      //Update RTop in L string
      memcpy(const_cast<char*>(pArg),&arg3,sizeof(double));
      //Update iterators 
      ltr++;
      current++;
    }
    //Current tree compartment is bud but the symbol is "F" --> new tree segment
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*> (*current)){
      cerr << "lignum2lstring Axis error in Fd:  current symbol is Bud with omega: " 
	   << GetValue(*bud,LGAomega) << " structures should match" << endl;
    }
    else{
      cerr << "lignum2lstring Axis error in Fd:  L file does not generate Lignum " << endl;
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
  //Ignore  other symbols, go forward in the string
  else{
    ltr++;
  }
  //Deal with the  next symbol
  return lignum2Lstring(ls,current,ltr,vav);
}

/*******************************************************
 *Get the main axis and with the user given data in vav*
 * start syncing LIGNUM and Lstring                    *
 *******************************************************/
template <class TS, class BUD, class N, class F>
int LSystem<TS,BUD,N,F>::lignum2Lstring(Tree<TS,BUD>& t, vector<N>& vav)
{
  LstringIterator ltr(mainstring);
  Axis<TS,BUD>& axis = GetAxis(t);
  list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);

  return lignum2Lstring(ls,ls.begin(),ltr,vav);
}

/*******************************************************************************
 *Update the structure of LIGNUM to  Lstring.                                  * 
 *Currently the length of the segment i.e., the argument                       *
 *of turtle command F is updated implicetly.                                   *
 *User can keep the symbol B for bud in sync with Lignum                       *
 *by giving the meaning of the symbols in order of                             *
 *appearance in the argument list. For example the call                        *
 *lignum2Lstring<MySegment,MyBud,LGMAD,LGMdouble(t,2,LGAtype,LGMstatus)        *
 *will update the type  and the status of the bud from LIGNUM to Lstring.      *
 *The algorithm is essentially the same as Lstring2Lignum                      *
 *so other operations are easily added and kept in sync.                       *
 ******************************************************************************/ 
template <class TS, class BUD, class N, class F>
int LSystem<TS,BUD,N,F>::lignumToLstring(Tree<TS,BUD>& t, int argnum,...)
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

  return lignum2Lstring(t,vav);
}

/************************************************************************
 *Lstring2Lignum for Axes and Branching points.                         *
 *Scan for SB's and EB's for the beginning and end of axes respectively.*
 ************************************************************************/
template <class TS, class BUD,class T,class F>
int LSystem<TS,BUD,T,F>::lstring2Lignum(list<Axis<TS,BUD>*>& ls, 
					typename list<Axis<TS,BUD>*>::iterator current, 
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
      Axis<TS,BUD>* axis = new Axis<TS,BUD>(GetPoint(turtle_stack.top()),
					    GetHeading(turtle_stack.top()),
					    &tree);
      ls.insert(current,axis);
      //Go to the first symbol of the new axis
      ltr++;
      list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
      lstring2Lignum(tc_ls,tc_ls.begin(),tree,ltr,turtle_stack,vav);
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
      lstring2Lignum(tc_ls,tc_ls.begin(),tree,ltr,turtle_stack,vav);
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
  return lstring2Lignum(ls,current,tree,ltr,turtle_stack,vav);
}
      
/**************************************************************
 *Add new structure to Lignum. It is assumed that the Lstring *
 *and Lignum match except the new structure in the Lstring.   *
 *This algorithm is similar to  L2Lignum but lstring2Lignum   *
 *adds only the new structure in Lstring into Lignum          *
 **************************************************************/
template <class TS, class BUD, class T, class F>
int LSystem<TS,BUD,T,F>::lstring2Lignum(list<TreeCompartment<TS,BUD>*>& ls,
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
      lstring2Lignum(al,al.begin(),tree,ltr,turtle_stack,vav);
      //Branching point done, move the current to the next tree segment
      current++;
    }
    //Current tree compartment is bud but the symbol is "SB" --> new branching point
    else if (dynamic_cast<BUD*> (*current)){
      BranchingPoint<TS,BUD>* bp = new BranchingPoint<TS,BUD>(GetPoint(turtle_stack.top()),
							      GetHeading(turtle_stack.top()),
							      turtle_stack.size(),
							      &tree);
      ls.insert(current,bp);
      list<Axis<TS,BUD>*>& al= GetAxisList(*bp);
      //Proceed into the branching point
      //Note we DO NOT return here but will deal with the brannching point
      lstring2Lignum(al,al.begin(),tree,ltr,turtle_stack,vav);
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
      //We will update this bud when its possible (matching bud in the string)
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
      SetValue(*ts,LGAL,arg1);
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
      TS* ts = new TS(GetPoint(turtle_stack.top()),
		      GetHeading(turtle_stack.top()),
		      turtle_stack.size(),arg1,GetValue(tree,LGPlr)*arg1,
		      0.0,&tree);
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
  //The symbol Fd(l,r,rtop)  means a tree segment length  l, radius r
  //and top radius rtop
  else if (strcmp(name,"Fd") == 0){
    //Get the arguments of "Fd" to move the turtle and for the segment
    //dimensions
    double arg1 = 0.0;
    double arg2 = 0.0;
    double arg3 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    const char* pArg = caller_data.Strct.pArg(0);
    memcpy((char*)&arg1,pArg,sizeof(double));
    pArg += sizeof(double);
    memcpy((char*)&arg2,pArg,sizeof(double));
    pArg += sizeof(double);
    memcpy((char*)&arg3,pArg,sizeof(double));
    //If the list is empty, we may have had in the previous step a symbol that
    //was ignored, but has now created segments and  buds. See for example 
    //symbodial.l. We give a chance and create a bud now, return  to this
    //algorithm and try again create the tree compartments.  
    if (ls.empty()){
      BUD* bud = new BUD(GetPoint(turtle_stack.top()),
			 GetHeading(turtle_stack.top()),
			 turtle_stack.size(),&tree);
      //We will update this bud when its possible (matching bud in the string)
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
      SetValue(*ts,LGAL,arg1);
      SetValue(*ts,LGAR,arg2);
      SetValue(*ts,LGARTop,arg3);
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
      TS* ts = new TS(GetPoint(turtle_stack.top()),
		      GetHeading(turtle_stack.top()),
		      turtle_stack.size(),arg1,GetValue(tree,LGPlr)*arg1,
		      0.0,&tree);
      //Set radius
      SetValue(*ts,LGAR,arg2);
      //Set top radius
      SetValue(*ts,LGARTop,arg3);
      ls.insert(current,ts);
      //Update turtle
      turtle_stack.top().forward(arg1);
      //Update the position of the bud to the end point of the segment
      SetPoint(*bud,GetEndPoint(*ts));
      //Update Lstring iterator 
      ltr++;
    }
    else{
      cerr << "lstring2lignum Axis error Fd,  L file does not generate Lignum " << endl;
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
      //Check if Bud indeed has parameters (it may not)
      if (caller_data.Strct.hasParameters() ){
	const char* pArg = caller_data.Strct.pArg(0);
	for (int i = 0; i < static_cast<int>(vav.size()); i++){
	  F arg = GetValue(*bud,vav[i]);
	  memcpy((char*)&arg,pArg,sizeof(F));
	  SetValue(*bud,vav[i],arg);
	  pArg += sizeof(F);
	}
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
      //Check if the Bud indeed has parameters (it may not!)
      if (caller_data.Strct.hasParameters()){
	const char* pArg = caller_data.Strct.pArg(0);
	for (int i = 0; i < static_cast<int>(vav.size()); i++){
	  F arg = GetValue(*bud,vav[i]);
	  memcpy((char*)&arg,pArg,sizeof(F));
	  SetValue(*bud,vav[i],arg);
	  pArg += sizeof(F);
	}
      }
      ltr++;
    }
    else{
      cerr << "Axis error 3 L file does not generate Lignum structure" << endl;
      //If control reaches here it is an error
    }
  }
  //Take care of  turtle commands
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
  //f: move the turtle forward but don't generate segment
  else if (strcmp(name,"f") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().forward(arg1);
    ltr++;
  }
  //Up: Rotate the turtle to face up in the world
  else if  (strcmp(name,"Up") == 0){
    turtle_stack.top().up();
    ltr++;
  }
  //Hrz: Rotate turtle so that heading is horizontal
  else if  (strcmp(name,"Hrz") == 0){
    turtle_stack.top().hrz();
    ltr++;
  }
  //HDir: Set heading direction to angle 'arg1' measured from world up
  else if (strcmp(name,"HDir") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().hdir(arg1);
    ltr++;
  }
  //HUp: Set heading direction to  angle 'arg1' measured from world up
  //if and only if heading is pointing downwards in world cordinates
  else if (strcmp(name,"HUp") == 0){
    double arg1 = 0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
    turtle_stack.top().hup(arg1);
    ltr++;
  }
  //H: query the turtle heading  
  else if (strcmp(name,"H") == 0){
    PositionVector h = GetHeading(turtle_stack.top());
    double x,y,z;
    x = h.getX();
    y = h.getY();
    z = h.getZ();
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    const char* pArg = caller_data.Strct.pArg(0);
    memcpy(const_cast<char*>(pArg),&x,sizeof(double));
    pArg += sizeof(double);
    memcpy(const_cast<char*>(pArg),&y,sizeof(double));
    pArg += sizeof(double);
    memcpy(const_cast<char*>(pArg),&z,sizeof(double));
    ltr++;
  }
  //L: query the turtle left  
  else if (strcmp(name,"L") == 0){
    PositionVector l = GetLeft(turtle_stack.top());
    double x,y,z;
    x = l.getX();
    y = l.getY();
    z = l.getZ();
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    const char* pArg = caller_data.Strct.pArg(0);
    memcpy(const_cast<char*>(pArg),&x,sizeof(double));
    pArg += sizeof(double);
    memcpy(const_cast<char*>(pArg),&y,sizeof(double));
    pArg += sizeof(double);
    memcpy(const_cast<char*>(pArg),&z,sizeof(double));
    ltr++;
  }
  //U: query the turtle up  
  else if (strcmp(name,"U") == 0){
    PositionVector u = GetUp(turtle_stack.top());
    double x,y,z;
    x = u.getX();
    y = u.getY();
    z = u.getZ();
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    const char* pArg = caller_data.Strct.pArg(0);
    memcpy(const_cast<char*>(pArg),&x,sizeof(double));
    pArg += sizeof(double);
    memcpy(const_cast<char*>(pArg),&y,sizeof(double));
    pArg += sizeof(double);
    memcpy(const_cast<char*>(pArg),&z,sizeof(double));
    ltr++;
  }
  //MoveTo(x,y,z): set turtle to given position Point(x,y,z)
  else if (strcmp(name,"MoveTo")){
    double x,y,z;
    x=y=z=0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    const char* pArg = caller_data.Strct.pArg(0);
    memcpy(&x,pArg,sizeof(double));
    pArg += sizeof(double);
    memcpy(&y,pArg,sizeof(double));
    pArg += sizeof(double);
    memcpy(&z,pArg,sizeof(double));
    SetPoint(turtle_stack.top(),Point(z,y,z));
    ltr++;
  }
  //SetHead(hx,hy,hz,ux,uy,uz): set turtle heading to PositionVector(hx,hy,hz)
  //and turtle up to PositionVector(ux,uy,uz). The vectors need not be normalized
  //(they are normalized here). Turtle left is defined as Cross(up,heading).
  //The module is ignored if 
  //1. the angle between heading and up is not 90 degrees (Dot product > R_EPSILON)
  //2. the length of either of the two vectors is less than R_EPSILON
  else if (strcmp(name,"SetHead")){
    double hx,hy,hz,ux,uy,uz;
    hx=hy=hz=ux=uy=uz=0.0;
    caller_data.Reset();
    caller_data.Strct.AddModuleAddr(ltr.Ptr());
    const char* pArg = caller_data.Strct.pArg(0);
    memcpy(&hx,pArg,sizeof(double));
    pArg += sizeof(double);
    memcpy(&hy,pArg,sizeof(double));
    pArg += sizeof(double);
    memcpy(&hz,pArg,sizeof(double));
    pArg += sizeof(double);
    memcpy(&ux,pArg,sizeof(double));
    pArg += sizeof(double);
    memcpy(&uy,pArg,sizeof(double));
    pArg += sizeof(double);
    memcpy(&uz,pArg,sizeof(double));
    PositionVector h(hx,hy,hz);//heading
    PositionVector u(ux,uy,uz);//up
    h.normalize();
    u.normalize();
    double dot = Dot(h,u);
    //ignore the symbol if h or u are of length 0 or not perpendicular.
    if (h.length() < R_EPSILON || u.length() < R_EPSILON || fabs(dot) > R_EPSILON){
      ltr++;
    }
    else{
      //left should have some length because h and u have
      PositionVector l = Cross(u,h);
      l.normalize();
      SetHeading(turtle_stack.top(),h);
      SetUp(turtle_stack.top(),u);
      SetLeft(turtle_stack.top(),l);
      ltr++;
    }
  }
  //Ignore  other symbols, go forward in the string
  else{
    ltr++;
  }
  //Deal with the  next symbol
  return lstring2Lignum(ls,current,tree,ltr,turtle_stack,vav);
}

/****************************************************************************
 *Create Turtle, get the main axis and with the user defined variables to be* 
 *updated start syncing lstring and LIGNUM.                                 *
 ****************************************************************************/
template <class TS, class BUD, class N, class F>
int LSystem<TS,BUD,N,F>::lstring2Lignum(Tree<TS,BUD>& t, vector<N>& vav)
{

  Turtle turtle(GetPoint(t));
  stack<Turtle> turtle_stack;
  LstringIterator ltr(mainstring);
  Axis<TS,BUD>& axis = GetAxis(t);
  turtle_stack.push(turtle);
  list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);

  return lstring2Lignum(ls,ls.begin(),t,ltr,turtle_stack,vav);
}

/*******************************************************************************
 *Update the structure of Lstring to  LIGNUM.                                  * 
 *Currently the length of the segment i.e., the argument                       *
 *of turtle command F is updated implicetly.                                   *
 *User can keep the symbol B for bud in sync with Lignum                       *
 *by giving the meaning of the symbols in order of                             *
 *appearance in the argument list. For example the call                        *
 *lstring2Lignum<MySegment,MyBud,LGMAD,LGMdouble(t,2,LGAtype,LGMstatus)        *
 *will update the type  and the status of the bud from Lstring to LIGNUM.      *
 *The algorithm is essentially the same as lignum2Lstring                      *
 *so other operations are easily added and kept in sync.                       *
 ******************************************************************************/ 
template <class TS, class BUD, class N, class F>
int LSystem<TS,BUD,N,F>::lstringToLignum(Tree<TS,BUD>& t, int argnum,...)
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
  return lstring2Lignum(t,vav);
}
