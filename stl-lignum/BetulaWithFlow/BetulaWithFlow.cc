#include <BetulaWithFlow.h>

namespace Lignum{

  LGMdouble GetValue(const BetulaWithFlow& ts, const LGMBETULA name)
    {
      //  LGMdouble unknown_value = 0.0;
      
      if (name == Nleaves)
	return ts.Nleaves;
      
      else if(name == Aleaf)
	return ts.Aleaf;
      
      return 0;
    }
  
 

 
  LGMdouble SetValue(BetulaWithFlow& ts, const LGMBETULA name, const LGMdouble value)
    {
      LGMdouble old_value = GetValue(ts,name);
      
      if (name == Nleaves)
	ts.Nleaves = value;
      
      else if(name == Aleaf)
	ts.Aleaf = value;
      
      return old_value;
    }
  

} //closing namespace Lignum



