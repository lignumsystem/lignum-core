#include <iostream>
#include <RootSystem.h>

namespace Lignum{

  LGMdouble GetValue(const RootSegment& rs, LGMAD name)
  {
    if (name == L){
      return rs.rsa.L;
    }
    else if (name == R){
      return rs.rsa.R;
    }
    else if (name == RTop){
      return rs.rsa.RTop;
    }
    else if (name == Rh){
      return rs.rsa.Rh;
    }
    else if (name == Rhair){
      return rs.rsa.Rhair;
    }
    else{
      cout << "RootSegment GetValue unknown attribute: " << name << endl;
      return -1.0;
    }
  }

  LGMdouble SetValue(RootSegment& rs, LGMAD name, LGMdouble value)
  {
    LGMdouble old_value = GetValue(rs,name);
    
    if (name == L){
      rs.rsa.L = value;
    }
    else if (name == R){
      rs.rsa.R = value;
    }
    else if (name == RTop){
      rs.rsa.RTop = value;
    }
    else if (name == Rh){
      rs.rsa.Rh = value;
    }
    else if (name == Rhair){
      rs.rsa.Rhair = value;
    }
    
    return old_value;
  }
    
  //GetVale/SetValue for RootTip
  LGMdouble GetValue(const RootTip& rt, LGMAD name)
  {
     if (name == LGMcollision){
       return rt.rta.collision;
     }
     else if (name ==  LGMstatus){
       return rt.rta.state;
     }
     else{
       cout << "RootTip GetValue unknown attribute: " << name << endl;
       return -1.0;
     }
  }

  LGMdouble SetValue(RootTip& rt, LGMAD name, LGMdouble value)
  {
    LGMdouble old_value = GetValue(rt,name);

    if (name == LGMcollision){
      rt.rta.collision = value;
    }
    else if (name ==  LGMstatus){
      rt.rta.state = value;
    }
    return old_value;
  }

  STATUS GetValue(const RootTip& rt, LGMAS name)
  {
     if (name == LGMstatus){
       return rt.rta.status;
     }
     else{
       cout << "RootTip GetValue unknown status: " << name << endl;
       return rt.rta.status;
     }
  }

  STATUS SetValue(RootTip& rt, LGMAS name, STATUS value)
  {
    STATUS old_value = GetValue(rt,name);
    
    if (name == LGMstatus){
      rt.rta.status = value;
    }

    return old_value;
  }

}//closing namespace Lignum 
