
#include <lsystem.h>


ProdCaller  ContextMatch(const LstringIterator& pos,CallerData& caller_data,int& prod);

SuccessorStorage succstrg;

void _Add(const void* pX, int size)
{
  succstrg.Add(pX, size);
}

class LSystem{
 public:
  void start();
  void derive();
  int derivationLength();
  void end();
  template <class TS, class BUD, class N, class F>
    int lignum2Lstring(Tree<TS,BUD>& t,int argnum = 0,...);
  template <class TS, class BUD, class N, class F>
    int lstring2Lignum(Tree<TS,BUD>& t,int argnum = 0,...);
 protected:
  template <class TS, class BUD, class N, class F>
    int lignum2Lstring(Tree<TS,BUD>& t, vector<N>& vav);
  template <class TS, class BUD,class T,class F>
    int lignum2Lstring(list<Axis<TS,BUD>*>& ls, 
		       typename list<Axis<TS,BUD>*>::iterator current, 
		       LstringIterator& ltr, vector<T>& vav);
  template <class TS, class BUD, class T, class F>
    int lignum2Lstring(list<TreeCompartment<TS,BUD>*>& ls,
		       typename list<TreeCompartment<TS,BUD>*>::iterator current,
		       LstringIterator& ltr, vector<T>& vav);
  template <class TS, class BUD, class N, class F>
    int lstring2Lignum(Tree<TS,BUD>& t, vector<N>& vav);
  template <class TS, class BUD, class T, class F>
    int lstring2Lignum(list<TreeCompartment<TS,BUD>*>& ls,
		       typename list<TreeCompartment<TS,BUD>*>::iterator current,
		       Tree<TS,BUD>& tree,
		       LstringIterator& ltr,
		       stack<Turtle>& turtle_stack,vector<T>& vav);

  template <class TS, class BUD,class T,class F>
    int lstring2Lignum(list<Axis<TS,BUD>*>& ls, 
		       typename list<Axis<TS,BUD>*>::iterator current, 
		       Tree<TS,BUD>& tree, LstringIterator& ltr, 
		       stack<Turtle>& turtle_stack, vector<T>& vav);	       
 private:
  Lstring mainstring;
  Lstring derivedstring;
};


inline void LSystem::start()
{
  Start();
  mainstring.Add(succstrg);
}

inline void LSystem::end()
{
  End();
}

inline int LSystem::derivationLength()
{
  return DerivationLength();
}

inline void LSystem::derive()
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



#include <LSystemI.h>
