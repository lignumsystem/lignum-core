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



namespace Lignum{

class TreeParameters{
public:
  TreeParameters();
  TP af;            //Needle mass - tree segment area relationship
  TP ar;            //Foliage - root relationship
  TP lr;            //L/R for a new tree segment
  TP mf;            //Maintenance respiration rate of foliage
  TP mr;            //Maintenance respiration rate of roots
  TP ms;            //Maintenance respiration rate of sapwood
  TP na;            //needle angle (radian)
  TP nl;            //needle length
  TP pr;            //Propotion of bound solar radiation used in photosynthesis
  TP q;             //Tree segment shortening factor
  TP sr;            //Senescence rate of roots
  TP ss;            //Senescence rate of sapwood
  TP rho;           //Density of wood
  TP xi;            //Fraction of heartwood in new tree segments
};

class TreeAttributes{
public:
  TreeAttributes();
  YEAR age;              //Age of the tree
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
  TP lambda;        //Variable to balance carbon balance equation
  TP g;             //Gravity
  TP eta;           //Dynamic viscosity of water
  TP k;             //Wood spesific conductivity or permeability
  TP rhow;          //Density of water
  TP Er;            //Elastic modulus of wood in radial direction
};

class TreeInitializationFiles{
public:
  void install(CString file) {treeFile = file;}

  CString treeFile;
};


template <class TS,class BUD = DefaultBud<TS> >
class Tree: public TreeCompartment<TS,BUD>{
  friend Axis<TS,BUD>& GetAxis(Tree<TS,BUD>& t);
  friend TP GetProduction(const Tree<TS,BUD>& t);
  friend void InitializeTree(Tree<TS,BUD>& tree, const CString& meta_file);
  friend TP GetValue(const Tree<TS,BUD>& tree, const TAD name);
  friend YEAR GetValue(const Tree<TS,BUD>& tree, const TAI name);
  friend TP SetValue(Tree<TS,BUD>& tree, const TAD name, const TP value);
  friend YEAR SetValue(Tree<TS,BUD>& tree, const TAI name, const YEAR value);
  friend TP GetValue(const Tree<TS,BUD>& tree, const TPD name);
  friend TP SetValue(Tree<TS,BUD>& tree, const TPD  name, const TP value);
  friend TP GetValue(const Tree<TS,BUD>& tree, const TTD name);
  friend TP SetValue(Tree<TS,BUD>& tree, const TTD name, const TP value);
  friend CString GetTreeInitializationFile(Tree<TS,BUD>& tree);
public:
  Tree();
  Tree(const Point<METER>& p, const PositionVector& d);
  void UpdateWaterFlow(TP time, const ConnectionMatrix<TS,BUD> &cm);
private:
  TP CountFlow(TreeSegment<TS,BUD> &in, TreeSegment<TS,BUD> &out);
  TreeAttributes ta;
  TreeFunctions tf;
  TreeParameters tp;
  TreeTransitVariables ttp;
  TreeInitializationFiles tif;

  Axis<TS,BUD> axis;
  RootSystem rs;
};

}//closing namespace Lignum

#include <TreeI.h>


#endif













