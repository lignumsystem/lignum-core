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

#include <cmath>
#include <list>
#include <algorithm>

namespace Lignum{
  //Functor  returning the diameter  breast height  given the  list of
  //tree compartments 'tc' in the main axis.
  template <class TS, class BUD>
  class DiameterBreastHeight{
  public:
    DiameterBreastHeight(double d = 0.0):d13(d){}
    double dbh(){return d13;}
    void operator()(TreeCompartment<TS,BUD>* tc)
    {
      if (TS* ts = dynamic_cast<TS*>(tc)){
	//segment above 1.3 meters. It is assumed the list is
	//traversed in reverse oder: for_each(ls.rbegin(),ls.rend(),dbh)
	if (GetPoint(*ts).getZ() >= 1.3){
	  //override previous value
	  d13 = 2.0*GetValue(*ts,R);
	}
      }
    }
  private:
    double& d13; //diameter at 1.3 m
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
    void DCrownBase(double d){DCL = d;}
    void HCrownBase(double h){HCB = h;} 
    //helper methods to collect foliage in side branches
    double BranchWf(){return BWf;} 
    void BranchWf(double wf){BWf = wf;}
    void AddBranchWf(double wf){BWf += wf;}
  private: 
    double DCL;  //diameter at crown limit
    double BWf ; //folige mass in a branch
    double HCB;  //height of the crown base
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
	if (GetValue(*ts,omega) == 1){
	  //if branches in the immediate branching point above have foliage
	  if (dcl.BranchWf() > 0.0){
	    //set the segment diameter to the diameter crown base
	    dcl.DCrownBase(2.0*GetValue(*ts,R));
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
	  dcl.AddBranchWf(GetValue(*ts,Wf)); 
	}
      }
      return dcl;
    }
  };


  template<class TS,class BUD>
  class MaxSegmentDiameter{
  public:
    double& operator()(double& d,TreeCompartment<TS,BUD>* tc)const
    {
      if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	//Update the maximum of segment diameters 
	SetValue(*bp,MaxD,max(GetValue(bp,MaxD),d));
      }
      return d;
    }
  };

  template<class TS,class BUD>
  class SegmentDiameter{
  public:
    double& operator()(double& d,TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* ts = dynamic_cast<TS*>(tc)){
	//Get the diameter of the segment an pass it to the 
	//branching point below
	d = 2.0*GetValue(*ts,R);
      }
      return d;
    }
  };


  //The vigour index as in Nikinmaa et al. 2003 Tree Physiology
  //VI_j = (d_j/d_M)^2*VI_below
  //Usage is with PropagateUp:
  //   ViData data(1);
  //   PropagateUp(tree,data,TreePhysiologyVigourIndex<TS,BUD>());
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
    ViData& viSegmentBelow(double vi){
      vi_segment_below = vi;
      return *this;
    }
  private:
    double vi_segment_below;
    list<double> segment_diameter_ls;
  };
    
  inline double ViData::operator()(double d)const
  {
    list<double>::const_iterator maxj = NULL;
    //maximum of the diameters
    maxj = max_element(segment_diameter_ls.begin(),segment_diameter_ls.end());
    //formula for vi from Nikinmaa et al 2003 Tree Physiology 
    //Note: if you write "d/*maxj"  the '/*' would be the beginning of
    //a comment!!
    double vi = pow(d / *maxj,2.0)*vi_segment_below;
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
	vi_data.addSegmentDiameter(GetValue(*bp,MaxD));
	//Reset the MaxD!!
	SetValue(*bp,MaxD,0.0);
      }
      //compute the VI for the segment
      else if (TS* ts = dynamic_cast<TS>(tc)){
	//special case (in the beginning) when there are no segment
	//diameters in  the list: add the  segment to the  list so you
	//compare the segment to itself at least, and get a meaningful
	//result; by definition VI is [0,1] and also comparison to the
	//segment itself is needed.  If  the diameter is twice it does
	//not  matter  (more troublesome  to  explicitely program  the
	//special case in the beginning)
	vi_data.addSegmentDiameter(2.0*GetValue(*ts,R));
	//ViData has the max diameter of the segments we need to compare with
	//to  compute the  VI (see  TreePhysiologyVigourIndex). Compute
	//the VI.
	double vi_value = vi_data(2.0*GetValue(*ts,R));
	//Update VI
	SetValue(*ts,vi,vi_value);
	//This will be the new segment below VI
	vi_data.viSegmentBelow(vi_value);
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

}//namespace Lignum
#endif
