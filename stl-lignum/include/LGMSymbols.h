#ifndef LGMSYMBOLS_H
#define LGMSYMBOLS_H

#include <map>

using namespace std;

enum TPD {af,ar,lr,mf,mr,ms,na,nl,pr,q,sr,ss,rho,xi};
enum TAD {area, fin, fout, H, ip,lb,L,M,omega,P,Pr,Qin,Qabs,R,Rf,Rn,Wf,Wr,Ws};
enum TAI {age};
enum TTD {lambda};


class cmpstr{
public:
  bool operator() (const char* s1,const char* s2);
};

class MapTPD{
public:
  MapTPD();
  map<const char *,TPD,cmpstr> tpd;
};

#endif
