#ifndef CF_TREESEGMENT_METABOLISMI_H
#define CF_TREESEGMENT_METABOLISMI_H

namespace Lignum{


//Calculate PHOTOSYNTHETIC rate of the segment
//as the function of absorbed radiation

template <class TS,class BUD>
void CfTreeSegment<TS,BUD>::photosynthesis()
{
  Tree<TS,BUD>& t = GetTree(*this);
  SetValue(*this,P, GetValue(t, pr) * GetValue(*this,Qabs));

}


//RESPIRATION rate of the segment as the function of needle mass
//and sapwood mass
template <class TS,class BUD>
void CfTreeSegment<TS,BUD>::respiration()
{
  LGMdouble resp = 0.0;
  Tree<TS,BUD>& t = GetTree(*this);
  //Rtot = Rfoliage + Rsapwood
  resp = GetValue(t, mf)*GetValue(*this,Wf) + GetValue(t,ms)*GetValue(*this,LGAWs);
  SetValue(*this,M, resp);
}

template <class TS,class BUD>
void CfTreeSegment<TS,BUD>::aging()
{
  //Add age (see foliage senescence below)
  SetValue(*this,LGAage,GetValue(*this,LGAage)+1.0);

  //Sapwood senescence
  LGMdouble dAs = GetValue(GetTree(*this),ss) * GetValue(*this,LGAAs);
  LGMdouble Ah_new =  dAs + GetValue(*this, LGAAh);
  LGMdouble Rh_new = sqrt(Ah_new/PI_VALUE);
  SetValue(*this,Rh,Rh_new);

  //Foliage senescence
  const ParametricCurve& fm = GetFunction(GetTree(*this),LGMFM);
  //This implementation assumes declining function of age from 1 to 0.
  LGMdouble Wf_new = fm(GetValue(*this,LGAage))*GetValue(*this,Wf);
  SetValue(*this,Wf,Wf_new);  
}

template <class TS, class BUD>
TcData& CfTreeSegment<TS,BUD>::diameterGrowth(TcData& data)
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
    //possible new radius
    LGMdouble Rnew = sqrt((Asu + Ahown + Asr)/PI_VALUE);
    //compare Rnew to R, choose max
    Rnew = max(Rnew, GetValue(*this,R));
    //New wood radius
    SetValue(*this,R,Rnew);
  }
  //Pass down sapwood area requirement
  SetValue(data,LGAAs,GetValue(*this,LGAAs)); 
  
  return data;
}

} //Closing namespace Lignum


#endif

