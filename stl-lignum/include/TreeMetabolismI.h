#ifndef TREEMETABOLISMI_H
#define TREEMETABOLISMI_H

#include <TreeMetabolism.h>




namespace Lignum{
  
//PHOTOSYBTHESIS
template <class TS,class BUD>
void Tree<TS,BUD>::photosynthesis()
{

  //Have TreeCompartments to do photosynthesis
  ForEach(*this, TreePhotosynthesis<TS,BUD>());
  
  //... and then SUM photosynthetic rates of all segments and update trees P

  LGMdouble initPh = 0.0;
  LGMdouble sumPh;
  sumPh = Accumulate(*this, initPh, SumTreePhotosynthesis<TS,BUD>());
  
  SetValue(*this, LGAP, sumPh);

}



//RESPIRATION
template <class TS,class BUD>
void Tree<TS,BUD>::respiration()
{
  //Have TreeCompartments to do photosynthesis
  ForEach(*this, TreeRespiration<TS,BUD>());
  
  //... and then SUM respiration rates of all segments and update tree M
  LGMdouble sumM = 0.0;

  sumM = Accumulate(*this, sumM, SumTreeRespiration<TS,BUD>());
  
  // Root respiration
  sumM += GetValue(*this,LGPmr)*GetValue(*this,LGAWr);

  SetValue(*this, LGAM, sumM);
}



} //closing namespace


#endif

 

























