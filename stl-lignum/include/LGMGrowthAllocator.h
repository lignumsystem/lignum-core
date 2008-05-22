#ifndef LGMGROWTHALLOCATOR_H
#define LGMGROWTHALLOCATOR_H
namespace Lignum{
//   The  LGMGrowthAllocator  functor   implements  the  allocation  of
//   photosynthates iteratively, i.e it puts into practice the solution
//   of equation P-M-G=0 where G =  iWs(l) + iWf(l) + iWr(l) and iWs is
//   the  new sapood,  iWf new  foliage and  iWr new  roots.   The user
//   provides  two  funtors  ELONGATION  and  DIAMETER_INCREMENT.   The
//   former elongates  the new segments  and the latter  calculates the
//   induced diameter  growth.  The  DATA collects necessary  data from
//   segments for the diameter growth.

//   The call of ELONGATION takes one parameter l (i.e. ELONGATION(l)).

//   The  call  of  DIAMETER_INCREMENT  by  AccumulateDown  requires  two
//   arguments, DATA and the current tree compartment. DIAMETER_INCREMENT
//   must  defdine two modes,  LGMALLOCATE and  LGMGROWTH.  In  the first
//   mode  during  the iteration  only  the  induced  diameter growth  is
//   determined  for  each segment  and  in  the  second mode  after  the
//   allocation also the dimensions for the segments are adjusted. One of
//   the two operating modes must be selected in the constructor.
 
//   DATA  must  implement  the  collection  if  iWs  and  iWf  in  the
//   tree. Also, the '+=' operator must be defined i.e.  add and assign
//   to sum  up at least new sapwood  mass and new foliage  mass in the
//   tree.  This operator is called by AccumulateDown at each branching
//   point.    DATA   must   implement   GetValue(data,   LGAiWs)   and
//   SetValue(data, LGAiWs,value) which return  and set the new sapwood
//   mass     (elongation    and    thickening)     respectively    and
//   GetValue(data,LGAiWf)  and SetValue(data,LGAiWf) which  return and
//   set the  new foliage  mass in the  tree respectively.   LGAiWf and
//   LGAiWs are defined  in LGMSymbols.h. Note that the  iWr is defined
//   as LGPar*iWf in LGMGrowthAllocator.

//   DATA  can collect  other values  from the  tree and  implement other
//   activities  too.   To  inspect  and  debug  DATA  it  can  be  given
//   explicitely in  a LGMGrowthAllocator constructor  and retrieved with
//   getData().  For  this DATA must  implement copy constructor  and the
//   '=' operator. If data contains only arithmetic types (integral types
//   or  floating  types) the  compiler  generated  copy constructor  and
//   assignment operator work properly (using the so called bitwise copy).

//   Usage:  Preconditons  are that  the  tree  has photosynthesized  and
//   respired    and   these    two   values    are    retrievable   with
//   GetValue(tree,TreeP)  and GetValue(tree,TreeM). Also  new structural
//   units  are created.  Then  one can  allocate  the photosynthates  by
//   executing the following schema:
//        try{
//          DATA data;
//          LGMGrowthAllocator<TS,BUD,ELONGATION,DIAMETER_INCREMENT,DATA> G(tree,data);
//          Bisection(0.0,10.0,G,0.001);
//        }
//        catch(TreeGrowthAllocatorException e){
//        //The allocation failed, something can be done here
//        }
//        catch(BisectionBracketException e){
//        //Bisection could not 'bracket' the growth, i.e. it could not find
//        //P-M-G > 0 and P-M-G < 0, something can be done here
//        }
//        DATA data;
//        AccumulateDown(pine1,data,DIAMETER_INCREMENT(LGMGROWTH));

//   It is optional to wrap the allocation into try-catch calls but it is
//   an  effective way  to  introduce exception  handling. Furthemore, to
//   follow the iteration with Bisection one can call it as
//        Bisection(0.0,10.0,G,0.001,true);
//   that gives terminal output  of the execution. User defined arguments
//   for Bisection are:
//                  0.0 the lower bound (lambda=0.0)
//                 10.0 the upper bound (lambda=10.0)
//                    G the LGMGrowthAllocator
//                0.001   the  accuracy,   the   distance  between   two
//                        consecutive lambda values in iteration
//           true/false gives verbose output or not, default is false

//   For a complete example see the project Lig-Crobas.

//   Finally,  the allocation  of growth  in  LIGNUM is  novel but  error
//   prone.  This  implementation is  the last one  in a  long historical
//   development. Most  notably we recommend  that the DIAMETER_INCREMENT
//   executes  in two  different  modes, LGMALLOCATE  and LGMGROWTH.  The
//   allocation and the actual growth can be two separate functors but as
//   they  must be essentially  the same  algorithm (growth  mode differs
//   only by adjusting the  segment dimensions) experience has shown that
//   they must be 'physically' close:  if one changes the other, one must
//   remember to change the other one too.

  enum LGMALLOCATORMODE {LGMALLOCATE,LGMGROWTH};
   
  template <class TS, class BUD> class Tree;

  template <class TS,class BUD,class ELONGATION,class DIAMETER_INCREMENT, class DATA>
  class LGMGrowthAllocator{
  public:
    LGMGrowthAllocator(Tree<TS,BUD>& tree)
      :t(tree),P(0.0),M(0.0){init();}
    LGMGrowthAllocator(Tree<TS,BUD>& tree,DATA d)
      :t(tree),data(d),P(0.0),M(0.0){init();}
    void init();
    DATA getData()const{return data;}
    double getP()const{return P;}
    double getM()const{return M;}
    double getL() const{return lambda;}
    double operator()(double l) const;
  private:
    Tree<TS,BUD>& t;
    mutable DATA data;
    double P;
    double M;
    mutable double lambda;//The lambda in  G = iWs(l) + iWfnew(l) + iWrnew(l)
  };

  template <class TS,class BUD,class ELONGATION,class DIAMETER_INCREMENT, class DATA>
  void LGMGrowthAllocator<TS,BUD,ELONGATION,DIAMETER_INCREMENT,DATA>::init()
  {
    P = GetValue(t,TreeP);
    M = GetValue(t,TreeM);
  }

  //This method, overloaded function operator, implements P-M-G=0
  template <class TS,class BUD,class ELONGATION,class DIAMETER_INCREMENT, class DATA>
  double LGMGrowthAllocator<TS,BUD,ELONGATION,DIAMETER_INCREMENT,DATA>::operator()(double l)const
  {
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
  }

}
#endif
