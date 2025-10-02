#ifndef LGMSYMBOLS_H
#define LGMSYMBOLS_H
/// \file LGMSymbols.h
/// \brief Enumeration symbols
///
///Defines a number of enumerations for Lignum.
///
/// + LGMAD = LIGNUM Attribute Double  
/// + LGMPD = LIGNUM Parameter Double  
/// + LGMTAD = LIGNUM Tree level attribute double.  
/// + LGMF   = Functions known in a tree  
/// + FILE_MODE = For reading in different types of input  
/// + LGMVERBOSE = Verbose or scanty output  
/// + LGMINITSTYLE = Old or new style, new style has a sequencs of mask files  
/// + LGMFLOW = Flow symbols  
///
///These enumerations are used in uniform manner with GetValue and SetValue 
///functions to query and change the values respectively denoted by the enumerations.
///
///If GetValue or SetValue fails to find value for variable *A value
///cannot be found for variable N* where N is an integer value for the enumeration.
///\note Enumeration values are prefixed with LGA, LGP etc.

///\brief Lignum  core model framework
namespace Lignum{
  ///Lignum Attributes double  
  ///
  ///These symbols are used to access (with GetValue, SetValue) the
  ///variables (either attributes or other variables) of TreeSegment,
  ///Bud, BrachingPoint, BroadLeaf in LIGNUM (in any compartment
  ///except Tree). As regards GetValue, it may be that the value
  ///returned is calculated on the basis of other variables.
  ///If you add a new symbol be sure to document it carefully.
  enum LGMAD {
    LGAA,           ///<  0   Segment base area based on R. Also BroadBeaf shape \e true area. \sa BroadLeaf::GetValue() TreeSegment::GetValue()													      
    LGAAbase,	    ///<  1   Area at the base of the \e tree														      
    LGAAf,	    ///<  2   Area of foliage																      
    LGAAfb,	    ///<  3   Foliage area, broad leaved (see ForestDescriptor in stl-voxelspace)										      
    LGAAfc,	    ///<  4   Foliage area, conifers (see ForestDescriptor in stl-voxelspace)										      
    LGAAh,	    ///<  5   Heartwood area																      
    LGAAhair,	    ///<  6   Root hair area																      
    LGAAhwbase,	    ///<  7   Heartwood area at the base															      
    LGAAs,	    ///<  8   Sapwood area																      
    LGAAs0,	    ///<  9   Original sapwood area															      
    LGAADbh,	    ///< 10   Area at D 1.3																      
    LGAAhwDbh,	    ///< 11   Heartwood area at D 1.3															      
    LGAAsDbh,	    ///< 12   Sapwood area at D 1.3															      
    LGAAsbase,	    ///< 13   Sapwood Area at the base															      
    LGAage,	    ///< 14   Age of an object																      
    LGAcbase,	    ///< 15   Crown base of a forest (see ForestDescriptor in stl-voxelspace)										      
    LGAcollision,   ///< 16   A bud can examine its growth sector if it collides with an obstacle										      
    LGADbase,	    ///< 17   Diameter at base (tree)															      
    LGADbaseHw,	    ///< 18   Diameter of heart wood at base (tree)													      
    LGADbh,	    ///< 19   Diameter at breast height (tree)														      
    LGADbhHw,	    ///< 20   Diameter of heart wood at breast height (tree)												      
    LGADcb,	    ///< 21   Diameter at crown base															      
    LGAdof,	    ///< 22   Degree of filling of leaf															      
    LGAdR,	    ///< 23   Change in radius (=difference of two growth rings)												      
    LGAH,	    ///< 24   Height of tree, also the Z coordinate at the segment base 											      
    LGAHcb,	    ///< 25   Height of crown base															      
    LGAHf,	    ///< 26   Height (thickness) of cylindrical layer of foliage in a segment, e.g. Hf = Lneedle*sin(needle_angle)          				      
    LGAHTop,	    ///< 27   Max height from ground of the tree, segment, etc.												      
    LGAip,	    ///< 28   Degree of interaction															      
    LGAiWf,	    ///< 29   New foliage in a tree															      
    LGAiWs,	    ///< 30   New sapwood in a tree															      
    LGAL,	    ///< 31   Length of segment																      
    LGALAIb,	    ///< 32   Leaf area index, broad leaved (see ForestDescriptor in stl-voxelspace)									      
    LGALAIc,	    ///< 33   Leaf area index, conifers (see ForestDescriptor in stl-voxelspace)										      
    LGAM,	    ///< 34   Rate of respiration (= amount of r. during the time step)											      
    LGAMaxD,	    ///< 35   Maximum diameter of the segments forking off and the segment above a branching point. Needed to calculate LGAvi  				      
    LGAomega,	    ///< 36   Gravelius order																      
    LGAP,	    ///< 37   Photosynthetic rate (= amount of p. during time step)											      
    LGAQabs,	    ///< 38   Amount of absorbed radiation														      
    LGAQin,	    ///< 39   Incoming radiant flux															      
    LGAR,	    ///< 40   Radius of segment (wood)															      
    LGARf,	    ///< 41   Radius of segment cylinder including also foliage (conifers)										      
    LGARh,	    ///< 42   Radius of heartwood																      
    LGARhair,	    ///< 43   Radius including root hair 															      
    LGARTop,	    ///< 44   Radius of segment at upper end														      
    LGASa,	    ///< 45   Surface area of the segment cylinder: 2*PI*R*L												      
    LGAsf,	    ///< 46   Specific leaf area (=leaf area/ leaf weight)												      
    LGAstarm,	    ///< 47   Star mean for a confiferous segment														      
    LGAstatus, 	    ///< 48   General counter to control e.g. bud burst. \sa Lignum::LGAstate
    LGAstate,	    ///< 49   Bud state can be dead, alive, dormant etc in LGMUnits.h. \sa LignumForest::LGAstatus
    LGAtauL,	    ///< 50   Transmission coefficient of leaf (in direction of the ray of light) 									      
    LGAtype,	    ///< 51   General type specifier, e.g. Bud:dominant, apical, lateral etc. The numerical values and their symbols of different types given in LGMUnits.h     
    LGAV,	    ///< 52   Segment volume based on R and L														      
    LGAVf,	    ///< 53   Volume occupied by the foliage in CfSegment 												      
    LGAVfrustum,    ///< 54   Volume of the segment frustum when LGAR > LGARTop												      
    LGAVh,	    ///< 55   Heartwood volume																      
    LGAVhair,	    ///< 56   Root hair volume																      
    LGAvi,	    ///< 57   Vigour index																      
    LGAVs,	    ///< 58   Sapwood volume																      
    LGAWf,	    ///< 59   Foliage mass (kg C)																      
    LGAWf0,	    ///< 60   Initial foliage mass (kg C)															      
    LGAWood,	    ///< 61   Mass of wood (=Wh+Ws)															      
    LGAWs, 	    ///< 62   Mass of sapwood (kg C)															      
    LGAWh,	    ///< 63   Mass of heartwood (kg C)															      
    LGAWhair,	    ///< 64   Mass of fine roots (root hair) (kg C)
    LGAWstem,	    ///< 65   Mass in the main axis (Ws+Wh)                                                                                                                     
    LGAT,            ///< 66   \attention Not used
  };

  /// \brief Lignum Parameters double
  ///   
  /// These symbols are used to access (with GetValue, SetValue) parameters
  /// in any Lignum::TreeCompartment of LIGNUM. 
  ///
  /// Keep the LGMPD enumeration in sync with MapLGMPD table constructor
  /// in TreeFriend.cc. MapLGMPD maps the names of  the parameters found
  /// in configuration files to the symbolic names in LGMPD.
  /// The variables MapLGMPD maps the names to are declared (and initialized) in Tree.h
  enum LGMPD {
    LGPaf,///< Needle mass - tree segment area (kgC/m^2)relationship
    LGPaleafmax,///< Maximum size of a leaf (m2)
    LGPapical, ///< Length of segment (new) forking off (lateral) = LGPapical * Len of not forking off
    LGPar, ///< Foliage - root relationship
    LGPdof,///< Degree of filling (proportion leaf surface fills of geometric shape - e.g. ellipsis - of the leaf).
    LGPLmin,///< Minimum length (m) allowed for a new segment
    LGPlr,///< Length - radius relationship of a tree segment
    LGPmf,///< Maintenance respiration rate of foliage
    LGPmr,///< Maintenance respiration rate of roots
    LGPms,///< Maintenance respiration rate of sapwood
    LGPna,///< Needle angle (radians)
    LGPnl,///< Needle length (na and nl define the cylinder of foliage in CfTreeSegment)
    LGPpr,///< Photosynthetic efficiency (=photos. rate = pr * intercepted rad.)
    LGPq,///< Segment shortening factor (obsolete with vigour index)
    LGPrhoW,///< Density of  wood in tree segment
    LGPrho_hair,///< Density of fine roots (root hair)
    LGPrho_root,///< Density root wood (sapwood)
    LGPsf,///< Specific leaf area (=leaf area/ leaf weight)
    LGPsr,///< Senescence rate of roots
    LGPss,///< Senescence rate of sapwood
    LGPtauL,///< Transmission coefficient (radiatiom) for leaf
    LGPxi, ///< Fraction of heartwood in newly created tree segments
    LGPyc, ///< Foliage mass (kgC) supported by 1 m^2 of sapwood
    LGPzbrentEpsilon,///< Accuracy in numerical computation to allocate P-M=G, i.e. root finding
    LGPlen_random,///< Parameter controlling random variation in lengths of new segments.
                  ///< Realization may differ with tree species.
    LGPe1, ///< Parameters in function that links height growth to that of diameter
    LGPe2  ///< See Sievanen R 1993 Scand. J. For. Res 8: 28-48.
  };//end enum LGMPD
  
  ///\brief Number of names in Lignum::LGMTAD enumerations.
  ///
  ///Lignum::LGMTADLENGTH will be used to intialize  the Lignum::TreeAttributes::v  vector in
  ///Lignum::Tree::ta holding  the attribute values.
  //\attention Set LGMTADLENGTH to the number of enumerations in Lignum::LGMTAD. 
  const int LGMTADLENGTH=8;

  ///\brief Lignum::TreeAttributes double names.
  ///
  ///\attention Set Lignum::LGMTADLENGTH to  number of names in Lignum::LGMTAD enumeration.
  enum LGMTAD {
    Treelambda,       ///< lambda s.t. P-M=G(lamda)
    Treelb,           ///< Longest branch \pre Needs update before valid
    TreeP,	      ///< Tree level photosynthesis									    
    TreeM,	      ///< Tree level respiration										    
    TreeWr,	      ///< Root mass											    
    TreeQinMax,	      ///< Max Qin of all segments in a tree								    
    TreeRefRadiation, ///< Variable that is used as reference radiation in calculations in tree (e.g. lentgth growth) 
    TreeId	      ///< Unique identifier (number) for the tree (Useful in LignumForest)                                       
  };		      

  /// LGMF: LIGNUM Functions. Usually used as LGMF(x)*Value. So to have no effect set constant function F(x) = 1.
  /// \note Not all have to be used in one model implementation.
  enum LGMF {
    LGMAL,    ///< Adjusted length For example for making branches below 0.002 to have Length 0 and branches				  
    LGMFM,    ///< Foliage mortality 						      
    LGMIP,    ///< Relative length of a new tree segment 			  
    LGMLONB,  ///< The effect of light to number of the buds. 		  
    LGMNB,    ///< Number of buds						  
    LGMVI,    ///< Function of vigour index				           
    LGMVIONB, ///< The effect of vigour index to the number of the buds. If no effect the value is always 1 of this function
    LGMGO     ///< The effect of Gravelius order in tree segment length    
  };
  ///Types of files used to initialize Tree \sa TreeMetaFileParser
  enum FILE_MODE {
    PARAMETER, ///< Retrieve parameters
    FUNCTION,  ///< Retrieve and install functions
    GRAPHICS,  ///< Visualization
    INITIAL    ///< InitialTree
  };
  ///If needed you may design verbose output for example
  ///when initializing trees 
  enum LGMVERBOSE {
      QUIET,  ///< No output
      VERBOSE ///< Verbose output
  };
  ///Firmameny initialization
  enum LGMINITSTYLE {
    OLD_INIT,///< One mask file allowed for Firmament
    NEW_INIT ///< Many mask files allowed for Firmament
  };

  ///\deprecated Used with experimental TreeSegmentWithFlow 
  enum LGMFLOW { fin, fout, Pr, Wm };

}//closing namespace Lignum


#endif
