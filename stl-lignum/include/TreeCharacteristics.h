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
//Usage is with PropagateUp:
//   ViData data(1);
//   PropagateUp(tree,data,TreePhysiologyVigourIndex<TS,BUD>());
//Each segment will have its vigour index ('vi') updated.

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



  //The vigour index as in Nikinmaa et al. 2003 Tree Physiology
  //VI_j = (d_j/d_M)^2*VI_below
  //Usage is with PropagateUp:
  //   ViData data(1);
  //   PropagateUp(tree,data,TreePhysiologyVigourIndex<TS,BUD>());
  class ViData{
  public:
    ViData(double init = 1)
      :diameter_segment_above(0.0),vi_segment_below(init){}
    //Copy constructor, required by PropagateUp
    ViData(const ViData& vi_data)
      :diameter_segment_above(vi_data.diameter_segment_above),
       vi_segment_below(vi_data.vi_segment_below),
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
    ViData& diameterSegmentAbove(double d){
      diameter_segment_above = d;
      return *this;
    }
    double diameterSegmentAbove()const{
      return diameter_segment_above;
    }
  private:
    double diameter_segment_above;
    double vi_segment_below;
    list<double> segment_diameter_ls;
  };
    
  inline double ViData::operator()(double d)const
  {
    list<double>::const_iterator maxj = NULL;
    //maximum of the diameters
    maxj = max_element(segment_diameter_ls.begin(),segment_diameter_ls.end());
    //formula for vi from Nikinmaa et al 2003 Tree Physiology 
    //Note: if you write d/*maxj the '/*' would be the beginning of
    //a comment
    double vi = pow(d / *maxj,2.0)*vi_segment_below;
    return vi;
  }
  
  inline ViData& ViData::operator=(const ViData& vi_data)
  {
    diameter_segment_above = vi_data.diameter_segment_above;
    vi_segment_below = vi_data.vi_segment_below;
    segment_diameter_ls = vi_data.segment_diameter_ls;
    return *this;
  }
  
  template <class TS, class BUD>
  class TreePhysiologyVigourIndex{
  public:
    ViData& operator()(ViData& data, TreeCompartment<TS,BUD>* tc)const
    {
      //peek "the segment above" diameter
      if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
	list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(*axis);
	//If there is a second segment
	if (ls.size() > 3){
	  //Get the second segment: [TS_0,BP_1,TS_2,....,B] 
	  TS* ts = dynamic_cast<TS*>(*(ls.begin()+2));
	  if (ts != NULL){
	    double d = 2.0*GetValue(*ts,R);
	    //set the segment above diameter
	    data.diameterSegmentAbove(d);
	  }
	  //We should not get here!
	  else{
	    cout << "Error TreePhysiologyVigourIndex, no segment" << endl;
	  }
	}
	//no segment above
	else{
	  data.diameterSegmentAbove(0.0);
	}
      }
      //peek diameters of the segments in the branching point 
      else if (BranchingPoint<TS,BUD>* bp = 
	       dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
	typename list<Axis<TS,BUD>*>::iterator iter = NULL;
	for (iter = axis_ls.begin(); iter != ls.end(); iter++){
	  Axis<TS,BUD>* axis = *iter;
	  list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(*axis);
	  TS* ts = dynamic_cast<TS*>(*(ls.begin()));
	  if (ts != NULL){
	    double d = 2.0*GetValue(*ts,R);
	    data.addSegmentDiameter(d);
	  }
	}
	//add the 'segment above diameter' seen and set by axis
	data.addSegmentDiameter(data.segmentAboveDiameter());
	//now there are all segment diameters needed in 'data'
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
	data.addSegmentDiameter(2.0*GetValue(*ts,R));
	//ViData has diameters of all the segments we need to compare with
	//to compute the VI, comopute the VI
	double vi_value = data(2.0*GetValue(*ts,R));
	//Update VI
	SetValue(*ts,vi,vi_value);
	//This will be the new segment below VI
	data.viSegmentBelow(vi_value);
	//clear the list of diameters
	data.reset();
      }
      //We are done
      return data;
    }//funtor operator()
  };//class TreeCharacteristics 
}//namespace Lignum
#endif
