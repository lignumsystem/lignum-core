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

  //TreeGrowthAllocator    and    TreeGrowthAllocatorPropagateUp   are
  //intended as generic functors to iterate the net photosynthates for
  //Cf  and  Hw  trees.   They   are  based  on  the  experience  with
  //LPineGrowthFunctor in LPine  and Lig-Grobas. The function operator
  //is  called   by  some  root  finding   algorithm,  say  Bisection:
  //TreeGrowthAllocator<TS,BUD,F1,F2> G(tree); Bisection(0,5,G); where
  //the TS and BUD are the segment and the bud, F1 is the user defined
  //functor to  adjust the segment  lengths as the function  of lamda,
  //and  F2 is to  calculate the  diameter growth  induced by  the new
  //segments  and foliage. TreeGrowthAllocatorPropaGateUp  is similar,
  //but  the  user  defined  data  is  passed  up  in  the  tree  with
  //PropagateUp in each iteration
  template <class TS, class BUD>
  class TreeGrowthAllocatorBase{
  public: 
    TreeGrowthAllocatorBase(Tree<TS,BUD>& t)
      :tree(t),P(0.0),M(0.0){}
    void init();
    double getP()const{return P;}
    double getM()const{return M;}
  protected:
    Tree<TS,BUD>& tree;
    double P;//Production of the tree
    double M;//Respiration of the tree
  };

  
  //The data of type T given by the user will be passed up in the tree
  //with PropagateUp
  template <class TS, class BUD, class F1, class F2>
  class TreeGrowthAllocator:
    public TreeGrowthAllocatorBase<TS,BUD>{
  public:
    TreeGrowthAllocator(Tree<TS,BUD>& t)
      :TreeGrowthAllocatorBase<TS,BUD>(t){}
    double operator()(double l);//The  function operator  called  by a
				//root        finding        function,
				//e.g.   Bisection   or   Zbrent,   to
				//allocate net photosynthates
  };
  
  //The data of type T given by the user will be passed up in the tree
  //with PropagateUp
  template <class TS, class BUD, class F1, class F2, class T>
  class TreeGrowthAllocatorPropagateUp:
    public TreeGrowthAllocatorBase<TS,BUD>{
  public:
    TreeGrowthAllocatorPropagateUp(Tree<TS,BUD>& t,const T& up1)
      :TreeGrowthAllocatorBase<TS,BUD>(t),up(up1){}
    double operator()(double l);
  private:
    const T up;
  };
  //Collect  photosynthates and  respiration once  per  (and obviously
  //before) growth allocation. Throw excption if P <= M
  template <class TS,class BUD>
  void TreeGrowthAllocatorBase<TS,BUD>::init()
  {
    P = GetValue(tree,TreeP);
    M =  GetValue(tree,TreeM);
    if (P-M <= 0.0)
      throw TreeGrowthAllocatorException(P,M);
  } 

  //This functor is repeatedly  called by some root finding algorithm,
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

  //As for TreeGrowthAllocator the functor is called by some iterative
  //method, but instead of ForEach the  data of type T is passed up in
  //the tree with PropagateUp
  template  <class TS,class BUD,class F1,class F2,class T>
  double TreeGrowthAllocatorPropagateUp<TS,BUD,F1,F2,T>::operator()(double l)
  {
    DiameterGrowthData data;
    //Reinitialize the data to passed up in the tree
    T up_new = up;
    //1.Elongate or shorten segment lengths
    PropagateUp(tree,up_new,F1(l));
    
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
