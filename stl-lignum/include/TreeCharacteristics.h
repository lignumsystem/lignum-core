#ifndef TREE_CHARACTERISTICS_H
#define TREE_CHARACTERISTICS_H
/// \file TreeCharacteristics.h
/// \brief Functors and functions to collect descriptive tree data
///
///Currently implemented:
///
/// \arg \c DiameterBreastHeight Compute diameter at breast
///height. Use it implicitely by calling GetValue(tree,LGADbh).
///
/// \arg \c DiameterCrownBase Diameter crown base and crown base height.
/// \code{.cc}
///  DCLData dcl;
///  AccumulateDown(tree,dcl,AddBranchWf(),DiameterCrownBase<TS,BUD>())
/// \endcode
///DCLData  will  contain the crown base height and diameter.
///
/// \arg \c CollectCrownLimitData Functor \c DiameterCrownBase does not
///always produce  good results for crown limit. CollectCrownLimitData
///produces a list of foliage masses and Qabs valus in branches forking off
///from the branching points in the  main axis and a list of heights of
///those branching points. Usage is:
/// \code{.cc}
///  CrownLimitData  cld;
///  AccumulateDown(tree,cld,AddCrownLimitData(),CollectCrownLimitData<TS,BUD>());
/// \endcode
///CrownLimitData will contain list of branch foliage masses, Qabs values  and
///their  heights in the tree crown. Retrieve  the list for further analysis, for example:
/// \code{.cc}
///  const list<pair<double,double> >& p = cld.WfHList()
/// \endcode
/// \c pair.first is the height and \c pair.second its foliage mass.
///
/// \arg \c TreePhysiologyVigourIndex Vigour index \f$ \mathcal{V} \f$
/// comparing segment diameters connected to the same branching point
/// (Nikinmaa et al. 2003 Tree Physiology)
/// \f[
/// \mathcal{V}_\mathrm{d} = (d/\max d_i)^2 \times \mathcal{V}_\mathrm{below}
/// \f]
///Usage is:
/// \code{.cc}
///  TreePhysiologyVigourIndex(tree);
/// \endcode
///Each segment will have its vigour index \f$ \mathcal{V} \f$ updated.
///The algorithmic complexity is \f$2\mathcal{O}(n)\f$.
///
#include <cmath>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>

namespace Lignum{
  //Functor  returning the diameter  breast height  given the  list of
  //tree compartments 'tc' in the main axis.
  template <class TS, class BUD>
  class DiameterBreastHeight{
  public:
    pair<double,double>& operator()(pair<double,double>& d13,
				    TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* ts = dynamic_cast<TS*>(tc)){
	//segment above 1.3 meters. It is assumed the list is
	//traversed in reverse oder: for_each(ls.rbegin(),ls.rend(),dbh)
	if (GetPoint(*ts).getZ() >= 1.3){
	  //override previous value
	  d13.first = 2.0*GetValue(*ts,LGAR);
	  d13.second = 2.0*GetValue(*ts,LGARh);
	}
      }
      return d13;
    }
  };


  //\brief Computing the  diameter at  the crown base  and the height  of the
  //crown base.
  ///
  ///The crown base definition here is simple:  If a
  ///side branch  (axis) starting  from a branching  point in  the main
  ///axis  has  segments  with  foliage,  the branch  is  part  of  the
  ///crown.  The computation of  the  crown  base  proceeds with
  ///AccumulateDown  checking  the foliage of  the side branches.
  ///If there is foliage,  the segment below the branching  point
  ///in the main axis  marks itself as crown base   possibly
  ///overriding   previous   value.
  ///
  ///Usage:
  ///\code{.cc}
  /// DCLData     dcl;
  /// AccumulateDown(tree,dcl,AddBranchWf(),DiameterCrownBase<TS,BUD>());
  ///\endcode
  //DCLData  will  contain the crown base height and diameter.
  class DCLData{
    friend class AddBranchWf;
  public:
    DCLData():DCL(0.0),BWf(0.0),HCB(0.0),DHWCB(0.0){}
    DCLData(const DCLData& dcl):
      DCL(dcl.DCL),BWf(dcl.BWf),HCB(dcl.HCB),DHWCB(dcl.DHWCB){}
    void clear(){DCL=BWf=HCB=DHWCB=0.0;}
    double DCrownBase(){return DCL;}
    double HCrownBase(){return HCB;} 
    double DHWCrownBase() {return DHWCB;}
    void DCrownBase(double d){DCL = d;}
    void HCrownBase(double h){HCB = h;}
    void DHWCrownBase(double dhw) {DHWCB = dhw;}
    //helper methods to collect foliage in side branches
    double BranchWf(){return BWf;} 
    void BranchWf(double wf){BWf = wf;}
    void AddBranchWf(double wf){BWf += wf;}
    //Total, sapwood and heartwood areas at crown base
    double ACrownBase(){return PI_VALUE*pow(DCL/2.0,2.0);}
    double AHwCrownBase(){return PI_VALUE*pow(DHWCB/2.0,2.0);}
    double ASwCrownBase(){return ACrownBase() - AHwCrownBase();}
  private: 
    double DCL;  //diameter at crown limit
    double BWf; //folige mass in a branch
    double HCB;  //height of the crown base
    double DHWCB;  //Diameter of heartwood at crown base
  };

  class AddBranchWf{
  public:
    DCLData& operator()(DCLData& dcl1, DCLData& dcl2)const;
  };
  

  inline DCLData& AddBranchWf::operator()(DCLData& dcl1, DCLData& dcl2)const
  {
    dcl1.BWf += dcl2.BWf;
    return dcl1;
  }
 
 
  template <class TS, class BUD>
  class DiameterCrownBase{
  public:
    DCLData& operator()(DCLData& dcl, TreeCompartment<TS,BUD>* tc)const
    {
      //if segment
      if (TS* ts = dynamic_cast<TS*>(tc)){
	//main axis
	if (GetValue(*ts,LGAomega) == 1){
	  //if branches in the immediate branching point above have foliage
	  if (dcl.BranchWf() > 0.0){
	    //set the segment diameter to the diameter crown base
	    dcl.DCrownBase(2.0*GetValue(*ts,LGAR));
	    dcl.DHWCrownBase(2.0*GetValue(*ts,LGARh));
	    //set the segment height to the crown base
	    dcl.HCrownBase(GetPoint(*ts).getZ()+GetValue(*ts,LGAL));
	    //reset  foliage  so  if  the branches  in  the  immediate
	    //branching  point  below don't  have  foliage, this  will
	    //remain the diameter and height in the crown base.
	    dcl.BranchWf(0.0);
	  }
	}
	else{
	  //in side branches, collect foliage
	  dcl.AddBranchWf(GetValue(*ts,LGAWf)); 
	}
      }
      return dcl;
    }
  };

  ///\brief Functor to choose max diameter of segments connected to a branching point
  template<class TS,class BUD>
  class MaxSegmentDiameter{
  public:
    ///\brief Choose maximum of two segment diameters
    ///\param d1 Segment diameter
    ///\param d2 Segment diameter
    ///\return \f$ max(d1,d2) \f$
    ///\note \p MaxSegmentDiameter is called by AccumulateDown in each branching point before \p SegmentDiameter
    double operator()(const double& d1, const double& d2)const
    {
      //Choose the maximum of the two segment diameters 
      return  max(d1,d2);
    }
  };

  ///\brief Functor to assign maximum diameter of segments connected to a branching point
  template<class TS,class BUD>
  class SegmentDiameter{
  public:
    ///\brief Assign max segment diameter in a branching point
    ///\param d Maximum segment diameter connected to a branching point
    ///\param tc Tree compartment
    ///\retval d Maximum segment diameter
    ///\pre MaxSegmentDiameter is called in each branching point to chooose maximum diameter between tree segments
    ///\post Each branching point has maximum of segment diameters 
    double& operator()(double& d,TreeCompartment<TS,BUD>* tc)const
    {
      //MaxSegmentDiameter has chosen maximum diameter 
      if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	SetValue(*bp,LGAMaxD,d);
      }
      if (TS* ts = dynamic_cast<TS*>(tc)){
	//Get the diameter of the  segment an pass it to the branching
	//point below.  Do not  take the diameter  of a  newly created
	//segment
	if (GetValue(*ts,LGAage) > 0.0)
	  d = 2.0*GetValue(*ts,LGAR);
	else
	  d = 0.0;
      }
      return d;
    }
  };


  ///\brief Implement Vigour index \f$ \mathcal{V} \f$ formula as in Nikinmaa et al. 2003 Tree Physiology
  ///
  ///\f[ \mathcal{V}_\mathrm{d} = (d/\max d_i)^2 \times \mathcal{V}_\mathrm{below} \f]
  ///
  class ViData{
  public:
    ///\brief Constructor
    ///
    ///\param init Default initial value for \f$ V = 1\f$   
    ViData(double init = 1)
      :vi_segment_below(init){}
    ///\brief Copy constructor, required by PropagateUp
    ///\param vi_data ViData 
    ViData(const ViData& vi_data)
      :vi_segment_below(vi_data.vi_segment_below),
       segment_diameter_ls(vi_data.segment_diameter_ls){}     
    ///\brief Assignment, required by PropagateUp
    ///\param vi_data ViData
    ViData& operator=(const ViData& vi_data);    
    ///\brief Calculate the Vigour index
    ///\param d Diameter of the tree segment
    ///\retval Vigour index
    ///\pre Vigour index \p vi_segment_below calculated
    double operator()(double d)const;
    ///\brief Reset the list of diameters \p segment_diameter_ls
    void reset(){segment_diameter_ls.clear();}
    ///\brief Add segment diameter \p d to list of diameters 
    ViData& addSegmentDiameter(double d){
      segment_diameter_ls.push_back(d);
      return *this;
    }
    ///\brief Vigour index in segment below
    ///\retval vi_segment_below Vigout index value
    double viSegmentBelow()const{return  vi_segment_below;}
    ViData& viSegmentBelow(double vi){
      vi_segment_below = vi;
      return *this;
    }
  private:
    ///Vigor index in the segment below the branching point
    double vi_segment_below;
    ///List of segment diameters connected to the same branching point
    list<double> segment_diameter_ls; 
  };
    
  //VI as a function of diameter 'd'
  inline double ViData::operator()(double d)const
  {
    list<double>::const_iterator maxj;
    //maximum of the diameters
    maxj = max_element(segment_diameter_ls.begin(),segment_diameter_ls.end());
    //formula for vi from Nikinmaa et al 2003 Tree Physiology 
    //Note: if you write "d/*maxj"  the '/*' would be the beginning of
    //a comment!!
    //Small vigour index values may lead to problems (unrealistic small segments
    //not able to grow)
    double vi = 0.0;
    if (*maxj > R_EPSILON)
      vi = pow(d / *maxj,2.0)*vi_segment_below;
    else
      vi = vi_segment_below;
    return vi;
  }
  
  inline ViData& ViData::operator=(const ViData& vi_data)
  {
    vi_segment_below = vi_data.vi_segment_below;
    segment_diameter_ls = vi_data.segment_diameter_ls;
    return *this;
  }

  ///\brief Traverse tree with Lignum::PropagateUp and calculate Vigour index.
  ///
  ///In each branching point collect maximum segment diameter.
  ///In each tree segment calculate  Vigour index 
  template <class TS, class BUD>
  class TPVigourIndex{
  public:
    ///\brief Calculate Vigour index
    ///\param vi_data Vigour index calculator class collecting also necessary data
    ///\param tc Tree compartment
    ///\retval vi_data Vigor index calculator 
    ViData& operator()(ViData& vi_data, TreeCompartment<TS,BUD>* tc)const
    {
      if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	//clear the list of diameters
	vi_data.reset();
	//The maximum of segment diameters of segments forking 
	//off from this branching point and the segment above
	vi_data.addSegmentDiameter(GetValue(*bp,LGAMaxD));
	//Reset the MaxD!!
	SetValue(*bp,LGAMaxD,0.0);
      }
      //compute the VI for the segment
      else if (TS* ts = dynamic_cast<TS*>(tc)){
	if (GetValue(*ts,LGAage) > 0){
	  //special case (in the beginning) when there are no segment
	  //diameters in  the list: add the  segment to the  list so you
	  //compare the segment to itself at least, and get a meaningful
	  //result; by definition VI is [0,1] and also comparison to the
	  //segment itself is needed.  If  the diameter is twice it does
	  //not  matter  (more troublesome  to  explicitely program  the
	  //special case in the beginning)
	  vi_data.addSegmentDiameter(2.0*GetValue(*ts,LGAR));
	  //ViData has the max diameter of the segments we need to compare with
	  //to  compute the  VI (see  TreePhysiologyVigourIndex). Compute
	  //the VI.
	  double vi_value = vi_data(2.0*GetValue(*ts,LGAR));
	  //Update VI
	  SetValue(*ts,LGAvi,vi_value);
	  //This will be the new segment below VI
	  vi_data.viSegmentBelow(vi_value);
	}
	else{
	  //Newly  created segment  will get  its vigour  from segment
	  //below (length and diameter will be adjusted accordingly,
	  //say Lsegment = lambda*vi*Qin/Qmax)
	  SetValue(*ts,LGAvi,vi_data.viSegmentBelow());
	}
      }
      //We are done
      return vi_data;
    }//functor operator()
  };//class TPVigourIndex


  ///\brief Vigour index as in Nikinmaa et al 2003 Tree  Physiology.
  ///\f[
  ///\mathcal{V}_\mathrm{d} = (d/\max d_i)^2 \times \mathcal{V}_\mathrm{below}
  ///\f]
  ///First,  AccumulateDown  segment   diameters  and  assign  in  each
  ///branching  point the  maximum  of the  diameters  of the  segments
  ///forking off from the branching  point and the segment above.  Then
  ///PropagateUp   the  Vigour index   according  to   its  formula.
  //Tthe computational  complexity  is  \f$2O(n)\f$.
  ///
  ///Two traversals are needed. First, assigning the maximum of  the
  ///diameters (going from  tip of the  branches to the
  //base of the tree ) and  then actually computing the Vigour index
  ///(going from the base  to the  branch tips).
  template <class TS,class BUD>
  void TreePhysiologyVigourIndex(Tree<TS,BUD>& t)
  {
    double d = 0.0;
    AccumulateDown(t,d,MaxSegmentDiameter<TS,BUD>(),SegmentDiameter<TS,BUD>());
    ViData vi(1.0);
    PropagateUp(t,vi,TPVigourIndex<TS,BUD>());
  }

  class CrownLimitData{
  public:
    CrownLimitData():wf_bp(0.0),qabs_bp(0.0){}
    CrownLimitData(const CrownLimitData& data)
      :wf_bp(data.wf_bp),qabs_bp(data.qabs_bp),
       wf_h_bp_ls(data.wf_h_bp_ls),dh_dwf_ls(data.dh_dwf_ls),
       h_qabs_ls(data.h_qabs_ls),dh_dqabs_ls(data.dh_dqabs_ls){}
    CrownLimitData& operator=(const CrownLimitData& data)
    {
      wf_bp = data.wf_bp;
      qabs_bp = data.qabs_bp;
      wf_h_bp_ls = data.wf_h_bp_ls;
      dh_dwf_ls = data.dh_dwf_ls;
      h_qabs_ls = data.h_qabs_ls;
      dh_dqabs_ls = data.dh_dqabs_ls;
      return *this;
    }
    CrownLimitData& addWf(double wf)
    {
      wf_bp += wf; 
      return *this;
    }
    CrownLimitData& Wf(double wf)
    {
      wf_bp = wf; 
      return *this;
    }
    double Wf()const{return wf_bp;}

    CrownLimitData& addQabs(double qabs)
    {
      qabs_bp += qabs; 
      return *this;
    }
    CrownLimitData& Qabs(double qabs)
    {
      qabs_bp = qabs; 
      return *this;
    }
    double Qabs()const{return qabs_bp;}

    CrownLimitData& addWfH(const pair<double,double>& hwf)
    {
      wf_h_bp_ls.push_front(hwf);
      return *this;
    }
    const list<pair<double,double> >& WfHList()const{return wf_h_bp_ls;}
    
    CrownLimitData& adddHdWf(const pair<double,double>& dhdwf)
    {
      dh_dwf_ls.push_front(dhdwf);
      return *this;
    }
    const list<pair<double,double> >& dHdWfList()const{return dh_dwf_ls;}
    
    CrownLimitData& addHQabs(const pair<double,double>& hqabs)
    {
      h_qabs_ls.push_front(hqabs);
      return *this;
    }
    const list<pair<double,double> >& HQabsList()const{return h_qabs_ls;}
    
    CrownLimitData& adddHdQabs(const pair<double,double>& dhdqabs)
    {
      dh_dqabs_ls.push_front(dhdqabs);
      return *this;
    }
    const list<pair<double,double> >& dHdQabsList()const{return dh_dqabs_ls;}
  private:
    ///Collect  foliage  mass  in  an axis,  sums  up  in
    ///branching points.
    double wf_bp;
    ///Collect \c Qabs  in an  axis, sums up  in branching
    ///points.
    double qabs_bp;
    ///list of the foliage masses in  the  branches forking off from a
    ///branching point in the  main axis, and the heights of those
    ///branching points: pair<h,Wf>
    list<pair<double,double> > wf_h_bp_ls;
    ///Same as  \p wf_h_bp_ls but now the list has \p pair<dh,dWf/dh>.
    list<pair<double,double> > dh_dwf_ls;
    ///List  of \p pair<h,Qabs> in branching   points  
    list<pair<double,double> > h_qabs_ls;
    ///same as \p wf_dh_dqabs_ls but  now the  list has \p pair<dh,dQabs/dh>
    list<pair<double,double> > dh_dqabs_ls;
  }; 

  ///\brief Helper functor to add \c Wf and \c Qabs values in branching points  
  class AddCrownLimitData{
  public:
    CrownLimitData& operator()(CrownLimitData& data1,CrownLimitData& data2)const
    {
      data1.addWf(data2.Wf());
      data1.addQabs(data2.Qabs());
      return data1;
    }
  };

  ///\brief Collect \c Wf and \c Qabs branchwise in the main axis
  template <class TS, class BUD>
  class CollectCrownLimitData{
  public:
    CrownLimitData& operator()(CrownLimitData& data,TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* ts = dynamic_cast<TS*>(tc)){
	//main axis
	if (GetValue(*ts,LGAomega) == 1){
	  double wf = data.Wf();
	  double qabs = data.Qabs();
	  double z = GetEndPoint(*ts).getZ();
	  double dz = GetValue(*ts,LGAL);
	  //foliage collected  from the branches forking  off from the
	  //branching point  above, and  the height of  that branching
	  //point (is the end point of this segment)
	  data.addWfH(pair<double,double>(z,wf));
	  //the same as above but now, mathematically speaking, if you
	  //sum the foliage  massess over the height of  the tree, you
	  //will get the total foliage mass in the tree crown
	  data.adddHdWf(pair<double,double>(dz,wf/dz));
	  //collect also the absorbed radiation in a tree by branching
	  //points
	  data.addHQabs(pair<double,double>(z,qabs));
	  //the same as above but now, mathematically speaking, if you
	  //sum the Qabs's  over the height of the  tree, you will get
	  //the total Qabs  in the tree crown
	  data.adddHdQabs(pair<double,double>(dz,qabs/dz));
	  //Clear  foliage, so it  does not  add up  to foliage  to be
	  //collected from the branches below
	  data.Wf(0.0);
	  data.Qabs(0.0);
	}
	//in side branches, collect foliage
	else{
	  data.addWf(GetValue(*ts,LGAWf));
	  data.addQabs(GetValue(*ts,LGAQabs));
	}
      }  
      return data;
    }//functor operator()
  };//class CollectCrownLimitData
}//namespace Lignum
#endif
