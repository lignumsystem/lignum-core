#include <Tree.h>

bool cmpstr::operator () (const char* s1,const char* s2)
{
  return strcmp(s1,s2) < 0;
}

MapTPD::MapTPD()
{
  tpd["af"] = af;
  tpd["ar"] = ar;
  tpd["lr"] = lr;
  tpd["mf"] = mf;
  tpd["mr"] = mr;
  tpd["ms"] = ms;
  tpd["na"] = na;
  tpd["nl"] = nl;
  tpd["pr"] = pr;
  tpd["q"] = q;
  tpd["sr"] = sr;
  tpd["ss"] = ss;
  tpd["rho"] = rho;
  tpd["xi"] = xi;
}


