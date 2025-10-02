/// \file Forest.h
/// \brief Experimental framework for multiple species forest not active
#ifndef FOREST_H
#define FOREST_H

#include <list>
#include <VTree.h>

using namespace std;

namespace Lignum{
  class Forest{
    friend list<VTree*>& GetCfTreeList(Forest& f){return f.p.first;}
    friend list<VTree*>& GetHwTreeList(Forest& f){return f.p.second;}
    friend void InsertCfTree(Forest& f,VTree& t);
    friend void InsertHwTree(Forest& f,VTree& t);
  private:
    pair<list<VTree*>,list<VTree*> > p;
  };


  inline void InsertCfTree(Forest& f,VTree& t)
    {
      f.p.first.push_back(&t);
    }

  inline void InsertHwTree(Forest& f,VTree& t)
    {
      f.p.second.push_back(&t);
    }

}//closing namepspace

#endif
