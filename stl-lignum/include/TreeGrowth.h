#ifndef TREEGROWTH_H
#define TREEGROWTH_H





#include <string>
#include <Tree.h>

// WrapStructuralgrowth takes care that the trees consisting of
// HwTreeSegments and CfTreeSegments ae handled correctly (these two
// cases are wrapped into)

template <class F, class TS, class BUD>
class WrapGrowth {
public:
  WrapGrowth(); //No functions from file
  WrapGrowth(std::string sbud, std::string sdoi); //buf function and
  WrapGrowth(ParametricCurve sbud, ParametricCurve sdoi);
  
  
  //degree of interaction functions from files
  bool operator() (Tree<TS, BUD>& tree);
 private:
  F growth_functor;
  ParametricCurve bud_fun, doi_fun; 
};





//This functor GrowthOfHwTree evaluates growth of tree consisting of
//HwTreeSegments



//This functor GrowthOfPineTree evaluates growth of tree consisting of
//CfTreeSegments
template <class TS, class BUD>
class GrowthOfCfTree {
public:
  bool operator()(Tree<TS,BUD>& tree);

  void setBud_fun(ParametricCurve& bud_fun_in) { bud_fun = bud_fun_in; }
  void setDoi_fun(ParametricCurve& doi_fun_in) { doi_fun = doi_fun_in; }
  ParametricCurve bud_fun;
  ParametricCurve doi_fun;
};


//This functor GrowthOfPineTree evaluates growth of tree consisting of
//CfTreeSegments
template <class TS, class BUD>
class GrowthOfPineTree 
{
public:
  bool operator()(Tree<TS,BUD>& tree);
  GrowthOfPineTree();
  
  void setBud_fun(ParametricCurve& bud_fun_in) { bud_fun = bud_fun_in; }
  void setDoi_fun(ParametricCurve& doi_fun_in) { doi_fun = doi_fun_in; }
  ParametricCurve bud_fun;
  ParametricCurve doi_fun;
};


//This functor GrowthOfHwTree evaluates growth of tree consisting of
//HwTreeSegments
template <class TS, class BUD>
class GrowthOfHwTree
{
public:
	bool operator()(Tree<TS,BUD>& tree);
	GrowthOfHwTree() {};
	
	void setBud_fun(ParametricCurve& bud_fun_in) { bud_fun = bud_fun_in; }
	void setDoi_fun(ParametricCurve& doi_fun_in) { doi_fun = doi_fun_in; }
//	void setNoL_fun(ParametricCurve& fun_in) { number_of_leaves = fun_in; }
	ParametricCurve bud_fun;
	ParametricCurve doi_fun;
//	ParametricCurve number_of_leaves_fun;
};


//This functor GrowthOfHwTree evaluates growth of tree consisting of
//HwTreeSegments
template <class TS, class BUD>
class GrowthOfWhiteBirch
{
public:
	bool operator()(Tree<TS,BUD>& tree);
	GrowthOfWhiteBirch() {};
	

};




template <class TS, class BUD>
void StructuralPineGrowth(Axis<TS,BUD> &tree, const ParametricCurve& bud_fun, TreeSegment<TS,BUD> *treesegment = NULL);



template <class TS, class BUD>
void StructuralHwTreeGrowth(Axis<TS,BUD> &ax, const ParametricCurve& bud_fun);

//Evaluate deltavariables before growth
template <class TS,class BUD>
class FoliageLossOfPineTree //: public AdaptableTCFunction<TS,BUD> 
{
public:
	FoliageLossOfPineTree(ParametricCurve d) { fol_mor = d; }
	TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
	ParametricCurve fol_mor;
};





template <class TS,class BUD>
class CollectNewHwFoliageMass
{ 
public:
	LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
};



template <class TS,class BUD>
class CollectNewCfFoliageMass
{ 
public:
	LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
};



class MotherInfo
{
public:
	LGMdouble Qin;
	LGMdouble vi;
	LGMdouble B;
};




template <class TS,class BUD>
class AddWhiteBirchSegments
{ 
public:
	MotherInfo& operator()(MotherInfo& mi, TreeCompartment<TS,BUD>* tc)const;

};




template <class TS,class BUD>
class AddSugarMapleSegments
{ 
public:
	MotherInfo& operator()(MotherInfo& mi, TreeCompartment<TS,BUD>* tc)const;
	ParametricCurve bud_fun;
};


template <class TS, class BUD>
Axis<TS,BUD>& RemoveNewComparments(Axis<TS,BUD> &axis);


#include <TreeGrowthI.h>

#endif
































