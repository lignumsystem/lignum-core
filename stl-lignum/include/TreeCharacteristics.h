#ifndef TREE_CHARACTERISTICS_H
#define TREE_CHARACTERISTICS_H

//The  file will contain  variety of  attributes describing  trees and
//forest stands. Currently implemented:
 
//Functor DiameterBreastHeight for for_each to compute Diameter Breast
//Height.  Use it implicitely by calling GetValue(tree,Dbh)

//AccumulateDown for Crown Base Diameter and Height is something like:
//  DCLData     dcl;
//  AccumulateDown(tree,dcl,AddBranchWf(),DiameterCrownBase<TS,BUD>())  
//DCLData  will  contain the crown base height and diameter.

//The Vigour Index as in Nikinmaa et al. 2003 Tree Physiology
//VI_j = (d_j/d_M)^2*VI_below
//Usage is: 
//    TreePhysiologyVigourIndex(tree);
//Each segment will have its vigour index ('vi') updated.
//The complexity is 2O(n). See  TreePhysiologyVigourIndex below.

//AccumulateDown for CollectCrownLimitData. DiameterCrownBase does not
//always produce  good results for  crown limit. CollectCrownLimitData
//produces a list of foliage masses and Qabs's in branches forking off
//from the branching points in the  main axis and a list of heights of
//those branching points.  Then one can print out those two lists, and
//the beauty is in the eyes of the beholder.  Usage is:
//CrownLimitData  cld;
//AccumulateDown(tree,cld,AddCrownLimitData(),CollectCrownLimitData<TS,BUD>());
//CrownLimitData will contain lists  of foliage masses and Qabs's and
//their  heights in  the crown.   Retrieve  the lists for printing  by
//calling  for example: 
//const   list<pair<double,double>  >&  p   =  cld.WfHList().
//pair.first is the height and pair.second its foliage mass.


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


  //Computing the  diameter at  the crown base  and the height  of the
  //crown base.  The definition  of the crown  (base) is simple:  If a
  //side branch  (axis) starting  from a branching  point in  the main
  //axis  has  segments  with  foliage,  the branch  is  part  of  the
  //crown. Not quite as the official scientific definition, but easier
  //to compute and  pretty much O.K. for Scots  pine.  The computation
  //of  the  crown  base  proceeds with  AccumulateDown  checking  the
  //foliage of  the side branches.   If there is foliage,  the segment
  //below the branching  point in the main axis  marks itself as crown
  //base   possibly   overriding   previous   value.   The   call   to
  //AccumulateDown is something like:
  //  DCLData     dcl;
  //  AccumulateDown(tree,dcl,AddBranchWf(),DiameterCrownBase<TS,BUD>())  
  //DCLData  will  contain the crown base height and diameter.
 
  class DCLData{
    friend class AddBranchWf;
  public:
    DCLData():DCL(0.0),BWf(0.0),HCB(0.0){}
    DCLData(const DCLData& dcl):
      DCL(dcl.DCL),BWf(dcl.BWf),HCB(dcl.HCB){}
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
  private: 
    double DCL;  //diameter at crown limit
    double BWf ; //folige mass in a branch
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
	    dcl.HCrownBase(GetPoint(*ts).getZ());
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

  //Helper functor for assigning max diameter of segments  connected to a branching point
  template<class TS,class BUD>
  class MaxSegmentDiameter{
  public:
    double operator()(const double& d1, const double& d2)const
    {
      //Choose the maximum of the two segment diameters 
      return  max(d1,d2);
    }
  };

  //Helper functor for assigning max diameter of segments  connected to a branching point
  template<class TS,class BUD>
  class SegmentDiameter{
  public:
    double& operator()(double& d,TreeCompartment<TS,BUD>* tc)const
    {
      //MaxSegmentDiameter has chosen 
      if (BranchingPoint<TS,BUD>* bp = 
	  dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
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


  //The vigour index as in Nikinmaa et al. 2003 Tree Physiology
  //VI_j = (d_j/d_M)^2*VI_below
  //Usage is with PropagateUp:
  //   ViData data(1);
  //   PropagateUp(tree,data,TPVigourIndex<TS,BUD>());
  class ViData{
  public:
    ViData(double init = 1)
      :vi_segment_below(init){}
    //Copy constructor, required by PropagateUp
    ViData(const ViData& vi_data)
      :vi_segment_below(vi_data.vi_segment_below),
       segment_diameter_ls(vi_data.segment_diameter_ls){}     
    //Assignment, required by PropagateUp
    ViData& operator=(const ViData& vi_data);    
    //Calculate the Vigour index 
    double operator()(double d)const;
    //reset the list of diameters
    void reset(){segment_diameter_ls.clear();}
    ViData& addSegmentDiameter(double d){
      segment_diameter_ls.push_back(d);
      return *this;
    }
    double viSegmentBelow()const{return  vi_segment_below;}
    ViData& viSegmentBelow(double vi){
      vi_segment_below = vi;
      return *this;
    }
  private:
    double vi_segment_below;
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
    //ALSO NOTE: the division will hit you hard if maxj is 0 or
    //a very small number. Probably resulting NaN.
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
  
  template <class TS, class BUD>
  class TPVigourIndex{
  public:
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


  //Interface to VigourIndex (VI) as in Nikinmaa et al 2003 Tree  Physiology   
  //paper.  The design  of LIGNUM hits back when  implementing the VI.
  //First,  AccumulateDown  segment   diameters  and  assign  in  each
  //branching  point the  maximum  of the  diameters  of the  segments
  //forking off from the branching  point and the segment above.  Then
  //PropagateUp   the  VI   according  to   its  formula.    Thus  the
  //computational  complexity  is  2O(n).    The  problem  is  that  a
  //branching point cannot see the segment above, only the segments in
  //the branches.   So two traversals are needed,  first assigning the
  //maximum of  the diameters (going from  tip of the  branches to the
  //base of the tree ) and  then actually computing the VI (going from
  //the base  to the  branch tips).  Perhaps  it would be  possible to
  //construct  an   algorithm  for  VI  with   single  traversal  only
  //(i.e. O(n) complexity) but I could not come up any straightforward
  //way of  doing it.  It  is the clarity versus  efficiency tradeoff,
  //where I chose clarity.
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
    double wf_bp;//collects  foliage  mass  in  an axis,  sums  up  in
		 //branching points.
    double qabs_bp;//collects Qabs  in an  axis, sums up  in branching
		   //points.
    list<pair<double,double> > wf_h_bp_ls;//list of the foliage masses
                                          //in  the  branches  forking
                                          //off from a branching point
                                          //in the  main axis, and the
                                          //heights of those branching
                                          //points: pair<h,Wf>
    list<pair<double,double> > dh_dwf_ls;//same as  wf_h_bp_ls but now
					 //the         list        has
					 //pair<dh,dWf/dh>          (in
					 //practice  dWf is Wf  and dh
					 //is the segment length)
    list<pair<double,double> > h_qabs_ls;//list  of pair<h,Qabs> in
					 //branching   points   (as
					 //above)
    list<pair<double,double> > dh_dqabs_ls;//same as wf_dh_dqabs_ls
					   //but  now the  list has
					   //pair<dh,dQabs/dh>
  }; 

  //Helper functor to add foliage masses and Qabs's in branching points  
  class AddCrownLimitData{
  public:
    CrownLimitData& operator()(CrownLimitData& data1,CrownLimitData& data2)const
    {
      data1.addWf(data2.Wf());
      data1.addQabs(data2.Qabs());
      return data1;
    }
  };

  //Collect Wf and Qabs branchwise in the main axis
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
