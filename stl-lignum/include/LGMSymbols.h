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
  //  LGPtauL   Transmission coefficient of leaf (in direction of
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


<<<<<<< LGMSymbols.h

  //LIGNUM  Parameter Double
  //Keep the LGMPD enumeration in sync with MapLGMPD table constructor
  //in TreeFriend.cc. MapLGMPD maps the names of  the parameters found
  //in configuration files to the symbolic names in LGMPD.
  enum LGMPD {LGPaf,LGPar,dofp,lr,mf,mr,ms,na,LGPnl,LGPpr, LGPq, LGPsf, 
              LGPsr,LGPss,LGPrhoW,LGPrho_root,LGPrho_hair, LGPyc, LGPxi,
	      LGPzbrentEpsilon, LGPLn_par, LGPn_ang_par};
  // LGPsla    specific leaf area. sf determined for leaf..
  // LGPaf     Needle mass - tree segment area (kgC/m^2)relationship
  // LGPar     Foliage - root relationship 
  // lr = Length - radius relationship of a tree segment
  // mf = Maintenance respiration rate of foliage
  // mr = Maintenance respiration rate of roots
  // ms = Maintenance respiration rate of sapwood
  // na = Needle angle (radians)
  // nl = Needle length (na and nl define the cylinder of foliage in CfTreeSegment)
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

  //LIGNUM Transit Variable Double
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
