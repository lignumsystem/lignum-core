#ifndef LGMSYMBOLS_H
#define LGMSYMBOLS_H

#include <map>

using namespace std;

namespace Lignum{


// Tree Attribute Double, Wm lisätty..Wr pois
enum LGMAD {A,age,dof,fin,fout,H,Hm,ip,lb,LM,LP,LWf,L,lw,M,omega,P,Pr,\
            Qin,Qabs,R,Rf,Rn,sf,sw,tauL,Wf,Wm,Ws};  


//Tree Attribute STATUS
enum LGMAS {state};

//Tree Parameter Double
enum LGMPD {af,ar,lr,mf,mr,ms,na,nl,pr,q,sr,ss,rho,xi}; 

//Tree Transit Variable Double
enum LGMTD {lambda, g, eta, Er, k, rhow}; 

class cmpstr{
public:
  bool operator() (const char* s1,const char* s2);
};

class MapTPD{
public:
  MapTPD();
  map<const char *,LGMPD,cmpstr> tpd;
};

}//closing namespace Lignum
#endif
