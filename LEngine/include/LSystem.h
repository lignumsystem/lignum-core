/*********************************************************************
 *The  class  LSystem provides  programming  interface  to L-system  *
 *rewriting of  the language L that lsystem.h  implements.  Note that*
 *neither lsys.h nor this  file  LSystem.h  are wrapped  with #infdef*
 *... #define ... #endif directives to prevent multiple inclusions of*
 *the header files. This is because both LSystem.h and lsystem.h must*
 *be  included several  times, once  for each  species of  the model.*
 *Multiple  decalarations and  definitions are  prevented by wrapping*
 *LSystem.h and lsys.h in namespaces.                             *
 *********************************************************************/
#include <lsys.h>

ProdCaller  ContextMatch(const LstringIterator& pos,CallerData& caller_data,int& prod);

//The succstrg, the temporary  expanded string or 'storage', is common
//within a species, but it is cleared after each derivation so it does
//not prevent multiple individuals of  the species to be modelled.  It
//only makes the program strictly sequential.
SuccessorStorage succstrg;

void _Add(const void* pX, int size)
{
  succstrg.Add(pX, size);
}

template <class TS, class BUD, class N = LGMAD, class F=LGMdouble>
class LSystem{
 public:
 void start();
 void derive();
 int derivationLength();
  void end();
  void endEach();
 void print(bool arg=false);
 int lignumToLstring(Tree<TS,BUD>& t,int argnum = 0,...);
 int lstringToLignum(Tree<TS,BUD>& t,int argnum = 0,...);
 int rootSystemToLstring(Tree<TS,BUD>& t,int argnum = 0,...);
 int lstringToRootSystem(Tree<TS,BUD>& t,int argnum = 0,...);
  int prune(Tree<TS,BUD>& t,int argnum = 0,...);
  template <class P,class I> 
  int prune(Tree<TS,BUD>& t,P p,I& init,int argnum = 0,...){
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
    AccumulateDown(t,init,p);
    return prune(t,vav);
  }
 protected:
 //above ground part
 int lignum2Lstring(Tree<TS,BUD>& t, vector<N>& vav);
 int lignum2Lstring(list<Axis<TS,BUD>*>& ls, 
		    typename list<Axis<TS,BUD>*>::iterator current, 
		    LstringIterator& ltr, vector<N>& vav);
 int lignum2Lstring(list<TreeCompartment<TS,BUD>*>& ls,
		    typename list<TreeCompartment<TS,BUD>*>::iterator current,
		    LstringIterator& ltr, vector<N>& vav);
 int lstring2Lignum(Tree<TS,BUD>& t, vector<N>& vav);
 int lstring2Lignum(list<TreeCompartment<TS,BUD>*>& ls,
		    typename list<TreeCompartment<TS,BUD>*>::iterator current,
		    Tree<TS,BUD>& tree,
		    LstringIterator& ltr,
		       stack<Turtle>& turtle_stack,vector<N>& vav);
 int lstring2Lignum(list<Axis<TS,BUD>*>& ls, 
		    typename list<Axis<TS,BUD>*>::iterator current, 
		    Tree<TS,BUD>& tree, LstringIterator& ltr, 
		    stack<Turtle>& turtle_stack, vector<N>& vav);
  int prune(Tree<TS,BUD>& t, vector<N>& vav);
  int prune(list<Axis<TS,BUD>*>& ls, 
	    typename list<Axis<TS,BUD>*>::iterator current, 
	    LstringIterator& ltr, vector<N>& vav);
  int prune(list<TreeCompartment<TS,BUD>*>& ls,
	    typename list<TreeCompartment<TS,BUD>*>::iterator current,
	    LstringIterator& ltr, vector<N>& vav);
 //root system part
 int rootSystem2Lstring(Tree<TS,BUD>& t, vector<N>& vav);
 int rootSystem2Lstring(list<RootAxis<Tree<TS,BUD> >*>& ls, 
			typename list<RootAxis<Tree<TS,BUD> > *>::iterator 
			current, 
			LstringIterator& ltr, vector<N>& vav);
 int rootSystem2Lstring(list<RootCompartment<Tree<TS,BUD> >*>& ls,
			typename list<RootCompartment<Tree<TS,BUD> >*>::iterator 
			current,
			LstringIterator& ltr, vector<N>& vav);
 int lstring2RootSystem(Tree<TS,BUD>& t, vector<N>& vav);
 int lstring2RootSystem(list<RootCompartment<Tree<TS,BUD> >*>& ls,
			typename list<RootCompartment<Tree<TS,BUD> >*>::iterator 
			current,
			Tree<TS,BUD>& tree,
			LstringIterator& ltr,
			stack<Turtle>& turtle_stack,vector<N>& vav);
 int lstring2RootSystem(list<RootAxis<Tree<TS,BUD> >*>& ls, 
			typename list<RootAxis<Tree<TS,BUD> >*>::iterator current, 
			Tree<TS,BUD>& tree, LstringIterator& ltr, 
			stack<Turtle>& turtle_stack, vector<N>& vav);

 private:
  Lstring mainstring;
  Lstring derivedstring;
};

template <class TS, class BUD, class N, class F>
inline void LSystem<TS,BUD,N,F>::start()
{
  Start();
  mainstring.Add(succstrg);
}

template <class TS, class BUD, class N, class F>
inline void LSystem<TS,BUD,N,F>::end()
{
  End();
}

template <class TS, class BUD, class N, class F>
inline void LSystem<TS,BUD,N,F>::endEach()
{
  EndEach();
}


template <class TS, class BUD, class N, class F>
inline int LSystem<TS,BUD,N,F>::derivationLength()
{
  return DerivationLength();
}

template <class TS, class BUD, class N, class F>
inline void LSystem<TS,BUD,N,F>::derive()
{
  StartEach();
  LstringIterator iterator(mainstring);
  derivedstring.Clear();

  while (!iterator.AtEnd())
  {
    CallerData cd;
    int i;
    //ProdCaller pCaller = FindMatch(iterator, cd);
    ProdCaller pCaller = ContextMatch(iterator, cd, i);
    if (NULL == pCaller)
    {
      iterator.AppendCurrent(succstrg);
      iterator++;
    }
    else
    {
      pCaller(&cd);
      iterator+=cd.Strct.Count();
    }
    derivedstring.Add(succstrg);
  }
  mainstring.Swap(derivedstring);
  EndEach();
}

template <class TS, class BUD, class N, class F>
inline void LSystem<TS,BUD,N,F>::print(bool arg)
{
  LstringIterator iterator(mainstring);
  CallerData caller_data;
  double arg1;
  while (!iterator.AtEnd()){
    const char* name = iterator.GetCurrentModuleName();
    cout << name;
    //fprintf(stdout,"%s",name);
    //print the argument value of f.
    if (arg = true){ 
      if (strcmp(name,"F") == 0||strcmp(name,"f") == 0 || 
	  strcmp(name,"Turn") == 0 || strcmp(name,"Pitch") == 0 ||
	  strcmp(name,"Roll") == 0 || strcmp(name,"HDir") == 0||
	  strcmp(name,"HUp") == 0){
	caller_data.Reset();
	caller_data.Strct.AddModuleAddr(iterator.Ptr());
	memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
	cout << "(" << arg1 << ")" << flush;
	//fprintf(stdout,"(%f)",arg1);
      }
      else{
	cout << "()" <<flush;
      }
    }
    iterator++;
  }
  cout << endl;
}

//Implementation of the conversion for the above ground part
#include <LSystemI.h>
#include <TreePruneI.h>
//Implementation of the conversion for the root system
#include <LSystemForRootsI.h>
