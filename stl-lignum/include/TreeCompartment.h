/// \file TreeCompartment.h
/// \brief TreeCompartment base class 
#ifndef TREECOMPARTMENT_H
#define TREECOMPARTMENT_H

#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
#include <LGMUnits.h>
#include <LGMSymbols.h>

using namespace cxxadt;

namespace Lignum{

  class TcData{
    friend LGMdouble GetValue(const TcData& data, LGMAD name);
    friend LGMdouble SetValue(TcData& data, LGMAD name, LGMdouble value);
  public:
    TcData():Asu(0.0){}
    virtual ~TcData(){} //makes dynamc cast possible
    TcData& operator = (const TcData&  tcd){
      Asu = tcd.Asu; return *this;
    }
    TcData& operator += (const TcData& tcd){
      Asu += tcd.Asu; return *this;
    }
  private:
    LGMdouble Asu; //Sapwood requirement above
  };

  inline LGMdouble GetValue(const TcData& data, LGMAD name)
  {
    if (name == LGAAs)
      return data.Asu;
    else{
      cout << "TcData GetValue unknown name: " << name << endl;
      return  data.Asu;
    }
  }


  inline LGMdouble SetValue(TcData& data, LGMAD name, LGMdouble value)
  {
    LGMdouble old_value = GetValue(data,name);
    data.Asu = value;
    return old_value;
  }

  ///\deprecated Use Lignum::LGMAD enumeration instead
  enum DGAD {DGWs,DGWf,DGWfnew};

  class DiameterGrowthData:public TcData{
    friend double GetValue(const DiameterGrowthData& dgd, LGMAD name);
    friend double SetValue(DiameterGrowthData& dgd, LGMAD name,double value);
    friend double GetValue(const DiameterGrowthData& dgd, DGAD name);
    friend double SetValue(DiameterGrowthData& dgd, DGAD name, double value);
  public:
    DiameterGrowthData():Ws(0.0),Wf(0.0),Wfnew(0.0),go(0.0){}
    DiameterGrowthData& operator=(TcData& tcd)
    {
      DiameterGrowthData& dgd = dynamic_cast<DiameterGrowthData&>(tcd);
      SetValue(*this,LGAAs,GetValue(dgd,LGAAs)); 
      SetValue(*this,DGWs,GetValue(dgd,DGWs));
      SetValue(*this,DGWf,GetValue(dgd,DGWf));
      SetValue(*this,DGWfnew,GetValue(dgd,DGWfnew));
      SetValue(*this,LGAomega,GetValue(dgd,LGAomega));
      return *this;
    }

    DiameterGrowthData& operator+=(TcData& tcd)
    {
      DiameterGrowthData& dgd = dynamic_cast<DiameterGrowthData&>(tcd);
      SetValue(*this,LGAAs,GetValue(*this,LGAAs)+GetValue(dgd,LGAAs));
      SetValue(*this,DGWs,GetValue(*this,DGWs)+GetValue(dgd,DGWs));
      SetValue(*this,DGWf,GetValue(*this,DGWf)+GetValue(dgd,DGWf));
      SetValue(*this,DGWfnew,GetValue(*this,DGWfnew)+GetValue(dgd,DGWfnew));
      //Recall to pass down gravelius order
      SetValue(*this,LGAomega,GetValue(dgd,LGAomega));
      return *this;
    }
    void clear(){
      SetValue(*this,LGAAs,0.0);
      SetValue(*this,DGWs,0.0);
      SetValue(*this,DGWf,0.0);
      SetValue(*this,DGWfnew,0.0);
    }
  private:
    double Ws,Wf,Wfnew;//Sapwood, total foliage and new foliage mass. 
    double go; //Graveliusorder
  };

  inline double GetValue(const DiameterGrowthData& dgd, LGMAD name)
  {
    if (name == LGAiWf)
      return dgd.Wfnew;
    else if (name == LGAiWs)
      return dgd.Ws;
    else if (name == LGAomega)
      return dgd.go;
    else  
      return GetValue(dynamic_cast<const TcData&>(dgd),name);
  }

  inline double SetValue(DiameterGrowthData& dgd,LGMAD name,double value)
  {
    double old_val = GetValue(dgd,name);
    if (name == LGAiWf)
      dgd.Wfnew = value;
    else if (name == LGAiWs)
      dgd.Ws = value;
    else if (name == LGAomega)
      dgd.go = value;
    else
      SetValue(dynamic_cast<TcData&>(dgd),name,value);
    return old_val;
  }


  
  inline double GetValue(const DiameterGrowthData& dgd, DGAD name)  
  {
    if (name == DGWs)
      return dgd.Ws;
    else if (name == DGWf)
      return dgd.Wf;
    else if (name == DGWfnew)
      return dgd.Wfnew;
    else{
      cout << " DiameterGrowthData GetValue unknown name:" << name << endl;
      return -1.0;
    }
  }
 
  inline double SetValue(DiameterGrowthData& dgd, DGAD name, double value)  
  {
    double old_value = GetValue(dgd,name);
    if (name == DGWs)
      dgd.Ws = value;
    else if (name == DGWf)
      dgd.Wf = value;
    else if (name == DGWfnew)
      dgd.Wfnew = value;
    return old_value;
  }

  template <class TS,class BUD=DefaultBud<TS> > 
  class TreeCompartment
  {
    template <class TS1,class BUD1> 
    friend Point GetPoint(const TreeCompartment<TS1,BUD1>& tc);

    template <class TS1,class BUD1> 
    friend PositionVector GetDirection(const TreeCompartment<TS1,BUD1>& tc);

    template <class TS1,class BUD1> 
    friend void SetPoint(TreeCompartment<TS1,BUD1>& tc, const Point& p);
	  
    template <class TS1,class BUD1> 
    friend void SetDirection(TreeCompartment<TS1,BUD1>& tc, const PositionVector& pv);

    template <class TS1,class BUD1> 
    friend Tree<TS1,BUD1>& GetTree(const TreeCompartment<TS1,BUD1>& tc);

    template <class TS1,class BUD1>
    friend LGMdouble GetValue(const TreeCompartment<TS1,BUD1>& tc, const LGMAD name);

    template <class TS1,class BUD1>
    friend LGMdouble SetValue(TreeCompartment<TS1,BUD1>& tc, const LGMAD name, const LGMdouble value);
  public:
    TreeCompartment();
    TreeCompartment(const Point& p, const PositionVector& d, Tree<TS,BUD>* t);
    TreeCompartment(Tree<TS,BUD>* t) { tree = t; }
    virtual ~TreeCompartment();
    virtual void photosynthesis() { /* Default: do nothing */ }
    virtual void respiration() {}
    virtual void aging(){}
    virtual TcData& diameterGrowth(TcData& data){return data;}
  protected:
    Point point;
    PositionVector direction;
    LGMdouble tc_age;
    Tree<TS,BUD>* tree;
  };




}  // closing namespace Lignum

#include <TreeCompartmentI.h>

#endif

