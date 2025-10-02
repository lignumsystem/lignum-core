/// \file TreeMetabolism.h
/// \brief Tree metabolism
///
/// Mostly deprecated functors based on methods in tree compartments.
/// Encouraging implementing functors that change attribute
/// values in tree compartments with SetValue and GetValue functions.
#ifndef TREEMETABOLISM_H
#define TREEMETABOLISM_H


#include <LGMdecl.h>
#include <LGMSymbols.h>
#include <TreeCompartment.h>


namespace Lignum{

  ///\brief Photosynthesis
  ///\deprecated TreeCompartment::photosynthsis deprecated
  template <class TS,class BUD>
  class TreePhotosynthesis
  {
  public:
    TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const{
      tc->photosynthesis();
      return tc;
    }
  };

  ///\brief Summation of photosynthates
  template <class TS, class BUD>
  class SumTreePhotosynthesis{
  public:
    LGMdouble operator () (LGMdouble& cumPh, TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* tts = dynamic_cast<TS*>(tc)){
	LGMdouble PP = GetValue(*tts, LGAP);
	cumPh += PP;
      }
      return cumPh;
    }
  };

  ///\brief Respiration
  ///\deprecated  TreeCompartment::respiration deprecated
  template <class TS,class BUD>
  class TreeRespiration{
  public:
    TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const{
      tc->respiration();
      return tc;
    }
  };
  
  ///\brief Summation of tree segment respiration
  template <class TS, class BUD>
  class SumTreeRespiration{
  public:
    LGMdouble operator () (LGMdouble& cumM, TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* tts = dynamic_cast<TS*>(tc))
	{
	  LGMdouble M_ts = GetValue(*tts, LGAM);
	  cumM += M_ts;
	}
      return cumM;
    }
  };

  ///\brief Increase age in tree compartments
  template <class TS, class BUD>
  class IncreaseAge{
  public:
    IncreaseAge(LGMdouble a = 1.0):age(a){}
    TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const
    {
      SetValue(*tc,LGAage,GetValue(*tc,LGAage)+age);
      return tc;
    }
  private:
    LGMdouble age;
  };
  

  ///\brief Aging processes in tree compartments
  ///\deprecated Use functors to implement application specific
  ///aging processes
  template <class TS, class BUD>
  class TreeAging{
  public:
    TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const
    {
      tc->aging();
      return tc;
    }
  };

  ////\brief Diameter growth
  ///\deprecated  Use functors to implement application specific
  ///diameter growth processes
  template <class TS, class BUD>
  class TreeDiameterGrowth{
  public:
     TcData& operator()(TcData& data,TreeCompartment<TS,BUD>* tc)const
    {
      data = tc->diameterGrowth(data);
      return data;
    }
  };
}

#endif

 

























