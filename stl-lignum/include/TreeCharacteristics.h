#ifndef TREE_CHARACTERISTICS_H
#define TREE_CHARACTERISTICS_H

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
  
}//namespace Lignum
#endif
