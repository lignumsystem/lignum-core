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
    lgmpd["sr"] = sr;
    lgmpd["ss"] = ss;
    lgmpd["rho"] = rho;
    lgmpd["xi"] = xi;
    lgmpd["zbrentEpsilon"] = zbrentEpsilon;
    lgmpd["Ln_par"] = Ln_par;
    lgmpd["n_ang_par"] = n_ang_par;
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
