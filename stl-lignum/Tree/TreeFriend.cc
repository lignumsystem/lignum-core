#include <InitializeTree.h>

namespace Lignum{

  template <>
  MapParameterType<LGMPD>::MapParameterType()
  {
    lgmpd["af"] = af;
    lgmpd["ar"] = ar;
    lgmpd["lr"] = lr;
    lgmpd["mf"] = mf;
    lgmpd["mr"] = mr;
    lgmpd["ms"] = ms;
    lgmpd["na"] = na;
    lgmpd["nl"] = nl;
    lgmpd["pr"] = pr;
    lgmpd["q"] = q;
    lgmpd["sf"] = sf;
    lgmpd["sr"] = sr;
    lgmpd["ss"] = ss;
    lgmpd["rho"] = rho;
    lgmpd["LGPxi"] = LGPxi;
    lgmpd["LGPzbrentEpsilon"] = LGPzbrentEpsilon;
    lgmpd["LGPLn_par"] = LGPLn_par;
    lgmpd["LGPn_ang_par"] = LGPn_ang_par;
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
