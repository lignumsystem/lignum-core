#ifndef LGMSYMBOLS_H
#define LGMSYMBOLS_H
//#include <cstring>
#include <map>
#include <string>



namespace Lignum{


// Tree Attribute Double, Wm lisätty
// Wr           dry weight of the roots
enum LGMAD {A,age,LGMcollision,dof, dR, H,Hm,ip,lb,LM,LP,LWf,L,lw,M, omega,P,
            Qin,Qabs,R,Rf,Rh,RTop,sf,LGMstatus,sw,tauL,LGMtype,vi,Wf,Ws,Wh,Wr};  

//  A       0   Area (of what?)
//  age     1   age of object
//  dof     2   degree of filling?
//  H       3   height of tree
//  Hm      4   ???
//  ip      5   degree of interction
//  lb      6   ???
//  LM      7   ???
//  LP      8   ???
//  LWf     9   ???
//  L       10  length of segment
//  lw      11  ???
//  M       12  rate of respiration (= amount of r. during the time step)
//  omega   13  Gravelius order
//  P       14  Photosynthetic rate (= amount of p. during time step)
//  Qin     15  incoming radiant flux
//  Qabs    16  amount of absorbed radiation
//  R       17  radius of segment
//  Rf      18  radius of segment cylinder that contains also foliage (cofers)
//  Rh      19  radius of heartwood
//  Rtop    20  raqdiaus of segment at upper end
//  sf      21  specifi leaf area (=leaf area/ leaf weight)
//  sw      22  ????
//  tauL    23  transmission coefficient of leaf (in direction of the ray of light)
//  Wf      24  foliage mass (kg C)
//  Ws      25  mass of sapwood (kg C)
//  Wh      26  mass of heartwood (kg C)
//  Wr      27  root mass (kg C)

enum LGMFLOW { fin, fout, Pr, Wm };

//Tree Attribute STATUS
enum LGMAS {state};

//Tree Parameter Double
// zbrentEpsilon       Accuracy in solving the root of P - M -dW(lambda)
enum LGMPD {af,ar,lr,mf,mr,ms,na,nl,pr,q,sr,ss,rho,xi,
          zbrentEpsilon, Ln_par, n_ang_par}; 

//Tree Transit Variable Double
enum LGMTD {lambda, g, eta, Er, k, rhow}; 





class cmpstr{
public:
	bool operator() (const char* s1,const char* s2);
};

class MapTPD{
public:
	MapTPD();
	std::map<std::string, LGMPD> tpd;
};


}//closing namespace Lignum


#endif
