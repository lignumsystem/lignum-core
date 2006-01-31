#ifndef LGMSYMBOLS_H
#define LGMSYMBOLS_H

//If you modify the contents of this file, please update also the
//documentation in the beginning.

//This file defines a number of enumerations for stl-ligum, namely
//LGMAD = LIGNUM Attribute Double
//LGMPD = LIGNUM Parameter Double
//LGMTAD = LIGNUM Tree level attribute double.
//LGMF   = Functions known in a tree
//FILE_MODE = For reading in different types of input
//LGMVERBOSE = Verbose or scanty output
//LGMINITSTYLE = Old or new style, new style has a sequencs of mask files.
//LGMFLOW = Flow symbols

//USAGE: The main functionality of these enumerations is to allow
//reference to variables (i.e. their values) with symbolic names. The
//values of variables (LGMAD) and parameters (LGMPD) in LIGNUM can be
//assessed and changed with GetValue(OBJECT, NAME) and
//SetValue(OBJECT, NAME) (OBJECT=the unit of LIGNUM - Tree,
//TreeSegment, etc - concerned, NAME=name of variable, parameter in
//enumeration). The naming of symbols that refer to LIGNUM variables
//is done as follows for LGMAD and LGMPD: the name of
//variable/parameter is prefixed with LGA/LGP. For example, the area
//of foliage is denoted by Af in LIGNUM, hence the symbol referring to
//this variable is LGAAf; the maintenance respiration rate of foliage
//(=parameter) is denoted by mf, hence enumeration symbol is LGPmf.

//The C++ compiler labels each symbol in the enumeration list with an
//integer (0,1,...) and later deals only with these numbers. Consequently, if
//GetValue(compartment, NAME) fails to find value for variable
//referrred to by NAME, an error message is issued that says "A value
//cannot be found for variable nn" (nn is an integer). The numbers on
//the left of the symbol documentation aid to identify for which
//symbol in the enumeration the value could not be found. Please keep
//the numbers of documentations in sync. with the the enumerations.

//OBS: DO NOT USE ENUMERATIONS AS SIMPLE VARIABLE NAMES!  To minimize
//the possibility of using enumerations as variable names, they have
//been prefixed with LGA, LGP etc.

namespace Lignum{
  //LGMAD = LIGNUM Attribute Double  *********************'
  
  // These symbols are used to access (GetValue, SetValue) the
  // variables (either attributes or other variables) of TreeSegment,
  // Bud, BrachingPoint, BroadLeaf in LIGNUM (in any compartment
  // except Tree). As regards GetValue, it may be that the value
  // returned is calculated on the basis of other variables.



  //If you add a new symbol be sure to document it carefully.

  enum LGMAD {LGAA,LGAAf,LGAAfb,LGAAfc,LGAAh, LGAAhair,LGAAs,
              LGAAs0,LGAage,LGAcbase,LGAcollision,
              LGADbase, LGADbaseHw, LGADbh,LGADbhHw,LGAdof, LGAdR,
	      LGAH,LGAHf,LGAHTop,LGAip,LGAL,LGALAIb,LGALAIc,
              LGAM, LGAMaxD,LGAomega,LGAP,LGAQabs,LGAQin,LGAR,LGARf,
              LGARh, LGARhair,LGARTop,LGASa,LGAsf,LGAstarm,LGAstatus, 
              LGAstate,LGAtauL, LGAtype,LGAV,LGAVf,LGAVh,LGAVhair,LGAvi,LGAVs,
              LGAWf, LGAWf0, LGAWs, LGAWh,LGAWhair, LGAT};


  //  0 LGAA      Segment base area based on R 
  //  1 LGAAf     Area of foliage
  //  2 LGAAfb    Foliage area, broad leaved (see ForestDescriptor in stl-voxelspace)
  //  3 LGAAfc    Foliage area, conifers (see ForestDescriptor in stl-voxelspace)
  //  4 LGAAh     Heartwood area
  //  5 LGAAhair  Root hair area
  //  6 LGAAs     Sapwood area
  //  7 LGAAs0    Original sapwood area
  //  8 LGAage    Age of an object
  //  9 LGAcbase  Crown base of a forest (see ForestDescriptor in stl-voxelspace)
  //  10 LGAcollision A bud can examine its growth sector if it collides 
  //               with an obstacle
  //  11 LGADbase  Diameter at base (tree)
  //  12 LGADbaseHw  Diameter of heart wood at base (tree)
  //  13 LGADbh    Diameter at breast height (tree)
  //  14 LGADbhHw    Diameter of heart wood at breast height (tree)
  //  15 LGAdof    Degree of filling of leaf
  //  16 LGAdR     Change in radius (=difference of two growth rings)
  //  17 LGAH      Height of tree, also the Z coordinate at the segment base 
  //  18 LGAHf     Height (thickness) of cylindrical layer of foliage 
  //               in a segment, e.g. Hf = Lneedle*sin(needle_angle) 
  //  19 LGAHTop   Max height from ground of the tree, segment, etc.
  //  20 LGAip     Degree of interaction
  //  21 LGAL      Length of segment
  //  22 LGALAIb   Leaf area index, broad leaved (see ForestDescriptor in stl-voxelspace)
  //  23 LGALAIc   Leaf area index, conifers (see ForestDescriptor in stl-voxelspace)
  //  24 LGAM      Rate of respiration (= amount of r. during the time step)
  //  25 LGAMaxD   Maximum diameter of the segments 
  //               forking off and the segment above a 
  //               branching point. Needed to calculate LGAvi 
  //  26 LGAomega  Gravelius order
  //  27 LGAP      Photosynthetic rate (= amount of p. during time step)
  //  28 LGAQabs   Amount of absorbed radiation
  //  29 LGAQin    Incoming radiant flux
  //  30 LGAR      Radius of segment (wood)
  //  31 LGARf     Radius of segment cylinder including also foliage (conifers)
  //  32 LGARh     Radius of heartwood
  //  33 LGARhair  Radius including root hair 
  //  34 LGARTop   Radius of segment at upper end
  //  35 LGASa     Surface area of the segment cylinder: 2*PI*R*L
  //  36 LGAsf     Specific leaf area (=leaf area/ leaf weight)
  //  37 LGAstarm  Star mean for a confiferous segment
  //  38 LGAstatus General counter to control e.g. bud burst.  
  //  39 LGAstate  Bud state can be dead, alive, dormant etc., see LGMUnits.h
  //  40 LGAtauL   Transmission coefficient of leaf (in direction of
  //               the ray of light) 
  //  41 LGAtype   General type specifier, e.g. Bud:dominant, apical,
  //               lateral etc. The numerical values and their symbols of
  //               different types given in LGMUnits.h
  //  42 LGAV      Segment volume based on R and L
  //  43 LGAVf     Volume occupied by the foliage in CfSegment 
  //  44 LGAVh     Heartwood volume
  //  45 LGAVhair  Root hair volume
  //  46 LGAvi     Vigour index
  //  47 LGAVs     Sapwood volume
  //  48 LGAWf     Foliage mass (kg C)
  //  49 LGAWf0    Initial foliage mass (kg C)
  //  50 LGAWs     Mass of sapwood (kg C)
  //  51 LGAWh     Mass of heartwood (kg C)
  //  52 LGAWhair  Mass of root hair (kg C)

  // LGMAD = LIGNUM Attribute Double

  //LIGNUM  Parameter Double   ************************************

  // These symbols are used to access (GetValue, SetValue) parameters
  // in any compartment (predominantly Tree) of LIGNUM. A parameter is
  // basically a variable that remains constant during
  // simulation. Depending on application, quantity can be either
  // variable or parameter - the variable having the same name can
  // therefore referred to in LGMAD and LGMPD. It is up to the
  // programmer of the application to make sure that correct variables
  // are accessed.

  //Keep the LGMPD enumeration in sync with MapLGMPD table constructor
  //in TreeFriend.cc. MapLGMPD maps the names of  the parameters found
  //in configuration files to the symbolic names in LGMPD.

  enum LGMPD {LGPaf, LGPaleafmax, LGPapical, LGPar, LGPdof, LGPLmin, 
	      LGPlr, LGPmf, LGPmr, LGPms,
	      LGPna, LGPnl, LGPpr, LGPq, LGPrhoW, LGPrho_hair, LGPrho_root,
	      LGPsf, LGPsr, LGPss, LGPtauL,LGPxi, LGPyc,LGPzbrentEpsilon };

  // 0  LGPaf  Needle mass - tree segment area (kgC/m^2)relationship
  // 1  LGPaleafmax  Maximum size of a leaf (m2)
  // 2  LGPapical   Length of segment (new) forking off (lateral) =
  //                LGPapical * Len of not forking off
  // 3  LGPar  Foliage - root relationship
  // 4  LGPdof Degree of filling (proportion leaf surface fills of geometric
  //          shape - e.g. ellipsis - of the leaf).
  // 5. LGPLmin Minimum length (m) allowed for a new segment
  // 6  LGPlr  Length - radius relationship of a tree segment
  // 7  LGPmf  Maintenance respiration rate of foliage
  // 8  LGPmr  Maintenance respiration rate of roots
  // 9  LGPms  Maintenance respiration rate of sapwood
  // 10  LGPna  Needle angle (radians)
  // 11  LGPnl  Needle length (na and nl define the cylinder of foliage in
  //           CfTreeSegment)
  // 12 LGPpr  Photsynthetic efficiency (=photos. rate = pr * intercepted rad.)
  // 13 LGPq   Segment shortening factor (becoming obsolete due to vigour
  //           index)
  // 14 LGPrhoW      Density of  wood in general (is usually used in Segment)
  // 15 LGPrho_hair  Density of root hair
  // 16 LGPrho_root  Density root sapwood
  // 17 LGPsf        Specific leaf area (=leaf area/ leaf weight)
  // 18 LGPsr        Senescence rate of roots
  // 19 LGPss        Senescence rate of sapwood
  // 20 LGPtauL      Transmission coefficient (light) for leaf
  // 21 LGPxi        Fraction of heartwood in newly created tree segments
  // 22 LGPyc	     Foliage mass (kgC) supported by 1 m^2 of sapwood
  // 23 LGPzbrentEpsilon  Accuracy in numerical computation in root finding
  //              (see Zbrent)


  //LGMTAD LIGNUM Tree level attribute double. **************************

  //Set LGMTADLENGTH to the number of enumerations in LGMTAD.  It will
  //intialize  the   vector<LGMdouble>  in  class   Tree  holding  the
  //attribute values.

  const int LGMTADLENGTH=7;

  enum LGMTAD {Treelambda,Treelb,TreeP,TreeM,TreeWr,TreeQinMax,
	       TreeRefRadiation};
  // Treelb  Longest branch
  // TreeP   Tree level photosynthesis
  // TreeM   Tree level respiration
  // TreeWr  Root mass
  // TreeQinMax  Max Qin of all segments in a tree
  // Treelambda  Variable to balance carbon balance equation
  // TreeRefRadiation   Variable that is used as reference radiation
  //                     in calculations in tree (e.g. lentgth growth)


  //LGMF   = Functions known in a tree   ********************************

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
  enum LGMINITSTYLE {OLD_INIT,NEW_INIT};

  //Goes with TreeSegmentWithFlow - will eventually be removed from
  //stl-lignum
  enum LGMFLOW { fin, fout, Pr, Wm };

}//closing namespace Lignum


#endif
