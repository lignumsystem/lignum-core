#ifndef LGMSYMBOLS_H
#define LGMSYMBOLS_H

namespace Lignum{

  //OBS: DO NOT USE ENUMERATIONS AS VARIABLE NAMES!
  //For example, _NEVER_ create double Wf;

  // Tree Attribute Double, Wm lisätty
  // Wr           dry weight of the roots
  enum LGMAD {A,Af,Ah, Ahair,As,As0,age,api, LGMcollision,dof, dR, H,Hf,Hm,ip,lb,LM,LP,LWf,L,lw,M, omega,P,
	      Qin,Qabs,R,Rf,Rh,Rhair,RTop,Sa,LGMstatus,sw,tauL,LGMtype,V,Vh,Vhair,Vs,vi,
              Wf,Wr, Ws,Wh,Whair};

  //  A       0   Segment area based on R (see GetValue)
  //  Af          area of foliage
  //  Ah          Heartwood area
  //  Ahair       Root hair area
  //  As          Sapwood area
  //  As0         Original sapwood area
  //  age     1   age of object
  //  dof     2   degree of filling?
  //  H       3   height of tree
  //  Hf          height of foliage 
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
  //  Rhair       Radius including root hair 
  //  Rtop    20  radius of segment at upper end
  //  Sa          Surface area of the segment cylinder: 2*PI*R*L 
  //  sw      22  ????
  //  tauL    23  transmission coefficient of leaf (in direction of the ray of light)
  //  Wf      24  foliage mass (kg C)
  //  Wr      27  root mass (kg C)
  //  Ws      25  mass of sapwood (kg C)
  //  Wh      26  mass of heartwood (kg C)
  //  Whair       mass of root hair (kg C)

  //  vi          vigour index
  //  V           Segment volume based on R
  //  Vh          Heartwood volume
  //  Vhair       Root hair volume
  //  Vs          Sapwood volume


  enum LGMFLOW { fin, fout, Pr, Wm };

  //Tree Attribute STATUS
  enum LGMAS {state};

  //enlisting tree level attributes
  enum LGMTAD {Treelb,TreeP,TreeM,TreeWr,TreeQinMax};
  //lb = longest branch
  //P  = tree level photosynthesis
  //M  = tree level respiration
  //Wr = root mass

  //Keep this in sync with the number of enumerations in LGMTAD
  //It will intialize the vector
#define LGMTADLENGTH 5
  //Tree Parameter Double
  // zbrentEpsilon       Accuracy in solving the root of P - M -dW(lambda)
  //Keep this list in synbc with MapLGMPD constructor in TreeFriend.cc


  enum LGMPD {af,al,ar,ca, dofp,lr,mf,mr,ms,na,nl,pr,q, rca, rld,sf, sla,sr,ss,rho,rho_root,rho_hair, yc, xi,
	      zbrentEpsilon, Ln_par, n_ang_par, fake_forest, nitroRoots, nitroWood, nitroLeaves};


 //cvs update
  // al					Maximun size of a leaf
 // ca					circulation angle
 // rca					random effect on circulation angle
 // rld					random effect on leaf distances in a single segment
 // yc					Foliage mass supported by 1m2 of sapwood
  // sla					specific leaf area. sf determined for leaf..
  // cvs update
  //af = Needle mass - tree segment area (kg/m^2)relationship
  //ar = Foliage - root relationship 
  //al=	Maximun size of a leaf
  //lr = Length - radius relationship of a tree segment
  //mf = Maintenance respiration rate of foliage
  //mr = Maintenance respiration rate of roots
  //ms = Maintenance respiration rate of sapwood
  //na = Needle angle (radians)
  //nl = Needle length (na and nl define the cylinder of foliage in CfTreeSegment)
  //pr = Proportion of bound solar radiation that is used in photosyntheesis
  //q  = segment shortening (becoming obsolete due to vigour index)
  //rho= Density of  wood (carbon = 50% dry weight)
  //rho_root = Density root sapwood
  //rho_hair = Density of root hair
  //sf = specific leaf area (=leaf area/ leaf weight)
  //sr = Senescence rate of roots
  //ss = Senescence rate of sapwood
  //xi = Fraction of heartwood in newly created tree segments
  //zbrentEpsilon = accuracy in numerical computation in root finding (see Zbrent)
  //Ln_par = ????????????????? 
  //n_ang_par = ??????????????
  //fake_forest = diffuseForestRegionRadiationSum is used (1 = yes, 0 = no)

  //Tree Transit Variable Double
  enum LGMTD {lambda, g, eta, Er, k, rhow}; 
  //lambda = elongates and shortens segments in tree to allocate photosynthates
  //         (see Zbrent)
  //g = ?????????????????
  //eta = ???????????????
  //Er = ????????????????
  //k =  ????????????????
  //rhow = ??????????????

  //There are parameters and functions and graphics 
  //to configure the tree. The initial tree (INITIAL) 
  //is becoming obsolete because of the L systems implementation
  //See TreeMetaFileParser.
  enum FILE_MODE {PARAMETER,FUNCTION,GRAPHICS,INITIAL};

  //Functions known in a tree
  enum LGMF {LGMAL,LGMFM,LGMIP,LGMLONB,LGMNB,LGMVI,LGMVIONB};
  //LGMAL = Adjusted length For example for making branches below 0.002 
  //        to have Length 0 and branches
  //LGMFM = Foliage mortality 
  //LGMIP = Relative length of a new tree segment 
  //LGMLONB = The effect of light to number of the buds. 
  //          If no effect the value is always 1 of this function.
  //LGMNB    = Number of buds
  //LGMVI    = Function of vigour index
  //LGMVIONB = The effect of vigour index to the number of the buds. 
  //           If no effect the value is always 1 of this function

  //If needed you may design verbose output for example
  //when initializing trees 
  enum LGMVERBOSE {QUIET,VERBOSE};
}//closing namespace Lignum


#endif
