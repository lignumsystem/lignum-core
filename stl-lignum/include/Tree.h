
#ifndef TREE_H
#define TREE_H


#include <list>
#include <stdlib.h>
#include <iostream.h>
#include <CString.h>
#include <ParametricCurve.h>
#include <TreeMetaFileParser.h>
#include <RootSystem.h>
#include <Bud.h>
#include <BranchingPoint.h>
#include <TreeSegment.h>
#include <Axis.h>

template <class TS>
TP GetProduction(const Tree<TS>& t);


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


class ConnectionMatrix{
public:
  ConnectionMatrix(int);
  void AddConnection(long int,long int);
  bool setValue(int, int, long int);
  long int **pointer;
  void print();
  int size;
private:
  int GetRow(long int);
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



template <class TS>
class Tree: public TreeCompartment<TS>{
  friend Axis<TS>& GetAxis(Tree<TS>& t){return t.axis;}
  friend TP GetProduction(const Tree<TS>& t);
  friend void InitializeTree(Tree<TS>& tree, const CString& meta_file);
  friend TP GetTreeAttributeValue(const Tree<TS>& tree, const TAD name);
  
  friend YEAR GetTreeAttributeValue(const Tree<TS>& tree, const TAI name);
  template <class T1,class T2>
  friend T2 SetTreeAttributeValue(Tree<TS>& tree, const T1 name, const T2 value);
  friend TP GetTreeParameterValue(const Tree<TS>& tree, const TPD name);
  friend TP SetTreeParameterValue(Tree<TS>& tree, const TPD  name, const TP value);
  friend TP GetTreeTransitVariableValue(const Tree<TS>& tree, const TTD name);
  friend TP SetTreeTransitVariableValue(Tree<TS>& tree, const TTD name, const TP value);
public:
  Tree();
  Tree(const Point<METER>& p, const PositionVector& d);
  void UpdateWaterFlow(TP time);
private:
 
  TreeSegment<TS>* GetTreeSegment(Axis<TS> &ax, long int add);
  void BuiltConnectionMatrix();
  int CountTreeSegments(Axis<TS> &ax);
  void makeAxis(Axis<TS> &ax, TreeSegment<TS> &ts);
  TP CountFlow(TreeSegment<TS> &in, TreeSegment<TS> &out);
  TreeAttributes ta;
  TreeFunctions tf;
  TreeParameters tp;
  TreeTransitVariables ttp;
  ConnectionMatrix *cm;
  Axis<TS> axis;
  RootSystem rs;
};
#endif



