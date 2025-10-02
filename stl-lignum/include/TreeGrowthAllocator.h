/// \file TreeGrowthAllocator.h
/// \brief Photosynthates allocation 
#ifndef TREE_GROWTH_ALLOCATOR_H
#define TREE_GROWTH_ALLOCATOR_H
#include <Lignum.h>
namespace Lignum{
  ///\brief Growth allocation exception if \f$ P < M \f$.
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

  ///\brief Base class for photosynthates allocators
  ///\sa TreeGrowthAllocator TreeGrowthAllovatorPropagateUp
  template <class TS, class BUD>
  class TreeGrowthAllocatorBase{
  public: 
    TreeGrowthAllocatorBase(Tree<TS,BUD>& t)
      :tree(t),P(0.0),M(0.0){}
    ///\brief Collect net production, i.e. P-M
    void init();
    ///\brief Get photosynthesis
    ///\retval P Photosynthates
    ///\brief Get respiration
    ///\retval M Resoiration
    double getP()const{return P;}
    double getM()const{return M;}
    ///\brief Update availabe photosynthesis.
    ///
    ///This is done e.g.  if something is taken to carbon pool before allocation
    ///\retval Previous available photosynthates 
    double setP(double p){
      double old_p=P;
      P=p;
      return old_p;
    }
  protected:
    Tree<TS,BUD>& tree;///< Tree
    double P;///< Production of the tree
    double M;///< Respiration of the tree
  };

  

  ///\brief Photosynthates allocator
  ///
  ///TreeGrowthAllocator is intended to iterate the net photosynthates
  ///for coniferous and hardwood trees. The function operator is  called
  ///by some root finding algorithm for example Bisection:
  ///\code{.cc}
  ///TreeGrowthAllocator<TS,BUD,F1,F2> G(tree);
  ///Bisection(0,5,G);
  ///\endcode
  ///\tparam TS Tree segment
  ///\tparam BUD Bud
  ///\tparam F1 User defined functor to  adjust the segment lengths as the function  of lamda,
  ///\tparam F2 User defined functor to  calculate the  diameter growth induced by  the new
  ///segments  and foliage.
  ///\sa TreeGrowthAllocatorPropaGateUp
  template <class TS, class BUD, class F1, class F2>
  class TreeGrowthAllocator:
    public TreeGrowthAllocatorBase<TS,BUD>{
  public:
    TreeGrowthAllocator(Tree<TS,BUD>& t)
      :TreeGrowthAllocatorBase<TS,BUD>(t){}
    ///\brief Photosynthates allocation
    ///\param l The \f$ \lambda \f$ parameter to adjust segment lengths
    ///\return \f$ P-M-G \f$ where \f$ G = iW_s(l) + iW_{f_{\mathrm{new}}}(l) + iW_{r_{\mathrm{new}}}(l) \f$
    double operator()(double l)const;			       							
  };

  ///\brief Photosynthates allocator
  ///
  ///TreeGrowthAllocatorPropagateUp is intended as generic functors
  ///to iterate the net photosynthates for coniferous and hardwood trees.
  ///The function operator is  called by some root finding algorithm
  ///for example Bisection:
  ///\code{.cc}
  ///TreeGrowthAllocatorPropagateUp<TS,BUD,F1,F2,T> G(tree);
  ///Bisection(0,5,G);
  ///\endcode
  ///\tparam TS Tree segment
  ///\tparam BUD Bud
  ///\tparam F1 User defined functor to  adjust the segment lengths as the function  of lamda,
  ///\tparam F2 User defined functor to  calculate the  diameter growth induced by  the new
  ///segments  and foliage.
  ///\tparam T User defined data to pass with PropagatUp
  ///\sa TreeGrowthAllocator
  template <class TS, class BUD, class F1, class F2, class T>
  class TreeGrowthAllocatorPropagateUp:
    public TreeGrowthAllocatorBase<TS,BUD>{
  public:
    TreeGrowthAllocatorPropagateUp(Tree<TS,BUD>& t,const T& up1)
      :TreeGrowthAllocatorBase<TS,BUD>(t),up(up1){}
    ///\brief Photosynthates allocation
    ///\param l The \f$ \lambda \f$ parameter to adjust segment lengths
    ///\return \f$ P-M-G \f$ where \f$ G = iW_s(l) + iW_{f_{\mathrm{new}}}(l) + iW_{r_{\mathrm{new}}}(l) \f$
    double operator()(double l)const;
  private:
    const T up;
  };
  
  ///Collect  photosynthates and  respiration once befor
  ///allocation.
  ///\exception TreeGrowthAllocationException if P <= M
  template <class TS,class BUD>
  void TreeGrowthAllocatorBase<TS,BUD>::init()
  {
    P = GetValue(tree,TreeP);
    M =  GetValue(tree,TreeM);
    if (P-M <= 0.0)
      throw TreeGrowthAllocatorException(P,M);
  } 

  ///This functor is repeatedly  called by some root finding algorithm,
  ///e.g. Bisection. After the iteration, the segment lengths
  ///in the new segments allocate P-M=G (including the induced diameter
  ///and root  growth).  F1: set  the segment lengths with  lamda.  F2:
  ///calculate  the  effect  of  diameter  growth induced  by  the  new
  ///segments  and the  foliage.   The  root growth  is  assumed to  be
  ///propotional to the new foliage mass: Wrnew = LGPar*Wfnew.
  template  <class TS,class BUD,class F1,class F2>
  double TreeGrowthAllocator<TS,BUD,F1,F2>::operator()(double l)const
  {
    DiameterGrowthData data;
    
    //1.Elongate or shorten segment lengths
    ForEach(this->tree,F1(l));
    
    //2. Simulate  diameter  growth  and  collect  sapwood  and  foliage
    //masses.
    data = AccumulateDown(this->tree,data,F2());   
      
    //3. return P-M-G where G = iWs(l) + iWfnew(l) + iWrnew(l)
    //iWs = sapwood mass: new segments + thickening
    //iWfnew = new foliage
    //iWrnew = new roots = ar*iWfnew
    return (this->P - this->M - GetValue(data,DGWs) - GetValue(data,DGWfnew) 
	    - GetValue(this->tree,LGPar)* GetValue(data,DGWfnew));
  }

  ///As for TreeGrowthAllocator the functor is called by some iterative
  ///method, but instead of ForEach the  data of type T is passed up in
  ///the tree with PropagateUp
  template  <class TS,class BUD,class F1,class F2,class T>
  double TreeGrowthAllocatorPropagateUp<TS,BUD,F1,F2,T>::operator()(double l)const
  {
    DiameterGrowthData data;
    //Reinitialize the data to passed up in the tree
    T up_new = up;
    //1.Elongate or shorten segment lengths
    PropagateUp(this->tree,up_new,F1(l));
    
    //2. Simulate  diameter  growth  and  collect  sapwood  and  foliage
    //masses.
    data = AccumulateDown(this->tree,data,F2());   
      
    //3. return P-M-G where G = iWs(l) + iWfnew(l) + iWrnew(l)
    //iWs = sapwood mass: new segments + thickening
    //iWfnew = new foliage
    //iWrnew = new roots = ar*iWfnew
    return this->P - this->M - GetValue(data,DGWs) - GetValue(data,DGWfnew)- 
      GetValue(this->tree,LGPar)* GetValue(data,DGWfnew);

  }
  
}//namespace Lignum
#endif
