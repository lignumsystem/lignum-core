#ifndef LSYSTEMI_H
#define LSYSTEMI_H

/*******************************************************************************
 *Update the structure of LIGNUM to  Lstring.                                  * 
 *Currently the length of the segment i.e., the argument                       *
 *of turtle command F is updated implicetly.                                   *
 *User can keep the symbol B for bud in sync with Lignum                       *
 *by giving the meaning of the symbols in order of                             *
 *appearance in the argument list. For example the call                        *
 *Lignum2Lstring<MySegment,MyBud,LGMAD,LGMdouble(t,Lstring,2,LGMtype,LGMstatus)*
 *will update the type  and the status of the bud from LIGNUM to Lstring.      *
 *The algorithm is essentially the same as Lstring2Lignum                      *
 *so other operations are easily added and kept in sync.                       *
 ******************************************************************************/ 
template <class TS, class BUD, class N, class F>
int LSystem::lignum2Lstring(Tree<TS,BUD>& t, const Lstring& s,int argnum = 0,...)
{
  va_list ap;
  vector<N> vav;

  LstringIterator ltr(s);
  Axis<TS,BUD>& axis = GetAxis(t);
  list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);

  //The C library standard requires that in call to va_arg 
  //the second (last) type parameter must *not* be array, function, float 
  //or integer type that changes when promoted. Unfortunately this means
  //that  the enumeration N that will denote the set of names of 
  //the variables of type F cannot be used. But we pass int to va_arg 
  //and type cast the return value back to N. Some compilers accept (as SGI CC)
  // N as such but it should be an error.
  va_start(ap,argnum);
  for (int i = 0; i < argnum; i++){
    vav.push_back(static_cast<N>(va_arg(ap,int)));
  }
  va_end(ap);

  return lignum2Lstring<TS,BUD,N,F>(ls,ls.begin(),ltr,vav);
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
int Lsystem::lstring2Lignum(Tree<TS,BUD>& t, const Lstring& s, int argnum = 0,...)
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
  return lstring2Lignum<TS,BUD,N,F>(ls,ls.begin(),t,ltr,turtle_stack,vav);
}


#endif
