#ifndef TREE_H
#define TREE_H

class Axis;
class Bud;
class BranchingPoint;
class Bud;
class Tree;
class TreeCompartment;
class TreeSegment;

#include <list>

#include <stdlib.h>
#include <iostream.h>

#include <CString.h>
#include <ParametricCurve.h>
#include <Point.h>

#include <LGMSymbols.h>
#include <LGMUnits.h>

#include <TreeMetaFileParser.h>

#include <TreeCompartment.h>
#include <Axis.h>
#include <BranchingPoint.h>
#include <Bud.h>
#include <TreeSegment.h>
#include <RootSystem.h>

TP GetProduction(const Tree& t);

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
};

class Tree: public TreeCompartment{
friend TP GetProduction(const Tree& t);
friend void InitializeTree(Tree& tree, const CString& meta_file);
friend TP GetAttributeValue(const Tree& tree, const TAD name);
friend YEAR GetAttributeValue(const Tree& tree, const TAI name);
template <class T1,class T2>
friend T2 SetAttributeValue(Tree& tree, const T1 name, const T2 value);
friend TP GetParameterValue(const Tree& tree, const TPD name);
friend TP SetParameterValue(Tree& tree, const TPD  name, const TP value);
friend TP GetTransitVariableValue(const Tree& tree, const TTD name);
friend TP SetTransitVariableValue(Tree& tree, const TTD name, const TP value);
public:
  Tree();
  Tree(const Point<METER>& p, const PositionVector& d);
  virtual void Production(){axis.Production();}
  virtual TP GetProduction(){return axis.GetProduction();}
private:
  TreeAttributes ta;
  TreeFunctions tf;
  TreeParameters tp;
  TreeTransitVariables ttp;
  Axis axis;
  RootSystem rs;
};


#endif


