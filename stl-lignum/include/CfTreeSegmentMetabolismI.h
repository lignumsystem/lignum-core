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
  resp = GetValue(t, mf)*GetValue(*this,Wf) + GetValue(t,ms)*GetValue(*this,Ws);
  SetValue(*this,M, resp);
}

template <class TS,class BUD>
void CfTreeSegment<TS,BUD>::aging()
{
  //Add age first: one (year) time step 
  SetValue(*this,age,GetValue(*this,age) + 1);

  //Sapwood senescence
  LGMdouble dAs = GetValue(GetTree(*this),ss) * GetValue(*this,As);
  LGMdouble Ah_new =  dAs + GetValue(*this, Ah);
  LGMdouble Rh_new = sqrt(Ah_new/PI_VALUE);
  SetValue(*this,Rh,Rh_new);

  //Foliage senescence
  const ParametricCurve& fm = GetFunction(GetTree(*this),LGMFM);
  //This implementation assumes declining function of age from 1 to 0.
  LGMdouble Wf_new = fm(GetValue(*this,age))*GetValue(*this,Wf);
  SetValue(*this,Wf,Wf_new);  
}

template <class TS, class BUD>
TcData& CfTreeSegment<TS,BUD>::diameterGrowth(TcData& data)
{
  CfData& cfdata = dynamic_cast<CfData&>(data);
 
  const ParametricCurve& fm = GetFunction(GetTree(*this),LGMFM);
  LGMdouble Asu = GetValue(data,As); //sapwood area from above
  LGMdouble Ahown  = GetValue(*this,Ah);//own heartwood
  //Sapwood  requirement  of  remaining  foliage,  assume  fm  returns
  //proportion initial  foliage present, declining function  from 1 to
  //0.
  LGMdouble Asr = fm(GetValue(*this,age))*GetValue(*this,As0);
  //possible new radius
  LGMdouble Rnew = sqrt((Asu + Ahown + Asr)/PI_VALUE);
  //compare Rnew to R, choose max
  Rnew = max(Rnew, GetValue(*this,R));
  //New wood radius
  SetValue(*this,R,Rnew);
  
  //Pass down sapwood area
  SetValue(data,As,GetValue(*this,As)); 

  return data;
}

} //Closing namespace Lignum


#endif

