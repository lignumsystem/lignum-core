///   \file  LGMGrowthAllocator.h
///   \brief Allocator functors to implement \f$P-M-G=0\f$.
///   \section allocators Carbon allocator functors 
///   The  `LGMGrowthAllocator`  functor   implements  the  allocation  of
///   photosynthates iteratively, i.e it puts into practice the solution
///   of equation \f$P-M-G=0\f$ where
///   \f$G =  iW_s(\lambda) + iW_f(\lambda) + iW_r(\lambda)\f$
///   and \f$iW_s\f$ is the  new sapood, \f$iW_f\f$ new  foliage and
///   \f$iW_r\f$ new  roots.  The \f$\lambda\f$ parameter is
///   used to find the equilibrium of the carbon balance equation.
///
///   The user provides  two  funtors  ELONGATION  and  DIAMETER_INCREMENT.
///   The former elongates  the new segments  and the latter  calculates the
///   induced diameter  growth.  The  DATA collects necessary  data from
///   segments for the diameter growth.
///
///   The call of ELONGATION takes the \f$\lambda\f$ as the parameter (ELONGATION(\f$\lambda\f$))
///   The  call  of  DIAMETER_INCREMENT  by  AccumulateDown  requires  two
///   arguments, DATA and the current tree compartment. DIAMETER_INCREMENT
///   must  defdine two modes,  LGMALLOCATE and  LGMGROWTH.  In  the first
///   mode  during  the iteration  only  the  induced  diameter growth  is
///   determined  for  each segment  and  in  the  second mode  after  the
///   allocation also the dimensions for the segments are adjusted. One of
///   the two operating modes must be selected in the constructor.
///
///   DATA  must  implement  the  collection  of  \f$iW_s\f$  and  \f$iW_f\f$  in  the
///   tree. Also, the `+=` operator, i.e. add and assign, must be defined 
///   to sum  up at least new sapwood  mass and new foliage  mass in the
///   tree.  This operator is called by AccumulateDown at each branching
///   point.    DATA   must   implement   `GetValue(data,   LGAiWs)`   and
///   `SetValue(data, LGAiWs,value) `which return  and set the new sapwood
///   mass     (elongation    and    thickening)     respectively    and
///   `GetValue(data,LGAiWf)`  and `SetValue(data,LGAiWf)` which  return and
///   set the  new foliage  mass in the  tree respectively.   `LGAiWf` and
///   `LGAiWs` are defined  in *LGMSymbols.h*. Note that the  \f$iW_r\f$ is defined
///   as `LGPar*LGAiWf` in `LGMGrowthAllocator`.
///
///   DATA  can collect  other values  from the  tree and  implement other
///   activities  too.   To  inspect  and  debug  DATA  it  can  be  given
///   explicitely in  a LGMGrowthAllocator constructor  and retrieved with
///   `getData()`.  For  this DATA must  implement copy constructor  and the
///   `=` operator. If data contains only arithmetic types (integral types
///   or  floating  types) the  compiler  generated  copy constructor  and
///   assignment operator work properly (using the so called bitwise copy).
///
///   **Usage:** <br>
///   Preconditons  are that  the  tree  has photosynthesized  and
///   respired    and   these    two   values    are    retrievable   with
///   `GetValue(tree,TreeP)`  and `GetValue(tree,TreeM)`. Also  new structural
///   units  are created.  Then  one can  allocate  the photosynthates  by
///   executing the following schema using cxxadt::Bisection function in allocation
///   (i.e. using Bisection method to find a root of a function):
///   \verbatim
///        try{
///          DATA data;
///          LGMGrowthAllocator<TS,BUD,ELONGATION,DIAMETER_INCREMENT,DATA> G(tree,data);
///          Bisection(0.0,10.0,G,0.001);
///        }
///        catch(TreeGrowthAllocatorException e){
///        //The allocation failed, something can be done here
///        }
///        catch(BisectionBracketException e){
///        //Bisection could not 'bracket' the growth, i.e. it could not find
///        //P-M-G > 0 because most likely P-M-G < 0. Thus Bisection cannot find the
///        //root of a function. Something can be done here to recover, e.g. end simulation
///        //in a controlled way
///        }
///        DATA data;
///        //New segments have right dimensions. Adjust old segment dimensions 
///        AccumulateDown(pine1,data,DIAMETER_INCREMENT(LGMGROWTH));
///  \endverbatim
///   It is optional to wrap the allocation into try-catch calls but it is
///   an  effective way  to  introduce exception  handling. Furthemore, to
///   follow the iteration with Bisection one can call it as:
///  \verbatim
///        Bisection(0.0,10.0,G,0.001,true);
///  \endverbatim
///   that gives terminal output  of the execution. User defined arguments
///   for Bisection are:
///  \verbatim
///        0.0   The lower bound (lambda=0.0)
///        10.0  The upper bound (lambda=10.0)
///        G the LGMGrowthAllocator
///        0.001 The  accuracy, the   difference (distance)
///              between   two consecutive l values in allocion
///              iteration considered as equilibrium
///        true/false gives verbose output or not, default is false
///   \endverbatim
///   For a complete example see the project Lig-Crobas. \sa Bisection
///
///   The  allocation of  growth in  LIGNUM is  novel but  error prone.
///   This  implementation  is  the  last  one  in  a  long  historical
///   development.    Most    notably    we    recommend    that    the
///   DIAMETER_INCREMENT executes  in two different  modes, LGMALLOCATE
///   and LGMGROWTH.
///
///   The  allocation and the actual growth  can be two
///   separate  functors  but as  they  must  be  essentially the  same
///   algorithm  (growth mode  differs  only by  adjusting the  segment
///   dimensions) experience  has shown that they  must be 'physically'
///   close: if one changes the  other, one must remember to change the
///   other one too.
///
///   Finally,  there  is also  LGMGrowthAllocator2.  The second  one
///   takes user defined  add and asign operator that  can be used in
///   AccumulateDown(tree,data,AddAssign(),DiameterGrowth()).       
///   The instantiation is
///   \verbatim
///     LGMGrowthAllocator2<TS,BUD,ELONGATION,ADD_ASSIGN,DIAMETERGROWTH> G(tree,data,ADD_ASSIGN())
///   \endverbatim
///   Note the  ADD_ASSIGN() in the constructor, because  it may itself
///   have  constructor  arguments,  e.g.  ParametricCurve,  but  the
///   schema for usage is the same as for LGMGrowthAllocator.
///
///   Unfortunately (but  naturally) one cannot  overload names using
///   differences in template arguments  only, so two different class
///   names are required.

#ifndef LGMGROWTHALLOCATOR_H
#define LGMGROWTHALLOCATOR_H
#include <TreeCompartment.h>
namespace Lignum{
  /// Growth allocation mode
  enum LGMALLOCATORMODE {LGMALLOCATE,///< Allocation mode
			 LGMGROWTH ///< Growth mode: adjust segment dimensions 
  };
   
  template <class TS, class BUD> class Tree;

  ///   \brief The  LGMGrowthAllocator  functor   implements  the  allocation  of
  ///   photosynthates iteratively.
  ///
  ///   It puts into practice the solution
  ///   of equation P-M-G=0 where G =  iWs(l) + iWf(l) + iWr(l) and iWs is
  ///   the  new sapood,  iWf new  foliage and  iWr new  roots.  The l is
  ///   the parameter to find the equilibrium of the carbon balance equation.
  template <class TS,class BUD,class ELONGATION,class DIAMETER_INCREMENT, class DATA>
  class LGMGrowthAllocator{
  public:
    ///\param tree The tree
    LGMGrowthAllocator(Tree<TS,BUD>& tree)
      :t(tree),P(0.0),M(0.0){init();}
    ///\param tree The tree
    ///\param d The data used
    LGMGrowthAllocator(Tree<TS,BUD>& tree,DATA d)
      :t(tree),data(d),data_orig(d),P(0.0),M(0.0){init();}
    void init();
    DATA getData()const{return data;}
    double getP()const{return P;}
    double getM()const{return M;}
    double getL() const{return lambda;}
    ///\param l The lambda carbon balance parameter
    double operator()(double l) const;
  private:
    Tree<TS,BUD>& t;///< Tree the tree compartment belongs to
    mutable DATA data;///< Data needed in allocation of photosynthates
    DATA data_orig;
    double P;///< Photosynthates
    double M;///< Respiration, maintenance and growth
    mutable double lambda;///< The lambda in  G = iWs(l) + iWfnew(l) + iWrnew(l)
  };

  ///Initialize available photosynthates and respiration
  template <class TS,class BUD,class ELONGATION,class DIAMETER_INCREMENT, class DATA>
  void LGMGrowthAllocator<TS,BUD,ELONGATION,DIAMETER_INCREMENT,DATA>::init()
  {
    P = GetValue(t,TreeP);
    M = GetValue(t,TreeM);
  }

  ///This method, overloaded function operator, implements P-M-G=0 and will be repeateadly
  ///called by e.g. cxxadt::Bisection function
  template <class TS,class BUD,class ELONGATION,class DIAMETER_INCREMENT, class DATA>
  double LGMGrowthAllocator<TS,BUD,ELONGATION,DIAMETER_INCREMENT,DATA>::operator()(double l)const
  {
    
    ///\par Basic carbon allocation
    ///\snippet{lineno} LGMGrowthAllocator.h GAlloc
    ///\internal
    //[GAlloc]
    //Reset data!!!!
    DATA data = data_orig;
    //0.Save current value of lambda
    lambda = l;
    //1.Elongate or shorten segment lengths
    ForEach(t,ELONGATION(l));

    //2. Simulate  diameter  growth  and  collect  sapwood  and  foliage
    //masses.
    data = AccumulateDown(t,data,DIAMETER_INCREMENT(LGMALLOCATE));   
  
    //3. return P-M-G=0 where G = iWs(l) + iWfnew(l) + iWrnew(l)
    //iWs = sapwood mass: new segments + thickening
    //iWfnew = new foliage
    //iWrnew = new roots = ar*iWfnew
    return P - M - GetValue(data,LGAiWs) - GetValue(data,LGAiWf) - GetValue(t,LGPar)* GetValue(data,LGAiWf);
    //[GAlloc]
    ///\endinternal
  }
  

  /// \brief The  LGMGrowthAllocator2  functor also  implements  the  allocation  of
  /// photosynthates iteratively.
  ///
  ///It takes user defined  add and asign operator AddAssign that  can be used in
  ///AccumulateDown(tree,data,AddAssign(),DiameterGrowth()). Also a reduction term can be used.
  ///That is, the allocation is P-M-G-reduction=0
  ///\sa reduction
  ///\tparam TS Tree segment
  ///\tparam BUD Bud
  ///\tparam ELONGATION Functor type to set segment length for new segments 
  ///\tparam ADD_ASSIGN Functor type to pass diameter growth infomation down  in a tree
  ///\tparam DIAMTER_INCREMENT Functor type to model diameter increment (e.g. pipe model) in a segment
  ///\tparam DATA Data structure to pass information down in a tree necessary fro diamter growth
  template <class TS,class BUD,class ELONGATION,class ADD_ASSIGN,class DIAMETER_INCREMENT, class DATA>
  class LGMGrowthAllocator2{
  public:
    ///\param tree The tree
    LGMGrowthAllocator2(Tree<TS,BUD>& tree)
      :t(tree),P(0.0),M(0.0), reduction(0.0){init();}
    ///\param tree The tree
    ///\param d The data to be used
    ///\param functor The user defined functor for data instead of default '+='
    ///\param fgo1 Segment length as f(go)
    ///\param fip1 Segment length as f(ip)
    ///\param fgo2 Segment length as f(go) after growth mode change
    ///\param fip2 Segment length as f(ip) after growth mode change
    LGMGrowthAllocator2(Tree<TS,BUD>& tree,DATA d, ADD_ASSIGN functor)
      :t(tree),data(d),data_orig(d),f(functor),P(0.0), M(0.0), reduction(0.0){init();}
    ///\param tree The tree
    ///\param d The data to be used
    ///\param functor The user defined functor for data instead of default '+='
    ///\param red0 The value for reduction
    LGMGrowthAllocator2(Tree<TS,BUD>& tree,DATA d, ADD_ASSIGN functor, const double red0)
      :t(tree),data(d),data_orig(d),f(functor),P(0.0), M(0.0), reduction(red0) {init();}
    void init();
    DATA getData()const{return data;}
    double getP()const{return P;}
    double getM()const{return M;}
    double getL() const{return lambda;}
    ///Tree growth allocator functor.
    ///\param L The lambda, \f$\lambda\f$, carbon balance parameter
    ///\retval Net photosynthates allocated to growth: P-M-G-R, where R is the reduction.
    ///\note Return value can be negative. \sa LGMGrowthAllocator2::reduction
    double operator()(double L) const;
  private:
    Tree<TS,BUD>& t; ///< Tree the tree compartment belongs to 
    mutable DATA data;///< Data passed down needed in allocation
    DATA data_orig;///< Remember the original data 
    ADD_ASSIGN f; ///< Functor manipulating data needed in allocation 
    double P;///< Available photosynthates
    double M;///< Respiration, growth and maintenance
    mutable double lambda;///< The lambda in  G = iWs(l) + iWfnew(l) + iWrnew(l)
    double reduction;///< A reduction factor R that can reduce available growth resource, that is, P-M-R=G
                     ///< Default value 0.
  };

  ///Initialize available photosynthates and respiration
  template <class TS,class BUD,class ELONGATION,class ADD_ASSIGN,class DIAMETER_INCREMENT, class DATA>
  void LGMGrowthAllocator2<TS,BUD,ELONGATION,ADD_ASSIGN,DIAMETER_INCREMENT,DATA>::init()
  {
    P = GetValue(t,TreeP);
    M = GetValue(t,TreeM);
  }

  //This method, overloaded function operator, implements P-M-G-reduction=0
  template <class TS,class BUD,class ELONGATION,class ADD_ASSIGN,class DIAMETER_INCREMENT, class DATA>
  double LGMGrowthAllocator2<TS,BUD,ELONGATION,ADD_ASSIGN,DIAMETER_INCREMENT,DATA>::operator()(double l)const
  {
    ///\par Carbon allocation with reduction
    ///\snippet{lineno} LGMGrowthAllocator.h GAlloc2
    ///\internal
    //[GAlloc2]
    //Reset data!!!!
    DATA data = data_orig;
    //0.Save current value of lambda
    lambda = l;
    //1.Elongate or shorten segment lengths
    ForEach(t,ELONGATION(l));

    //2. Simulate  diameter  growth  and  collect  sapwood  and  foliage
    //masses.
    data = AccumulateDown(t,data,f,DIAMETER_INCREMENT(LGMALLOCATE));   
  
    //3. return P-M-G=0 where G = iWs(l) + iWfnew(l) + iWrnew(l)
    //iWs = sapwood mass: new segments + thickening
    //iWfnew = new foliage
    //iWrnew = new roots = ar*iWfnew 
    return P - M - GetValue(data,LGAiWs) - GetValue(data,LGAiWf) - GetValue(t,LGPar)* GetValue(data,LGAiWf)
      - reduction;
    //[GAlloc2]
    ///\endinternal
  }

  
  ///Here is LGMGrowthAllocator3 that realizes allocation to fine- and coarse roots
  ///according to ~/Riston-D/E/LIGNUM/SSCS/Tuomo/LIGNUM-juuret/Lignum-roots.tex
  ///Now the equation is: P-M-G=0 where G =  iWs(l) + iWf(l) + iWfr(l) + Wfr_senecence + 
  /// iWcr(l) + Wcr_senecence
  template <class TS,class BUD,class ELONGATION,class ADD_ASSIGN,class DIAMETER_INCREMENT, class DATA>
  class LGMGrowthAllocator3{
  public:
    LGMGrowthAllocator3(Tree<TS,BUD>& tree)
      :t(tree),P(0.0),M(0.0){init();}
    LGMGrowthAllocator3(Tree<TS,BUD>& tree,DATA d, ADD_ASSIGN functor)
      :t(tree),data(d),data_orig(d),f(functor),P(0.0),M(0.0){init();}
    void init();
    DATA getData()const{return data;}
    double getP()const{return P;}
    double getM()const{return M;}
    double getL() const{return lambda;}
    double operator()(double l) const;
  private:
    Tree<TS,BUD>& t;///< The tree tree compartment belongs to
    mutable DATA data;///< Data passwd down in a tree needed in allocation of photosynthates
    DATA data_orig;///< Original data
    ADD_ASSIGN f;///< The operator on data instead of default '+=' operator
    double P;///<Available photosynthates
    double M;///<Respiration, maintenance and growth 
    mutable double lambda;///<The lambda in  G = iWs(l) + iWfnew(l) + iWrnew(l)
  };

  ///Initialize available photosynthates and respiration
  template <class TS,class BUD,class ELONGATION,class ADD_ASSIGN,class DIAMETER_INCREMENT, class DATA>
  void LGMGrowthAllocator3<TS,BUD,ELONGATION,ADD_ASSIGN,DIAMETER_INCREMENT,DATA>::init()
  {
    P = GetValue(t,TreeP);
    M = GetValue(t,TreeM);
  }

  ///This method, overloaded function operator, implements P-M-G=0
  template <class TS,class BUD,class ELONGATION,class ADD_ASSIGN,class DIAMETER_INCREMENT, class DATA>
  double LGMGrowthAllocator3<TS,BUD,ELONGATION,ADD_ASSIGN,DIAMETER_INCREMENT,DATA>::operator()(double l)const
  {
    //Reset data!!!!
    DATA data = data_orig;
    //0.Save current value of lambda
    lambda = l;
    //1.Elongate or shorten segment lengths
    ForEach(t,ELONGATION(l));

    //2. Simulate  diameter  growth  and  collect  sapwood  and  foliage
    //masses.
    data = AccumulateDown(t,data,f,DIAMETER_INCREMENT(LGMALLOCATE));   
  
    //3. return P-M-G=0 where G = iWs(l) + iWfnew(l) + iWrnew(l)
    //iWs = sapwood mass: new segments + thickening
    //iWfnew = new foliage
    //iWrnew = new roots = ar*iWfnew
 
    //return P - M - GetValue(data,LGAiWs) - GetValue(data,LGAiWf) - GetValue(t,LGPar)* GetValue(data,LGAiWf);

    Axis<TS,BUD>& axis = GetAxis(t);
    TreeSegment<TS, BUD>* ts = GetFirstTreeSegment(axis);
    LGMdouble Rh = GetValue(*ts, LGARh);
    LGMdouble As = GetValue(data, LGAAs);
    LGMdouble Rnew = sqrt(As/PI_VALUE+Rh*Rh);
    LGMdouble Rold = GetValue(*ts, LGAR);
    Rnew = max(Rnew,Rold);
    LGMdouble Wcr = 170.0*pow(Rold,2.4);
    LGMdouble sWcr = 0.018*Wcr;
    LGMdouble iWcr = 170.0*pow(Rnew,2.4)-Wcr;
    LGMdouble iWfr= GetValue(t,LGPar)* GetValue(data,LGAiWf);
    //LGMdouble Wf = 100.0*PI_VALUE*Rold*Rold;  //This is an approximation
    LGMdouble Wf = GetValue(data, DGWf);
    LGMdouble sWfr = 0.5*GetValue(t,LGPar)*Wf;


    return P - M - GetValue(data,LGAiWs) - GetValue(data,LGAiWf) - iWcr - sWcr - iWfr - sWfr;

 
  }


}
#endif
