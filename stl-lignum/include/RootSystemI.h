#ifndef ROOTSYSTEMI_H
#define ROOTSYSTEMI_H

#include <iostream>

namespace Lignum{
  template <class TREE>
  LGMdouble GetValue(const RootSegment<TREE>& rs, LGMAD name)
  {
    //Getting values, first basic simple attributes
    switch (name){
    case L:
      return rs.rsa.L;     //Length
    case R:
      return rs.rsa.R;     //Radius (sapwood)
    case RTop:
      return rs.rsa.RTop;  //Radius at top (sapwood)
    case Rh:
      return rs.rsa.Rh;    //Radius heartwood
    case Rhair:
      return rs.rsa.Rhair; //Radius root hair
    case omega:
      return rs.rsa.omega;
      //Compound attributes, areas
    case A:                //Segment area based on R
      return PI_VALUE*pow(GetValue(rs,R),2.0);
    case Ah:               //Heartwood area
      return PI_VALUE*pow(GetValue(rs,Rh),2.0);
    case As:               //Sapwood Area
      return GetValue(rs,A) - GetValue(rs,Ah);
    case Ahair:            //Root hair area
      return PI_VALUE*pow(GetValue(rs,Rhair),2.0) - GetValue(rs,A);
      //Compound attributes, volumes
    case V:                //Segment volume based on A
      return GetValue(rs,A)*GetValue(rs,L);
    case Vh:               //Heartwood volume
      return GetValue(rs,Ah)*GetValue(rs,L);
    case Vs:               //Sapwood volume
      return GetValue(rs,V) - GetValue(rs,Vh);
    case Vhair:            //Root hair volume
      return GetValue(rs,Ahair)*GetValue(rs,L) - GetValue(rs,V);
      //Compound attributes, weights
    case Ws:               //sapwood weight
      return GetValue(GetTree(rs),rho_root)*GetValue(rs,Vs);
    case Whair:            //root hair weight
      return GetValue(GetTree(rs),rho_hair)*GetValue(rs,Vhair);
    default:
      cout << "RootSegment GetValue unknown attribute: " << name << endl;
      return -1.0;
    }
  }

  //Setting values for root segment. Note: only simple values are set.
  template <class TREE>
  LGMdouble SetValue(RootSegment<TREE>& rs, LGMAD name, LGMdouble value)
  {
    LGMdouble old_value = GetValue(rs,name);
    
    switch (name){
    case L:
      rs.rsa.L = value;
      break;
    case R:
      rs.rsa.R = value;
      break;
    case RTop:
      rs.rsa.RTop = value;
      break;
    case Rh:
      rs.rsa.Rh = value;
      break;
    case Rhair:
      rs.rsa.Rhair = value;
      break;
    case omega:
      rs.rsa.omega = value;
      break;
    default:
      cout << "RootSegment SetValue unknown (simple) attribute:"
	   << name << endl;
    }
    return old_value;
  }

   template <class TR>
   Point GetEndPoint(RootSegment<TR>& rs)
   {
      return GetPoint(rs)+GetValue(rs,L)*(Point)GetDirection(rs);
   }

  //GetValue and SetValue  for RootTip. Attributes  status and  state feel
  //confusing, try  to rename them.  I believe  the enumeration STATUS
  //for state is the reason for confusion.
  template <class TREE>
  LGMdouble GetValue(const RootTip<TREE>& rt, LGMAD name)
  {
    switch (name){
    case LGMcollision:
       return rt.rta.collision;
    case LGMstatus:
       return rt.rta.status;
    case omega:
       return rt.rta.omega;
    default:
       cout << "RootTip GetValue unknown attribute: " << name << endl;
       return -1.0;
    }
  }
  
  template <class TREE>
  LGMdouble SetValue(RootTip<TREE>& rt, LGMAD name, LGMdouble value)
  {
    LGMdouble old_value = GetValue(rt,name);
    switch (name){
    case LGMcollision:
      rt.rta.collision = value;
      break;
    case LGMstatus:
      rt.rta.status = value;
      break;
    case omega:
      rt.rta.omega = value;
      break;
    default:
      cout << "RootTip SetValue unknown attribute: " << name << endl;
    }
 
    return old_value;
  }

  template <class TREE>
  STATUS GetValue(const RootTip<TREE>& rt, LGMAS name)
  {
     if (name == state){
       return rt.rta.state;
     }
     else{
       cout << "RootTip GetValue unknown status: " << name << endl;
       return rt.rta.state;
     }
  }

  template <class TREE>
  STATUS SetValue(RootTip<TREE>& rt, LGMAS name, STATUS value)
  {
    STATUS old_value = GetValue(rt,name);
    
    if (name == state){
      rt.rta.state = value;
    }

    return old_value;
  }

}//closing namespace Lignum

#endif
