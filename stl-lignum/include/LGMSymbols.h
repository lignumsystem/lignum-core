#ifndef LGMSYMBOLS_H
#define LGMSYMBOLS_H

#include <map>

using namespace std;

namespace Lignum{

//Broad Leaf Attributes
enum BLA {Larea,dof,lw,sf,tauL,LP,LM,LQabs,LQin,LWf}; 

// Tree Attribute Double, Wm lisätty..Wr pois
enum TAD {area,fin,fout,H,Hm,ip,lb,L,M,omega,P,Pr,Qin,Qabs,R,Rf,Rn,Wf,Wm,Ws};  

//TreeAttribute Integer
enum TAI {age};

//Tree Attribute STATUS
enum TAS {state};

//Tree Parameter Double
enum TPD {af,ar,lr,mf,mr,ms,na,nl,pr,q,sr,ss,rho,xi}; 

//Tree Transit Variable Double
enum TTD {lambda, g, eta, Er, k, rhow}; 

class cmpstr{
public:
  bool operator() (const char* s1,const char* s2);
};

class MapTPD{
public:
  MapTPD();
  map<const char *,TPD,cmpstr> tpd;
};

}//closing namespace Lignum
#endif
