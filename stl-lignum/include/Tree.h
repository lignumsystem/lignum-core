#ifndef TREE_H
#define TREE_H
#include <algorithm>
#include <numeric>
#include <list>
#include <stdlib.h>
#include <iostream>
using namespace std;


#include <string>
#include <ParametricCurve.h>
#include <Point.h>
#include <PositionVector.h>

using namespace cxxadt;

#include <LGMdecl.h>
#include <Algorithms.h>
#include <TreeFunctor.h>
#include <TreeMetaFileParser.h>
#include <RootSystem.h>
#include <RootAlgorithms.h>
#include <Bud.h>
#include <DefaultBud.h>
#include <BranchingPoint.h>
#include <TreeSegment.h>
#include <HwTreeSegment.h>
#include <CfTreeSegment.h>
#include <CreateLeaves.h>
#include <Axis.h>
#include <ConnectionMatrix.h>
#include <FirmamentWithMask.h>
#include <TreeRadiation.h>
#include <TreeBookkeeping.h>
#include <TreeCharacteristics.h>

using namespace sky;


namespace Lignum{


  class TreeParameters{
  public:
    TreeParameters();
    LGMdouble af;            //Needle mass - tree segment area relationship
    LGMdouble ar;            //Foliage - root relationship
    LGMdouble lr;            //L/R for a new tree segment
    LGMdouble mf;            //Maintenance respiration rate of foliage
    LGMdouble mr;            //Maintenance respiration rate of roots
    LGMdouble ms;            //Maintenance respiration rate of sapwood
    LGMdouble na;            //needle angle (radian)
    LGMdouble nl;            //needle length
    LGMdouble pr;            //Propotion of bound solar radiation used in photosynthesis
    LGMdouble q;             //Tree segment shortening factor
    LGMdouble sf;            //Specific foliage area (=foliage area(total)/weight)
    LGMdouble sr;            //Senescence rate of roots
    LGMdouble ss;            //Senescence rate of sapwood
    LGMdouble rhoW;          //Density of wood
    LGMdouble rho_root;      //Density of root sapwood
    LGMdouble rho_hair;      //Density of root hair
    LGMdouble xi;            //Fraction of heartwood in new tree segments
    LGMdouble zbrentEpsilon; //Accuracy    for    finding   root    of
			     //P-M-dW(lambda), i.e. allocation.

    LGMdouble dof;    //Degree of filling (proportion leaf surface fills
                      // of geometric shape - e.g. ellipsis - of the leaf).
    LGMdouble tauL;   //Transmission   coeffient  (light)   for  leaf,
		      //should be about 0.06  for green leaf. NOTE: be
		      //careful  here, the attenuation  coefficient is
		      //the opposite (1-tauL)

    LGMdouble aleafmax;    //Maximum size of a leaf (m2)
    
    LGMdouble yc;     //Foliage mass supported by 1m2 of sapwood
  };
 
  //TreeAttributes  are  in a  (long)  vector  indexed by  enumeration
  //LGMTAD defined in LGMSymbols.h
  class TreeAttributes{
  public:
    TreeAttributes(int size = LGMTADLENGTH);
    vector<LGMdouble> v;
  };

  class TreeFunctions{
  public:
    ParametricCurve nb;   //number of new buds
    ParametricCurve ip;   //light relative length of a new tree segment 
    ParametricCurve fm;   //foliage mortality 
    ParametricCurve vi;   //vigour index function
    ParametricCurve al;   //adjusted  length. For  example  for making
    
//branches below 0.002  to have length 0 and
    //branches between 0.002 and 0.01 have length 0.002 (short
    //segments)...
    
    ParametricCurve LightOnNumBuds; // the  effect of light  to number
    // of  the buds. If  no effect the
    //  value  is  always  1  of  this
    // function
    
    ParametricCurve VigourOnNumBuds;// the  effect of vigour  index to
    // the  number of the  buds. If no
    // effect the value is always 1 of
    // this function
  };

  class TreeInitializationFiles{
  public:
    void install(string file) {treeFile = file;}

    string treeFile;
  };
  
  template <class TS,class BUD = DefaultBud<TS> >
    class Tree: public TreeCompartment<TS,BUD>{

      template <class TS1,class BUD1>

      friend class InitializeTree;
    
	  template <class TS1,class BUD1>
     friend LGMdouble GetValue(const Tree<TS1,BUD1>& tree, const LGMAD name);

      template <class TS1,class BUD1>
      friend Axis<TS1,BUD1>& GetAxis(Tree<TS1,BUD1>& t);

      template <class TS1,class BUD1>
      friend RootAxis<Tree<TS1,BUD1> >& GetRootAxis(Tree<TS1,BUD1>& t);

      template <class TS1,class BUD1>
      friend LGMdouble GetValue(const Tree<TS1,BUD1>& tree, const LGMTAD name);

      template <class TS1,class BUD1>
      friend LGMdouble SetValue(Tree<TS1,BUD1>& tree, const LGMTAD name, 
				const LGMdouble value);

      template <class TS1,class BUD1>
      friend LGMdouble GetValue(const Tree<TS1,BUD1>& tree, const LGMPD name);

      template <class TS1,class BUD1>
      friend LGMdouble SetValue(Tree<TS1,BUD1>& tree, const LGMPD  name, 
				const LGMdouble value);

      template <class TS1,class BUD1>
      friend string GetTreeInitializationFile(Tree<TS1,BUD1>& tree);
  
      template <class TS1,class BUD1>
      friend void SetFirmament(const Tree<TS1,BUD1>& tree, const FirmamentWithMask& f);

      template <class TS1,class BUD1>
      friend FirmamentWithMask& GetFirmament(Tree<TS1,BUD1>& tree);

      template <class TS1,class BUD1>
      friend const ParametricCurve& GetFunction(const Tree<TS1,BUD1>& tree, LGMF name);

      template <class TS1, class BUD1, class F>
      friend void EvaluateRadiationForTree(Tree<TS1,BUD1>& tree, const F& f);

      public:
      Tree();
      Tree(const Point& p, const PositionVector& d);
      Tree(const Point& p, const PositionVector& d, 
	   LGMdouble len, LGMdouble rad, int num_buds);

      void photosynthesis();
      void respiration();
      TreeFunctions tf;  //cvs update

	
    private:
      TreeAttributes ta;
      TreeParameters tp;
     
      TreeInitializationFiles tif;
      FirmamentWithMask f;
      Axis<TS,BUD> axis;
      RootAxis<Tree<TS,BUD> > root_axis;
    };

  //Tree with Firmament (FRMNT)
  template <class FRMNT, class TS, class BUD = DefaultBud<TS> > 
    class FTree: public Tree<TS,BUD>{
      public:
      FTree(const Point& p, const PositionVector& pv):Tree<TS,BUD>(p,pv){}
      private:
      FRMNT frmnt;
    };

}//closing namespace Lignum

#include <InitializeTree.h>
#include <TreeI.h>
#include <TreeMetabolismI.h>
#include <TreeRadiationI.h>

#endif

