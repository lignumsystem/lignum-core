#ifndef TREE_H
#define TREE_H
#include <algorithm>
#include <numeric>
#include <list>
#include <stdlib.h>
#include <iostream.h>
#include <stream.h>

#include <CString.h>
#include <ParametricCurve.h>
#include <Point.h>
#include <PositionVector.h>

using namespace cxxadt;

#include <Algorithms.h>
#include <TreeFunctor.h>
#include <LGMdecl.h>
#include <TreeMetaFileParser.h>
#include <RootSystem.h>
#include <Bud.h>
#include <DefaultBud.h>
#include <BranchingPoint.h>
#include <TreeSegment.h>
#include <HwTreeSegment.h>
#include <CfTreeSegment.h>
#include <Axis.h>
#include <ConnectionMatrix.h>
#include <Firmament.h>
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
  LGMdouble sr;            //Senescence rate of roots
  LGMdouble ss;            //Senescence rate of sapwood
  LGMdouble rho;           //Density of wood
  LGMdouble xi;            //Fraction of heartwood in new tree segments
};

class TreeAttributes{
public:
  TreeAttributes();
  double age;            //Age of the tree
  METER lb;              //Longest branch (as vertical projection from the main stem)
  KGC P;                 //Photosynthesis of the tree during the time step
  KGC M;                 //Respiration of the tree during the time step
  KGC Wr;                //Root mass
};


class TreeFunctions{
public:
  ParametricCurve nb;       //number of new buds
  ParametricCurve ip;       //relative length of a new tree segment 
  ParametricCurve fm;       //foliage mortality 
};

class TreeTransitVariables{
public:
  TreeTransitVariables();
  LGMdouble lambda;        //Variable to balance carbon balance equation
  LGMdouble g;             //Gravity
  LGMdouble eta;           //Dynamic viscosity of water
  LGMdouble k;             //Wood spesific conductivity or permeability
  LGMdouble rhow;          //Density of water
  LGMdouble Er;            //Elastic modulus of wood in radial direction
};

class TreeInitializationFiles{
public:
  void install(CString file) {treeFile = file;}

  CString treeFile;
};


template <class TS,class BUD = DefaultBud<TS> >
class Tree: public Lignum::TreeCompartment<TS,BUD>{
  friend Axis<TS,BUD>& GetAxis(Tree<TS,BUD>& t);
  friend LGMdouble GetProduction(const Tree<TS,BUD>& t);
  friend void InitializeTree(Tree<TS,BUD>& tree, const CString& meta_file);
  friend LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMAD name);
  friend LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMAD name, const LGMdouble value);
  friend LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMPD name);
  friend LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMPD  name, const LGMdouble value);
  friend LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMTD name);
  friend LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMTD name, const LGMdouble value);
  friend CString GetTreeInitializationFile(Tree<TS,BUD>& tree);
  friend Firmament& GetFirmament(Tree<TS,BUD>& tree);
public:
  Tree();
  Tree(const Point<METER>& p, const PositionVector& d);
  void UpdateWaterFlow(LGMdouble time, const ConnectionMatrix<TS,BUD> &cm);
private:
  LGMdouble CountFlow(TreeSegment<TS,BUD> &in, TreeSegment<TS,BUD> &out);
  TreeAttributes ta;
  TreeFunctions tf;
  TreeParameters tp;
  TreeTransitVariables ttp;
  TreeInitializationFiles tif;
  sky::Firmament f;

  Axis<TS,BUD> axis;
  RootSystem rs;
};

}//closing namespace Lignum

#include <TreeI.h>


#endif













