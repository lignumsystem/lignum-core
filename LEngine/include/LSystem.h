/// \file LSystem.h
/// \brief Application programming interface to L-systems.
///
///The  class  LSystem provides  programming  interface  to L-systems 
///by rewriting of  the language L that *lsystem.h*  implements.
///
///Note that neither *lsys.h* nor this  file  *LSystem.h*  are wrapped  with
/// \code{.cc}
/// #infdef
/// #define
/// 
/// #endif
/// \endcode
///directives to prevent multiple inclusions of the header files.
///This is because both *LSystem.h* and *lsystem.h* must be included several times,
///once  for each  species of the model implementation.
///
///Multiple  decalarations and definitions prevented by wrapping
///*LSystem.h* and *lsys.h* in namespaces.                             
 
#include <lsys.h>

///\brief Left and Right context search in L-system string
ProdCaller  ContextMatch(const LstringIterator& pos,CallerData& caller_data,int& prod);

///\brief The succstrg, the temporary  expanded string or 'storage'.
///The \p succstrg is common within a species, but it is cleared
///after each derivation so it does not prevent multiple individuals
///of the species to be modelled.
///\note The \p succstrg usage makes the L-systems evaluations strictly sequential.
SuccessorStorage succstrg;

///\brief Add new element to \p succstrg
///\param pX The new element
///\param size Size of the new element
void _Add(const void* pX, int size)
{
  succstrg.Add(pX, size);
}

///\brief Programing interface for L-system and Lignum tree structural development
///\tparam TS Tree segment type
///\tparam BUD Bud type
///\tparam N Enumeration type naming structure or variables  passing information between Lignum and L-system
///\tparam F Type for the structure or variables with the name in N 
template <class TS, class BUD, class N = LGMAD, class F=LGMdouble>
class LSystem{
 public:
  ///\brief Initialize L-system and evaluate Start axiom
 void start();
 ///\brief L-system derivation
 void derive();
 int derivationLength();
 ///\brief Evaluate End rule as a last step
 void end();
 ///\brief Evaluate EndEach rule after each LSystem::derive()
 void endEach();
 ///\brief Print L-system to s
 ///\param arg if *true* Print module arguments.
 void print(bool arg=false);
 ///\brief Update L-string with Lignum structure
 ///\param t Lignum tree
 ///\param argnum Number of variable arguments
 ///\param[in] ... Parameter values from Lignum to L-string
 int lignumToLstring(Tree<TS,BUD>& t,int argnum = 0,...);
 ///\brief lstringToLignum Update Lignum structure with L-string
 ///\param t Lignum tree 
 ///\param argnum Number of variable arguments
 ///\param[in] ... Parameter values from L-string to Lignum 
 int lstringToLignum(Tree<TS,BUD>& t,int argnum = 0,...);
 int rootSystemToLstring(Tree<TS,BUD>& t,int argnum = 0,...);
 int lstringToRootSystem(Tree<TS,BUD>& t,int argnum = 0,...);
 ///\brief Prune dead branches.
 ///
 ///An axis or branch is dead if  the   buds  area   dead
 ///and  none   of  its   segments  contain foliage.
 ///After  the  pruning  update  the structure  of  LIGNUM  to L-string.
 ///The algorithm is essentially the same as Lstring2Lignum.
 ///\param t Lignum tree
 ///\param argnum Number of variable arguments
 ///\param[in] ... Parameter values from L-string to Lignum
 ///\retval -1 Error
 ///\retval 0 Normal exit
 ///\post Lignum tree topology and L-string topology match
 int prune(Tree<TS,BUD>& t,int argnum = 0,...);
 ///\brief Prune tree from dead branches.
 ///
 ///As in prune(Tree&,int,...) but with AccumalateDown call 
 ///\tparam P Functor type for AccumulateDown
 ///\tparam I Initial value type for AcculateDown
 ///\param t Lignum tree
 ///\param p Functor for AccumulatDown
 ///\param init Initial value for \p p
 ///\param argnum Number of variable arguments
 ///\param[in] ... Parameter values fron L-string to Lignum
 ///\retval -1 Error
 ///\retval 0 Normal exit
 ///\pre AcumulateDown with \p p and \p init is called before prune(Tree&,int,...)
 ///\post Lignum tree topology and L-string topology match
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
 ///\brief Lignum tree conversion to L-string.
 ///
 ////Entry point to conversion
 ///\param t Lignum tree
 ///\param vav Variable argument list. Parameters to be passed from Lignum to L-string
 ///\retval -1 Error
 ///\retval 0 Normal exit
 int lignum2Lstring(Tree<TS,BUD>& t, vector<N>& vav);
 ///\brief Axis conversion to L-string
 ///\param ls Axis list
 ///\param current Current position in \p ls
 ///\param ltr Current position in the L-string
 ///\param vav Parameters to be passe from Lignum to L-string
 ///\retval -1 Error
 ///\retval 0  Normal exit
 int lignum2Lstring(list<Axis<TS,BUD>*>& ls, 
		    typename list<Axis<TS,BUD>*>::iterator current, 
		    LstringIterator& ltr, vector<N>& vav);
 ///\brief Tree comprtment list conversion to L-string
 ///\param ls Tree compartment list
 ///\param current Current position in \p ls
 ///\param ltr Current position in the L-string
 ///\param vav Parameters to be passe from Lignum to L-string
 ///\retval -1 Error
 ///\retval 0  Normal exit
 int lignum2Lstring(list<TreeCompartment<TS,BUD>*>& ls,
		    typename list<TreeCompartment<TS,BUD>*>::iterator current,
		    LstringIterator& ltr, vector<N>& vav);
 ///\brief L-string to Lignum tree conversion
 ///
 ///Entry point to conversion
 ///\param t Lignum tree
 ///\param vav Variable argument list. Parameters to be passed from Lignum to L-string
 ///\retval -1 Error
 ///\retval 0 Normal exit
 int lstring2Lignum(Tree<TS,BUD>& t, vector<N>& vav);
 ///\brief L-string to Tree compartment list conversion 
 ///\param ls Tree compartment list
 ///\param current Current position in \p ls
 ///\param tree Lignum tree
 ///\param ltr L-string iterator
 ///\param turtle_stack Stack of turtles for branches
 ///\param vav Parameters to be passe from Lignum to L-string
 ///\retval -1 Error
 ///\retval 0  Normal exit
 int lstring2Lignum(list<TreeCompartment<TS,BUD>*>& ls,
		    typename list<TreeCompartment<TS,BUD>*>::iterator current,
		    Tree<TS,BUD>& tree,
		    LstringIterator& ltr,
		    stack<Turtle>& turtle_stack,vector<N>& vav);
 ///\brief L-string to Axis list conversion 
 ///\param ls Tree compartment list
 ///\param current Current position in \p ls
 ///\param tree Lignum tree
 ///\param ltr L-string iterator
 ///\param turtle_stack Stack of turtles for branches
 ///\param vav Parameters to be passe from Lignum to L-string
 ///\retval -1 Error
 ///\retval 0  Normal exit
 int lstring2Lignum(list<Axis<TS,BUD>*>& ls, 
		    typename list<Axis<TS,BUD>*>::iterator current, 
		    Tree<TS,BUD>& tree, LstringIterator& ltr, 
		    stack<Turtle>& turtle_stack, vector<N>& vav);
  ///\brief Entry point to prune Lignum tree
  ///
  ///Get the main axis and with the user given data in \p vav
  ///start syncing Lignum and Lstring
  ///\param t Lignum tree
  ///\param vav Variable arguments for L-string
  ///\retval -1 Error
  ///\retval 0 Normal exit
  int prune(Tree<TS,BUD>& t, vector<N>& vav);
  ///\brief Axis list pruning
  ///\param ls Axis list
  ///\param current Iterator to current Axis
  ///\param ltr Iterator to current Axis in L-string
  ///\param vav Variable argument list
  ///\retval -1 Error
  ///\retval 0 Normal exit
  int prune(list<Axis<TS,BUD>*>& ls, 
	    typename list<Axis<TS,BUD>*>::iterator current, 
	    LstringIterator& ltr, vector<N>& vav);
  ///\brief Tree compartment list  pruning
  ///\param ls Tree compartment list
  ///\param current Iterator to current tree compartment
  ///\param ltr Iterator to current Axis in L-string
  ///\param vav Variable argument list
  ///\retval -1 Error
  ///\retval 0 Normal exit
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
  ///L-system string, status of the L-string after each derivation
  Lstring mainstring;
  ///Derived string, will be resetted after L-system derivation
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
    if (arg == true){ 
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
