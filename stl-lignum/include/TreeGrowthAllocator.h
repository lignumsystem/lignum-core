#ifndef TREE_GROWTH_ALLOCATOR_H
#define TREE_GROWTH_ALLOCATOR_H
#include <Lignum.h>
namespace Lignum{
  //This exception is thrown from TreeGrowthAllocator::init if P < M.
  class TreeGrowthAllocatorException{
  public:
    TreeGrowthAllocatorException(double p, double m)
      :P(p),M(m){}
    double getP()const{return P;}
    double getM()const{return M;}
  private:
    double P;
    double M;
  };

  //TreeGrowthAllocator is  intended as  a generic functor  to iterate
  //the net  photosynthates for Cf and  Hw trees.  It is  based on the
  //experience  with LPineGrowthFunctor in  LPine and  Lig-Grobas. The
  //function operator  is called by  some root finding  algorithm, say
  //Bisection: TreeGrowthAllocator<T,F1,F2> G(tree); Bisection(0,5,G);
  //where the T is the tree,  F1 is the user defined functor to adjust
  //the  segment  lengths as  the  function of  lamda,  and  F2 is  to
  //calculate  the diameter  growth induced  by the  new  segments and
  //foliage.
  template <class TS, class BUD, class F1, class F2>
  class TreeGrowthAllocator{
  public: 
    TreeGrowthAllocator(Tree<TS,BUD>& t)
      :tree(t){}
    double operator()(double l);//The  function operator  called  by a
				//root        finding        function,
				//e.g.   Bisection   or   Zbrent,   to
				//allocate net photosynthates
    void init();
    double getP()const{return P;}
    double getM()const{return M;}
  private:
    Tree<TS,BUD>& tree;
    double P;//Production of the tree
    double M;//Respiration of the tree
  };


  //Collect  photosynthates and  respiration once  per  (and obviously
  //before) growth allocation. Throw excption if P < M
  template <class TS,class BUD,class F1,class F2>
  void TreeGrowthAllocator<TS,BUD,F1,F2>::init()
  {
    double p = 0.0;
    P = Accumulate(t,p,SumTreePhotosynthesis<TS,BUD>());
    double m = 0.0;
    M =  Accumulate(t,m,SumTreeRespiration<TS,BUD>());
    if (P-M < 0.0)
      throw TreeGrowthAllocatorException(P,M);
  } 

  //This functor is repeteadly  called by some root finding algorithm,
  //e.g. Bisection or Zbrent. After the iteration, the segment lengths
  //in the new segments allocate P-M=G (including the induced diameter
  //and root  growth).  F1: set  the segment lengths with  lamda.  F2:
  //calculate  the  effect  of  diameter  growth induced  by  the  new
  //segments  and the  foliage.   The  root growth  is  assumed to  be
  //propotional to the new foliage mass: Wrnew = LGPar*Wfnew.
  template  <class TS,class BUD,class F1,class F2>
  double TreeGrowthAllocator<TS,BUD,F1,F2>::operator()(double l)
  {
    DiameterGrowthData data;
    
    //1.Elongate or shorten segment lengths
    ForEach(tree,F1(l));
    
    //2. Simulate  diameter  growth  and  collect  sapwood  and  foliage
    //masses.
    data = AccumulateDown(tree,data,F2());   
  
    
    //3. return P-M-G where G = iWs(l) + iWfnew(l) + iWrnew(l)
    //iWs = sapwood mass: new segments + thickening
    //iWfnew = new foliage
    //iWrnew = new roots = ar*iWfnew
 
    return (P - M - GetValue(data,DGWs) - GetValue(data,DGWfnew) 
	    - GetValue(tree,LGPar)* GetValue(data,DGWfnew));
  }
}//namespace Lignum
#endif
