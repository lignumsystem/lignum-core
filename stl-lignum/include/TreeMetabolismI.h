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
  
  LGMdouble nit = GetValue(*this, nitroLeaves);
  sumPh = sumPh * tf.nitroMaxPhotosynthesis(nit);

  SetValue(*this, LGAP, sumPh);

}



//RESPIRATION
template <class TS,class BUD>
void Tree<TS,BUD>::respiration()
{
	//Have TreeCompartments to do photosynthesis
	ForEach(*this, TreeRespiration<TS,BUD>());


	//... and then SUM respiration rates of all segments and update tree M
	LGMdouble initM = 0.0;
	LGMdouble sumM;
	sumM = Accumulate(*this, initM, SumTreeRespiration<TS,BUD>());


	LGMdouble nit = GetValue(*this, nitroLeaves);
	sumM = sumM * tf.nitroMaxPhotosynthesis(nit);

	// Root respiration
	LGMdouble nit_roots = GetValue(*this, nitroRoots);
    sumM += GetValue(*this,mr)*GetValue(*this,LGAWr) * this->tf.nitroRespiration(nit_roots);

  
	SetValue(*this, LGAM, sumM);
}



} //closing namespace


#endif

 

























