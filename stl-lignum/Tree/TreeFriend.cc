#include <InitializeTree.h>

namespace Lignum{

  template <>
  MapParameterType<LGMPD>::MapParameterType()
  {
    lgmpd["LGPaf"] = LGPaf;
    lgmpd["LGPaleafmax"] = LGPaleafmax;
    lgmpd["LGPar"] = LGPar;
    lgmpd["LGPlr"] = LGPlr;
    lgmpd["LGPmf"] = LGPmf;
    lgmpd["LGPmr"] = LGPmr;
    lgmpd["LGPms"] = LGPms;
    lgmpd["LGPna"] = LGPna;
    lgmpd["LGPnl"] = LGPnl;
    lgmpd["LGPpr"] = LGPpr;
    lgmpd["LGPq"] = LGPq;
    lgmpd["LGPsf"] = LGPsf;
    lgmpd["LGPsr"] = LGPsr;
    lgmpd["LGPss"] = LGPss;
    lgmpd["LGPrhoW"] = LGPrhoW;
    lgmpd["LGPxi"] = LGPxi;
    lgmpd["LGPzbrentEpsilon"] = LGPzbrentEpsilon;
  }

  template <>
  MapParameterType<LGMTD>::MapParameterType()
  {
    lgmpd["lambda"] = lambda;
    lgmpd["g"] = g;
    lgmpd["eta"] = eta;
    lgmpd["Er"] = Er;
    lgmpd["k"] = k;
    lgmpd["rhow"] = rhow;
  }
}//closing namespace Lignum
