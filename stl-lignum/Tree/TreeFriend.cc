#include <MapParameterType.h>
#include <LGMSymbols.h>

namespace Lignum{

  template <>
  MapParameterType<LGMPD>::MapParameterType()
  {
    lgmpd["LGPaf"] = LGPaf;
    lgmpd["LGPaleafmax"] = LGPaleafmax;
    lgmpd["LGPar"] = LGPar;
    lgmpd["LGPdof"] = LGPdof;
    lgmpd["LGPLmin"] = LGPLmin;
    lgmpd["LGPlr"] = LGPlr;
    lgmpd["LGPmf"] = LGPmf;
    lgmpd["LGPmr"] = LGPmr;
    lgmpd["LGPms"] = LGPms;
    lgmpd["LGPna"] = LGPna;
    lgmpd["LGPnl"] = LGPnl;
    lgmpd["LGPpr"] = LGPpr;
    lgmpd["LGPq"] = LGPq;
    lgmpd["LGPrhoW"] = LGPrhoW;
    lgmpd["LGPrho_hair"] = LGPrho_hair;
    lgmpd["LGPrho_root"] = LGPrho_root;
    lgmpd["LGPsf"] = LGPsf;
    lgmpd["LGPsr"] = LGPsr;
    lgmpd["LGPss"] = LGPss;
    lgmpd["LGPtauL"] = LGPtauL;
    lgmpd["LGPxi"] = LGPxi;
    lgmpd["LGPyc"] = LGPyc;
    lgmpd["LGPzbrentEpsilon"] = LGPzbrentEpsilon;
    lgmpd["LGPapical"] = LGPapical;
    lgmpd["LGPlen_random"] = LGPlen_random;
  }



}//closing namespace Lignum
