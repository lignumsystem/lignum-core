#ifndef LGMSYMBOLS_H
#define LGMSYMBOLS_H

namespace Lignum{

  //OBS: DO NOT USE ENUMERATIONS AS VARIABLE NAMES!
  //For example, _NEVER_ create: double Wf;

  //_AND_, if you add a new symbol be sure to document it carefully!

  // LGMAD = LIGNUM Attribute Double

  // LGMPD = LIGNUM Parameter Double

  // Wr           dry weight of the roots
  enum LGMAD {LGAA,LGAAf,LGAAh, LGAAhair,LGAAs,LGAAs0,LGAage,api, LGAcollision,
              LGADbase,LGADbh,LGAdof, dR, LGAH,LGAHf,Hm,LGAip,
              lb,LM,LP,LWf,LGAL,lw,M, MaxD,omega,P,
	      Qin,Qabs,R,Rf,Rh,Rhair,RTop,Sa,LGMstatus,sw,tauL,LGMtype,V,Vh,
	      Vhair,LGAvi,LGAVs,
              LGAWf, LGAWr, LGAWs, LGAWh, LGAWhair};

  //  LGAA      Segment area based on R (see GetValue)
  //  LGAAf     area of foliage
  //  LGAAh     Heartwood area
  //  LGAAhair  Root hair area
  //  LGAAs     Sapwood area
  //  LGAAs0    Original sapwood area
  //  LGAage    age of object
  //  api    ???  
  //  LGAcollision a bud can examine its growth sector if it collides with an obstacle
  //  LGADbase  diameter at base
  //  LGADbh    diameter at breast height
  //  LGAdof    degree of filling?
  //  LGAH      height of tree, also the Z coordinate at the segment end point 
  //  LGAHf     height (thickness) of cylindrical layer of foliage in a segment 
  //  Hm     ???
  //  LGAip     degree of interction
  //  lb     ???
  //  LM     ???
  //  LP     ???
  //  LWf    ???
  //  LGAL      length of segment
  //  lw     ???
  //  M      rate of respiration (= amount of r. during the time step)
  //  MaxD   maximum diameter of the segments forking off and the segment above a branching point 
  //  omega  Gravelius order
  //  P      Photosynthetic rate (= amount of p. during time step)
  //  Qin    incoming radiant flux
  //  Qabs   amount of absorbed radiation
  //  R      radius of segment (wood)
  //  Rf     radius of segment cylinder that contains also foliage (conifers)
  //  Rh     radius of heartwood
  //  Rhair  Radius including root hair 
  //  Rtop   radius of segment at upper end
  //  Sa     Surface area of the segment cylinder: 2*PI*R*L 
  //  sw     ????
  //  tauL   transmission coefficient of leaf (in direction of the ray of light)
  //  V      Segment volume based on R
  //  Vh     Heartwood volume
  //  Vhair  Root hair volume
  //  vi     vigour index
  //  LGAVs     Sapwood volume
  //  LGAWf     foliage mass (kg C)
  //  LGAWr     root mass (kg C)
  //  LGAWs     mass of sapwood (kg C)
  //  LGAWh     mass of heartwood (kg C)
  //  LGAWhair  mass of root hair (kg C)


  enum LGMFLOW { fin, fout, Pr, Wm };

  //Tree Attribute STATUS
  enum LGMAS {state};

  //enlisting tree level attributes
  enum LGMTAD {Treelb,TreeP,TreeM,TreeWr,TreeQinMax};
  //lb = longest branch
  //P  = tree level photosynthesis
  //M  = tree level respiration
  //Wr = root mass
  //TreeQinMax = max Qin of all segments in a tree

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
