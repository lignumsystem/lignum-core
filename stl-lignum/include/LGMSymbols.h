#ifndef LGMSYMBOLS_H
#define LGMSYMBOLS_H

#include <map>

using namespace std;

enum TPD {af,ar,lr,mf,mr,ms,na,nl,pr,q,sr,ss,rho,xi};
enum TAD {ip,lb,L,M,omega,P,Qin,Qabs,R,Rn,Wf,Wr};
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
