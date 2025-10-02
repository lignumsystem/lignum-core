/// \file HwTreeSegmentMetabolismI.h
/// \brief Hardwood tree segment implementation
#ifndef HWTREESEGMENTMETABOLISMI_H
#define HWTREESEGMENTMETABOLISMI_H

namespace Lignum{

  //PHOTOSYNHETIC rate of HwTreeSegment (sum of those of leaves)

template <class TS,class BUD,class S>
void HwTreeSegment<TS,BUD,S>::photosynthesis()
  {
  Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));
  LGMdouble p0 = GetValue(tt, LGPpr);
  for(typename list<BroadLeaf<S>*>::iterator i = leaf_ls.begin();
	i != leaf_ls.end(); i++) {
    (*i)->photosynthesis(p0);
  }
}

//RESPIRATION rate  of HwTreeSegment (sum of leaves  + segment sapwood
//resp.)  This  is NOT a good  way to implement  metabolism. We should
//have a  simple basic method  (say, parameter times biomass)  and all
//the experiments with  N or P or whatever nutrient  should be done in
//subclasses plugged in to a final program.
template <class TS,class BUD,class S>
void HwTreeSegment<TS,BUD,S>::respiration()
{
  Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));

  LGMdouble m_hw = 0.0;
  LGMdouble mf_par = GetValue(tt, LGPmf);

  for(typename list<BroadLeaf<S>*>::iterator i = leaf_ls.begin(); i != leaf_ls.end(); i++) {
    m_hw += mf_par * GetValue(**i,LGAWf);
  }

  // Respiration of wooden part

  m_hw += GetValue(tt,LGPms)*GetValue(*this,LGAWs);

  SetValue(*this, LGAM, m_hw);
}



template <class TS,class BUD, class S>
void HwTreeSegment<TS,BUD, S>::aging()
{
  //Add age (see foliage senescence below)
  SetValue(*this,LGAage,GetValue(*this,LGAage)+1.0);
}



//HwTree Diameter growth function

template <class TS, class BUD, class S>
TcData& HwTreeSegment<TS, BUD, S>::diameterGrowth(TcData& data)
{
  //New segment (age == 0) is iteratively set. 
  if (GetValue(*this,LGAage) > 0.0){
    const ParametricCurve& fm = GetFunction(GetTree(*this),LGMFM);
    LGMdouble Asu = GetValue(data,LGAAs); //sapwood area from above
    LGMdouble Ahown  = GetValue(*this,LGAAh);//own heartwood
    //Sapwood  requirement  of  remaining  foliage,  assume  fm  returns
    //proportion initial  foliage present, declining function  from 1 to
    //0.
    LGMdouble Asr = fm(GetValue(*this,LGAage))*GetValue(*this,LGAAs0);
    // cout<<GetValue(*this,LGAage)<<": the value of age and As0:"<<GetValue(*this,LGAAs0)<<endl; 
    //**cout<<"the value of Asr:"<<Asr<<endl;
    //possible new radius
    LGMdouble Rnew = sqrt((Asu + Ahown + Asr)/PI_VALUE);
    //compare Rnew to R, choose max
    Rnew = max(Rnew, GetValue(*this,LGAR));
    //New wood radius
    //**cout<<Rnew<<": the value of new radius"<<endl;
    SetValue(*this,LGAR, Rnew);
  }
  //Pass down sapwood area requirement
  SetValue(data,LGAAs,GetValue(*this,LGAAs));   
  return data;
}


} //closing namespace Lignum
#endif



