#ifndef LGMSYMBOLS_H
#define LGMSYMBOLS_H

namespace Lignum{

  //OBS:  DO  NOT USE  ENUMERATIONS  AS  SIMPLE  VARIABLE NAMES!   For
  //example, NEVER create: double LGAWf;
  //AND, if you add a new symbol be sure to document it carefully, see
  //for example LGMAD below.
  //LGMAD = LIGNUM Attribute Double
  //LGMPD = LIGNUM Parameter Double

  enum LGMAD {LGAA,LGAAf,LGAAh, LGAAhair,LGAAs,LGAAs0,LGAage,LGAcollision,
              LGADbase,LGADbh,LGAdof, LGAdR, LGAH,LGAHf,LGAHTop,LGAip,
              LGAL,LGAM, LGAMaxD,LGAomega,LGAP,LGAQabs,LGAQin,LGAR,LGARf,
              LGARh, LGARhair,LGARTop,LGASa,LGAsf,LGAstatus, LGAstate,LGAtauL, 
              LGAtype,LGAV,LGAVh,LGAVhair,LGAvi,LGAVs,LGAWf, LGAWr, LGAWs, 
              LGAWh,LGAWhair};

  //  LGAA      Segment base area based on R 
  //  LGAAf     Area of foliage
  //  LGAAh     Heartwood area
  //  LGAAhair  Root hair area
  //  LGAAs     Sapwood area
  //  LGAAs0    Original sapwood area
  //  LGAage    Age of an object
  //  LGAcollision A bud can examine its growth sector if it collides 
  //               with an obstacle
  //  LGADbase  Diameter at base (tree)
  //  LGADbh    Diameter at breast height (tree)
  //  LGAdof    Degree of filling of leaf
  //  LGAdR     Change in radius (=difference of two growth rings)
  //  LGAH      Height of tree, also the Z coordinate at the segment base 
  //  LGAHf     Height (thickness) of cylindrical layer of foliage 
  //            in a segment, e.g. Hf = Lneedle*sin(needle_angle) 
  //  LGAHTop   Max height from ground of the tree, segment, etc.
  //  LGAip     Degree of interction
  //  LGAL      Length of segment
  //  LGAM      Rate of respiration (= amount of r. during the time step)
  //  LGAMaxD   Maximum diameter of the segments 
  //            forking off and the segment above a 
  //            branching point. Needed to calculate LGAvi 
  //  LGAomega  Gravelius order
  //  LGAP      Photosynthetic rate (= amount of p. during time step)
  //  LGAQin    Incoming radiant flux
  //  LGAQabs   Amount of absorbed radiation
  //  LGAR      Radius of segment (wood)
  //  LGARf     Radius of segment cylinder including also foliage (conifers)
  //  LGARh     Radius of heartwood
  //  LGARhair  Radius including root hair 
  //  LGARTop   Radius of segment at upper end
  //  LGASa     Surface area of the segment cylinder: 2*PI*R*L
  //  LGAsf     Specific leaf area (=leaf area/ leaf weight)
  //  LGAstatus General counter to control e.g. bud burst.  
  //  LGAstate  Bud state can be dead, alive, dormant etc., see LGMUnits.h
  //  LGPtauL = Transmission coefficient of leaf (in direction of
  //            the ray of light) 
  //  LGAtype   General type specifier, e.g. Bud:dominant, apical,
  //            lateral etc. The numerical values and their symbols of
  //            different types given in LGMUnits.h
  //  LGAV      Segment volume based on R and L
  //  LGAVh     Heartwood volume
  //  LGAVhair  Root hair volume
  //  LGAvi     Vigour index
  //  LGAVs     Sapwood volume
  //  LGAWf     Foliage mass (kg C)
  //  LGAWr     Root mass (kg C)
  //  LGAWs     Mass of sapwood (kg C)
  //  LGAWh     Mass of heartwood (kg C)
  //  LGAWhair  Mass of root hair (kg C)


  enum LGMFLOW { fin, fout, Pr, Wm };

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

  //LIGNUM Parameter Double
  //Keep this list in synbc with MapLGMPD constructor in TreeFriend.cc

  enum LGMPD {LGPaf,al,ar,dofp,lr,mf,mr,ms,na,LGPnl,LGPpr, LGPq, LGPsf, 
              LGPsr,LGPss,LGPrhoW,LGPrho_root,LGPrho_hair, LGPyc, LGPxi,
	      LGPzbrentEpsilon, LGPLn_par, LGPn_ang_par};


 //cvs update
  // al					Maximun size of a leaf
 // LGPyc					Foliage mass supported by 1m2 of sapwood
  // LGPsla  specific leaf area. sf determined for leaf..
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
  //LGPpr = Photsynthetic efficiency (=photos. rate = pr * intercepted rad.)
  //LGPq  = segment shortening (becoming obsolete due to vigour index)
  //LGPrhoW= Density of  wood in general (is usually used in Segment)
  //rho_root = Density root sapwood
  //LGPrho_hair = Density of root hair
  //LGPsf = specific leaf area (=leaf area/ leaf weight)
  //LGPsr = Senescence rate of roots
  //LGPss = Senescence rate of sapwood
  //LGPxi = Fraction of heartwood in newly created tree segments
  //LGPzbrentEpsilon = accuracy in numerical computation in root finding (see Zbrent)
  //LGPLn_par = ????????????????? 
  //LGPn_ang_par = ??????????????

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
