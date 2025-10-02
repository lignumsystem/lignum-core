/// \file CfTreeSegment.h
/// \brief Coniferous tree segment
#ifndef CFTREESEGMENT_H
#define CFTREESEGMENT_H

#include <list>
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
#include <CfTreeFunctor.h>
#include <TreeSegment.h>

namespace Lignum{

  using namespace cxxadt;

  ///\brief Coniferous tree segment attributes 
  class CfTreeSegmentAttributes{
  public:
    CfTreeSegmentAttributes():
      Hf(0.0),P(0.0),Qin(0.0),Qabs(0.0),Rf(0.0),starm(0.0),Wf(0.0),Wf0(0.0) {}
    METER Hf;       ///<Foliage height
    LGMdouble P;    ///<Amount of photosynthesis (kg C) during time step
    LGMdouble Qin;  ///<Irradiance of incoming radiation (MJ/m2)
    LGMdouble Qabs; ///<Amount of absorbed radiation (MJ) (during time step)
    METER Rf;       ///<Radius to foliage limit
    LGMdouble sf;   ///<Specific  leaf area  m2/kgC.  Use  the  LGPsf as
		    ///<default     in    the     constructors.    Other
		    ///<implementations (e.g. sf= f(ip)) may follow)
    LGMdouble starm;///<Star mean for the coniferous segment
    KGC Wf;         ///<Foliage mass of the tree segment
    KGC Wf0;        ///<Initial foliage mass of the tree segment
  };

  ///\brief Sapwood area operations
  class CfData:public TcData{
  public:
    ///\brief Asssignment
    ///\param tcd CfData
    CfData& operator = (TcData&  tcd){
      CfData& cfdata = dynamic_cast<CfData&>(tcd);
      SetValue(*this,LGAAs,GetValue(cfdata,LGAAs)); 
      return *this;
    }
    ///\brief Add and assign
    ///\param tcd CfData
    CfData& operator += (TcData& tcd){
      CfData& cfdata = dynamic_cast<CfData&>(tcd);
      SetValue(*this,LGAAs,GetValue(*this,LGAAs)+GetValue(cfdata,LGAAs));
      return *this;
    }
    ///\brief Clear sapwood area
    void clear(){SetValue(*this,LGAAs,0.0);} 
  };

  ///\brief Coniferous tree segment
  template <class TS,class BUD=DefaultBud<TS> >
  class CfTreeSegment:public TreeSegment<TS,BUD>{
    ///\brief Get attribute value
    ///\param ts Coniferous tree segment
    ///\param name Attribute name
    ///\return Attribute value for \p name
    ///\sa Lignum::LGMAD enumeration names
    template <class TS1,class BUD1>
    friend LGMdouble GetValue(const CfTreeSegment<TS1,BUD1>& ts, const LGMAD name);
    template <class TS1,class BUD1>
    ///\brief Get attribute value
    ///\param ts Coniferous tree segment
    ///\param name Attribute name
    ///\param value Attribute value
    ///\return Previous attribute value for \p name
    ///\sa Lignum::LGMAD enumeration names
    friend LGMdouble SetValue(CfTreeSegment<TS1,BUD1>& ts, const LGMAD name,
			      const LGMdouble value);
  public:
    ///\brief Constructor
    ///
    ///Construct CfTreeSegment by   giving  all   needed   attributes
    ///and parameters explicitely in the constructor.
    ///\param p Position for segment base 
    ///\param d Direction
    ///\param go Gravelius order
    ///\param l Length
    ///\param r Radius
    ///\param rh Heartwood radius
    ///\param sf Specific leaf area
    ///\param af Foliage area
    ///\param nl Needle length
    ///\param na Needle angle
    ///\param t  Tree the tree segment belongs to
    ///\note Specific leaf area \f$ S_f = \frac{A_f}{W_f} \f$ where \f$ A_f \f$ leaf area and \f$ W_f \f$ foliage mass
    CfTreeSegment(const Point& p, const PositionVector& d, 
		  const LGMdouble go, const METER l, const METER r, 
		  const METER rh, const LGMdouble sf, const LGMdouble af, 
		  const LGMdouble nl, const LGMdouble na, Tree<TS,BUD>* t);
    ///\brief Constructor
    ///Construct CfTreeSegment using parameter values usually given in a configuration file Tree.txt
    ///\param p Position for segment base 
    ///\param d Direction
    ///\param go Gravelius order
    ///\param l Length
    ///\param r Radius
    ///\param rh Heartwood radius
    ///\param t  Tree the tree segment belongs to
    CfTreeSegment(const Point& p,const PositionVector& d,const LGMdouble go,const METER l,
		  const METER r,const METER rh,Tree<TS,BUD>* t);
    ///\brief Constructor
    ///\param t Tree the tree segment belongs to
    CfTreeSegment(Tree<TS,BUD>* t):TreeSegment<TS,BUD>(t) { }
    ///\brief Photosynthesis
    ///\deprecated Implement photosynthesis with functors 
    void photosynthesis();
    ///\brief Respiration
    ///\deprecated Implement respiration with functors
    void respiration();
    ///\brief Tree and tree segment aging
    ///\deprecated Implement aging with functors 
    void aging();
    ///\brief Diameter growth
    ///\deprecated Implement diameter growth with functors  
    TcData& diameterGrowth(TcData& data);
  private:
    CfTreeSegmentAttributes cftsa;///< Coniferous tree segment attributes
  };


}//close namespace Lignum

#include <CfTreeSegmentI.h>
#include <CfTreeSegmentMetabolismI.h>


#endif



