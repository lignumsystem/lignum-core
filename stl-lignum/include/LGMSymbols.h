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

  //  0 LGAA      Segment base area based on R 
  //  1 LGAAf     Area of foliage
  //  2 LGAAh     Heartwood area
  //  3 LGAAhair  Root hair area
  //  4 LGAAs     Sapwood area
  //  5 LGAAs0    Original sapwood area
  //  6 LGAage    Age of an object
  //  7 LGAcollision A bud can examine its growth sector if it collides 
  //               with an obstacle
  //  8 LGADbase  Diameter at base (tree)
  //  9 LGADbh    Diameter at breast height (tree)
  //  10 LGAdof    Degree of filling of leaf
  //  11 LGAdR     Change in radius (=difference of two growth rings)
  //  12 LGAH      Height of tree, also the Z coordinate at the segment base 
  //  13 LGAHf     Height (thickness) of cylindrical layer of foliage 
  //            in a segment, e.g. Hf = Lneedle*sin(needle_angle) 
  //  14 LGAHTop   Max height from ground of the tree, segment, etc.
  //  15 LGAip     Degree of interction
  //  16 LGAL      Length of segment
  //  17 LGAM      Rate of respiration (= amount of r. during the time step)
  //  18 LGAMaxD   Maximum diameter of the segments 
  //            forking off and the segment above a 
  //            branching point. Needed to calculate LGAvi 
  //  19 LGAomega  Gravelius order
  //  20 LGAP      Photosynthetic rate (= amount of p. during time step)
  //  21 LGAQin    Incoming radiant flux
  //  22 LGAQabs   Amount of absorbed radiation
  //  23 LGAR      Radius of segment (wood)
  //  24 LGARf     Radius of segment cylinder including also foliage (conifers)
  //  25 LGARh     Radius of heartwood
  //  26 LGARhair  Radius including root hair 
  //  27 LGARTop   Radius of segment at upper end
  //  28 LGASa     Surface area of the segment cylinder: 2*PI*R*L
  //  29 LGAsf     Specific leaf area (=leaf area/ leaf weight)
  //  30 LGAstatus General counter to control e.g. bud burst.  
  //  31 LGAstate  Bud state can be dead, alive, dormant etc., see LGMUnits.h
  //  32 LGPtauL   Transmission coefficient of leaf (in direction of
  //            the ray of light) 
  //  33 LGAtype   General type specifier, e.g. Bud:dominant, apical,
  //            lateral etc. The numerical values and their symbols of
  //            different types given in LGMUnits.h
  //  34 LGAV      Segment volume based on R and L
  //  35 LGAVh     Heartwood volume
  //  36 LGAVhair  Root hair volume
  //  37 LGAvi     Vigour index
  //  38 LGAVs     Sapwood volume
  //  39 LGAWf     Foliage mass (kg C)
  //  40 LGAWr     Root mass (kg C)
  //  41 LGAWs     Mass of sapwood (kg C)
  //  42 LGAWh     Mass of heartwood (kg C)
  //  43 LGAWhair  Mass of root hair (kg C)


  enum LGMFLOW { fin, fout, Pr, Wm };

  //LGMTAD LIGNUM Tree level  attribute double.
  //Set LGMTADLENGTH to the number of enumerations in LGMTAD.  It will
  //intialize  the   vector<LGMdouble>  in  class   Tree  holding  the
  //attribute values.
  const int LGMTADLENGTH=5;
  enum LGMTAD {Treelb,TreeP,TreeM,TreeWr,TreeQinMax};
  // Treelb  Longest branch
  // TreeP   Tree level photosynthesis
  // TreeM   Tree level respiration
  // TreeWr  Root mass
  // TreeQinMax  Max Qin of all segments in a tree

  //LIGNUM  Parameter Double
  //Keep the LGMPD enumeration in sync with MapLGMPD table constructor
  //in TreeFriend.cc. MapLGMPD maps the names of  the parameters found
  //in configuration files to the symbolic names in LGMPD.
  enum LGMPD {LGPaf,LGPar,LGPdof,LGPlr,LGPmf,LGPmr,LGPms,LGPna,
	      LGPnl,LGPpr, LGPq, LGPsf, LGPsr,LGPss,LGPrhoW,
	      LGPrho_root,LGPrho_hair, LGPyc, LGPxi,
	      LGPzbrentEpsilon, LGPLn_par, LGPn_ang_par};

  // LGPaf     Needle mass - tree segment area (kgC/m^2)relationship
  // LGPar     Foliage - root relationship 
  // LGPlr = Length - radius relationship of a tree segment
  // LGPmf = Maintenance respiration rate of foliage
  // LGPmr = Maintenance respiration rate of roots
  // LGPms = Maintenance respiration rate of sapwood
  // LGPna = Needle angle (radians)
  // LGPnl = Needle length (na and nl define the cylinder of foliage in CfTreeSegment)
  // LGPpr  Proportion of bound solar radiation that is used in photosyntheesis
  // LGPq   Segment shortening (becoming obsolete due to vigour index)
  // LGPrhoW      Density of  wood in general (is usually used in Segment)
  // LGPrho_root  Density root sapwood
  // LGPrho_hair  Density of root hair
  // LGPsf        Specific leaf area (=leaf area/ leaf weight)
  // LGPsr        Senescence rate of roots
  // LGPss        Senescence rate of sapwood
  // LGPyc	  Foliage mass (kgC) supported by 1 m^2 of sapwood
  // LGPxi        Fraction of heartwood in newly created tree segments
  // LGPzbrentEpsilon  Accuracy in numerical computation in root finding (see Zbrent)
  // LGPLn_par = ????????????????? 
  // LGPn_ang_par = ??????????????

 //cvs update
  // al					Maximun size of a leaf
 // LGPyc					Foliage mass supported by 1m2 of sapwood
  // LGPsla  specific leaf area. sf determined for leaf..
  // cvs update

  //LGPmf = Maintenance respiration rate of foliage
  //LGPmr = Maintenance respiration rate of roots
  //LGPms = Maintenance respiration rate of sapwood
  //LGPna = Needle angle (radians)
  //LGPnl = Needle length (na and nl define the cylinder of foliage in CfTreeSegment)
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
  //lambda  Elongates and shortens segments in tree to allocate photosynthates
  //         (see Zbrent)
  //g = ?????????????????450 258 34 57 / 450 686 02 40
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
