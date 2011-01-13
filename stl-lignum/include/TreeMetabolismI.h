#ifndef TREEMETABOLISMI_H
#define TREEMETABOLISMI_H

#include <TreeMetabolism.h>




namespace Lignum{
  
//PHOTOSYNTHESIS
template <class TS,class BUD>
void Tree<TS,BUD>::photosynthesis()
{

  //cout << "Design of LIGNUM gears towards the use of functors" <<endl
  //     << "Tree<TS,BUD>::photosynthesis() is depricated" << endl
  //     << "Consider the use of functors  TreePhotosynthesis and  SumTreePhotosynthesis" <<endl;

  //Have TreeCompartments to do photosynthesis
  ForEach(*this, TreePhotosynthesis<TS,BUD>());
  
  //... and then SUM photosynthetic rates of all segments and update trees P

  LGMdouble initPh = 0.0;
  LGMdouble sumPh;
  sumPh = Accumulate(*this, initPh, SumTreePhotosynthesis<TS,BUD>());
  SetValue(*this, TreeP, sumPh);
}



//RESPIRATION
template <class TS,class BUD>
void Tree<TS,BUD>::respiration()
{
  // cout << "Design of LIGNUM gears towards the use of functors" <<endl
  //      << "Tree<TS,BUD>::respiration() is depricated" << endl
  //      << "Consider the use of functors  TreeRespiration and  SumTreeRespiration" <<endl;
  //Have TreeCompartments to do photosynthesis
  ForEach(*this, TreeRespiration<TS,BUD>());
  
  //... and then SUM respiration rates of all segments and update tree M
  LGMdouble sumM = 0.0;

  sumM = Accumulate(*this, sumM, SumTreeRespiration<TS,BUD>());
  
  // Root respiration
  sumM += GetValue(*this,LGPmr)*GetValue(*this,TreeWr);
  SetValue(*this, TreeM, sumM);
}



} //closing namespace


#endif

 

























