#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <Lsystem.h>

SuccessorStorage succstrg;

void _Add(const void* pX, int size)
{
  succstrg.Add(pX, size);
}

class LSystem{
 public:
  void start();
  void derive();
  template <class TS, class BUD, class N, class F>
    int lstring2Lignum(Tree<TS,BUD>& t,int argnum = 0,...);
  template <class TS, class BUD, class N, class F>
    int lignum2Lstring(Tree<TS,BUD>& t,int argnum = 0,...);
 private:
  Lstring mainstring;
  Lstring derivedstring;
};

inline void LSystem::start()
{
  Start();
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

#endif
